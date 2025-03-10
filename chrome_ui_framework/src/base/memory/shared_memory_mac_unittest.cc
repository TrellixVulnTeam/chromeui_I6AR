// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <servers/bootstrap.h>

#include "base/command_line.h"
#include "base/mac/mach_logging.h"
#include "base/mac/scoped_mach_port.h"
#include "base/memory/shared_memory.h"
#include "base/process/process_handle.h"
#include "base/rand_util.h"
#include "base/strings/stringprintf.h"
#include "base/sys_info.h"
#include "base/test/multiprocess_test.h"
#include "base/test/test_timeouts.h"
#include "testing/multiprocess_func_list.h"

namespace base {

namespace {

static const std::string g_service_switch_name = "service_name";

// Structs used to pass a mach port from client to server.
struct MachSendPortMessage {
  mach_msg_header_t header;
  mach_msg_body_t body;
  mach_msg_port_descriptor_t data;
};
struct MachReceivePortMessage {
  mach_msg_header_t header;
  mach_msg_body_t body;
  mach_msg_port_descriptor_t data;
  mach_msg_trailer_t trailer;
};

// Makes the current process into a Mach Server with the given |service_name|.
mach_port_t BecomeMachServer(const char* service_name) {
  mach_port_t port;
  kern_return_t kr = bootstrap_check_in(bootstrap_port, service_name, &port);
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "BecomeMachServer";
  return port;
}

// Returns the mach port for the Mach Server with the given |service_name|.
mach_port_t LookupServer(const char* service_name) {
  mach_port_t server_port;
  kern_return_t kr =
      bootstrap_look_up(bootstrap_port, service_name, &server_port);
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "LookupServer";
  return server_port;
}

mach_port_t MakeReceivingPort() {
  mach_port_t client_port;
  kern_return_t kr =
      mach_port_allocate(mach_task_self(),         // our task is acquiring
                         MACH_PORT_RIGHT_RECEIVE,  // a new receive right
                         &client_port);            // with this name
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "MakeReceivingPort";
  return client_port;
}

// Blocks until a mach message is sent to |server_port|. This mach message
// must contain a mach port. Returns that mach port.
mach_port_t ReceiveMachPort(mach_port_t port_to_listen_on) {
  MachReceivePortMessage recv_msg;
  mach_msg_header_t* recv_hdr = &(recv_msg.header);
  recv_hdr->msgh_local_port = port_to_listen_on;
  recv_hdr->msgh_size = sizeof(recv_msg);
  kern_return_t kr =
      mach_msg(recv_hdr,               // message buffer
               MACH_RCV_MSG,           // option indicating service
               0,                      // send size
               recv_hdr->msgh_size,    // size of header + body
               port_to_listen_on,      // receive name
               MACH_MSG_TIMEOUT_NONE,  // no timeout, wait forever
               MACH_PORT_NULL);        // no notification port
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "ReceiveMachPort";
  mach_port_t other_task_port = recv_msg.data.name;
  return other_task_port;
}

// Passes a copy of the send right of |port_to_send| to |receiving_port|.
void SendMachPort(mach_port_t receiving_port,
                  mach_port_t port_to_send,
                  int disposition) {
  MachSendPortMessage send_msg;
  mach_msg_header_t* send_hdr;
  send_hdr = &(send_msg.header);
  send_hdr->msgh_bits =
      MACH_MSGH_BITS(MACH_MSG_TYPE_COPY_SEND, 0) | MACH_MSGH_BITS_COMPLEX;
  send_hdr->msgh_size = sizeof(send_msg);
  send_hdr->msgh_remote_port = receiving_port;
  send_hdr->msgh_local_port = MACH_PORT_NULL;
  send_hdr->msgh_reserved = 0;
  send_hdr->msgh_id = 0;
  send_msg.body.msgh_descriptor_count = 1;
  send_msg.data.name = port_to_send;
  send_msg.data.disposition = disposition;
  send_msg.data.type = MACH_MSG_PORT_DESCRIPTOR;
  int kr = mach_msg(send_hdr,               // message buffer
                    MACH_SEND_MSG,          // option indicating send
                    send_hdr->msgh_size,    // size of header + body
                    0,                      // receive limit
                    MACH_PORT_NULL,         // receive name
                    MACH_MSG_TIMEOUT_NONE,  // no timeout, wait forever
                    MACH_PORT_NULL);        // no notification port
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "SendMachPort";
}

std::string CreateRandomServiceName() {
  return StringPrintf("SharedMemoryMacMultiProcessTest.%llu", RandUint64());
}

// Sets up the mach communication ports with the server. Returns a port to which
// the server will send mach objects.
mach_port_t CommonChildProcessSetUp() {
  CommandLine cmd_line = *CommandLine::ForCurrentProcess();
  std::string service_name =
      cmd_line.GetSwitchValueASCII(g_service_switch_name);
  mac::ScopedMachSendRight server_port(LookupServer(service_name.c_str()));
  mach_port_t client_port = MakeReceivingPort();

  // Send the port that this process is listening on to the server.
  SendMachPort(server_port, client_port, MACH_MSG_TYPE_MAKE_SEND);
  return client_port;
}

// The number of active names in the current task's port name space.
mach_msg_type_number_t GetActiveNameCount() {
  mach_port_name_array_t name_array;
  mach_msg_type_number_t names_count;
  mach_port_type_array_t type_array;
  mach_msg_type_number_t types_count;
  kern_return_t kr = mach_port_names(mach_task_self(), &name_array,
                                     &names_count, &type_array, &types_count);
  MACH_CHECK(kr == KERN_SUCCESS, kr) << "GetActiveNameCount";
  return names_count;
}

}  // namespace

class SharedMemoryMacMultiProcessTest : public MultiProcessTest {
 public:
  SharedMemoryMacMultiProcessTest() {}

