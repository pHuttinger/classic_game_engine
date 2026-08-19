//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Common.h"

namespace cge
{
//----------------------------------------------------
// Common
//----------------------------------------------------
void CgeInit()
{
  HWND hwnd = GetConsoleWindow();
  ShowWindow(hwnd, SW_HIDE);
}

void CgeWriteImpl(std::ostream& stream, const std::string& text, ETerminalColor color)
{
  auto now = std::chrono::system_clock::now();
  std::string timestamp = std::format("{:%Y-%m-%d %H:%M:%S}", now);

  stream << timestamp << " | ";

  if (color == ETerminalColor::White)
  {
    stream << text << std::endl;
    return;
  }

  std::string start = "\033[";
  std::string end = "\033[0m";

  switch (color)
  {
    case ETerminalColor::Red   : start += "31m"; break;
    case ETerminalColor::Green : start += "32m"; break;
    case ETerminalColor::Blue  : start += "34m"; break;
    case ETerminalColor::Yellow: start += "33m"; break;
  }

  stream << start + text + end << std::endl;
}

void CgeWrite(const std::string& text, ETerminalColor color)
{
#ifdef _DEBUG
  CgeWriteImpl(std::cout, text, color);
#endif
}

void CgeWriteError(const std::string& text, const std::string& file, const uint32_t line)
{
  std::string output = std::format("Error --> '{}' [{}:{}]", text, file, line);
#ifdef _DEBUG
  CgeWriteImpl(std::cerr, output, ETerminalColor::Red);
#else
  MessageBox(NULL, output.c_str(), "Error", MB_OK | MB_ICONERROR);
#endif
}

void CgeErrorExit(const std::string& text)
{
  MessageBox(nullptr, text.c_str(), "Error!", MB_ICONERROR | MB_OK);
  PostQuitMessage(-1);
}

bool CgeWasErrorRaised()
{
  static bool wasErrorRaised = false;
  const bool _wasErrorRaised = wasErrorRaised;
  wasErrorRaised = true;
  return _wasErrorRaised;
}

//----------------------------------------------------
// TResult
//----------------------------------------------------
TResult::TResult()
  : m_isOK(true)
  , m_text("")
  , m_line(0)
{
}

TResult::TResult(const bool isOK, const char* text, const char* file, const int line)
  : m_isOK(isOK)
  , m_text(text)
  , m_file(file)
  , m_line(line)
{
}

bool TResult::IsOK() const
{
  return m_isOK;
}

bool TResult::IsError() const
{
  return !IsOK();
}

std::string TResult::GetText() const
{
  return m_text + "\nFILE: " + m_file + "\nLINE: " + std::to_string(m_line);
}

//static
TResult TResult::Okay()
{
  return TResult();
}

//static
TResult TResult::Error(const std::string& msg, std::source_location sourceLocation)
{
  return TResult(false, msg.c_str(), sourceLocation.file_name(), sourceLocation.line());
}
}