//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

//----------------------------------------------------
// C++
//----------------------------------------------------
#ifdef __cplusplus

#include <Common/Inc/Common.h>

#define float2   glm::vec2
#define float3   glm::vec3
#define float4   glm::vec4
#define float4x4 glm::mat4

#define FINAL final

#define PADDING(num) float m_padding##num;

//----------------------------------------------------
// HLSL
//----------------------------------------------------
#else

#define FINAL

#define PADDING(num)

#endif

