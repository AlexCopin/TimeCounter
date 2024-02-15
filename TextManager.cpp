#include "TextManager.h"


void TextManager::AddText(HDC hdc, const TCHAR text[], int8_t textSize /* = DEFAULT_TEXT_SIZE*/)
{
  TextOut(hdc, textSize, currentYOffset, text, _tcslen(text));
  currentYOffset += textSize*3 + offsetY;
}
