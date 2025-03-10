// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is auto-generated from
// gpu/command_buffer/build_gles2_cmd_buffer.py
// It's formatted by clang-format using chromium coding style:
//    clang-format -i -style=chromium filename
// DO NOT EDIT!

#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_UTILS_IMPLEMENTATION_AUTOGEN_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_UTILS_IMPLEMENTATION_AUTOGEN_H_

static const GLES2Util::EnumToString enum_to_string_table[] = {
    {
        0x8D77, "GL_RGB16UI",
    },
    {
        0x8D76, "GL_RGBA16UI",
    },
    {
        0x9260, "GL_GCCSO_SHADER_BINARY_FJ",
    },
    {
        0x9009, "GL_TEXTURE_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x8D71, "GL_RGB32UI",
    },
    {
        0x8D70, "GL_RGBA32UI",
    },
    {
        0x8C76, "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH",
    },
    {
        0x8825, "GL_DRAW_BUFFER0_EXT",
    },
    {
        0x8D94, "GL_RED_INTEGER",
    },
    {
        0x0BC1, "GL_ALPHA_TEST_FUNC_QCOM",
    },
    {
        0x884C, "GL_TEXTURE_COMPARE_MODE_EXT",
    },
    {
        0x0BC2, "GL_ALPHA_TEST_REF_QCOM",
    },
    {
        0x884D, "GL_TEXTURE_COMPARE_FUNC_EXT",
    },
    {
        0x884E, "GL_COMPARE_REF_TO_TEXTURE_EXT",
    },
    {
        0x8E76, "GL_TESS_GEN_MODE_EXT",
    },
    {
        0x8E77, "GL_TESS_GEN_SPACING_EXT",
    },
    {
        0x000D, "GL_TRIANGLE_STRIP_ADJACENCY_EXT",
    },
    {
        0x000E, "GL_PATCHES_EXT",
    },
    {
        0x000B, "GL_LINE_STRIP_ADJACENCY_EXT",
    },
    {
        0x000C, "GL_TRIANGLES_ADJACENCY_EXT",
    },
    {
        0x000A, "GL_LINES_ADJACENCY_EXT",
    },
    {
        0x92CF, "GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT",
    },
    {
        0x93A1, "GL_BGRA8_EXT",
    },
    {
        0x813C, "GL_TEXTURE_BASE_LEVEL",
    },
    {
        0, "GL_FALSE",
    },
    {
        0x00400000, "GL_STENCIL_BUFFER_BIT6_QCOM",
    },
    {
        64, "GL_MAILBOX_SIZE_CHROMIUM",
    },
    {
        0x9500, "GL_PERFQUERY_GPA_EXTENDED_COUNTERS_INTEL",
    },
    {
        0x78F2, "GL_SCANOUT_CHROMIUM",
    },
    {
        0x9138, "GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG",
    },
    {
        0x8FC4, "GL_SHADER_BINARY_VIV",
    },
    {
        0x90A7, "GL_MITER_REVERT_CHROMIUM",
    },
    {
        0x9130, "GL_SGX_PROGRAM_BINARY_IMG",
    },
    {
        0x9133, "GL_RENDERBUFFER_SAMPLES_IMG",
    },
    {
        0x82E0, "GL_BUFFER_KHR",
    },
    {
        0x9135, "GL_MAX_SAMPLES_IMG",
    },
    {
        0x9134, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG",
    },
    {
        0x9137, "GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG",
    },
    {
        0x9136, "GL_TEXTURE_SAMPLES_IMG",
    },
    {
        0x8D88, "GL_RGBA16I",
    },
    {
        0x8D89, "GL_RGB16I",
    },
    {
        0x00000020, "GL_COLOR_BUFFER_BIT5_QCOM",
    },
    {
        0x0008, "GL_MAP_INVALIDATE_BUFFER_BIT_EXT",
    },
    {
        0x0BC0, "GL_ALPHA_TEST_QCOM",
    },
    {
        0x0006, "GL_TRIANGLE_FAN",
    },
    {
        0x0007, "GL_QUADS_EXT",
    },
    {
        0x0004, "GL_TRIANGLES",
    },
    {
        0x0005, "GL_TRIANGLE_STRIP",
    },
    {
        0x0002, "GL_LINE_LOOP",
    },
    {
        0x0003, "GL_LINE_STRIP",
    },
    {
        0x0000, "GL_POINTS",
    },
    {
        0x0001, "GL_LINES",
    },
    {
        0x8D7D, "GL_RGB8UI",
    },
    {
        0x93F0, "GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV2_IMG",
    },
    {
        0x93F1, "GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV2_IMG",
    },
    {
        0x0D04, "GL_PACK_SKIP_PIXELS",
    },
    {
        0x900E, "GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x900D, "GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT",
    },
    {
        0x8C7F, "GL_TRANSFORM_FEEDBACK_BUFFER_MODE",
    },
    {
        0x900F, "GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x900A, "GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x900C, "GL_SAMPLER_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x8213, "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE",
    },
    {
        0x88B9, "GL_WRITE_ONLY_OES",
    },
    {
        0x8211, "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT",
    },
    {
        0x8210, "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT",
    },
    {
        0x8741, "GL_PROGRAM_BINARY_LENGTH_OES",
    },
    {
        0x8740, "GL_Z400_BINARY_AMD",
    },
    {
        0x8215, "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE",
    },
    {
        0x8C4D, "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_NV",
    },
    {
        0x8192, "GL_GENERATE_MIPMAP_HINT",
    },
    {
        0x8E79, "GL_TESS_GEN_POINT_MODE_EXT",
    },
    {
        0x8A54, "GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT",
    },
    {
        0x8A55, "GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT",
    },
    {
        0x8A56, "GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT",
    },
    {
        0x8A57, "GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT",
    },
    {
        0x8A51, "GL_RGB_RAW_422_APPLE",
    },
    {
        0x87F9, "GL_3DC_X_AMD",
    },
    {
        0x8A53, "GL_SYNC_OBJECT_APPLE",
    },
    {
        0x78FB, "GL_RGB_YCBCR_422_CHROMIUM",
    },
    {
        0x8DF8, "GL_SHADER_BINARY_FORMATS",
    },
    {
        0x8DF9, "GL_NUM_SHADER_BINARY_FORMATS",
    },
    {
        0x826D, "GL_DEBUG_GROUP_STACK_DEPTH_KHR",
    },
    {
        0x8E75, "GL_TESS_CONTROL_OUTPUT_VERTICES_EXT",
    },
    {
        0x826B, "GL_DEBUG_SEVERITY_NOTIFICATION_KHR",
    },
    {
        0x826C, "GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR",
    },
    {
        0x8B59, "GL_BOOL_VEC4",
    },
    {
        0x826A, "GL_DEBUG_TYPE_POP_GROUP_KHR",
    },
    {
        0x8B57, "GL_BOOL_VEC2",
    },
    {
        0x8DF1, "GL_MEDIUM_FLOAT",
    },
    {
        0x8B55, "GL_INT_VEC4",
    },
    {
        0x8B54, "GL_INT_VEC3",
    },
    {
        0x8DF4, "GL_MEDIUM_INT",
    },
    {
        0x8DF5, "GL_HIGH_INT",
    },
    {
        0x8B51, "GL_FLOAT_VEC3",
    },
    {
        0x8B50, "GL_FLOAT_VEC2",
    },
    {
        0x806D, "GL_UNPACK_SKIP_IMAGES",
    },
    {
        0x806E, "GL_UNPACK_IMAGE_HEIGHT",
    },
    {
        0x806F, "GL_TEXTURE_3D_OES",
    },
    {
        0x92E7, "GL_IS_PER_PATCH_EXT",
    },
    {
        0x92E0, "GL_DEBUG_OUTPUT_KHR",
    },
    {
        0x806A, "GL_TEXTURE_BINDING_3D_OES",
    },
    {
        0x8D8E, "GL_RGBA8I",
    },
    {
        0x8CE3, "GL_COLOR_ATTACHMENT3_EXT",
    },
    {
        0x9274, "GL_COMPRESSED_RGB8_ETC2",
    },
    {
        0x1904, "GL_GREEN_NV",
    },
    {
        0x928D, "GL_DST_OUT_NV",
    },
    {
        0x8069, "GL_TEXTURE_BINDING_2D",
    },
    {
        0x8A2E, "GL_MAX_COMBINED_UNIFORM_BLOCKS",
    },
    {
        0x8F96, "GL_RGB8_SNORM",
    },
    {
        0x8260, "GL_UNDEFINED_VERTEX_EXT",
    },
    {
        0x8261, "GL_NO_RESET_NOTIFICATION_KHR",
    },
    {
        0x0D02, "GL_PACK_ROW_LENGTH",
    },
    {
        0x8DFA, "GL_SHADER_COMPILER",
    },
    {
        0x8DFB, "GL_MAX_VERTEX_UNIFORM_VECTORS",
    },
    {
        0x8DFC, "GL_MAX_VARYING_VECTORS",
    },
    {
        0x8B5C, "GL_FLOAT_MAT4",
    },
    {
        0x8B5B, "GL_FLOAT_MAT3",
    },
    {
        0x8268, "GL_DEBUG_TYPE_MARKER_KHR",
    },
    {
        0x8269, "GL_DEBUG_TYPE_PUSH_GROUP_KHR",
    },
    {
        0x1905, "GL_BLUE_NV",
    },
    {
        0x87FF, "GL_PROGRAM_BINARY_FORMATS_OES",
    },
    {
        0x87FE, "GL_NUM_PROGRAM_BINARY_FORMATS_OES",
    },
    {
        0x8A41, "GL_UNIFORM_BLOCK_NAME_LENGTH",
    },
    {
        0x2600, "GL_NEAREST",
    },
    {
        0x2601, "GL_LINEAR",
    },
    {
        0x8C03, "GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG",
    },
    {
        0x821B, "GL_MAJOR_VERSION",
    },
    {
        0x821A, "GL_DEPTH_STENCIL_ATTACHMENT",
    },
    {
        0x8A40, "GL_UNIFORM_BLOCK_DATA_SIZE",
    },
    {
        0x821D, "GL_NUM_EXTENSIONS",
    },
    {
        0x88BB, "GL_BUFFER_ACCESS_OES",
    },
    {
        0x88BC, "GL_BUFFER_MAPPED_OES",
    },
    {
        0x88BD, "GL_BUFFER_MAP_POINTER_OES",
    },
    {
        0x88BF, "GL_TIME_ELAPSED_EXT",
    },
    {
        0x8A46, "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER",
    },
    {
        0x6003, "GL_GET_ERROR_QUERY_CHROMIUM",
    },
    {
        0x8F94, "GL_R8_SNORM",
    },
    {
        0x0C10, "GL_SCISSOR_BOX",
    },
    {
        0x0C11, "GL_SCISSOR_TEST",
    },
    {
        0x1700, "GL_PATH_MODELVIEW_CHROMIUM",
    },
    {
        0x80000000, "GL_MULTISAMPLE_BUFFER_BIT7_QCOM",
    },
    {
        0x94F8, "GL_PERFQUERY_COUNTER_DATA_UINT32_INTEL",
    },
    {
        0x90a4, "GL_ROUND_CHROMIUM",
    },
    {
        0x8A48, "GL_TEXTURE_SRGB_DECODE_EXT",
    },
    {
        0x300E, "GL_CONTEXT_LOST",
    },
    {
        0x90a3, "GL_SQUARE_CHROMIUM",
    },
    {
        0x02000000, "GL_MULTISAMPLE_BUFFER_BIT1_QCOM",
    },
    {
        0x8C2F, "GL_ANY_SAMPLES_PASSED_EXT",
    },
    {
        0x8BD2, "GL_TEXTURE_WIDTH_QCOM",
    },
    {
        0x8C2D, "GL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT",
    },
    {
        0x8C2C, "GL_TEXTURE_BINDING_BUFFER_EXT",
    },
    {
        0x8C2B, "GL_MAX_TEXTURE_BUFFER_SIZE_EXT",
    },
    {
        0x8C2A, "GL_TEXTURE_BUFFER_EXT",
    },
    {
        0x8BD7, "GL_TEXTURE_TYPE_QCOM",
    },
    {
        0x8B8D, "GL_CURRENT_PROGRAM",
    },
    {
        0x8BD9, "GL_TEXTURE_NUM_LEVELS_QCOM",
    },
    {
        0x00200000, "GL_STENCIL_BUFFER_BIT5_QCOM",
    },
    {
        0x8D9F, "GL_INT_2_10_10_10_REV",
    },
    {
        0x8B8A, "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH",
    },
    {
        0x8B8B, "GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES",
    },
    {
        0x8B8C, "GL_SHADING_LANGUAGE_VERSION",
    },
    {
        0x8BDA, "GL_TEXTURE_TARGET_QCOM",
    },
    {
        0x8BDB, "GL_TEXTURE_OBJECT_VALID_QCOM",
    },
    {
        0x8BDC, "GL_STATE_RESTORE",
    },
    {
        0x8B88, "GL_SHADER_SOURCE_LENGTH",
    },
    {
        0x8B89, "GL_ACTIVE_ATTRIBUTES",
    },
    {
        0x93C9, "GL_COMPRESSED_RGBA_ASTC_6x6x6_OES",
    },
    {
        0x93C8, "GL_COMPRESSED_RGBA_ASTC_6x6x5_OES",
    },
    {
        0x8B84, "GL_INFO_LOG_LENGTH",
    },
    {
        0x8B85, "GL_ATTACHED_SHADERS",
    },
    {
        0x8B86, "GL_ACTIVE_UNIFORMS",
    },
    {
        0x8B87, "GL_ACTIVE_UNIFORM_MAX_LENGTH",
    },
    {
        0x8B80, "GL_DELETE_STATUS",
    },
    {
        0x8B81, "GL_COMPILE_STATUS",
    },
    {
        0x8B82, "GL_LINK_STATUS",
    },
    {
        0x8B83, "GL_VALIDATE_STATUS",
    },
    {
        0x9380, "GL_NUM_SAMPLE_COUNTS",
    },
    {
        0x8D48, "GL_STENCIL_INDEX8",
    },
    {
        0x8D46, "GL_STENCIL_INDEX1_OES",
    },
    {
        0x8D47, "GL_STENCIL_INDEX4_OES",
    },
    {
        0x8D44, "GL_RENDERBUFFER_INTERNAL_FORMAT",
    },
    {
        0x00000100, "GL_DEPTH_BUFFER_BIT",
    },
    {
        0x8D42, "GL_RENDERBUFFER_WIDTH",
    },
    {
        0x8D43, "GL_RENDERBUFFER_HEIGHT",
    },
    {
        0x8D40, "GL_FRAMEBUFFER",
    },
    {
        0x8D41, "GL_RENDERBUFFER",
    },
    {
        0x90B7, "GL_PATH_STENCIL_FUNC_CHROMIUM",
    },
    {
        0x8A3A, "GL_UNIFORM_BLOCK_INDEX",
    },
    {
        0x88B8, "GL_READ_ONLY",
    },
    {
        0x0BD0, "GL_DITHER",
    },
    {
        0x90B9, "GL_PATH_STENCIL_VALUE_MASK_CHROMIUM",
    },
    {
        0x90B8, "GL_PATH_STENCIL_REF_CHROMIUM",
    },
    {
        0x93D3, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR",
    },
    {
        0x1D00, "GL_FLAT_CHROMIUM",
    },
    {
        0x9144, "GL_MAX_DEBUG_LOGGED_MESSAGES_KHR",
    },
    {
        0x1801, "GL_DEPTH_EXT",
    },
    {
        0x1800, "GL_COLOR_EXT",
    },
    {
        0x1802, "GL_STENCIL_EXT",
    },
    {
        0x9288, "GL_SRC_OVER_NV",
    },
    {
        0x9120, "GL_BUFFER_MAP_LENGTH",
    },
    {
        0x0B21, "GL_LINE_WIDTH",
    },
    {
        0x9308, "GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT",
    },
    {
        0x81A5, "GL_DEPTH_COMPONENT16",
    },
    {
        0x81A6, "GL_DEPTH_COMPONENT24_OES",
    },
    {
        0x81A7, "GL_DEPTH_COMPONENT32_OES",
    },
    {
        0x88FD, "GL_VERTEX_ATTRIB_ARRAY_INTEGER",
    },
    {
        0x88FE, "GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE",
    },
    {
        0x88FF, "GL_MAX_ARRAY_TEXTURE_LAYERS",
    },
    {
        0x8B6A, "GL_FLOAT_MAT4x3_NV",
    },
    {
        0x93D0, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR",
    },
    {
        0x9143, "GL_MAX_DEBUG_MESSAGE_LENGTH_KHR",
    },
    {
        0x8DFD, "GL_MAX_FRAGMENT_UNIFORM_VECTORS",
    },
    {
        0x9145, "GL_DEBUG_LOGGED_MESSAGES_KHR",
    },
    {
        0x9146, "GL_DEBUG_SEVERITY_HIGH_KHR",
    },
    {
        0x9147, "GL_DEBUG_SEVERITY_MEDIUM_KHR",
    },
    {
        0x9148, "GL_DEBUG_SEVERITY_LOW_KHR",
    },
    {
        0x8F63, "GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT",
    },
    {
        0x8F60, "GL_MALI_SHADER_BINARY_ARM",
    },
    {
        0x8F61, "GL_MALI_PROGRAM_BINARY_ARM",
    },
    {
        0x8F66, "GL_FRAGMENT_SHADER_FRAMEBUFFER_FETCH_MRT_ARM",
    },
    {
        0x8F67, "GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT",
    },
    {
        0x8F64, "GL_SHADER_PIXEL_LOCAL_STORAGE_EXT",
    },
    {
        0x8F65, "GL_FETCH_PER_SAMPLE_ARM",
    },
    {
        0x92D3, "GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT",
    },
    {
        0x87EE, "GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD",
    },
    {
        0x822B, "GL_RG8_EXT",
    },
    {
        0x822F, "GL_RG16F_EXT",
    },
    {
        0x822D, "GL_R16F_EXT",
    },
    {
        0x822E, "GL_R32F_EXT",
    },
    {
        1, "GL_ES_VERSION_2_0",
    },
    {
        0x84F9, "GL_DEPTH_STENCIL_OES",
    },
    {
        0x82DB, "GL_TEXTURE_VIEW_MIN_LEVEL_EXT",
    },
    {
        0x8368, "GL_UNSIGNED_INT_2_10_10_10_REV_EXT",
    },
    {
        0x8819, "GL_LUMINANCE_ALPHA32F_EXT",
    },
    {
        0x8818, "GL_LUMINANCE32F_EXT",
    },
    {
        0x82DF, "GL_TEXTURE_IMMUTABLE_LEVELS",
    },
    {
        0x8363, "GL_UNSIGNED_SHORT_5_6_5",
    },
    {
        0x9051, "GL_IMAGE_BUFFER_EXT",
    },
    {
        0x84F2, "GL_ALL_COMPLETED_NV",
    },
    {
        0x8E5A, "GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT",
    },
    {
        0x84F4, "GL_FENCE_CONDITION_NV",
    },
    {
        0x8366, "GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT",
    },
    {
        0x8365, "GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT",
    },
    {
        0x84F7, "GL_COMMANDS_COMPLETED_CHROMIUM",
    },
    {
        0x8F9C, "GL_SIGNED_NORMALIZED",
    },
    {
        0x92D5, "GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT",
    },
    {
        0x881E, "GL_LUMINANCE16F_EXT",
    },
    {
        0x84FA, "GL_UNSIGNED_INT_24_8_OES",
    },
    {
        0x0A, "GL_QUADRATIC_CURVE_TO_CHROMIUM",
    },
    {
        0x92D4, "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT",
    },
    {
        0x881A, "GL_RGBA16F_EXT",
    },
    {
        0x84FE, "GL_TEXTURE_MAX_ANISOTROPY_EXT",
    },
    {
        0x0901, "GL_CCW",
    },
    {
        0x0900, "GL_CW",
    },
    {
        0x9317, "GL_MAX_FRAMEBUFFER_LAYERS_EXT",
    },
    {
        0x8229, "GL_R8_EXT",
    },
    {
        0x8230, "GL_RG32F_EXT",
    },
    {
        0x9312, "GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT",
    },
    {
        0x9283, "GL_DISJOINT_NV",
    },
    {
        0x8221, "GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED",
    },
    {
        0x8227, "GL_RG_EXT",
    },
    {
        0x8B66, "GL_FLOAT_MAT2x4_NV",
    },
    {
        0x8B67, "GL_FLOAT_MAT3x2_NV",
    },
    {
        0x8E1E, "GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x8B62, "GL_SAMPLER_2D_SHADOW_EXT",
    },
    {
        0x8B63, "GL_SAMPLER_2D_RECT_ARB",
    },
    {
        0x8B60, "GL_SAMPLER_CUBE",
    },
    {
        0x00001000, "GL_DEPTH_BUFFER_BIT4_QCOM",
    },
    {
        0x8B68, "GL_FLOAT_MAT3x4_NV",
    },
    {
        0x83F0, "GL_COMPRESSED_RGB_S3TC_DXT1_EXT",
    },
    {
        0x8D6A, "GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT",
    },
    {
        0x00000080, "GL_COLOR_BUFFER_BIT7_QCOM",
    },
    {
        0x88F0, "GL_DEPTH24_STENCIL8_OES",
    },
    {
        0x8E1F, "GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x80A0, "GL_SAMPLE_COVERAGE",
    },
    {
        0x0C, "GL_CUBIC_CURVE_TO_CHROMIUM",
    },
    {
        0x928F, "GL_DST_ATOP_NV",
    },
    {
        0x80A9, "GL_SAMPLES",
    },
    {
        0x80A8, "GL_SAMPLE_BUFFERS",
    },
    {
        0x0D55, "GL_ALPHA_BITS",
    },
    {
        0x0D54, "GL_BLUE_BITS",
    },
    {
        0x0D57, "GL_STENCIL_BITS",
    },
    {
        0x0D56, "GL_DEPTH_BITS",
    },
    {
        0x8CD5, "GL_FRAMEBUFFER_COMPLETE",
    },
    {
        0x0D50, "GL_SUBPIXEL_BITS",
    },
    {
        0x0D53, "GL_GREEN_BITS",
    },
    {
        0x0D52, "GL_RED_BITS",
    },
    {
        0x8037, "GL_POLYGON_OFFSET_FILL",
    },
    {
        0x928C, "GL_SRC_OUT_NV",
    },
    {
        0x8034, "GL_UNSIGNED_SHORT_5_5_5_1",
    },
    {
        0x8033, "GL_UNSIGNED_SHORT_4_4_4_4",
    },
    {
        0x928B, "GL_DST_IN_NV",
    },
    {
        0x0305, "GL_ONE_MINUS_DST_ALPHA",
    },
    {
        0x0304, "GL_DST_ALPHA",
    },
    {
        0x0307, "GL_ONE_MINUS_DST_COLOR",
    },
    {
        0x0306, "GL_DST_COLOR",
    },
    {
        0x0301, "GL_ONE_MINUS_SRC_COLOR",
    },
    {
        0x0300, "GL_SRC_COLOR",
    },
    {
        0x0303, "GL_ONE_MINUS_SRC_ALPHA",
    },
    {
        0x0302, "GL_SRC_ALPHA",
    },
    {
        0x8212, "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE",
    },
    {
        0x0308, "GL_SRC_ALPHA_SATURATE",
    },
    {
        0x2A00, "GL_POLYGON_OFFSET_UNITS",
    },
    {
        0xFFFFFFFF, "GL_ALL_SHADER_BITS_EXT",
    },
    {
        0x82DC, "GL_TEXTURE_VIEW_NUM_LEVELS_EXT",
    },
    {
        0x8C29, "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT",
    },
    {
        0x82DD, "GL_TEXTURE_VIEW_MIN_LAYER_EXT",
    },
    {
        0x00800000, "GL_STENCIL_BUFFER_BIT7_QCOM",
    },
    {
        0x82DE, "GL_TEXTURE_VIEW_NUM_LAYERS_EXT",
    },
    {
        0x00020000, "GL_STENCIL_BUFFER_BIT1_QCOM",
    },
    {
        0x8D00, "GL_DEPTH_ATTACHMENT",
    },
    {
        0x8FA0, "GL_PERFMON_GLOBAL_MODE_QCOM",
    },
    {
        0x8815, "GL_RGB32F_EXT",
    },
    {
        0x8A35, "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH",
    },
    {
        0x8814, "GL_RGBA32F_EXT",
    },
    {
        0x6006, "GL_ASYNC_PIXEL_PACK_COMPLETED_CHROMIUM",
    },
    {
        0x9277, "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2",
    },
    {
        0x6004, "GL_COMMANDS_ISSUED_CHROMIUM",
    },
    {
        0x813D, "GL_TEXTURE_MAX_LEVEL_APPLE",
    },
    {
        0x8816, "GL_ALPHA32F_EXT",
    },
    {
        0x813B, "GL_TEXTURE_MAX_LOD",
    },
    {
        0x8CDD, "GL_FRAMEBUFFER_UNSUPPORTED",
    },
    {
        0x8CDF, "GL_MAX_COLOR_ATTACHMENTS_EXT",
    },
    {
        0x90F3, "GL_CONTEXT_ROBUST_ACCESS_KHR",
    },
    {
        0x90F2, "GL_MAX_MULTIVIEW_BUFFERS_EXT",
    },
    {
        0x90F1, "GL_MULTIVIEW_EXT",
    },
    {
        0x90F0, "GL_COLOR_ATTACHMENT_EXT",
    },
    {
        0x803C, "GL_ALPHA8_OES",
    },
    {
        0x8904, "GL_MIN_PROGRAM_TEXEL_OFFSET",
    },
    {
        0x84F5, "GL_TEXTURE_RECTANGLE_ARB",
    },
    {
        0x882A, "GL_DRAW_BUFFER5_EXT",
    },
    {
        0x8E7F, "GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x80AA, "GL_SAMPLE_COVERAGE_VALUE",
    },
    {
        0x84F6, "GL_TEXTURE_BINDING_RECTANGLE_ARB",
    },
    {
        0x80AB, "GL_SAMPLE_COVERAGE_INVERT",
    },
    {
        0x8E7D, "GL_MAX_PATCH_VERTICES_EXT",
    },
    {
        0x9105, "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES",
    },
    {
        0x8E7E, "GL_MAX_TESS_GEN_LEVEL_EXT",
    },
    {
        0x9102, "GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES",
    },
    {
        0x8C40, "GL_SRGB_EXT",
    },
    {
        0x8E7B, "GL_FRACTIONAL_ODD_EXT",
    },
    {
        0x00000040, "GL_COLOR_BUFFER_BIT6_QCOM",
    },
    {
        0x882B, "GL_DRAW_BUFFER6_EXT",
    },
    {
        0x8E7C, "GL_FRACTIONAL_EVEN_EXT",
    },
    {
        0x8C8E, "GL_TRANSFORM_FEEDBACK_BUFFER",
    },
    {
        0x8C8D, "GL_SEPARATE_ATTRIBS",
    },
    {
        0x8C8F, "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING",
    },
    {
        0x8C8A, "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS",
    },
    {
        0x8C8C, "GL_INTERLEAVED_ATTRIBS",
    },
    {
        0x8C8B, "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS",
    },
    {
        0x8C17, "GL_UNSIGNED_NORMALIZED_EXT",
    },
    {
        0x8A3E, "GL_UNIFORM_IS_ROW_MAJOR",
    },
    {
        0x8E7A, "GL_ISOLINES_EXT",
    },
    {
        0x8F95, "GL_RG8_SNORM",
    },
    {
        0x8D99, "GL_RGBA_INTEGER",
    },
    {
        0x8D98, "GL_RGB_INTEGER",
    },
    {
        0x8A4A, "GL_SKIP_DECODE_EXT",
    },
    {
        0x8A4F, "GL_PROGRAM_PIPELINE_OBJECT_EXT",
    },
    {
        0x882C, "GL_DRAW_BUFFER7_EXT",
    },
    {
        0x0010, "GL_MAP_FLUSH_EXPLICIT_BIT_EXT",
    },
    {
        0x8918, "GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT",
    },
    {
        0x8919, "GL_SAMPLER_BINDING",
    },
    {
        0x92CD, "GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT",
    },
    {
        0x92CE, "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT",
    },
    {
        0x8C85, "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE",
    },
    {
        0x8D7C, "GL_RGBA8UI",
    },
    {
        0x6007, "GL_LATENCY_QUERY_CHROMIUM",
    },
    {
        0x8D83, "GL_RGB32I",
    },
    {
        0x8916, "GL_GEOMETRY_LINKED_VERTICES_OUT_EXT",
    },
    {
        0x8917, "GL_GEOMETRY_LINKED_INPUT_TYPE_EXT",
    },
    {
        0x881F, "GL_LUMINANCE_ALPHA16F_EXT",
    },
    {
        0x84FD, "GL_MAX_TEXTURE_LOD_BIAS",
    },
    {
        0x882D, "GL_DRAW_BUFFER8_EXT",
    },
    {
        0x8A43, "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES",
    },
    {
        0x8A42, "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS",
    },
    {
        0x8F37, "GL_COPY_WRITE_BUFFER_NV",
    },
    {
        0x8F36, "GL_COPY_READ_BUFFER_NV",
    },
    {
        0x84FF, "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT",
    },
    {
        0x8A3C, "GL_UNIFORM_ARRAY_STRIDE",
    },
    {
        0x8A44, "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER",
    },
    {
        0x0B74, "GL_DEPTH_FUNC",
    },
    {
        0x8A49, "GL_DECODE_EXT",
    },
    {
        0x881B, "GL_RGB16F_EXT",
    },
    {
        0x0B71, "GL_DEPTH_TEST",
    },
    {
        0x0B70, "GL_DEPTH_RANGE",
    },
    {
        0x0B73, "GL_DEPTH_CLEAR_VALUE",
    },
    {
        0x0B72, "GL_DEPTH_WRITEMASK",
    },
    {
        0x8BD5, "GL_TEXTURE_INTERNAL_FORMAT_QCOM",
    },
    {
        0x85BA, "GL_UNSIGNED_SHORT_8_8_APPLE",
    },
    {
        0x8C87, "GL_PRIMITIVES_GENERATED_EXT",
    },
    {
        0x8C80, "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS",
    },
    {
        0x8C83, "GL_TRANSFORM_FEEDBACK_VARYINGS",
    },
    {
        0x8D69, "GL_PRIMITIVE_RESTART_FIXED_INDEX",
    },
    {
        0x882E, "GL_DRAW_BUFFER9_EXT",
    },
    {
        0x8A32, "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x8A31, "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS",
    },
    {
        0x8C89, "GL_RASTERIZER_DISCARD",
    },
    {
        0x8C88, "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN",
    },
    {
        0x8C1A, "GL_TEXTURE_2D_ARRAY",
    },
    {
        0x910D, "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES",
    },
    {
        0x8E80, "GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x910B, "GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES",
    },
    {
        0x910C, "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES",
    },
    {
        0x94FA, "GL_PERFQUERY_COUNTER_DATA_FLOAT_INTEL",
    },
    {
        0x8073, "GL_MAX_3D_TEXTURE_SIZE_OES",
    },
    {
        0x8072, "GL_TEXTURE_WRAP_R_OES",
    },
    {
        0x9289, "GL_DST_OVER_NV",
    },
    {
        0x882F, "GL_DRAW_BUFFER10_EXT",
    },
    {
        0x8074, "GL_VERTEX_ARRAY_KHR",
    },
    {
        0x80E1, "GL_BGRA_EXT",
    },
    {
        0x908B, "GL_CONVEX_HULL_CHROMIUM",
    },
    {
        0x8ED7, "GL_COVERAGE_AUTOMATIC_NV",
    },
    {
        0x8ED6, "GL_COVERAGE_EDGE_FRAGMENTS_NV",
    },
    {
        0x8ED5, "GL_COVERAGE_ALL_FRAGMENTS_NV",
    },
    {
        0x8ED4, "GL_COVERAGE_SAMPLES_NV",
    },
    {
        0x8ED3, "GL_COVERAGE_BUFFERS_NV",
    },
    {
        0x8ED2, "GL_COVERAGE_ATTACHMENT_NV",
    },
    {
        0x8ED1, "GL_COVERAGE_COMPONENT4_NV",
    },
    {
        0x8ED0, "GL_COVERAGE_COMPONENT_NV",
    },
    {
        0x8217, "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE",
    },
    {
        0x8E89, "GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT",
    },
    {
        0x8216, "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE",
    },
    {
        0x8A36, "GL_ACTIVE_UNIFORM_BLOCKS",
    },
    {
        0x8A37, "GL_UNIFORM_TYPE",
    },
    {
        0x8A34, "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT",
    },
    {
        0x3006, "GL_CLIP_DISTANCE6_APPLE",
    },
    {
        0x800B, "GL_FUNC_REVERSE_SUBTRACT",
    },
    {
        0x8A33, "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS",
    },
    {
        0x00000400, "GL_STENCIL_BUFFER_BIT",
    },
    {
        0x800A, "GL_FUNC_SUBTRACT",
    },
    {
        0x8214, "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE",
    },
    {
        0x8A38, "GL_UNIFORM_SIZE",
    },
    {
        0x8A39, "GL_UNIFORM_NAME_LENGTH",
    },
    {
        0x8E2C, "GL_DEPTH_COMPONENT16_NONLINEAR_NV",
    },
    {
        0x889F, "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING",
    },
    {
        0x8219, "GL_FRAMEBUFFER_UNDEFINED_OES",
    },
    {
        0x8E23, "GL_TRANSFORM_FEEDBACK_PAUSED",
    },
    {
        0x8E22, "GL_TRANSFORM_FEEDBACK",
    },
    {
        0x8E25, "GL_TRANSFORM_FEEDBACK_BINDING",
    },
    {
        0x9054, "GL_IMAGE_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x8E28, "GL_TIMESTAMP_EXT",
    },
    {
        0x8006, "GL_FUNC_ADD",
    },
    {
        0x8007, "GL_MIN_EXT",
    },
    {
        0x8004, "GL_ONE_MINUS_CONSTANT_ALPHA",
    },
    {
        0x8005, "GL_BLEND_COLOR",
    },
    {
        0x8002, "GL_ONE_MINUS_CONSTANT_COLOR",
    },
    {
        0x8003, "GL_CONSTANT_ALPHA",
    },
    {
        0x8001, "GL_CONSTANT_COLOR",
    },
    {
        0x0204, "GL_GREATER",
    },
    {
        0x0205, "GL_NOTEQUAL",
    },
    {
        0x0206, "GL_GEQUAL",
    },
    {
        0x0207, "GL_ALWAYS",
    },
    {
        0x0200, "GL_NEVER",
    },
    {
        0x0201, "GL_LESS",
    },
    {
        0x0202, "GL_EQUAL",
    },
    {
        0x0203, "GL_LEQUAL",
    },
    {
        0x8BD6, "GL_TEXTURE_FORMAT_QCOM",
    },
    {
        0x8228, "GL_RG_INTEGER",
    },
    {
        0x2901, "GL_REPEAT",
    },
    {
        0x9067, "GL_UNSIGNED_INT_IMAGE_BUFFER_EXT",
    },
    {
        0x92A0, "GL_EXCLUSION_KHR",
    },
    {
        0x93D8, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR",
    },
    {
        0x93D9, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR",
    },
    {
        0x8FB2, "GL_GPU_OPTIMIZED_QCOM",
    },
    {
        0x190A, "GL_LUMINANCE_ALPHA",
    },
    {
        0x8FB0, "GL_BINNING_CONTROL_HINT_QCOM",
    },
    {
        0x905C, "GL_INT_IMAGE_BUFFER_EXT",
    },
    {
        0x1E00, "GL_KEEP",
    },
    {
        0x1E01, "GL_REPLACE",
    },
    {
        0x1E02, "GL_INCR",
    },
    {
        0x1E03, "GL_DECR",
    },
    {
        0x93D6, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR",
    },
    {
        0x93D7, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR",
    },
    {
        0x93D4, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR",
    },
    {
        0x93D5, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR",
    },
    {
        0x886D, "GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS_EXT",
    },
    {
        0x04, "GL_LINE_TO_CHROMIUM",
    },
    {
        0x0BE2, "GL_BLEND",
    },
    {
        0x84CB, "GL_TEXTURE11",
    },
    {
        0x8D55, "GL_RENDERBUFFER_STENCIL_SIZE",
    },
    {
        0x8D54, "GL_RENDERBUFFER_DEPTH_SIZE",
    },
    {
        0x8D57, "GL_MAX_SAMPLES_ANGLE",
    },
    {
        0x8D56, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_ANGLE",
    },
    {
        0x8D51, "GL_RENDERBUFFER_GREEN_SIZE",
    },
    {
        0x8D50, "GL_RENDERBUFFER_RED_SIZE",
    },
    {
        0x8D53, "GL_RENDERBUFFER_ALPHA_SIZE",
    },
    {
        0x8D52, "GL_RENDERBUFFER_BLUE_SIZE",
    },
    {
        0x92A6, "GL_VIVIDLIGHT_NV",
    },
    {
        0x8DCC, "GL_INT_SAMPLER_CUBE",
    },
    {
        0x8905, "GL_MAX_PROGRAM_TEXEL_OFFSET",
    },
    {
        0x00080000, "GL_STENCIL_BUFFER_BIT3_QCOM",
    },
    {
        0x92A7, "GL_LINEARLIGHT_NV",
    },
    {
        0x00, "GL_CLOSE_PATH_CHROMIUM",
    },
    {
        0x8DCF, "GL_INT_SAMPLER_2D_ARRAY",
    },
    {
        0x02, "GL_MOVE_TO_CHROMIUM",
    },
    {
        0x886A, "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED",
    },
    {
        0x8C41, "GL_SRGB8_NV",
    },
    {
        0x9079, "GL_PATH_JOIN_STYLE_CHROMIUM",
    },
    {
        0x0C01, "GL_DRAW_BUFFER_EXT",
    },
    {
        0x9075, "GL_PATH_STROKE_WIDTH_CHROMIUM",
    },
    {
        0x9076, "GL_PATH_END_CAPS_CHROMIUM",
    },
    {
        0x886C, "GL_MAX_TESS_CONTROL_INPUT_COMPONENTS_EXT",
    },
    {
        0x90CB, "GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT",
    },
    {
        0x8DCA, "GL_INT_SAMPLER_2D",
    },
    {
        0x93C7, "GL_COMPRESSED_RGBA_ASTC_6x5x5_OES",
    },
    {
        0x8B5F, "GL_SAMPLER_3D_OES",
    },
    {
        0x8B95, "GL_PALETTE8_RGB8_OES",
    },
    {
        0x9250, "GL_SHADER_BINARY_DMP",
    },
    {
        0x9251, "GL_SMAPHS30_PROGRAM_BINARY_DMP",
    },
    {
        0x9252, "GL_SMAPHS_PROGRAM_BINARY_DMP",
    },
    {
        0x9253, "GL_DMP_PROGRAM_BINARY_DMP",
    },
    {
        0x8DC8, "GL_UNSIGNED_INT_VEC4",
    },
    {
        0x3000, "GL_CLIP_DISTANCE0_APPLE",
    },
    {
        0x8C92, "GL_ATC_RGB_AMD",
    },
    {
        0x8DC1, "GL_SAMPLER_2D_ARRAY",
    },
    {
        0x9154, "GL_VERTEX_ARRAY_OBJECT_EXT",
    },
    {
        0x9153, "GL_QUERY_OBJECT_EXT",
    },
    {
        0x8864, "GL_QUERY_COUNTER_BITS_EXT",
    },
    {
        0x9151, "GL_BUFFER_OBJECT_EXT",
    },
    {
        0x8C93, "GL_ATC_RGBA_EXPLICIT_ALPHA_AMD",
    },
    {
        0x00000002, "GL_CONTEXT_FLAG_DEBUG_BIT_KHR",
    },
    {
        0x8A3F, "GL_UNIFORM_BLOCK_BINDING",
    },
    {
        0x00000000, "GL_PERFQUERY_SINGLE_CONTEXT_INTEL",
    },
    {
        0x00000001, "GL_SYNC_FLUSH_COMMANDS_BIT_APPLE",
    },
    {
        0x9248, "GL_OVERLAY_TRANSFORM_ROTATE_90_CHROMIUM",
    },
    {
        0x00000004, "GL_GEOMETRY_SHADER_BIT_EXT",
    },
    {
        0x1702, "GL_TEXTURE",
    },
    {
        0x3003, "GL_CLIP_DISTANCE3_APPLE",
    },
    {
        0x00000008, "GL_TESS_CONTROL_SHADER_BIT_EXT",
    },
    {
        0x8B58, "GL_BOOL_VEC3",
    },
    {
        0x8A3D, "GL_UNIFORM_MATRIX_STRIDE",
    },
    {
        0x8828, "GL_DRAW_BUFFER3_EXT",
    },
    {
        0x8DF0, "GL_LOW_FLOAT",
    },
    {
        0x1906, "GL_ALPHA",
    },
    {
        0x1907, "GL_RGB",
    },
    {
        0x8FBB, "GL_GPU_DISJOINT_EXT",
    },
    {
        0x1901, "GL_STENCIL_INDEX_OES",
    },
    {
        0x1902, "GL_DEPTH_COMPONENT",
    },
    {
        0x8B56, "GL_BOOL",
    },
    {
        0x93DB, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR",
    },
    {
        0x8B9B, "GL_IMPLEMENTATION_COLOR_READ_FORMAT",
    },
    {
        0x8B9A, "GL_IMPLEMENTATION_COLOR_READ_TYPE",
    },
    {
        0x93DA, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR",
    },
    {
        0x1908, "GL_RGBA",
    },
    {
        0x8DF2, "GL_HIGH_FLOAT",
    },
    {
        0x93DD, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR",
    },
    {
        0x8827, "GL_DRAW_BUFFER2_EXT",
    },
    {
        0x9243, "GL_UNPACK_COLORSPACE_CONVERSION_CHROMIUM",
    },
    {
        0x8DF3, "GL_LOW_INT",
    },
    {
        0x82E8, "GL_MAX_LABEL_LENGTH_KHR",
    },
    {
        0x82E6, "GL_SAMPLER_KHR",
    },
    {
        0x0C02, "GL_READ_BUFFER_EXT",
    },
    {
        0x82E3, "GL_QUERY_KHR",
    },
    {
        0x82E2, "GL_PROGRAM_KHR",
    },
    {
        0x82E1, "GL_SHADER_KHR",
    },
    {
        0x8B52, "GL_FLOAT_VEC4",
    },
    {
        0x8239, "GL_RG16I",
    },
    {
        0x8238, "GL_RG8UI",
    },
    {
        0x8DF6, "GL_UNSIGNED_INT_10_10_10_2_OES",
    },
    {
        0x8A30, "GL_MAX_UNIFORM_BLOCK_SIZE",
    },
    {
        0x9273, "GL_COMPRESSED_SIGNED_RG11_EAC",
    },
    {
        0x8231, "GL_R8I",
    },
    {
        0x8866, "GL_QUERY_RESULT_EXT",
    },
    {
        0x8233, "GL_R16I",
    },
    {
        0x8DF7, "GL_INT_10_10_10_2_OES",
    },
    {
        0x8235, "GL_R32I",
    },
    {
        0x8234, "GL_R16UI",
    },
    {
        0x8237, "GL_RG8I",
    },
    {
        0x8236, "GL_R32UI",
    },
    {
        0x8B69, "GL_FLOAT_MAT4x2_NV",
    },
    {
        0x812D, "GL_CLAMP_TO_BORDER_EXT",
    },
    {
        0x812F, "GL_CLAMP_TO_EDGE",
    },
    {
        0x92A4, "GL_LINEARDODGE_NV",
    },
    {
        0x8DD8, "GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT",
    },
    {
        0x8DD9, "GL_GEOMETRY_SHADER_EXT",
    },
    {
        0x86A3, "GL_COMPRESSED_TEXTURE_FORMATS",
    },
    {
        0x8DD4, "GL_UNSIGNED_INT_SAMPLER_CUBE",
    },
    {
        0x9244, "GL_BIND_GENERATES_RESOURCE_CHROMIUM",
    },
    {
        0x8DD2, "GL_UNSIGNED_INT_SAMPLER_2D",
    },
    {
        0x8DD3, "GL_UNSIGNED_INT_SAMPLER_3D",
    },
    {
        0x8DD0, "GL_INT_SAMPLER_BUFFER_EXT",
    },
    {
        0x86A2, "GL_NUM_COMPRESSED_TEXTURE_FORMATS",
    },
    {
        0x0CF3, "GL_UNPACK_SKIP_ROWS_EXT",
    },
    {
        0x0CF2, "GL_UNPACK_ROW_LENGTH_EXT",
    },
    {
        0x140C, "GL_FIXED",
    },
    {
        0x140B, "GL_HALF_FLOAT",
    },
    {
        0x8008, "GL_MAX_EXT",
    },
    {
        0x0CF5, "GL_UNPACK_ALIGNMENT",
    },
    {
        0x8867, "GL_QUERY_RESULT_AVAILABLE_EXT",
    },
    {
        0x8D82, "GL_RGBA32I",
    },
    {
        0x8009, "GL_BLEND_EQUATION",
    },
    {
        0x911F, "GL_BUFFER_ACCESS_FLAGS",
    },
    {
        0x1401, "GL_UNSIGNED_BYTE",
    },
    {
        0x1400, "GL_BYTE",
    },
    {
        0x1403, "GL_UNSIGNED_SHORT",
    },
    {
        0x1402, "GL_SHORT",
    },
    {
        0x1405, "GL_UNSIGNED_INT",
    },
    {
        0x1404, "GL_INT",
    },
    {
        0x1406, "GL_FLOAT",
    },
    {
        0x8C1D, "GL_TEXTURE_BINDING_2D_ARRAY",
    },
    {
        0x8DDF, "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT",
    },
    {
        0x8043, "GL_LUMINANCE4_ALPHA4_OES",
    },
    {
        0x8040, "GL_LUMINANCE8_OES",
    },
    {
        0x8045, "GL_LUMINANCE8_ALPHA8_OES",
    },
    {
        0x8CD1, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME",
    },
    {
        0x00040000, "GL_STENCIL_BUFFER_BIT2_QCOM",
    },
    {
        0x8CD0, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE",
    },
    {
        0x823A, "GL_RG16UI",
    },
    {
        0x8CE4, "GL_COLOR_ATTACHMENT4_EXT",
    },
    {
        0x823B, "GL_RG32I",
    },
    {
        0x8CD3, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE",
    },
    {
        0x846E, "GL_ALIASED_LINE_WIDTH_RANGE",
    },
    {
        0x0B90, "GL_STENCIL_TEST",
    },
    {
        0x8CD2, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL",
    },
    {
        0x881C, "GL_ALPHA16F_EXT",
    },
    {
        0x928E, "GL_SRC_ATOP_NV",
    },
    {
        0x8CD4, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES",
    },
    {
        0x9113, "GL_SYNC_CONDITION_APPLE",
    },
    {
        0x8CD7, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT",
    },
    {
        0x08000000, "GL_MULTISAMPLE_BUFFER_BIT3_QCOM",
    },
    {
        0x93A4, "GL_PACK_REVERSE_ROW_ORDER_ANGLE",
    },
    {
        0x8038, "GL_POLYGON_OFFSET_FACTOR",
    },
    {
        0x94F9, "GL_PERFQUERY_COUNTER_DATA_UINT64_INTEL",
    },
    {
        0x851A, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z",
    },
    {
        0x851C, "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    },
    {
        0x8CD9, "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS",
    },
    {
        24, "GL_SYNC_TOKEN_SIZE_CHROMIUM",
    },
    {
        0x84CC, "GL_TEXTURE12",
    },
    {
        0x0BA2, "GL_VIEWPORT",
    },
    {
        0x84CA, "GL_TEXTURE10",
    },
    {
        0x78F1, "GL_MAP_CHROMIUM",
    },
    {
        0x84CF, "GL_TEXTURE15",
    },
    {
        0x84CE, "GL_TEXTURE14",
    },
    {
        0x84CD, "GL_TEXTURE13",
    },
    {
        0x83F9, "GL_PERFQUERY_DONOT_FLUSH_INTEL",
    },
    {
        0x9115, "GL_SYNC_FLAGS_APPLE",
    },
    {
        0x9286, "GL_SRC_NV",
    },
    {
        0x83F3, "GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE",
    },
    {
        0x83F2, "GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE",
    },
    {
        0x83F1, "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT",
    },
    {
        0x9114, "GL_SYNC_STATUS_APPLE",
    },
    {
        0x8C0A, "GL_SGX_BINARY_IMG",
    },
    {
        0x93BB, "GL_COMPRESSED_RGBA_ASTC_10x10_KHR",
    },
    {
        0x911C, "GL_CONDITION_SATISFIED_APPLE",
    },
    {
        0x911B, "GL_TIMEOUT_EXPIRED_APPLE",
    },
    {
        0x911A, "GL_ALREADY_SIGNALED_APPLE",
    },
    {
        0x9284, "GL_CONJOINT_NV",
    },
    {
        0x9124, "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT",
    },
    {
        0x911D, "GL_WAIT_FAILED_APPLE",
    },
    {
        0x929A, "GL_COLORBURN_KHR",
    },
    {
        0x929B, "GL_HARDLIGHT_KHR",
    },
    {
        0x929C, "GL_SOFTLIGHT_KHR",
    },
    {
        0x846D, "GL_ALIASED_POINT_SIZE_RANGE",
    },
    {
        0x929E, "GL_DIFFERENCE_KHR",
    },
    {
        0x929F, "GL_MINUS_NV",
    },
    {
        0x9282, "GL_UNCORRELATED_NV",
    },
    {
        0x9298, "GL_LIGHTEN_KHR",
    },
    {
        0x9299, "GL_COLORDODGE_KHR",
    },
    {
        0x9111, "GL_MAX_SERVER_WAIT_TIMEOUT_APPLE",
    },
    {
        0x93A6, "GL_PROGRAM_BINARY_ANGLE",
    },
    {
        0x9117, "GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE",
    },
    {
        0x93A0, "GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE",
    },
    {
        0x93A3, "GL_FRAMEBUFFER_ATTACHMENT_ANGLE",
    },
    {
        0x93A2, "GL_TEXTURE_USAGE_ANGLE",
    },
    {
        0x8802, "GL_STENCIL_BACK_PASS_DEPTH_FAIL",
    },
    {
        0x9119, "GL_SIGNALED_APPLE",
    },
    {
        0x9118, "GL_UNSIGNALED_APPLE",
    },
    {
        0x9294, "GL_MULTIPLY_KHR",
    },
    {
        0x9295, "GL_SCREEN_KHR",
    },
    {
        0x9296, "GL_OVERLAY_KHR",
    },
    {
        0x9297, "GL_DARKEN_KHR",
    },
    {
        0x0020, "GL_MAP_UNSYNCHRONIZED_BIT_EXT",
    },
    {
        0x8E78, "GL_TESS_GEN_VERTEX_ORDER_EXT",
    },
    {
        0x8C01, "GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG",
    },
    {
        0x8C00, "GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG",
    },
    {
        0x8A52, "GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT",
    },
    {
        0x8C02, "GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG",
    },
    {
        0x84C9, "GL_TEXTURE9",
    },
    {
        0x84C8, "GL_TEXTURE8",
    },
    {
        0x8869, "GL_MAX_VERTEX_ATTRIBS",
    },
    {
        0x84C3, "GL_TEXTURE3",
    },
    {
        0x84C2, "GL_TEXTURE2",
    },
    {
        0x84C1, "GL_TEXTURE1",
    },
    {
        0x84C0, "GL_TEXTURE0",
    },
    {
        0x84C7, "GL_TEXTURE7",
    },
    {
        0x84C6, "GL_TEXTURE6",
    },
    {
        0x84C5, "GL_TEXTURE5",
    },
    {
        0x8803, "GL_STENCIL_BACK_PASS_DEPTH_PASS",
    },
    {
        0x928A, "GL_SRC_IN_NV",
    },
    {
        0x8518, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y",
    },
    {
        0x8519, "GL_TEXTURE_CUBE_MAP_POSITIVE_Z",
    },
    {
        0x8514, "GL_TEXTURE_BINDING_CUBE_MAP",
    },
    {
        0x8515, "GL_TEXTURE_CUBE_MAP_POSITIVE_X",
    },
    {
        0x8516, "GL_TEXTURE_CUBE_MAP_NEGATIVE_X",
    },
    {
        0x8517, "GL_TEXTURE_CUBE_MAP_POSITIVE_Y",
    },
    {
        0x8218, "GL_FRAMEBUFFER_DEFAULT",
    },
    {
        0x8513, "GL_TEXTURE_CUBE_MAP",
    },
    {
        0x8626, "GL_CURRENT_VERTEX_ATTRIB",
    },
    {
        0x92B1, "GL_PLUS_CLAMPED_NV",
    },
    {
        0x92B0, "GL_HSL_LUMINOSITY_KHR",
    },
    {
        0x92B3, "GL_MINUS_CLAMPED_NV",
    },
    {
        0x92B2, "GL_PLUS_CLAMPED_ALPHA_NV",
    },
    {
        0x8765, "GL_BUFFER_USAGE",
    },
    {
        0x8764, "GL_BUFFER_SIZE",
    },
    {
        0x8B99, "GL_PALETTE8_RGB5_A1_OES",
    },
    {
        0x0503, "GL_STACK_OVERFLOW_KHR",
    },
    {
        0x0502, "GL_INVALID_OPERATION",
    },
    {
        0x0501, "GL_INVALID_VALUE",
    },
    {
        0x0500, "GL_INVALID_ENUM",
    },
    {
        0x0507, "GL_CONTEXT_LOST_KHR",
    },
    {
        0x0506, "GL_INVALID_FRAMEBUFFER_OPERATION",
    },
    {
        0x0505, "GL_OUT_OF_MEMORY",
    },
    {
        0x0504, "GL_STACK_UNDERFLOW_KHR",
    },
    {
        0x0CF4, "GL_UNPACK_SKIP_PIXELS_EXT",
    },
    {
        0x0B44, "GL_CULL_FACE",
    },
    {
        0x8B5E, "GL_SAMPLER_2D",
    },
    {
        0x0B46, "GL_FRONT_FACE",
    },
    {
        0x8FB3, "GL_RENDER_DIRECT_TO_FRAMEBUFFER_QCOM",
    },
    {
        0x824A, "GL_DEBUG_SOURCE_APPLICATION_KHR",
    },
    {
        0x824B, "GL_DEBUG_SOURCE_OTHER_KHR",
    },
    {
        0x824C, "GL_DEBUG_TYPE_ERROR_KHR",
    },
    {
        0x824D, "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR",
    },
    {
        0x824E, "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR",
    },
    {
        0x824F, "GL_DEBUG_TYPE_PORTABILITY_KHR",
    },
    {
        0x8DD7, "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY",
    },
    {
        0x8B31, "GL_VERTEX_SHADER",
    },
    {
        0x8B30, "GL_FRAGMENT_SHADER",
    },
    {
        0x8FB1, "GL_CPU_OPTIMIZED_QCOM",
    },
    {
        0x93D2, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR",
    },
    {
        0x82FB, "GL_CONTEXT_RELEASE_BEHAVIOR_KHR",
    },
    {
        0x8B5A, "GL_FLOAT_MAT2",
    },
    {
        0x84D8, "GL_TEXTURE24",
    },
    {
        0x84D9, "GL_TEXTURE25",
    },
    {
        0x84D6, "GL_TEXTURE22",
    },
    {
        0x84D7, "GL_TEXTURE23",
    },
    {
        0x84D4, "GL_TEXTURE20",
    },
    {
        0x0D05, "GL_PACK_ALIGNMENT",
    },
    {
        0x84D2, "GL_TEXTURE18",
    },
    {
        0x84D3, "GL_TEXTURE19",
    },
    {
        0x84D0, "GL_TEXTURE16",
    },
    {
        0x84D1, "GL_TEXTURE17",
    },
    {
        0x93D1, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR",
    },
    {
        0x84DF, "GL_TEXTURE31",
    },
    {
        0x8B97, "GL_PALETTE8_R5_G6_B5_OES",
    },
    {
        0x84DD, "GL_TEXTURE29",
    },
    {
        0x84DE, "GL_TEXTURE30",
    },
    {
        0x84DB, "GL_TEXTURE27",
    },
    {
        0x84DC, "GL_TEXTURE28",
    },
    {
        0x84DA, "GL_TEXTURE26",
    },
    {
        0x8242, "GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR",
    },
    {
        0x8243, "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR",
    },
    {
        0x8244, "GL_DEBUG_CALLBACK_FUNCTION_KHR",
    },
    {
        0x8245, "GL_DEBUG_CALLBACK_USER_PARAM_KHR",
    },
    {
        0x8246, "GL_DEBUG_SOURCE_API_KHR",
    },
    {
        0x8247, "GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR",
    },
    {
        0x8248, "GL_DEBUG_SOURCE_SHADER_COMPILER_KHR",
    },
    {
        0x8249, "GL_DEBUG_SOURCE_THIRD_PARTY_KHR",
    },
    {
        0x8B94, "GL_PALETTE4_RGB5_A1_OES",
    },
    {
        0x94F4, "GL_PERFQUERY_COUNTER_RAW_INTEL",
    },
    {
        0x823C, "GL_RG32UI",
    },
    {
        0x8A29, "GL_UNIFORM_BUFFER_START",
    },
    {
        0x8A28, "GL_UNIFORM_BUFFER_BINDING",
    },
    {
        0x92BE, "GL_PRIMITIVE_BOUNDING_BOX_EXT",
    },
    {
        0x8645, "GL_VERTEX_ATTRIB_ARRAY_POINTER",
    },
    {
        0x8865, "GL_CURRENT_QUERY_EXT",
    },
    {
        0x8E5B, "GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_OES",
    },
    {
        0x8E5C, "GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_OES",
    },
    {
        0x8E5D, "GL_FRAGMENT_INTERPOLATION_OFFSET_BITS_OES",
    },
    {
        0x906A, "GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x906F, "GL_RGB10_A2UI",
    },
    {
        0x8E72, "GL_PATCH_VERTICES_EXT",
    },
    {
        0x8BD3, "GL_TEXTURE_HEIGHT_QCOM",
    },
    {
        0x87FA, "GL_3DC_XY_AMD",
    },
    {
        0x84C4, "GL_TEXTURE4",
    },
    {
        0x1A, "GL_CONIC_CURVE_TO_CHROMIUM",
    },
    {
        0x821C, "GL_MINOR_VERSION",
    },
    {
        0x8E8A, "GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT",
    },
    {
        0x85B5, "GL_VERTEX_ARRAY_BINDING_OES",
    },
    {
        0x8253, "GL_GUILTY_CONTEXT_RESET_KHR",
    },
    {
        0x8D6B, "GL_MAX_ELEMENT_INDEX",
    },
    {
        0x8D6C, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT",
    },
    {
        0x92A1, "GL_CONTRAST_NV",
    },
    {
        0x8252, "GL_LOSE_CONTEXT_ON_RESET_KHR",
    },
    {
        0x8C4C, "GL_COMPRESSED_SRGB_S3TC_DXT1_NV",
    },
    {
        0x8C4E, "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_NV",
    },
    {
        0x8251, "GL_DEBUG_TYPE_OTHER_KHR",
    },
    {
        0x8C4F, "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_NV",
    },
    {
        0x9309, "GL_REFERENCED_BY_GEOMETRY_SHADER_EXT",
    },
    {
        0x93E9, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x6_OES",
    },
    {
        0x93E8, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6x5_OES",
    },
    {
        0x8C43, "GL_SRGB8_ALPHA8_EXT",
    },
    {
        0x8C42, "GL_SRGB_ALPHA_EXT",
    },
    {
        0x8C45, "GL_SLUMINANCE8_ALPHA8_NV",
    },
    {
        0x8C44, "GL_SLUMINANCE_ALPHA_NV",
    },
    {
        0x8C47, "GL_SLUMINANCE8_NV",
    },
    {
        0x8C46, "GL_SLUMINANCE_NV",
    },
    {
        0x93E1, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x3x3_OES",
    },
    {
        0x93E0, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_3x3x3_OES",
    },
    {
        0x93E3, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x4_OES",
    },
    {
        0x93E2, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4x3_OES",
    },
    {
        0x93E5, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x4_OES",
    },
    {
        0x93E4, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4x4_OES",
    },
    {
        0x93E7, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5x5_OES",
    },
    {
        0x93E6, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5x5_OES",
    },
    {
        0x8D68, "GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES",
    },
    {
        0x8E82, "GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT",
    },
    {
        0x8E81, "GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT",
    },
    {
        0x85BB, "GL_UNSIGNED_SHORT_8_8_REV_APPLE",
    },
    {
        0x8E87, "GL_TESS_EVALUATION_SHADER_EXT",
    },
    {
        0x8E86, "GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT",
    },
    {
        0x8E85, "GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_EXT",
    },
    {
        0x8E84, "GL_MAX_TESS_PATCH_COMPONENTS_EXT",
    },
    {
        0x8D61, "GL_HALF_FLOAT_OES",
    },
    {
        0x8D62, "GL_RGB565",
    },
    {
        0x8E88, "GL_TESS_CONTROL_SHADER_EXT",
    },
    {
        0x8D64, "GL_ETC1_RGB8_OES",
    },
    {
        0x8D65, "GL_TEXTURE_EXTERNAL_OES",
    },
    {
        0x8D66, "GL_SAMPLER_EXTERNAL_OES",
    },
    {
        0x8D67, "GL_TEXTURE_BINDING_EXTERNAL_OES",
    },
    {
        0x10000000, "GL_MULTISAMPLE_BUFFER_BIT4_QCOM",
    },
    {
        0x04000000, "GL_MULTISAMPLE_BUFFER_BIT2_QCOM",
    },
    {
        0x90D7, "GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT",
    },
    {
        0x90D9, "GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT",
    },
    {
        0x90D8, "GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT",
    },
    {
        0x8CEE, "GL_COLOR_ATTACHMENT14_EXT",
    },
    {
        0x8DC7, "GL_UNSIGNED_INT_VEC3",
    },
    {
        0x90A6, "GL_BEVEL_CHROMIUM",
    },
    {
        0x1701, "GL_PATH_PROJECTION_CHROMIUM",
    },
    {
        0x2800, "GL_TEXTURE_MAG_FILTER",
    },
    {
        0x2801, "GL_TEXTURE_MIN_FILTER",
    },
    {
        0x2802, "GL_TEXTURE_WRAP_S",
    },
    {
        0x2803, "GL_TEXTURE_WRAP_T",
    },
    {
        0x8DCB, "GL_INT_SAMPLER_3D",
    },
    {
        0x3007, "GL_CLIP_DISTANCE7_APPLE",
    },
    {
        0x2703, "GL_LINEAR_MIPMAP_LINEAR",
    },
    {
        0x3005, "GL_CLIP_DISTANCE5_APPLE",
    },
    {
        0x3004, "GL_CLIP_DISTANCE4_APPLE",
    },
    {
        0x8B98, "GL_PALETTE8_RGBA4_OES",
    },
    {
        0x3002, "GL_CLIP_DISTANCE2_APPLE",
    },
    {
        0x3001, "GL_CLIP_DISTANCE1_APPLE",
    },
    {
        0x2702, "GL_NEAREST_MIPMAP_LINEAR",
    },
    {
        0x1F03, "GL_EXTENSIONS",
    },
    {
        0x1F02, "GL_VERSION",
    },
    {
        0x1F01, "GL_RENDERER",
    },
    {
        0x1F00, "GL_VENDOR",
    },
    {
        0x9247, "GL_OVERLAY_TRANSFORM_FLIP_VERTICAL_CHROMIUM",
    },
    {
        0x2701, "GL_LINEAR_MIPMAP_NEAREST",
    },
    {
        0x9245, "GL_OVERLAY_TRANSFORM_NONE_CHROMIUM",
    },
    {
        0x92B4, "GL_INVERT_OVG_NV",
    },
    {
        0x9249, "GL_OVERLAY_TRANSFORM_ROTATE_180_CHROMIUM",
    },
    {
        0x0B94, "GL_STENCIL_FAIL",
    },
    {
        0x8B4A, "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    },
    {
        0x8B4B, "GL_MAX_VARYING_COMPONENTS",
    },
    {
        0x8B4C, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    },
    {
        0x8B4D, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    },
    {
        0x8B4F, "GL_SHADER_TYPE",
    },
    {
        0x9122, "GL_MAX_VERTEX_OUTPUT_COMPONENTS",
    },
    {
        0x9123, "GL_MAX_GEOMETRY_INPUT_COMPONENTS_EXT",
    },
    {
        0x83FB, "GL_PERFQUERY_WAIT_INTEL",
    },
    {
        0x9121, "GL_BUFFER_MAP_OFFSET",
    },
    {
        0x9089, "GL_COUNT_DOWN_CHROMIUM",
    },
    {
        0x9088, "GL_COUNT_UP_CHROMIUM",
    },
    {
        0x00004000, "GL_COLOR_BUFFER_BIT",
    },
    {
        0x9125, "GL_MAX_FRAGMENT_INPUT_COMPONENTS",
    },
    {
        0x00000010, "GL_TESS_EVALUATION_SHADER_BIT_EXT",
    },
    {
        0x8834, "GL_DRAW_BUFFER15_EXT",
    },
    {
        0x8833, "GL_DRAW_BUFFER14_EXT",
    },
    {
        0x8832, "GL_DRAW_BUFFER13_EXT",
    },
    {
        0x8831, "GL_DRAW_BUFFER12_EXT",
    },
    {
        0x8830, "GL_DRAW_BUFFER11_EXT",
    },
    {
        0x8DC5, "GL_SAMPLER_CUBE_SHADOW_NV",
    },
    {
        0x94FF, "GL_PERFQUERY_COUNTER_DESC_LENGTH_MAX_INTEL",
    },
    {
        0x94FE, "GL_PERFQUERY_COUNTER_NAME_LENGTH_MAX_INTEL",
    },
    {
        0x94FD, "GL_PERFQUERY_QUERY_NAME_LENGTH_MAX_INTEL",
    },
    {
        0x94FC, "GL_PERFQUERY_COUNTER_DATA_BOOL32_INTEL",
    },
    {
        0x94FB, "GL_PERFQUERY_COUNTER_DATA_DOUBLE_INTEL",
    },
    {
        0x93B8, "GL_COMPRESSED_RGBA_ASTC_10x5_KHR",
    },
    {
        0x8B65, "GL_FLOAT_MAT2x3_NV",
    },
    {
        0x00010000, "GL_STENCIL_BUFFER_BIT0_QCOM",
    },
    {
        0x83FA, "GL_PERFQUERY_FLUSH_INTEL",
    },
    {
        0x0D03, "GL_PACK_SKIP_ROWS",
    },
    {
        0x84F3, "GL_FENCE_STATUS_NV",
    },
    {
        0x908D, "GL_BOUNDING_BOX_CHROMIUM",
    },
    {
        0x88E6, "GL_STATIC_COPY",
    },
    {
        0x0B93, "GL_STENCIL_VALUE_MASK",
    },
    {
        0x0B92, "GL_STENCIL_FUNC",
    },
    {
        0x0B91, "GL_STENCIL_CLEAR_VALUE",
    },
    {
        0x883D, "GL_BLEND_EQUATION_ALPHA",
    },
    {
        0x0B97, "GL_STENCIL_REF",
    },
    {
        0x0B96, "GL_STENCIL_PASS_DEPTH_PASS",
    },
    {
        0x0B95, "GL_STENCIL_PASS_DEPTH_FAIL",
    },
    {
        0x2700, "GL_NEAREST_MIPMAP_NEAREST",
    },
    {
        0x94F5, "GL_PERFQUERY_COUNTER_TIMESTAMP_INTEL",
    },
    {
        0x0B98, "GL_STENCIL_WRITEMASK",
    },
    {
        0x94F3, "GL_PERFQUERY_COUNTER_THROUGHPUT_INTEL",
    },
    {
        0x94F2, "GL_PERFQUERY_COUNTER_DURATION_RAW_INTEL",
    },
    {
        0x94F1, "GL_PERFQUERY_COUNTER_DURATION_NORM_INTEL",
    },
    {
        0x94F0, "GL_PERFQUERY_COUNTER_EVENT_INTEL",
    },
    {
        0x8B40, "GL_PROGRAM_OBJECT_EXT",
    },
    {
        0x1004, "GL_TEXTURE_BORDER_COLOR_EXT",
    },
    {
        0x8A2D, "GL_MAX_FRAGMENT_UNIFORM_BLOCKS",
    },
    {
        0x8B48, "GL_SHADER_OBJECT_EXT",
    },
    {
        0x8B49, "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    },
    {
        0x813A, "GL_TEXTURE_MIN_LOD",
    },
    {
        0x8DE1, "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT",
    },
    {
        0x8DE0, "GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT",
    },
    {
        0x924C, "GL_MOUSE_POSITION_CHROMIUM",
    },
    {
        0x924B, "GL_SUBSCRIBED_VALUES_BUFFER_CHROMIUM",
    },
    {
        0x924A, "GL_OVERLAY_TRANSFORM_ROTATE_270_CHROMIUM",
    },
    {
        0x8A2F, "GL_MAX_UNIFORM_BUFFER_BINDINGS",
    },
    {
        0x20000000, "GL_MULTISAMPLE_BUFFER_BIT5_QCOM",
    },
    {
        0x8A2A, "GL_UNIFORM_BUFFER_SIZE",
    },
    {
        0x0BA7, "GL_PATH_PROJECTION_MATRIX_CHROMIUM",
    },
    {
        0x0DE1, "GL_TEXTURE_2D",
    },
    {
        0x8A2C, "GL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT",
    },
    {
        0x80C9, "GL_BLEND_SRC_RGB",
    },
    {
        0x80C8, "GL_BLEND_DST_RGB",
    },
    {
        0x912F, "GL_TEXTURE_IMMUTABLE_FORMAT_EXT",
    },
    {
        0x8A2B, "GL_MAX_VERTEX_UNIFORM_BLOCKS",
    },
    {
        0x9246, "GL_OVERLAY_TRANSFORM_FLIP_HORIZONTAL_CHROMIUM",
    },
    {
        0x88EC, "GL_PIXEL_UNPACK_BUFFER",
    },
    {
        0x8D8F, "GL_RGB8I",
    },
    {
        0x8059, "GL_RGB10_A2_EXT",
    },
    {
        0x8058, "GL_RGBA8_OES",
    },
    {
        0x8B93, "GL_PALETTE4_RGBA4_OES",
    },
    {
        0x88EB, "GL_PIXEL_PACK_BUFFER",
    },
    {
        0x8E83, "GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT",
    },
    {
        0x8051, "GL_RGB8_OES",
    },
    {
        0x8CAD, "GL_DEPTH32F_STENCIL8",
    },
    {
        0x8052, "GL_RGB10_EXT",
    },
    {
        0x8CAB, "GL_RENDERBUFFER_SAMPLES_ANGLE",
    },
    {
        0x8CAC, "GL_DEPTH_COMPONENT32F",
    },
    {
        0x8057, "GL_RGB5_A1",
    },
    {
        0x8056, "GL_RGBA4",
    },
    {
        0x8232, "GL_R8UI",
    },
    {
        0x90A4, "GL_ROUND_CHROMIUM",
    },
    {
        0x150A, "GL_INVERT",
    },
    {
        0x01000000, "GL_MULTISAMPLE_BUFFER_BIT0_QCOM",
    },
    {
        0x78ED, "GL_PIXEL_PACK_TRANSFER_BUFFER_CHROMIUM",
    },
    {
        0x78EE, "GL_PIXEL_PACK_TRANSFER_BUFFER_BINDING_CHROMIUM",
    },
    {
        0x78EF, "GL_PIXEL_UNPACK_TRANSFER_BUFFER_BINDING_CHROMIUM",
    },
    {
        0x0B45, "GL_CULL_FACE_MODE",
    },
    {
        0x8B92, "GL_PALETTE4_R5_G6_B5_OES",
    },
    {
        0x00100000, "GL_STENCIL_BUFFER_BIT4_QCOM",
    },
    {
        0x8E4E, "GL_LAST_VERTEX_CONVENTION_EXT",
    },
    {
        0x8E4D, "GL_FIRST_VERTEX_CONVENTION_EXT",
    },
    {
        0x8E24, "GL_TRANSFORM_FEEDBACK_ACTIVE",
    },
    {
        0x8E45, "GL_TEXTURE_SWIZZLE_A",
    },
    {
        0x8E44, "GL_TEXTURE_SWIZZLE_B",
    },
    {
        0x8E43, "GL_TEXTURE_SWIZZLE_G",
    },
    {
        0x8E42, "GL_TEXTURE_SWIZZLE_R",
    },
    {
        0x8D20, "GL_STENCIL_ATTACHMENT",
    },
    {
        0x8B91, "GL_PALETTE4_RGBA8_OES",
    },
    {
        0x00000200, "GL_DEPTH_BUFFER_BIT1_QCOM",
    },
    {
        0x78EC, "GL_PIXEL_UNPACK_TRANSFER_BUFFER_CHROMIUM",
    },
    {
        0x78FA, "GL_RGB_YUV_420_CHROMIUM",
    },
    {
        0x00008000, "GL_COVERAGE_BUFFER_BIT_NV",
    },
    {
        0x1506, "GL_XOR_NV",
    },
    {
        0x8CA8, "GL_READ_FRAMEBUFFER_ANGLE",
    },
    {
        0x8CA9, "GL_DRAW_FRAMEBUFFER_ANGLE",
    },
    {
        0x8CA6, "GL_FRAMEBUFFER_BINDING",
    },
    {
        0x8CA7, "GL_RENDERBUFFER_BINDING",
    },
    {
        0x8CA4, "GL_STENCIL_BACK_VALUE_MASK",
    },
    {
        0x8CA5, "GL_STENCIL_BACK_WRITEMASK",
    },
    {
        0x8B90, "GL_PALETTE4_RGB8_OES",
    },
    {
        0x8CA3, "GL_STENCIL_BACK_REF",
    },
    {
        0x80E8, "GL_MAX_ELEMENTS_VERTICES",
    },
    {
        0x80CB, "GL_BLEND_SRC_ALPHA",
    },
    {
        0x80CA, "GL_BLEND_DST_ALPHA",
    },
    {
        0x8CE7, "GL_COLOR_ATTACHMENT7_EXT",
    },
    {
        0x93B0, "GL_COMPRESSED_RGBA_ASTC_4x4_KHR",
    },
    {
        0x93B1, "GL_COMPRESSED_RGBA_ASTC_5x4_KHR",
    },
    {
        0x93B2, "GL_COMPRESSED_RGBA_ASTC_5x5_KHR",
    },
    {
        0x93B3, "GL_COMPRESSED_RGBA_ASTC_6x5_KHR",
    },
    {
        0x93B4, "GL_COMPRESSED_RGBA_ASTC_6x6_KHR",
    },
    {
        0x93B5, "GL_COMPRESSED_RGBA_ASTC_8x5_KHR",
    },
    {
        0x93B6, "GL_COMPRESSED_RGBA_ASTC_8x6_KHR",
    },
    {
        0x93B7, "GL_COMPRESSED_RGBA_ASTC_8x8_KHR",
    },
    {
        0x8CD6, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT",
    },
    {
        0x93B9, "GL_COMPRESSED_RGBA_ASTC_10x6_KHR",
    },
    {
        0x80E9, "GL_MAX_ELEMENTS_INDICES",
    },
    {
        0x8CE5, "GL_COLOR_ATTACHMENT5_EXT",
    },
    {
        0x8C84, "GL_TRANSFORM_FEEDBACK_BUFFER_START",
    },
    {
        0x0BA6, "GL_PATH_MODELVIEW_MATRIX_CHROMIUM",
    },
    {
        0x8DC2, "GL_SAMPLER_BUFFER_EXT",
    },
    {
        0x8C36, "GL_SAMPLE_SHADING_OES",
    },
    {
        0x8C37, "GL_MIN_SAMPLE_SHADING_VALUE_OES",
    },
    {
        0x8F97, "GL_RGBA8_SNORM",
    },
    {
        0x8CE9, "GL_COLOR_ATTACHMENT9_EXT",
    },
    {
        0x8DAD, "GL_FLOAT_32_UNSIGNED_INT_24_8_REV",
    },
    {
        0x8B96, "GL_PALETTE8_RGBA8_OES",
    },
    {
        0x8872, "GL_MAX_TEXTURE_IMAGE_UNITS",
    },
    {
        0x8DC6, "GL_UNSIGNED_INT_VEC2",
    },
    {
        0x8508, "GL_DECR_WRAP",
    },
    {
        0x92AD, "GL_HSL_HUE_KHR",
    },
    {
        0x92AE, "GL_HSL_SATURATION_KHR",
    },
    {
        0x92AF, "GL_HSL_COLOR_KHR",
    },
    {
        0x8BD4, "GL_TEXTURE_DEPTH_QCOM",
    },
    {
        0x8DC4, "GL_SAMPLER_2D_ARRAY_SHADOW_NV",
    },
    {
        0x8507, "GL_INCR_WRAP",
    },
    {
        0x82FC, "GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_KHR",
    },
    {
        0x8895, "GL_ELEMENT_ARRAY_BUFFER_BINDING",
    },
    {
        0x8894, "GL_ARRAY_BUFFER_BINDING",
    },
    {
        0x92A3, "GL_INVERT_RGB_NV",
    },
    {
        0x905F, "GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT",
    },
    {
        0x92A5, "GL_LINEARBURN_NV",
    },
    {
        0x8893, "GL_ELEMENT_ARRAY_BUFFER",
    },
    {
        0x8892, "GL_ARRAY_BUFFER",
    },
    {
        0x92A8, "GL_PINLIGHT_NV",
    },
    {
        0x92A9, "GL_HARDMIX_NV",
    },
    {
        0x9112, "GL_OBJECT_TYPE_APPLE",
    },
    {
        0x90CC, "GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT",
    },
    {
        0x90CD, "GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT",
    },
    {
        0x919F, "GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT_EXT",
    },
    {
        0x919E, "GL_TEXTURE_BUFFER_SIZE_EXT",
    },
    {
        0x919D, "GL_TEXTURE_BUFFER_OFFSET_EXT",
    },
    {
        0x8BD8, "GL_TEXTURE_IMAGE_VALID_QCOM",
    },
    {
        0x9278, "GL_COMPRESSED_RGBA8_ETC2_EAC",
    },
    {
        0x9279, "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC",
    },
    {
        0x8DA7, "GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT",
    },
    {
        0x9272, "GL_COMPRESSED_RG11_EAC",
    },
    {
        0x8DA8, "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT",
    },
    {
        0x9270, "GL_COMPRESSED_R11_EAC",
    },
    {
        0x9271, "GL_COMPRESSED_SIGNED_R11_EAC",
    },
    {
        0x9276, "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2",
    },
    {
        0x887F, "GL_GEOMETRY_SHADER_INVOCATIONS_EXT",
    },
    {
        0x8A3B, "GL_UNIFORM_OFFSET",
    },
    {
        0x9275, "GL_COMPRESSED_SRGB8_ETC2",
    },
    {
        0x84D5, "GL_TEXTURE21",
    },
    {
        0x8C3A, "GL_R11F_G11F_B10F_APPLE",
    },
    {
        0x8C3B, "GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE",
    },
    {
        0x8C3D, "GL_RGB9_E5_APPLE",
    },
    {
        0x8C3E, "GL_UNSIGNED_INT_5_9_9_9_REV_APPLE",
    },
    {
        0x9287, "GL_DST_NV",
    },
    {
        0x93BA, "GL_COMPRESSED_RGBA_ASTC_10x8_KHR",
    },
    {
        0x9285, "GL_BLEND_ADVANCED_COHERENT_KHR",
    },
    {
        0x93BC, "GL_COMPRESSED_RGBA_ASTC_12x10_KHR",
    },
    {
        0x93BD, "GL_COMPRESSED_RGBA_ASTC_12x12_KHR",
    },
    {
        0x84E8, "GL_MAX_RENDERBUFFER_SIZE",
    },
    {
        0x9281, "GL_BLEND_OVERLAP_NV",
    },
    {
        0x9280, "GL_BLEND_PREMULTIPLIED_SRC_NV",
    },
    {
        0x00002000, "GL_DEPTH_BUFFER_BIT5_QCOM",
    },
    {
        0x8370, "GL_MIRRORED_REPEAT",
    },
    {
        0x84E0, "GL_ACTIVE_TEXTURE",
    },
    {
        0x8800, "GL_STENCIL_BACK_FUNC",
    },
    {
        0x8801, "GL_STENCIL_BACK_FAIL",
    },
    {
        0x0D33, "GL_MAX_TEXTURE_SIZE",
    },
    {
        0x0D32, "GL_MAX_CLIP_DISTANCES_APPLE",
    },
    {
        0x8624, "GL_VERTEX_ATTRIB_ARRAY_STRIDE",
    },
    {
        0x8625, "GL_VERTEX_ATTRIB_ARRAY_TYPE",
    },
    {
        0x8622, "GL_VERTEX_ATTRIB_ARRAY_ENABLED",
    },
    {
        0x8623, "GL_VERTEX_ATTRIB_ARRAY_SIZE",
    },
    {
        0x9086, "GL_PATH_STROKE_BOUND_CHROMIUM",
    },
    {
        0x8DB9, "GL_FRAMEBUFFER_SRGB_EXT",
    },
    {
        0x907a, "GL_PATH_MITER_LIMIT_CHROMIUM",
    },
    {
        0x9307, "GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT",
    },
    {
        0x8259, "GL_ACTIVE_PROGRAM_EXT",
    },
    {
        0x8258, "GL_PROGRAM_SEPARABLE_EXT",
    },
    {
        0x8257, "GL_PROGRAM_BINARY_RETRIEVABLE_HINT",
    },
    {
        0x8256, "GL_RESET_NOTIFICATION_STRATEGY_KHR",
    },
    {
        0x8255, "GL_UNKNOWN_CONTEXT_RESET_KHR",
    },
    {
        0x8254, "GL_INNOCENT_CONTEXT_RESET_KHR",
    },
    {
        0x1100, "GL_DONT_CARE",
    },
    {
        0x1101, "GL_FASTEST",
    },
    {
        0x1102, "GL_NICEST",
    },
    {
        0x8250, "GL_DEBUG_TYPE_PERFORMANCE_KHR",
    },
    {
        0x8CEB, "GL_COLOR_ATTACHMENT11_EXT",
    },
    {
        0x8CEC, "GL_COLOR_ATTACHMENT12_EXT",
    },
    {
        0x0408, "GL_FRONT_AND_BACK",
    },
    {
        0x8CEA, "GL_COLOR_ATTACHMENT10_EXT",
    },
    {
        0x8CEF, "GL_COLOR_ATTACHMENT15_EXT",
    },
    {
        0x8CED, "GL_COLOR_ATTACHMENT13_EXT",
    },
    {
        0x8829, "GL_DRAW_BUFFER4_EXT",
    },
    {
        0x0404, "GL_FRONT",
    },
    {
        0x0405, "GL_BACK",
    },
    {
        0x88E1, "GL_STREAM_READ",
    },
    {
        0x88E0, "GL_STREAM_DRAW",
    },
    {
        0x88E2, "GL_STREAM_COPY",
    },
    {
        0x88E5, "GL_STATIC_READ",
    },
    {
        0x88E4, "GL_STATIC_DRAW",
    },
    {
        0x93C6, "GL_COMPRESSED_RGBA_ASTC_5x5x5_OES",
    },
    {
        0x88E9, "GL_DYNAMIC_READ",
    },
    {
        0x88E8, "GL_DYNAMIC_DRAW",
    },
    {
        0x9291, "GL_PLUS_NV",
    },
    {
        0x8CAA, "GL_READ_FRAMEBUFFER_BINDING_ANGLE",
    },
    {
        0x93C5, "GL_COMPRESSED_RGBA_ASTC_5x5x4_OES",
    },
    {
        0x40000000, "GL_MULTISAMPLE_BUFFER_BIT6_QCOM",
    },
    {
        0x88EA, "GL_DYNAMIC_COPY",
    },
    {
        0x9116, "GL_SYNC_FENCE_APPLE",
    },
    {
        0x93C4, "GL_COMPRESSED_RGBA_ASTC_5x4x4_OES",
    },
    {
        0x88EE, "GL_ETC1_SRGB8_NV",
    },
    {
        0x88ED, "GL_PIXEL_PACK_BUFFER_BINDING",
    },
    {
        0x88EF, "GL_PIXEL_UNPACK_BUFFER_BINDING",
    },
    {
        0x93C3, "GL_COMPRESSED_RGBA_ASTC_4x4x4_OES",
    },
    {
        0x00000800, "GL_DEPTH_BUFFER_BIT3_QCOM",
    },
    {
        0x1903, "GL_RED_EXT",
    },
    {
        0x93C2, "GL_COMPRESSED_RGBA_ASTC_4x4x3_OES",
    },
    {
        0x8CE2, "GL_COLOR_ATTACHMENT2_EXT",
    },
    {
        0x8BC1, "GL_COUNTER_RANGE_AMD",
    },
    {
        0x8CE0, "GL_COLOR_ATTACHMENT0",
    },
    {
        0x8CE1, "GL_COLOR_ATTACHMENT1_EXT",
    },
    {
        0x8CE6, "GL_COLOR_ATTACHMENT6_EXT",
    },
    {
        0x93C1, "GL_COMPRESSED_RGBA_ASTC_4x3x3_OES",
    },
    {
        0x8A1F, "GL_RGB_422_APPLE",
    },
    {
        0x93DC, "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR",
    },
    {
        0x9292, "GL_PLUS_DARKER_NV",
    },
    {
        0x8CE8, "GL_COLOR_ATTACHMENT8_EXT",
    },
    {
        0x93C0, "GL_COMPRESSED_RGBA_ASTC_3x3x3_OES",
    },
    {
        0x0C23, "GL_COLOR_WRITEMASK",
    },
    {
        0x0C22, "GL_COLOR_CLEAR_VALUE",
    },
    {
        0x8A11, "GL_UNIFORM_BUFFER",
    },
    {
        0x8823, "GL_WRITEONLY_RENDERING_QCOM",
    },
    {
        0x8824, "GL_MAX_DRAW_BUFFERS_EXT",
    },
    {
        0x825E, "GL_LAYER_PROVOKING_VERTEX_EXT",
    },
    {
        0x825A, "GL_PROGRAM_PIPELINE_BINDING_EXT",
    },
    {
        0x1909, "GL_LUMINANCE",
    },
    {
        0x0D3A, "GL_MAX_VIEWPORT_DIMS",
    },
    {
        0x8B53, "GL_INT_VEC2",
    },
    {
        0x8826, "GL_DRAW_BUFFER1_EXT",
    },
    {
        0x809E, "GL_SAMPLE_ALPHA_TO_COVERAGE",
    },
    {
        0x8BC0, "GL_COUNTER_TYPE_AMD",
    },
    {
        0x8BC3, "GL_PERCENTAGE_AMD",
    },
    {
        0x8BC2, "GL_UNSIGNED_INT64_AMD",
    },
    {
        0x8BC5, "GL_PERFMON_RESULT_SIZE_AMD",
    },
    {
        0x8BC4, "GL_PERFMON_RESULT_AVAILABLE_AMD",
    },
    {
        0x8BC6, "GL_PERFMON_RESULT_AMD",
    },
};

const GLES2Util::EnumToString* const GLES2Util::enum_to_string_table_ =
    enum_to_string_table;
const size_t GLES2Util::enum_to_string_table_len_ =
    sizeof(enum_to_string_table) / sizeof(enum_to_string_table[0]);

std::string GLES2Util::GetStringAttachment(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COLOR_ATTACHMENT0, "GL_COLOR_ATTACHMENT0"},
      {GL_DEPTH_ATTACHMENT, "GL_DEPTH_ATTACHMENT"},
      {GL_STENCIL_ATTACHMENT, "GL_STENCIL_ATTACHMENT"},
      {GL_DEPTH_STENCIL_ATTACHMENT, "GL_DEPTH_STENCIL_ATTACHMENT"},
      {GL_COLOR_EXT, "GL_COLOR_EXT"},
      {GL_DEPTH_EXT, "GL_DEPTH_EXT"},
      {GL_STENCIL_EXT, "GL_STENCIL_EXT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBackbufferAttachment(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COLOR_EXT, "GL_COLOR_EXT"},
      {GL_DEPTH_EXT, "GL_DEPTH_EXT"},
      {GL_STENCIL_EXT, "GL_STENCIL_EXT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBlitFilter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NEAREST, "GL_NEAREST"}, {GL_LINEAR, "GL_LINEAR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_INTERLEAVED_ATTRIBS, "GL_INTERLEAVED_ATTRIBS"},
      {GL_SEPARATE_ATTRIBS, "GL_SEPARATE_ATTRIBS"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BUFFER_SIZE, "GL_BUFFER_SIZE"},
      {GL_BUFFER_USAGE, "GL_BUFFER_USAGE"},
      {GL_BUFFER_ACCESS_FLAGS, "GL_BUFFER_ACCESS_FLAGS"},
      {GL_BUFFER_MAPPED, "GL_BUFFER_MAPPED"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferParameter64(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BUFFER_SIZE, "GL_BUFFER_SIZE"},
      {GL_BUFFER_MAP_LENGTH, "GL_BUFFER_MAP_LENGTH"},
      {GL_BUFFER_MAP_OFFSET, "GL_BUFFER_MAP_OFFSET"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ARRAY_BUFFER, "GL_ARRAY_BUFFER"},
      {GL_ELEMENT_ARRAY_BUFFER, "GL_ELEMENT_ARRAY_BUFFER"},
      {GL_COPY_READ_BUFFER, "GL_COPY_READ_BUFFER"},
      {GL_COPY_WRITE_BUFFER, "GL_COPY_WRITE_BUFFER"},
      {GL_PIXEL_PACK_BUFFER, "GL_PIXEL_PACK_BUFFER"},
      {GL_PIXEL_UNPACK_BUFFER, "GL_PIXEL_UNPACK_BUFFER"},
      {GL_TRANSFORM_FEEDBACK_BUFFER, "GL_TRANSFORM_FEEDBACK_BUFFER"},
      {GL_UNIFORM_BUFFER, "GL_UNIFORM_BUFFER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferUsage(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_STREAM_DRAW, "GL_STREAM_DRAW"},
      {GL_STATIC_DRAW, "GL_STATIC_DRAW"},
      {GL_DYNAMIC_DRAW, "GL_DYNAMIC_DRAW"},
      {GL_STREAM_READ, "GL_STREAM_READ"},
      {GL_STREAM_COPY, "GL_STREAM_COPY"},
      {GL_STATIC_READ, "GL_STATIC_READ"},
      {GL_STATIC_COPY, "GL_STATIC_COPY"},
      {GL_DYNAMIC_READ, "GL_DYNAMIC_READ"},
      {GL_DYNAMIC_COPY, "GL_DYNAMIC_COPY"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferfi(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_DEPTH_STENCIL, "GL_DEPTH_STENCIL"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferfv(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COLOR, "GL_COLOR"}, {GL_DEPTH, "GL_DEPTH"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferiv(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COLOR, "GL_COLOR"}, {GL_STENCIL, "GL_STENCIL"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringBufferuiv(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COLOR, "GL_COLOR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringCapability(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BLEND, "GL_BLEND"},
      {GL_CULL_FACE, "GL_CULL_FACE"},
      {GL_DEPTH_TEST, "GL_DEPTH_TEST"},
      {GL_DITHER, "GL_DITHER"},
      {GL_POLYGON_OFFSET_FILL, "GL_POLYGON_OFFSET_FILL"},
      {GL_SAMPLE_ALPHA_TO_COVERAGE, "GL_SAMPLE_ALPHA_TO_COVERAGE"},
      {GL_SAMPLE_COVERAGE, "GL_SAMPLE_COVERAGE"},
      {GL_SCISSOR_TEST, "GL_SCISSOR_TEST"},
      {GL_STENCIL_TEST, "GL_STENCIL_TEST"},
      {GL_RASTERIZER_DISCARD, "GL_RASTERIZER_DISCARD"},
      {GL_PRIMITIVE_RESTART_FIXED_INDEX, "GL_PRIMITIVE_RESTART_FIXED_INDEX"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringCmpFunction(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NEVER, "GL_NEVER"},     {GL_LESS, "GL_LESS"},
      {GL_EQUAL, "GL_EQUAL"},     {GL_LEQUAL, "GL_LEQUAL"},
      {GL_GREATER, "GL_GREATER"}, {GL_NOTEQUAL, "GL_NOTEQUAL"},
      {GL_GEQUAL, "GL_GEQUAL"},   {GL_ALWAYS, "GL_ALWAYS"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringCompressedTextureFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_COMPRESSED_R11_EAC, "GL_COMPRESSED_R11_EAC"},
      {GL_COMPRESSED_SIGNED_R11_EAC, "GL_COMPRESSED_SIGNED_R11_EAC"},
      {GL_COMPRESSED_RG11_EAC, "GL_COMPRESSED_RG11_EAC"},
      {GL_COMPRESSED_SIGNED_RG11_EAC, "GL_COMPRESSED_SIGNED_RG11_EAC"},
      {GL_COMPRESSED_RGB8_ETC2, "GL_COMPRESSED_RGB8_ETC2"},
      {GL_COMPRESSED_SRGB8_ETC2, "GL_COMPRESSED_SRGB8_ETC2"},
      {GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
       "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2"},
      {GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
       "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2"},
      {GL_COMPRESSED_RGBA8_ETC2_EAC, "GL_COMPRESSED_RGBA8_ETC2_EAC"},
      {GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,
       "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringDrawMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_POINTS, "GL_POINTS"},
      {GL_LINE_STRIP, "GL_LINE_STRIP"},
      {GL_LINE_LOOP, "GL_LINE_LOOP"},
      {GL_LINES, "GL_LINES"},
      {GL_TRIANGLE_STRIP, "GL_TRIANGLE_STRIP"},
      {GL_TRIANGLE_FAN, "GL_TRIANGLE_FAN"},
      {GL_TRIANGLES, "GL_TRIANGLES"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringDstBlendFactor(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ZERO, "GL_ZERO"},
      {GL_ONE, "GL_ONE"},
      {GL_SRC_COLOR, "GL_SRC_COLOR"},
      {GL_ONE_MINUS_SRC_COLOR, "GL_ONE_MINUS_SRC_COLOR"},
      {GL_DST_COLOR, "GL_DST_COLOR"},
      {GL_ONE_MINUS_DST_COLOR, "GL_ONE_MINUS_DST_COLOR"},
      {GL_SRC_ALPHA, "GL_SRC_ALPHA"},
      {GL_ONE_MINUS_SRC_ALPHA, "GL_ONE_MINUS_SRC_ALPHA"},
      {GL_DST_ALPHA, "GL_DST_ALPHA"},
      {GL_ONE_MINUS_DST_ALPHA, "GL_ONE_MINUS_DST_ALPHA"},
      {GL_CONSTANT_COLOR, "GL_CONSTANT_COLOR"},
      {GL_ONE_MINUS_CONSTANT_COLOR, "GL_ONE_MINUS_CONSTANT_COLOR"},
      {GL_CONSTANT_ALPHA, "GL_CONSTANT_ALPHA"},
      {GL_ONE_MINUS_CONSTANT_ALPHA, "GL_ONE_MINUS_CONSTANT_ALPHA"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringEquation(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FUNC_ADD, "GL_FUNC_ADD"},
      {GL_FUNC_SUBTRACT, "GL_FUNC_SUBTRACT"},
      {GL_FUNC_REVERSE_SUBTRACT, "GL_FUNC_REVERSE_SUBTRACT"},
      {GL_MIN, "GL_MIN"},
      {GL_MAX, "GL_MAX"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringFaceMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_CW, "GL_CW"}, {GL_CCW, "GL_CCW"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringFaceType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FRONT, "GL_FRONT"},
      {GL_BACK, "GL_BACK"},
      {GL_FRONT_AND_BACK, "GL_FRONT_AND_BACK"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringFrameBufferParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
       "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE"},
      {GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
       "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME"},
      {GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
       "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL"},
      {GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE,
       "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE"},
      {GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE,
       "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE"},
      {GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE,
       "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE"},
      {GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING,
       "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING"},
      {GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER,
       "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringFrameBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FRAMEBUFFER, "GL_FRAMEBUFFER"},
      {GL_DRAW_FRAMEBUFFER, "GL_DRAW_FRAMEBUFFER"},
      {GL_READ_FRAMEBUFFER, "GL_READ_FRAMEBUFFER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringGLState(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ACTIVE_TEXTURE, "GL_ACTIVE_TEXTURE"},
      {GL_ALIASED_LINE_WIDTH_RANGE, "GL_ALIASED_LINE_WIDTH_RANGE"},
      {GL_ALIASED_POINT_SIZE_RANGE, "GL_ALIASED_POINT_SIZE_RANGE"},
      {GL_ALPHA_BITS, "GL_ALPHA_BITS"},
      {GL_ARRAY_BUFFER_BINDING, "GL_ARRAY_BUFFER_BINDING"},
      {GL_BLUE_BITS, "GL_BLUE_BITS"},
      {GL_COMPRESSED_TEXTURE_FORMATS, "GL_COMPRESSED_TEXTURE_FORMATS"},
      {GL_CURRENT_PROGRAM, "GL_CURRENT_PROGRAM"},
      {GL_DEPTH_BITS, "GL_DEPTH_BITS"},
      {GL_DEPTH_RANGE, "GL_DEPTH_RANGE"},
      {GL_ELEMENT_ARRAY_BUFFER_BINDING, "GL_ELEMENT_ARRAY_BUFFER_BINDING"},
      {GL_FRAMEBUFFER_BINDING, "GL_FRAMEBUFFER_BINDING"},
      {GL_GENERATE_MIPMAP_HINT, "GL_GENERATE_MIPMAP_HINT"},
      {GL_GREEN_BITS, "GL_GREEN_BITS"},
      {GL_IMPLEMENTATION_COLOR_READ_FORMAT,
       "GL_IMPLEMENTATION_COLOR_READ_FORMAT"},
      {GL_IMPLEMENTATION_COLOR_READ_TYPE, "GL_IMPLEMENTATION_COLOR_READ_TYPE"},
      {GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
       "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS"},
      {GL_MAX_CUBE_MAP_TEXTURE_SIZE, "GL_MAX_CUBE_MAP_TEXTURE_SIZE"},
      {GL_MAX_FRAGMENT_UNIFORM_VECTORS, "GL_MAX_FRAGMENT_UNIFORM_VECTORS"},
      {GL_MAX_RENDERBUFFER_SIZE, "GL_MAX_RENDERBUFFER_SIZE"},
      {GL_MAX_TEXTURE_IMAGE_UNITS, "GL_MAX_TEXTURE_IMAGE_UNITS"},
      {GL_MAX_TEXTURE_SIZE, "GL_MAX_TEXTURE_SIZE"},
      {GL_MAX_VARYING_VECTORS, "GL_MAX_VARYING_VECTORS"},
      {GL_MAX_VERTEX_ATTRIBS, "GL_MAX_VERTEX_ATTRIBS"},
      {GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS"},
      {GL_MAX_VERTEX_UNIFORM_VECTORS, "GL_MAX_VERTEX_UNIFORM_VECTORS"},
      {GL_MAX_VIEWPORT_DIMS, "GL_MAX_VIEWPORT_DIMS"},
      {GL_NUM_COMPRESSED_TEXTURE_FORMATS, "GL_NUM_COMPRESSED_TEXTURE_FORMATS"},
      {GL_NUM_SHADER_BINARY_FORMATS, "GL_NUM_SHADER_BINARY_FORMATS"},
      {GL_PACK_ALIGNMENT, "GL_PACK_ALIGNMENT"},
      {GL_RED_BITS, "GL_RED_BITS"},
      {GL_RENDERBUFFER_BINDING, "GL_RENDERBUFFER_BINDING"},
      {GL_SAMPLE_BUFFERS, "GL_SAMPLE_BUFFERS"},
      {GL_SAMPLE_COVERAGE_INVERT, "GL_SAMPLE_COVERAGE_INVERT"},
      {GL_SAMPLE_COVERAGE_VALUE, "GL_SAMPLE_COVERAGE_VALUE"},
      {GL_SAMPLES, "GL_SAMPLES"},
      {GL_SCISSOR_BOX, "GL_SCISSOR_BOX"},
      {GL_SHADER_BINARY_FORMATS, "GL_SHADER_BINARY_FORMATS"},
      {GL_SHADER_COMPILER, "GL_SHADER_COMPILER"},
      {GL_SUBPIXEL_BITS, "GL_SUBPIXEL_BITS"},
      {GL_STENCIL_BITS, "GL_STENCIL_BITS"},
      {GL_TEXTURE_BINDING_2D, "GL_TEXTURE_BINDING_2D"},
      {GL_TEXTURE_BINDING_CUBE_MAP, "GL_TEXTURE_BINDING_CUBE_MAP"},
      {GL_UNPACK_ALIGNMENT, "GL_UNPACK_ALIGNMENT"},
      {GL_BIND_GENERATES_RESOURCE_CHROMIUM,
       "GL_BIND_GENERATES_RESOURCE_CHROMIUM"},
      {GL_VERTEX_ARRAY_BINDING_OES, "GL_VERTEX_ARRAY_BINDING_OES"},
      {GL_VIEWPORT, "GL_VIEWPORT"},
      {GL_BLEND_COLOR, "GL_BLEND_COLOR"},
      {GL_BLEND_EQUATION_RGB, "GL_BLEND_EQUATION_RGB"},
      {GL_BLEND_EQUATION_ALPHA, "GL_BLEND_EQUATION_ALPHA"},
      {GL_BLEND_SRC_RGB, "GL_BLEND_SRC_RGB"},
      {GL_BLEND_DST_RGB, "GL_BLEND_DST_RGB"},
      {GL_BLEND_SRC_ALPHA, "GL_BLEND_SRC_ALPHA"},
      {GL_BLEND_DST_ALPHA, "GL_BLEND_DST_ALPHA"},
      {GL_COLOR_CLEAR_VALUE, "GL_COLOR_CLEAR_VALUE"},
      {GL_DEPTH_CLEAR_VALUE, "GL_DEPTH_CLEAR_VALUE"},
      {GL_STENCIL_CLEAR_VALUE, "GL_STENCIL_CLEAR_VALUE"},
      {GL_COLOR_WRITEMASK, "GL_COLOR_WRITEMASK"},
      {GL_CULL_FACE_MODE, "GL_CULL_FACE_MODE"},
      {GL_DEPTH_FUNC, "GL_DEPTH_FUNC"},
      {GL_DEPTH_WRITEMASK, "GL_DEPTH_WRITEMASK"},
      {GL_FRONT_FACE, "GL_FRONT_FACE"},
      {GL_LINE_WIDTH, "GL_LINE_WIDTH"},
      {GL_POLYGON_OFFSET_FACTOR, "GL_POLYGON_OFFSET_FACTOR"},
      {GL_POLYGON_OFFSET_UNITS, "GL_POLYGON_OFFSET_UNITS"},
      {GL_STENCIL_FUNC, "GL_STENCIL_FUNC"},
      {GL_STENCIL_REF, "GL_STENCIL_REF"},
      {GL_STENCIL_VALUE_MASK, "GL_STENCIL_VALUE_MASK"},
      {GL_STENCIL_BACK_FUNC, "GL_STENCIL_BACK_FUNC"},
      {GL_STENCIL_BACK_REF, "GL_STENCIL_BACK_REF"},
      {GL_STENCIL_BACK_VALUE_MASK, "GL_STENCIL_BACK_VALUE_MASK"},
      {GL_STENCIL_WRITEMASK, "GL_STENCIL_WRITEMASK"},
      {GL_STENCIL_BACK_WRITEMASK, "GL_STENCIL_BACK_WRITEMASK"},
      {GL_STENCIL_FAIL, "GL_STENCIL_FAIL"},
      {GL_STENCIL_PASS_DEPTH_FAIL, "GL_STENCIL_PASS_DEPTH_FAIL"},
      {GL_STENCIL_PASS_DEPTH_PASS, "GL_STENCIL_PASS_DEPTH_PASS"},
      {GL_STENCIL_BACK_FAIL, "GL_STENCIL_BACK_FAIL"},
      {GL_STENCIL_BACK_PASS_DEPTH_FAIL, "GL_STENCIL_BACK_PASS_DEPTH_FAIL"},
      {GL_STENCIL_BACK_PASS_DEPTH_PASS, "GL_STENCIL_BACK_PASS_DEPTH_PASS"},
      {GL_BLEND, "GL_BLEND"},
      {GL_CULL_FACE, "GL_CULL_FACE"},
      {GL_DEPTH_TEST, "GL_DEPTH_TEST"},
      {GL_DITHER, "GL_DITHER"},
      {GL_POLYGON_OFFSET_FILL, "GL_POLYGON_OFFSET_FILL"},
      {GL_SAMPLE_ALPHA_TO_COVERAGE, "GL_SAMPLE_ALPHA_TO_COVERAGE"},
      {GL_SAMPLE_COVERAGE, "GL_SAMPLE_COVERAGE"},
      {GL_SCISSOR_TEST, "GL_SCISSOR_TEST"},
      {GL_STENCIL_TEST, "GL_STENCIL_TEST"},
      {GL_RASTERIZER_DISCARD, "GL_RASTERIZER_DISCARD"},
      {GL_PRIMITIVE_RESTART_FIXED_INDEX, "GL_PRIMITIVE_RESTART_FIXED_INDEX"},
      {GL_COPY_READ_BUFFER_BINDING, "GL_COPY_READ_BUFFER_BINDING"},
      {GL_COPY_WRITE_BUFFER_BINDING, "GL_COPY_WRITE_BUFFER_BINDING"},
      {GL_DRAW_BUFFER0, "GL_DRAW_BUFFER0"},
      {GL_DRAW_BUFFER1, "GL_DRAW_BUFFER1"},
      {GL_DRAW_BUFFER2, "GL_DRAW_BUFFER2"},
      {GL_DRAW_BUFFER3, "GL_DRAW_BUFFER3"},
      {GL_DRAW_BUFFER4, "GL_DRAW_BUFFER4"},
      {GL_DRAW_BUFFER5, "GL_DRAW_BUFFER5"},
      {GL_DRAW_BUFFER6, "GL_DRAW_BUFFER6"},
      {GL_DRAW_BUFFER7, "GL_DRAW_BUFFER7"},
      {GL_DRAW_BUFFER8, "GL_DRAW_BUFFER8"},
      {GL_DRAW_BUFFER9, "GL_DRAW_BUFFER9"},
      {GL_DRAW_BUFFER10, "GL_DRAW_BUFFER10"},
      {GL_DRAW_BUFFER11, "GL_DRAW_BUFFER11"},
      {GL_DRAW_BUFFER12, "GL_DRAW_BUFFER12"},
      {GL_DRAW_BUFFER13, "GL_DRAW_BUFFER13"},
      {GL_DRAW_BUFFER14, "GL_DRAW_BUFFER14"},
      {GL_DRAW_BUFFER15, "GL_DRAW_BUFFER15"},
      {GL_DRAW_FRAMEBUFFER_BINDING, "GL_DRAW_FRAMEBUFFER_BINDING"},
      {GL_FRAGMENT_SHADER_DERIVATIVE_HINT,
       "GL_FRAGMENT_SHADER_DERIVATIVE_HINT"},
      {GL_GPU_DISJOINT_EXT, "GL_GPU_DISJOINT_EXT"},
      {GL_MAJOR_VERSION, "GL_MAJOR_VERSION"},
      {GL_MAX_3D_TEXTURE_SIZE, "GL_MAX_3D_TEXTURE_SIZE"},
      {GL_MAX_ARRAY_TEXTURE_LAYERS, "GL_MAX_ARRAY_TEXTURE_LAYERS"},
      {GL_MAX_COLOR_ATTACHMENTS, "GL_MAX_COLOR_ATTACHMENTS"},
      {GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
       "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS"},
      {GL_MAX_COMBINED_UNIFORM_BLOCKS, "GL_MAX_COMBINED_UNIFORM_BLOCKS"},
      {GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
       "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS"},
      {GL_MAX_DRAW_BUFFERS, "GL_MAX_DRAW_BUFFERS"},
      {GL_MAX_ELEMENT_INDEX, "GL_MAX_ELEMENT_INDEX"},
      {GL_MAX_ELEMENTS_INDICES, "GL_MAX_ELEMENTS_INDICES"},
      {GL_MAX_ELEMENTS_VERTICES, "GL_MAX_ELEMENTS_VERTICES"},
      {GL_MAX_FRAGMENT_INPUT_COMPONENTS, "GL_MAX_FRAGMENT_INPUT_COMPONENTS"},
      {GL_MAX_FRAGMENT_UNIFORM_BLOCKS, "GL_MAX_FRAGMENT_UNIFORM_BLOCKS"},
      {GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
       "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS"},
      {GL_MAX_PROGRAM_TEXEL_OFFSET, "GL_MAX_PROGRAM_TEXEL_OFFSET"},
      {GL_MAX_SAMPLES, "GL_MAX_SAMPLES"},
      {GL_MAX_SERVER_WAIT_TIMEOUT, "GL_MAX_SERVER_WAIT_TIMEOUT"},
      {GL_MAX_TEXTURE_LOD_BIAS, "GL_MAX_TEXTURE_LOD_BIAS"},
      {GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS,
       "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS"},
      {GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS,
       "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS"},
      {GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS,
       "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS"},
      {GL_MAX_UNIFORM_BLOCK_SIZE, "GL_MAX_UNIFORM_BLOCK_SIZE"},
      {GL_MAX_UNIFORM_BUFFER_BINDINGS, "GL_MAX_UNIFORM_BUFFER_BINDINGS"},
      {GL_MAX_VARYING_COMPONENTS, "GL_MAX_VARYING_COMPONENTS"},
      {GL_MAX_VERTEX_OUTPUT_COMPONENTS, "GL_MAX_VERTEX_OUTPUT_COMPONENTS"},
      {GL_MAX_VERTEX_UNIFORM_BLOCKS, "GL_MAX_VERTEX_UNIFORM_BLOCKS"},
      {GL_MAX_VERTEX_UNIFORM_COMPONENTS, "GL_MAX_VERTEX_UNIFORM_COMPONENTS"},
      {GL_MIN_PROGRAM_TEXEL_OFFSET, "GL_MIN_PROGRAM_TEXEL_OFFSET"},
      {GL_MINOR_VERSION, "GL_MINOR_VERSION"},
      {GL_NUM_EXTENSIONS, "GL_NUM_EXTENSIONS"},
      {GL_NUM_PROGRAM_BINARY_FORMATS, "GL_NUM_PROGRAM_BINARY_FORMATS"},
      {GL_PACK_ROW_LENGTH, "GL_PACK_ROW_LENGTH"},
      {GL_PACK_SKIP_PIXELS, "GL_PACK_SKIP_PIXELS"},
      {GL_PACK_SKIP_ROWS, "GL_PACK_SKIP_ROWS"},
      {GL_PIXEL_PACK_BUFFER_BINDING, "GL_PIXEL_PACK_BUFFER_BINDING"},
      {GL_PIXEL_UNPACK_BUFFER_BINDING, "GL_PIXEL_UNPACK_BUFFER_BINDING"},
      {GL_PROGRAM_BINARY_FORMATS, "GL_PROGRAM_BINARY_FORMATS"},
      {GL_READ_BUFFER, "GL_READ_BUFFER"},
      {GL_READ_FRAMEBUFFER_BINDING, "GL_READ_FRAMEBUFFER_BINDING"},
      {GL_SAMPLER_BINDING, "GL_SAMPLER_BINDING"},
      {GL_TIMESTAMP_EXT, "GL_TIMESTAMP_EXT"},
      {GL_TEXTURE_BINDING_2D_ARRAY, "GL_TEXTURE_BINDING_2D_ARRAY"},
      {GL_TEXTURE_BINDING_3D, "GL_TEXTURE_BINDING_3D"},
      {GL_TRANSFORM_FEEDBACK_BINDING, "GL_TRANSFORM_FEEDBACK_BINDING"},
      {GL_TRANSFORM_FEEDBACK_ACTIVE, "GL_TRANSFORM_FEEDBACK_ACTIVE"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
       "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING"},
      {GL_TRANSFORM_FEEDBACK_PAUSED, "GL_TRANSFORM_FEEDBACK_PAUSED"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_START,
       "GL_TRANSFORM_FEEDBACK_BUFFER_START"},
      {GL_UNIFORM_BUFFER_BINDING, "GL_UNIFORM_BUFFER_BINDING"},
      {GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
       "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT"},
      {GL_UNIFORM_BUFFER_SIZE, "GL_UNIFORM_BUFFER_SIZE"},
      {GL_UNIFORM_BUFFER_START, "GL_UNIFORM_BUFFER_START"},
      {GL_UNPACK_IMAGE_HEIGHT, "GL_UNPACK_IMAGE_HEIGHT"},
      {GL_UNPACK_ROW_LENGTH, "GL_UNPACK_ROW_LENGTH"},
      {GL_UNPACK_SKIP_IMAGES, "GL_UNPACK_SKIP_IMAGES"},
      {GL_UNPACK_SKIP_PIXELS, "GL_UNPACK_SKIP_PIXELS"},
      {GL_UNPACK_SKIP_ROWS, "GL_UNPACK_SKIP_ROWS"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringGetMaxIndexType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringGetTexParamTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_2D, "GL_TEXTURE_2D"},
      {GL_TEXTURE_CUBE_MAP, "GL_TEXTURE_CUBE_MAP"},
      {GL_TEXTURE_2D_ARRAY, "GL_TEXTURE_2D_ARRAY"},
      {GL_TEXTURE_3D, "GL_TEXTURE_3D"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringHintMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FASTEST, "GL_FASTEST"},
      {GL_NICEST, "GL_NICEST"},
      {GL_DONT_CARE, "GL_DONT_CARE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringHintTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_GENERATE_MIPMAP_HINT, "GL_GENERATE_MIPMAP_HINT"},
      {GL_FRAGMENT_SHADER_DERIVATIVE_HINT,
       "GL_FRAGMENT_SHADER_DERIVATIVE_HINT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringImageInternalFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_RGB, "GL_RGB"},
      {GL_RGB_YUV_420_CHROMIUM, "GL_RGB_YUV_420_CHROMIUM"},
      {GL_RGB_YCBCR_422_CHROMIUM, "GL_RGB_YCBCR_422_CHROMIUM"},
      {GL_RGBA, "GL_RGBA"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringImageUsage(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_MAP_CHROMIUM, "GL_MAP_CHROMIUM"},
      {GL_SCANOUT_CHROMIUM, "GL_SCANOUT_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringIndexType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringIndexedBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TRANSFORM_FEEDBACK_BUFFER, "GL_TRANSFORM_FEEDBACK_BUFFER"},
      {GL_UNIFORM_BUFFER, "GL_UNIFORM_BUFFER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringIndexedGLState(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TRANSFORM_FEEDBACK_BUFFER_BINDING,
       "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_START,
       "GL_TRANSFORM_FEEDBACK_BUFFER_START"},
      {GL_UNIFORM_BUFFER_BINDING, "GL_UNIFORM_BUFFER_BINDING"},
      {GL_UNIFORM_BUFFER_SIZE, "GL_UNIFORM_BUFFER_SIZE"},
      {GL_UNIFORM_BUFFER_START, "GL_UNIFORM_BUFFER_START"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringInternalFormatParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NUM_SAMPLE_COUNTS, "GL_NUM_SAMPLE_COUNTS"},
      {GL_SAMPLES, "GL_SAMPLES"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringInvalidateFrameBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_FRAMEBUFFER, "GL_FRAMEBUFFER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringMapBufferAccess(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_MAP_READ_BIT, "GL_MAP_READ_BIT"},
      {GL_MAP_WRITE_BIT, "GL_MAP_WRITE_BIT"},
      {GL_MAP_INVALIDATE_RANGE_BIT, "GL_MAP_INVALIDATE_RANGE_BIT"},
      {GL_MAP_INVALIDATE_BUFFER_BIT, "GL_MAP_INVALIDATE_BUFFER_BIT"},
      {GL_MAP_FLUSH_EXPLICIT_BIT, "GL_MAP_FLUSH_EXPLICIT_BIT"},
      {GL_MAP_UNSYNCHRONIZED_BIT, "GL_MAP_UNSYNCHRONIZED_BIT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringMatrixMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_PATH_PROJECTION_CHROMIUM, "GL_PATH_PROJECTION_CHROMIUM"},
      {GL_PATH_MODELVIEW_CHROMIUM, "GL_PATH_MODELVIEW_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPathCoordType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BYTE, "GL_BYTE"},   {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_SHORT, "GL_SHORT"}, {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_FLOAT, "GL_FLOAT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPathCoverMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_CONVEX_HULL_CHROMIUM, "GL_CONVEX_HULL_CHROMIUM"},
      {GL_BOUNDING_BOX_CHROMIUM, "GL_BOUNDING_BOX_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPathFillMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_INVERT, "GL_INVERT"},
      {GL_COUNT_UP_CHROMIUM, "GL_COUNT_UP_CHROMIUM"},
      {GL_COUNT_DOWN_CHROMIUM, "GL_COUNT_DOWN_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPathParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_PATH_STROKE_WIDTH_CHROMIUM, "GL_PATH_STROKE_WIDTH_CHROMIUM"},
      {GL_PATH_END_CAPS_CHROMIUM, "GL_PATH_END_CAPS_CHROMIUM"},
      {GL_PATH_JOIN_STYLE_CHROMIUM, "GL_PATH_JOIN_STYLE_CHROMIUM"},
      {GL_PATH_MITER_LIMIT_CHROMIUM, "GL_PATH_MITER_LIMIT_CHROMIUM"},
      {GL_PATH_STROKE_BOUND_CHROMIUM, "GL_PATH_STROKE_BOUND_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPixelStore(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_PACK_ALIGNMENT, "GL_PACK_ALIGNMENT"},
      {GL_UNPACK_ALIGNMENT, "GL_UNPACK_ALIGNMENT"},
      {GL_PACK_ROW_LENGTH, "GL_PACK_ROW_LENGTH"},
      {GL_PACK_SKIP_PIXELS, "GL_PACK_SKIP_PIXELS"},
      {GL_PACK_SKIP_ROWS, "GL_PACK_SKIP_ROWS"},
      {GL_UNPACK_ROW_LENGTH, "GL_UNPACK_ROW_LENGTH"},
      {GL_UNPACK_IMAGE_HEIGHT, "GL_UNPACK_IMAGE_HEIGHT"},
      {GL_UNPACK_SKIP_PIXELS, "GL_UNPACK_SKIP_PIXELS"},
      {GL_UNPACK_SKIP_ROWS, "GL_UNPACK_SKIP_ROWS"},
      {GL_UNPACK_SKIP_IMAGES, "GL_UNPACK_SKIP_IMAGES"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringPixelType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_UNSIGNED_SHORT_5_6_5, "GL_UNSIGNED_SHORT_5_6_5"},
      {GL_UNSIGNED_SHORT_4_4_4_4, "GL_UNSIGNED_SHORT_4_4_4_4"},
      {GL_UNSIGNED_SHORT_5_5_5_1, "GL_UNSIGNED_SHORT_5_5_5_1"},
      {GL_BYTE, "GL_BYTE"},
      {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_SHORT, "GL_SHORT"},
      {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
      {GL_INT, "GL_INT"},
      {GL_HALF_FLOAT, "GL_HALF_FLOAT"},
      {GL_FLOAT, "GL_FLOAT"},
      {GL_UNSIGNED_INT_2_10_10_10_REV, "GL_UNSIGNED_INT_2_10_10_10_REV"},
      {GL_UNSIGNED_INT_10F_11F_11F_REV, "GL_UNSIGNED_INT_10F_11F_11F_REV"},
      {GL_UNSIGNED_INT_5_9_9_9_REV, "GL_UNSIGNED_INT_5_9_9_9_REV"},
      {GL_UNSIGNED_INT_24_8, "GL_UNSIGNED_INT_24_8"},
      {GL_FLOAT_32_UNSIGNED_INT_24_8_REV, "GL_FLOAT_32_UNSIGNED_INT_24_8_REV"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringProgramParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_DELETE_STATUS, "GL_DELETE_STATUS"},
      {GL_LINK_STATUS, "GL_LINK_STATUS"},
      {GL_VALIDATE_STATUS, "GL_VALIDATE_STATUS"},
      {GL_INFO_LOG_LENGTH, "GL_INFO_LOG_LENGTH"},
      {GL_ATTACHED_SHADERS, "GL_ATTACHED_SHADERS"},
      {GL_ACTIVE_ATTRIBUTES, "GL_ACTIVE_ATTRIBUTES"},
      {GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH"},
      {GL_ACTIVE_UNIFORMS, "GL_ACTIVE_UNIFORMS"},
      {GL_ACTIVE_UNIFORM_MAX_LENGTH, "GL_ACTIVE_UNIFORM_MAX_LENGTH"},
      {GL_ACTIVE_UNIFORM_BLOCKS, "GL_ACTIVE_UNIFORM_BLOCKS"},
      {GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
       "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH"},
      {GL_TRANSFORM_FEEDBACK_BUFFER_MODE, "GL_TRANSFORM_FEEDBACK_BUFFER_MODE"},
      {GL_TRANSFORM_FEEDBACK_VARYINGS, "GL_TRANSFORM_FEEDBACK_VARYINGS"},
      {GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
       "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringQueryObjectParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_QUERY_RESULT_EXT, "GL_QUERY_RESULT_EXT"},
      {GL_QUERY_RESULT_AVAILABLE_EXT, "GL_QUERY_RESULT_AVAILABLE_EXT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringQueryParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_CURRENT_QUERY_EXT, "GL_CURRENT_QUERY_EXT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringQueryTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ANY_SAMPLES_PASSED_EXT, "GL_ANY_SAMPLES_PASSED_EXT"},
      {GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT,
       "GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT"},
      {GL_COMMANDS_ISSUED_CHROMIUM, "GL_COMMANDS_ISSUED_CHROMIUM"},
      {GL_LATENCY_QUERY_CHROMIUM, "GL_LATENCY_QUERY_CHROMIUM"},
      {GL_ASYNC_PIXEL_PACK_COMPLETED_CHROMIUM,
       "GL_ASYNC_PIXEL_PACK_COMPLETED_CHROMIUM"},
      {GL_COMMANDS_COMPLETED_CHROMIUM, "GL_COMMANDS_COMPLETED_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringReadBuffer(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NONE, "GL_NONE"},
      {GL_BACK, "GL_BACK"},
      {GL_COLOR_ATTACHMENT0, "GL_COLOR_ATTACHMENT0"},
      {GL_COLOR_ATTACHMENT1, "GL_COLOR_ATTACHMENT1"},
      {GL_COLOR_ATTACHMENT2, "GL_COLOR_ATTACHMENT2"},
      {GL_COLOR_ATTACHMENT3, "GL_COLOR_ATTACHMENT3"},
      {GL_COLOR_ATTACHMENT4, "GL_COLOR_ATTACHMENT4"},
      {GL_COLOR_ATTACHMENT5, "GL_COLOR_ATTACHMENT5"},
      {GL_COLOR_ATTACHMENT6, "GL_COLOR_ATTACHMENT6"},
      {GL_COLOR_ATTACHMENT7, "GL_COLOR_ATTACHMENT7"},
      {GL_COLOR_ATTACHMENT8, "GL_COLOR_ATTACHMENT8"},
      {GL_COLOR_ATTACHMENT9, "GL_COLOR_ATTACHMENT9"},
      {GL_COLOR_ATTACHMENT10, "GL_COLOR_ATTACHMENT10"},
      {GL_COLOR_ATTACHMENT11, "GL_COLOR_ATTACHMENT11"},
      {GL_COLOR_ATTACHMENT12, "GL_COLOR_ATTACHMENT12"},
      {GL_COLOR_ATTACHMENT13, "GL_COLOR_ATTACHMENT13"},
      {GL_COLOR_ATTACHMENT14, "GL_COLOR_ATTACHMENT14"},
      {GL_COLOR_ATTACHMENT15, "GL_COLOR_ATTACHMENT15"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringReadPixelFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ALPHA, "GL_ALPHA"},
      {GL_RGB, "GL_RGB"},
      {GL_RGBA, "GL_RGBA"},
      {GL_RED, "GL_RED"},
      {GL_RED_INTEGER, "GL_RED_INTEGER"},
      {GL_RG, "GL_RG"},
      {GL_RG_INTEGER, "GL_RG_INTEGER"},
      {GL_RGB_INTEGER, "GL_RGB_INTEGER"},
      {GL_RGBA_INTEGER, "GL_RGBA_INTEGER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringReadPixelType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_UNSIGNED_SHORT_5_6_5, "GL_UNSIGNED_SHORT_5_6_5"},
      {GL_UNSIGNED_SHORT_4_4_4_4, "GL_UNSIGNED_SHORT_4_4_4_4"},
      {GL_UNSIGNED_SHORT_5_5_5_1, "GL_UNSIGNED_SHORT_5_5_5_1"},
      {GL_BYTE, "GL_BYTE"},
      {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_SHORT, "GL_SHORT"},
      {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
      {GL_INT, "GL_INT"},
      {GL_HALF_FLOAT, "GL_HALF_FLOAT"},
      {GL_FLOAT, "GL_FLOAT"},
      {GL_UNSIGNED_INT_2_10_10_10_REV, "GL_UNSIGNED_INT_2_10_10_10_REV"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringRenderBufferFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_RGBA4, "GL_RGBA4"},
      {GL_RGB565, "GL_RGB565"},
      {GL_RGB5_A1, "GL_RGB5_A1"},
      {GL_DEPTH_COMPONENT16, "GL_DEPTH_COMPONENT16"},
      {GL_STENCIL_INDEX8, "GL_STENCIL_INDEX8"},
      {GL_R8, "GL_R8"},
      {GL_R8UI, "GL_R8UI"},
      {GL_R8I, "GL_R8I"},
      {GL_R16UI, "GL_R16UI"},
      {GL_R16I, "GL_R16I"},
      {GL_R32UI, "GL_R32UI"},
      {GL_R32I, "GL_R32I"},
      {GL_RG8, "GL_RG8"},
      {GL_RG8UI, "GL_RG8UI"},
      {GL_RG8I, "GL_RG8I"},
      {GL_RG16UI, "GL_RG16UI"},
      {GL_RG16I, "GL_RG16I"},
      {GL_RG32UI, "GL_RG32UI"},
      {GL_RG32I, "GL_RG32I"},
      {GL_RGB8, "GL_RGB8"},
      {GL_RGBA8, "GL_RGBA8"},
      {GL_SRGB8_ALPHA8, "GL_SRGB8_ALPHA8"},
      {GL_RGB10_A2, "GL_RGB10_A2"},
      {GL_RGBA8UI, "GL_RGBA8UI"},
      {GL_RGBA8I, "GL_RGBA8I"},
      {GL_RGB10_A2UI, "GL_RGB10_A2UI"},
      {GL_RGBA16UI, "GL_RGBA16UI"},
      {GL_RGBA16I, "GL_RGBA16I"},
      {GL_RGBA32UI, "GL_RGBA32UI"},
      {GL_RGBA32I, "GL_RGBA32I"},
      {GL_DEPTH_COMPONENT24, "GL_DEPTH_COMPONENT24"},
      {GL_DEPTH_COMPONENT32F, "GL_DEPTH_COMPONENT32F"},
      {GL_DEPTH24_STENCIL8, "GL_DEPTH24_STENCIL8"},
      {GL_DEPTH32F_STENCIL8, "GL_DEPTH32F_STENCIL8"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringRenderBufferParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_RENDERBUFFER_RED_SIZE, "GL_RENDERBUFFER_RED_SIZE"},
      {GL_RENDERBUFFER_GREEN_SIZE, "GL_RENDERBUFFER_GREEN_SIZE"},
      {GL_RENDERBUFFER_BLUE_SIZE, "GL_RENDERBUFFER_BLUE_SIZE"},
      {GL_RENDERBUFFER_ALPHA_SIZE, "GL_RENDERBUFFER_ALPHA_SIZE"},
      {GL_RENDERBUFFER_DEPTH_SIZE, "GL_RENDERBUFFER_DEPTH_SIZE"},
      {GL_RENDERBUFFER_STENCIL_SIZE, "GL_RENDERBUFFER_STENCIL_SIZE"},
      {GL_RENDERBUFFER_WIDTH, "GL_RENDERBUFFER_WIDTH"},
      {GL_RENDERBUFFER_HEIGHT, "GL_RENDERBUFFER_HEIGHT"},
      {GL_RENDERBUFFER_INTERNAL_FORMAT, "GL_RENDERBUFFER_INTERNAL_FORMAT"},
      {GL_RENDERBUFFER_SAMPLES, "GL_RENDERBUFFER_SAMPLES"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringRenderBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_RENDERBUFFER, "GL_RENDERBUFFER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringResetStatus(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_GUILTY_CONTEXT_RESET_ARB, "GL_GUILTY_CONTEXT_RESET_ARB"},
      {GL_INNOCENT_CONTEXT_RESET_ARB, "GL_INNOCENT_CONTEXT_RESET_ARB"},
      {GL_UNKNOWN_CONTEXT_RESET_ARB, "GL_UNKNOWN_CONTEXT_RESET_ARB"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringSamplerParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_MAG_FILTER, "GL_TEXTURE_MAG_FILTER"},
      {GL_TEXTURE_MIN_FILTER, "GL_TEXTURE_MIN_FILTER"},
      {GL_TEXTURE_MIN_LOD, "GL_TEXTURE_MIN_LOD"},
      {GL_TEXTURE_MAX_LOD, "GL_TEXTURE_MAX_LOD"},
      {GL_TEXTURE_WRAP_S, "GL_TEXTURE_WRAP_S"},
      {GL_TEXTURE_WRAP_T, "GL_TEXTURE_WRAP_T"},
      {GL_TEXTURE_WRAP_R, "GL_TEXTURE_WRAP_R"},
      {GL_TEXTURE_COMPARE_MODE, "GL_TEXTURE_COMPARE_MODE"},
      {GL_TEXTURE_COMPARE_FUNC, "GL_TEXTURE_COMPARE_FUNC"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringShaderBinaryFormat(uint32_t value) {
  return GLES2Util::GetQualifiedEnumString(NULL, 0, value);
}

std::string GLES2Util::GetStringShaderParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_SHADER_TYPE, "GL_SHADER_TYPE"},
      {GL_DELETE_STATUS, "GL_DELETE_STATUS"},
      {GL_COMPILE_STATUS, "GL_COMPILE_STATUS"},
      {GL_INFO_LOG_LENGTH, "GL_INFO_LOG_LENGTH"},
      {GL_SHADER_SOURCE_LENGTH, "GL_SHADER_SOURCE_LENGTH"},
      {GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE,
       "GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringShaderPrecision(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_LOW_FLOAT, "GL_LOW_FLOAT"},   {GL_MEDIUM_FLOAT, "GL_MEDIUM_FLOAT"},
      {GL_HIGH_FLOAT, "GL_HIGH_FLOAT"}, {GL_LOW_INT, "GL_LOW_INT"},
      {GL_MEDIUM_INT, "GL_MEDIUM_INT"}, {GL_HIGH_INT, "GL_HIGH_INT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringShaderType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_VERTEX_SHADER, "GL_VERTEX_SHADER"},
      {GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringSrcBlendFactor(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ZERO, "GL_ZERO"},
      {GL_ONE, "GL_ONE"},
      {GL_SRC_COLOR, "GL_SRC_COLOR"},
      {GL_ONE_MINUS_SRC_COLOR, "GL_ONE_MINUS_SRC_COLOR"},
      {GL_DST_COLOR, "GL_DST_COLOR"},
      {GL_ONE_MINUS_DST_COLOR, "GL_ONE_MINUS_DST_COLOR"},
      {GL_SRC_ALPHA, "GL_SRC_ALPHA"},
      {GL_ONE_MINUS_SRC_ALPHA, "GL_ONE_MINUS_SRC_ALPHA"},
      {GL_DST_ALPHA, "GL_DST_ALPHA"},
      {GL_ONE_MINUS_DST_ALPHA, "GL_ONE_MINUS_DST_ALPHA"},
      {GL_CONSTANT_COLOR, "GL_CONSTANT_COLOR"},
      {GL_ONE_MINUS_CONSTANT_COLOR, "GL_ONE_MINUS_CONSTANT_COLOR"},
      {GL_CONSTANT_ALPHA, "GL_CONSTANT_ALPHA"},
      {GL_ONE_MINUS_CONSTANT_ALPHA, "GL_ONE_MINUS_CONSTANT_ALPHA"},
      {GL_SRC_ALPHA_SATURATE, "GL_SRC_ALPHA_SATURATE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringStencilOp(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_KEEP, "GL_KEEP"},           {GL_ZERO, "GL_ZERO"},
      {GL_REPLACE, "GL_REPLACE"},     {GL_INCR, "GL_INCR"},
      {GL_INCR_WRAP, "GL_INCR_WRAP"}, {GL_DECR, "GL_DECR"},
      {GL_DECR_WRAP, "GL_DECR_WRAP"}, {GL_INVERT, "GL_INVERT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringStringType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_VENDOR, "GL_VENDOR"},
      {GL_RENDERER, "GL_RENDERER"},
      {GL_VERSION, "GL_VERSION"},
      {GL_SHADING_LANGUAGE_VERSION, "GL_SHADING_LANGUAGE_VERSION"},
      {GL_EXTENSIONS, "GL_EXTENSIONS"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringSubscriptionTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_MOUSE_POSITION_CHROMIUM, "GL_MOUSE_POSITION_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringSyncCondition(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_SYNC_GPU_COMMANDS_COMPLETE, "GL_SYNC_GPU_COMMANDS_COMPLETE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringSyncParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_SYNC_STATUS, "GL_SYNC_STATUS"},
      {GL_OBJECT_TYPE, "GL_OBJECT_TYPE"},
      {GL_SYNC_CONDITION, "GL_SYNC_CONDITION"},
      {GL_SYNC_FLAGS, "GL_SYNC_FLAGS"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTexture3DTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_3D, "GL_TEXTURE_3D"},
      {GL_TEXTURE_2D_ARRAY, "GL_TEXTURE_2D_ARRAY"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureBindTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_2D, "GL_TEXTURE_2D"},
      {GL_TEXTURE_CUBE_MAP, "GL_TEXTURE_CUBE_MAP"},
      {GL_TEXTURE_3D, "GL_TEXTURE_3D"},
      {GL_TEXTURE_2D_ARRAY, "GL_TEXTURE_2D_ARRAY"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureCompareFunc(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_LEQUAL, "GL_LEQUAL"}, {GL_GEQUAL, "GL_GEQUAL"},
      {GL_LESS, "GL_LESS"},     {GL_GREATER, "GL_GREATER"},
      {GL_EQUAL, "GL_EQUAL"},   {GL_NOTEQUAL, "GL_NOTEQUAL"},
      {GL_ALWAYS, "GL_ALWAYS"}, {GL_NEVER, "GL_NEVER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureCompareMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NONE, "GL_NONE"},
      {GL_COMPARE_REF_TO_TEXTURE, "GL_COMPARE_REF_TO_TEXTURE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ALPHA, "GL_ALPHA"},
      {GL_LUMINANCE, "GL_LUMINANCE"},
      {GL_LUMINANCE_ALPHA, "GL_LUMINANCE_ALPHA"},
      {GL_RGB, "GL_RGB"},
      {GL_RGBA, "GL_RGBA"},
      {GL_RED, "GL_RED"},
      {GL_RED_INTEGER, "GL_RED_INTEGER"},
      {GL_RG, "GL_RG"},
      {GL_RG_INTEGER, "GL_RG_INTEGER"},
      {GL_RGB_INTEGER, "GL_RGB_INTEGER"},
      {GL_RGBA_INTEGER, "GL_RGBA_INTEGER"},
      {GL_DEPTH_COMPONENT, "GL_DEPTH_COMPONENT"},
      {GL_DEPTH_STENCIL, "GL_DEPTH_STENCIL"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureInternalFormat(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_ALPHA, "GL_ALPHA"},
      {GL_LUMINANCE, "GL_LUMINANCE"},
      {GL_LUMINANCE_ALPHA, "GL_LUMINANCE_ALPHA"},
      {GL_RGB, "GL_RGB"},
      {GL_RGBA, "GL_RGBA"},
      {GL_R8, "GL_R8"},
      {GL_R8_SNORM, "GL_R8_SNORM"},
      {GL_R16F, "GL_R16F"},
      {GL_R32F, "GL_R32F"},
      {GL_R8UI, "GL_R8UI"},
      {GL_R8I, "GL_R8I"},
      {GL_R16UI, "GL_R16UI"},
      {GL_R16I, "GL_R16I"},
      {GL_R32UI, "GL_R32UI"},
      {GL_R32I, "GL_R32I"},
      {GL_RG8, "GL_RG8"},
      {GL_RG8_SNORM, "GL_RG8_SNORM"},
      {GL_RG16F, "GL_RG16F"},
      {GL_RG32F, "GL_RG32F"},
      {GL_RG8UI, "GL_RG8UI"},
      {GL_RG8I, "GL_RG8I"},
      {GL_RG16UI, "GL_RG16UI"},
      {GL_RG16I, "GL_RG16I"},
      {GL_RG32UI, "GL_RG32UI"},
      {GL_RG32I, "GL_RG32I"},
      {GL_RGB8, "GL_RGB8"},
      {GL_SRGB8, "GL_SRGB8"},
      {GL_RGB565, "GL_RGB565"},
      {GL_RGB8_SNORM, "GL_RGB8_SNORM"},
      {GL_R11F_G11F_B10F, "GL_R11F_G11F_B10F"},
      {GL_RGB9_E5, "GL_RGB9_E5"},
      {GL_RGB16F, "GL_RGB16F"},
      {GL_RGB32F, "GL_RGB32F"},
      {GL_RGB8UI, "GL_RGB8UI"},
      {GL_RGB8I, "GL_RGB8I"},
      {GL_RGB16UI, "GL_RGB16UI"},
      {GL_RGB16I, "GL_RGB16I"},
      {GL_RGB32UI, "GL_RGB32UI"},
      {GL_RGB32I, "GL_RGB32I"},
      {GL_RGBA8, "GL_RGBA8"},
      {GL_SRGB8_ALPHA8, "GL_SRGB8_ALPHA8"},
      {GL_RGBA8_SNORM, "GL_RGBA8_SNORM"},
      {GL_RGB5_A1, "GL_RGB5_A1"},
      {GL_RGBA4, "GL_RGBA4"},
      {GL_RGB10_A2, "GL_RGB10_A2"},
      {GL_RGBA16F, "GL_RGBA16F"},
      {GL_RGBA32F, "GL_RGBA32F"},
      {GL_RGBA8UI, "GL_RGBA8UI"},
      {GL_RGBA8I, "GL_RGBA8I"},
      {GL_RGB10_A2UI, "GL_RGB10_A2UI"},
      {GL_RGBA16UI, "GL_RGBA16UI"},
      {GL_RGBA16I, "GL_RGBA16I"},
      {GL_RGBA32UI, "GL_RGBA32UI"},
      {GL_RGBA32I, "GL_RGBA32I"},
      {GL_DEPTH_COMPONENT16, "GL_DEPTH_COMPONENT16"},
      {GL_DEPTH_COMPONENT24, "GL_DEPTH_COMPONENT24"},
      {GL_DEPTH_COMPONENT32F, "GL_DEPTH_COMPONENT32F"},
      {GL_DEPTH24_STENCIL8, "GL_DEPTH24_STENCIL8"},
      {GL_DEPTH32F_STENCIL8, "GL_DEPTH32F_STENCIL8"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureInternalFormatStorage(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_RGB565, "GL_RGB565"},
      {GL_RGBA4, "GL_RGBA4"},
      {GL_RGB5_A1, "GL_RGB5_A1"},
      {GL_ALPHA8_EXT, "GL_ALPHA8_EXT"},
      {GL_LUMINANCE8_EXT, "GL_LUMINANCE8_EXT"},
      {GL_LUMINANCE8_ALPHA8_EXT, "GL_LUMINANCE8_ALPHA8_EXT"},
      {GL_RGB8_OES, "GL_RGB8_OES"},
      {GL_RGBA8_OES, "GL_RGBA8_OES"},
      {GL_R8, "GL_R8"},
      {GL_R8_SNORM, "GL_R8_SNORM"},
      {GL_R16F, "GL_R16F"},
      {GL_R32F, "GL_R32F"},
      {GL_R8UI, "GL_R8UI"},
      {GL_R8I, "GL_R8I"},
      {GL_R16UI, "GL_R16UI"},
      {GL_R16I, "GL_R16I"},
      {GL_R32UI, "GL_R32UI"},
      {GL_R32I, "GL_R32I"},
      {GL_RG8, "GL_RG8"},
      {GL_RG8_SNORM, "GL_RG8_SNORM"},
      {GL_RG16F, "GL_RG16F"},
      {GL_RG32F, "GL_RG32F"},
      {GL_RG8UI, "GL_RG8UI"},
      {GL_RG8I, "GL_RG8I"},
      {GL_RG16UI, "GL_RG16UI"},
      {GL_RG16I, "GL_RG16I"},
      {GL_RG32UI, "GL_RG32UI"},
      {GL_RG32I, "GL_RG32I"},
      {GL_RGB8, "GL_RGB8"},
      {GL_SRGB8, "GL_SRGB8"},
      {GL_RGB8_SNORM, "GL_RGB8_SNORM"},
      {GL_R11F_G11F_B10F, "GL_R11F_G11F_B10F"},
      {GL_RGB9_E5, "GL_RGB9_E5"},
      {GL_RGB16F, "GL_RGB16F"},
      {GL_RGB32F, "GL_RGB32F"},
      {GL_RGB8UI, "GL_RGB8UI"},
      {GL_RGB8I, "GL_RGB8I"},
      {GL_RGB16UI, "GL_RGB16UI"},
      {GL_RGB16I, "GL_RGB16I"},
      {GL_RGB32UI, "GL_RGB32UI"},
      {GL_RGB32I, "GL_RGB32I"},
      {GL_RGBA8, "GL_RGBA8"},
      {GL_SRGB8_ALPHA8, "GL_SRGB8_ALPHA8"},
      {GL_RGBA8_SNORM, "GL_RGBA8_SNORM"},
      {GL_RGB10_A2, "GL_RGB10_A2"},
      {GL_RGBA16F, "GL_RGBA16F"},
      {GL_RGBA32F, "GL_RGBA32F"},
      {GL_RGBA8UI, "GL_RGBA8UI"},
      {GL_RGBA8I, "GL_RGBA8I"},
      {GL_RGB10_A2UI, "GL_RGB10_A2UI"},
      {GL_RGBA16UI, "GL_RGBA16UI"},
      {GL_RGBA16I, "GL_RGBA16I"},
      {GL_RGBA32UI, "GL_RGBA32UI"},
      {GL_RGBA32I, "GL_RGBA32I"},
      {GL_DEPTH_COMPONENT16, "GL_DEPTH_COMPONENT16"},
      {GL_DEPTH_COMPONENT24, "GL_DEPTH_COMPONENT24"},
      {GL_DEPTH_COMPONENT32F, "GL_DEPTH_COMPONENT32F"},
      {GL_DEPTH24_STENCIL8, "GL_DEPTH24_STENCIL8"},
      {GL_DEPTH32F_STENCIL8, "GL_DEPTH32F_STENCIL8"},
      {GL_COMPRESSED_R11_EAC, "GL_COMPRESSED_R11_EAC"},
      {GL_COMPRESSED_SIGNED_R11_EAC, "GL_COMPRESSED_SIGNED_R11_EAC"},
      {GL_COMPRESSED_RG11_EAC, "GL_COMPRESSED_RG11_EAC"},
      {GL_COMPRESSED_SIGNED_RG11_EAC, "GL_COMPRESSED_SIGNED_RG11_EAC"},
      {GL_COMPRESSED_RGB8_ETC2, "GL_COMPRESSED_RGB8_ETC2"},
      {GL_COMPRESSED_SRGB8_ETC2, "GL_COMPRESSED_SRGB8_ETC2"},
      {GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
       "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2"},
      {GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
       "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2"},
      {GL_COMPRESSED_RGBA8_ETC2_EAC, "GL_COMPRESSED_RGBA8_ETC2_EAC"},
      {GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,
       "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureMagFilterMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NEAREST, "GL_NEAREST"}, {GL_LINEAR, "GL_LINEAR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureMinFilterMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NEAREST, "GL_NEAREST"},
      {GL_LINEAR, "GL_LINEAR"},
      {GL_NEAREST_MIPMAP_NEAREST, "GL_NEAREST_MIPMAP_NEAREST"},
      {GL_LINEAR_MIPMAP_NEAREST, "GL_LINEAR_MIPMAP_NEAREST"},
      {GL_NEAREST_MIPMAP_LINEAR, "GL_NEAREST_MIPMAP_LINEAR"},
      {GL_LINEAR_MIPMAP_LINEAR, "GL_LINEAR_MIPMAP_LINEAR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_MAG_FILTER, "GL_TEXTURE_MAG_FILTER"},
      {GL_TEXTURE_MIN_FILTER, "GL_TEXTURE_MIN_FILTER"},
      {GL_TEXTURE_WRAP_S, "GL_TEXTURE_WRAP_S"},
      {GL_TEXTURE_WRAP_T, "GL_TEXTURE_WRAP_T"},
      {GL_TEXTURE_BASE_LEVEL, "GL_TEXTURE_BASE_LEVEL"},
      {GL_TEXTURE_COMPARE_FUNC, "GL_TEXTURE_COMPARE_FUNC"},
      {GL_TEXTURE_COMPARE_MODE, "GL_TEXTURE_COMPARE_MODE"},
      {GL_TEXTURE_IMMUTABLE_FORMAT, "GL_TEXTURE_IMMUTABLE_FORMAT"},
      {GL_TEXTURE_IMMUTABLE_LEVELS, "GL_TEXTURE_IMMUTABLE_LEVELS"},
      {GL_TEXTURE_MAX_LEVEL, "GL_TEXTURE_MAX_LEVEL"},
      {GL_TEXTURE_MAX_LOD, "GL_TEXTURE_MAX_LOD"},
      {GL_TEXTURE_MIN_LOD, "GL_TEXTURE_MIN_LOD"},
      {GL_TEXTURE_WRAP_R, "GL_TEXTURE_WRAP_R"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TEXTURE_2D, "GL_TEXTURE_2D"},
      {GL_TEXTURE_CUBE_MAP_POSITIVE_X, "GL_TEXTURE_CUBE_MAP_POSITIVE_X"},
      {GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "GL_TEXTURE_CUBE_MAP_NEGATIVE_X"},
      {GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "GL_TEXTURE_CUBE_MAP_POSITIVE_Y"},
      {GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y"},
      {GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "GL_TEXTURE_CUBE_MAP_POSITIVE_Z"},
      {GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureUsage(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_NONE, "GL_NONE"},
      {GL_FRAMEBUFFER_ATTACHMENT_ANGLE, "GL_FRAMEBUFFER_ATTACHMENT_ANGLE"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTextureWrapMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_CLAMP_TO_EDGE, "GL_CLAMP_TO_EDGE"},
      {GL_MIRRORED_REPEAT, "GL_MIRRORED_REPEAT"},
      {GL_REPEAT, "GL_REPEAT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTransformFeedbackBindTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_TRANSFORM_FEEDBACK, "GL_TRANSFORM_FEEDBACK"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringTransformFeedbackPrimitiveMode(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_POINTS, "GL_POINTS"},
      {GL_LINES, "GL_LINES"},
      {GL_TRIANGLES, "GL_TRIANGLES"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringUniformBlockParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNIFORM_BLOCK_BINDING, "GL_UNIFORM_BLOCK_BINDING"},
      {GL_UNIFORM_BLOCK_DATA_SIZE, "GL_UNIFORM_BLOCK_DATA_SIZE"},
      {GL_UNIFORM_BLOCK_NAME_LENGTH, "GL_UNIFORM_BLOCK_NAME_LENGTH"},
      {GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS"},
      {GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
       "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES"},
      {GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
       "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER"},
      {GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER,
       "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringUniformParameter(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_UNIFORM_SIZE, "GL_UNIFORM_SIZE"},
      {GL_UNIFORM_TYPE, "GL_UNIFORM_TYPE"},
      {GL_UNIFORM_NAME_LENGTH, "GL_UNIFORM_NAME_LENGTH"},
      {GL_UNIFORM_BLOCK_INDEX, "GL_UNIFORM_BLOCK_INDEX"},
      {GL_UNIFORM_OFFSET, "GL_UNIFORM_OFFSET"},
      {GL_UNIFORM_ARRAY_STRIDE, "GL_UNIFORM_ARRAY_STRIDE"},
      {GL_UNIFORM_MATRIX_STRIDE, "GL_UNIFORM_MATRIX_STRIDE"},
      {GL_UNIFORM_IS_ROW_MAJOR, "GL_UNIFORM_IS_ROW_MAJOR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringValueBufferTarget(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_SUBSCRIBED_VALUES_BUFFER_CHROMIUM,
       "GL_SUBSCRIBED_VALUES_BUFFER_CHROMIUM"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringVertexAttribIType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BYTE, "GL_BYTE"},   {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_SHORT, "GL_SHORT"}, {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_INT, "GL_INT"},     {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringVertexAttribType(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_BYTE, "GL_BYTE"},
      {GL_UNSIGNED_BYTE, "GL_UNSIGNED_BYTE"},
      {GL_SHORT, "GL_SHORT"},
      {GL_UNSIGNED_SHORT, "GL_UNSIGNED_SHORT"},
      {GL_FLOAT, "GL_FLOAT"},
      {GL_INT, "GL_INT"},
      {GL_UNSIGNED_INT, "GL_UNSIGNED_INT"},
      {GL_HALF_FLOAT, "GL_HALF_FLOAT"},
      {GL_INT_2_10_10_10_REV, "GL_INT_2_10_10_10_REV"},
      {GL_UNSIGNED_INT_2_10_10_10_REV, "GL_UNSIGNED_INT_2_10_10_10_REV"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringVertexAttribute(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED"},
      {GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
       "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING"},
      {GL_VERTEX_ATTRIB_ARRAY_ENABLED, "GL_VERTEX_ATTRIB_ARRAY_ENABLED"},
      {GL_VERTEX_ATTRIB_ARRAY_SIZE, "GL_VERTEX_ATTRIB_ARRAY_SIZE"},
      {GL_VERTEX_ATTRIB_ARRAY_STRIDE, "GL_VERTEX_ATTRIB_ARRAY_STRIDE"},
      {GL_VERTEX_ATTRIB_ARRAY_TYPE, "GL_VERTEX_ATTRIB_ARRAY_TYPE"},
      {GL_CURRENT_VERTEX_ATTRIB, "GL_CURRENT_VERTEX_ATTRIB"},
      {GL_VERTEX_ATTRIB_ARRAY_INTEGER, "GL_VERTEX_ATTRIB_ARRAY_INTEGER"},
      {GL_VERTEX_ATTRIB_ARRAY_DIVISOR, "GL_VERTEX_ATTRIB_ARRAY_DIVISOR"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

std::string GLES2Util::GetStringVertexPointer(uint32_t value) {
  static const EnumToString string_table[] = {
      {GL_VERTEX_ATTRIB_ARRAY_POINTER, "GL_VERTEX_ATTRIB_ARRAY_POINTER"},
  };
  return GLES2Util::GetQualifiedEnumString(string_table,
                                           arraysize(string_table), value);
}

#endif  // GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_UTILS_IMPLEMENTATION_AUTOGEN_H_
