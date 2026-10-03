//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#undef UNICODE

//----------------------------------------------------
// General
//----------------------------------------------------
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include <expected>
#include <functional>
#include <source_location>
#include <windows.h>

#ifdef _DEBUG
#include <intrin.h>
#include <iostream>
#endif

#include "ComPtr.h"

//----------------------------------------------------
// GLM
//----------------------------------------------------
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

//----------------------------------------------------
// General
//----------------------------------------------------
namespace cge
{
enum class ETerminalColor
{
  White,
  Red,
  Green,
  Blue,
  Yellow
};

void Init();
void WriteImpl(std::ostream& stream, const std::string& text, ETerminalColor color);
void Write(const std::string& text, ETerminalColor color = ETerminalColor::White);
void WriteError(const std::string& text, const std::string& file, const uint32_t line);
void ErrorExit(const std::string& text);
bool WasErrorRaised();
bool IsDebugging();

//----------------------------------------------------
// TResult
//----------------------------------------------------
struct TResult final
{
  TResult();
  TResult(const bool isOK, const char* text, const char* file, const int line);
  virtual ~TResult() = default;

  bool IsOK() const;
  bool IsError() const;
  std::string GetText() const;

  static TResult Okay();
  static TResult Error(const std::string& msg, std::source_location sourceLocation = std::source_location::current());

private:

  bool        m_isOK = false;
  std::string m_text;
  std::string m_file;
  uint16_t    m_line = 0;
};

//----------------------------------------------------
// TDataHandle
//----------------------------------------------------
struct TDataHandle final
{
  size_t m_size  = 0U;
  void*  m_pData = nullptr;
};
}

//----------------------------------------------------

#ifdef _DEBUG
#define CGE_INIT()
#else
#define CGE_INIT() cge::Init()
#endif

#define CGE_ERROR(msg) cge::WriteError(msg, __FILE__, __LINE__)
#ifdef _DEBUG
#define CGE_INFO(msg) cge::Write(msg, cge::ETerminalColor::Blue)
#define CGE_MILESTONE(msg) cge::Write(msg, cge::ETerminalColor::Green)
#define CGE_WARN(msg) cge::Write(msg, cge::ETerminalColor::Yellow)
#else
#define CGE_INFO(msg)
#define CGE_MILESTONE(msg)
#define CGE_WARN(msg)
#endif

//----------------------------------------------------

#ifdef _DEBUG
#define CGE_DEBUG_BREAK() __debugbreak()
#else
#define CGE_DEBUG_BREAK()
#endif

//----------------------------------------------------

#define CGE_TRY(fct) \
if (TResult result = fct; result.IsError()) \
{ \
  if(!cge::WasErrorRaised()) \
  { \
    CGE_ERROR(result.GetText()); \
    CGE_DEBUG_BREAK(); \
  } \
  return result; \
}

//----------------------------------------------------

#define CGE_HRESULT_CHECK(hr, msg) \
if(hr != S_OK) return cge::TResult::Error(msg);