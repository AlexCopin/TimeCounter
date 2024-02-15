#pragma once
#include <cstdint>
#include <string>

#include "framework.h"


struct Text
{
public:
  std::string Value;

};


class TextManager
{
public:
  static constexpr int8_t DEFAULT_TEXT_SIZE = 5;

  int currentYOffset = 5;
  //Draw methods
  void AddText(HDC hdc, const TCHAR text[], int8_t textSize = DEFAULT_TEXT_SIZE);
private:
  int offsetY = 2;
};
