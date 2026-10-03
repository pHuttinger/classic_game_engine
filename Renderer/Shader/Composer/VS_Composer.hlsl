//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "Composer.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
  PS_INPUT output;

  output.position = input.position;
  output.texcoord = input.texcoord;
	
  return output;
}