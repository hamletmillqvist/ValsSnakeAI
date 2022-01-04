#pragma once

#include <vector>
#include <string>

#ifndef vsai_stringdef
#define String std::wstring
#define Str(str) L ## str
#define toStr(i) std::to_wstring(i)
#define vsai_stringdef 1
#endif

// Splits a wstring using the designated seperator.
std::vector<String> splitString(String& str, char seperator);

// Converts a character from HEXADECIMAL to DECIMAL.
int const hexToInt(wchar_t& symbol);

// Converts a value into HEXADECIMAL.
char const intToHex(int& value);