  CommandLine MakeCmdLine(const std::string& procname) override {
    CommandLine command_line = MultiProcessTest::MakeCmdLine(procname);
    // Pass the service name to the child process.
    command_line.AppendSwitchASCII(g_service_switch_name, service_name_);
    return command_line;
  }

  void SetUpChild(const std::string& name) {
    // Make a random service name so that this test doesn't conflict with other
    // similar tests.
    service_name_ = CreateRandomServiceName();
    server_port_.reset(BecomeMachServer(service_name_.c_str()));
    child_process_ = SpawnChild(name);
    client_port_.reset(ReceiveMachPort(server_port_));
  }

  static const int s_memory_size = 99999;

 protected:
  std::string service_name_;

  // A port on which the main process listens for mach messages from the child
  // process.
  mac::ScopedMachReceiveRight server_port_;

  // A port on which the child process listens for mach messages from the main
  // process.
  mac::ScopedMachSendRight client_port_;

  base::Process child_process_;
  DISALLOW_COPY_AND_ASSIGN(SharedMemoryMacMultiProcessTest);
};

// Tests that content written to shared memory in the server process can be read
// by the child process.
TEST_F(SharedMemoryMacMultiProcessTest, MachBasedSharedMemory) {
  SetUpChild("MachBasedSharedMemoryClient");

  SharedMemoryHandle shm(s_memory_size);
  ASSERT_TRUE(shm.IsValid());
  SharedMemory shared_memory(shm, false);
  shared_memory.Map(s_memory_size);
  memset(shared_memory.memory(), 'a', s_memory_size);

  // Send the underlying memory object to the client process.
  SendMachPort(client_port_, shm.GetMemoryObject(), MACH_MSG_TYPE_COPY_SEND);
  int rv = -1;
  ASSERT_TRUE(child_process_.WaitForExitWithTimeout(
      TestTimeouts::action_timeout(), &rv));
  EXPECT_EQ(0, rv);
}

MULTIPROCESS_TEST_MAIN(MachBasedSharedMemoryClient) {
  mac::ScopedMachReceiveRight client_port(CommonChildProcessSetUp());
  // The next mach port should be for a memory object.
  mach_port_t memory_object = ReceiveMachPort(client_port);
  SharedMemoryHandle shm(memory_object,
                         SharedMemoryMacMultiProcessTest::s_memory_size,
                         GetCurrentProcId());
  SharedMemory shared_memory(shm, false);
  shared_memory.Map(SharedMemoryMacMultiProcessTest::s_memory_size);
  const char* start = static_cast<const char*>(shared_memory.memory());
  for (int i = 0; i < SharedMemoryMacMultiProcessTest::s_memory_size; ++i) {
    DCHECK_EQ(start[i], 'a');
  }
  return 0;
}

// Tests that mapping shared memory with an offset works correctly.
TEST_F(SharedMemoryMacMultiProcessTest, MachBasedSharedMemoryWithOffset) {
  SetUpChild("MachBasedSharedMemoryWithOffsetClient");

  SharedMemoryHandle shm(s_memory_size);
  ASSERT_TRUE(shm.IsValid());
  SharedMemory shared_memory(shm, false);
  shared_memory.Map(s_memory_size);

  size_t page_size = SysInfo::VMAllocationGranularity();
  char* start = static_cast<char*>(shared_memory.memory());
  memset(start, 'a', page_size);
  memset(start + page_size, 'b', page_size);
  memset(start + 2 * page_size, 'c', page_size);

  // Send the underlying memory object to the client process.
  SendMachPort(client_port_, shm.GetMemoryObject(), MACH_MSG_TYPE_COPY_SEND);
  int rv = -1;
  ASSERT_TRUE(child_process_.WaitForExitWithTimeout(
      TestTimeouts::action_timeout(), &rv));
  EXPECT_EQ(0, rv);
}

MULTIPROCESS_TEST_MAIN(MachBasedSharedMemoryWithOffsetClient) {
  mac::ScopedMachReceiveRight client_port(CommonChildProcessSetUp());
  // The next mach port should be for a memory object.
  mach_port_t memory_object = ReceiveMachPort(client_port);
  SharedMemoryHandle shm(memory_object,
                         SharedMemoryMacMultiProcessTest::s_memory_size,
                         GetCurrentProcId());
  SharedMemory shared_memory(shm, false);
  size_t page_size = SysInfo::VMAllocationGranularity();
  shared_memory.MapAt(page_size, 2 * page_size);
  const char* start = static_cast<const char*>(shared_memory.memory());
  for (size_t i = 0; i < page_size; ++i) {
    DCHECK_EQ(start[i], 'b');
  }
  for (size_t i = page_size; i < 2 * page_size; ++i) {
    DCHECK_EQ(start[i], 'c');
  }
  return 0;
}

// Tests that duplication and closing has the right effect on Mach reference
// counts.
TEST_F(SharedMemoryMacMultiProcessTest, MachDuplicateAndClose) {
  mach_msg_type_number_t active_name_count = GetActiveNameCount();

  // Making a new SharedMemoryHandle increments the name count.
  SharedMemoryHandle shm(s_memory_size);
  ASSERT_TRUE(shm.IsValid());
  EXPECT_EQ(active_name_count + 1, GetActiveNameCount());

  // Duplicating the SharedMemoryHandle increments the ref count, but doesn't
  // make a new name.
  shm.Duplicate();
  EXPECT_EQ(active_name_count + 1, GetActiveNameCount());

  // Closing the SharedMemoryHandle decrements the ref count. The first time has
  // no effect.
  shm.Close();
  EXPECT_EQ(active_name_count + 1, GetActiveNameCount());

  // Closing the SharedMemoryHandle decrements the ref count. The second time
  // destroys the port.
  shm.Close();
  EXPECT_EQ(active_name_count, GetActiveNameCount());
}

// Tests that passing a SharedMemoryHandle to a SharedMemory object also passes
// ownership, and that destroying the SharedMemory closes the SharedMemoryHandle
// as well.
TEST_F(SharedMemoryMacMultiProcessTest, MachSharedMemoryTakesOwnership) {
  mach_msg_type_number_t active_name_count = GetActiveNameCount();

  // Making a new SharedMemoryHandle increments the name count.
  SharedMemoryHandle shm(s_memory_size);
  ASSERT_TRUE(shm.IsValid());
  EXPECT_EQ(active_name_count + 1, GetActiveNameCount());

  // Name count doesn't change when mapping the memory.
  scoped_ptr<SharedMemory> shared_memory(new SharedMemory(shm, false));
  shared_memory->Map(s_memory_size);
  EXPECT_EQ(active_name_count + 1, GetActiveNameCount());

  // Destroying the SharedMemory object frees the resource.
  shared_memory.reset();
  EXPECT_EQ(active_name_count, GetActiveNameCount());
}

// Tests that the read-only flag works.
TEST_F(SharedMemoryMacMultiProcessTest, MachReadOnly) {
  SharedMemoryHandle shm(s_memory_size);
  ASSERT_TRUE(shm.IsValid());
  SharedMemory shared_memory(shm, false);
  shared_memory.Map(s_memory_size);
  memset(shared_memory.memory(), 'a', s_memory_size);

  SharedMemoryHandle shm2 = shm.Duplicate();
  ASSERT_TRUE(shm2.IsValid());
  SharedMemory shared_memory2(shm, true);
  shared_memory2.Map(s_memory_size);
  ASSERT_DEATH(memset(shared_memory2.memory(), 'b', s_memory_size), "");
}

}  //  namespace base
