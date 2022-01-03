#pragma once

#include <vector>
#include <string>

#ifndef vsai_stringdef
#define String std::wstring
#define Str(str) L ## str
#define toStr(i) std::to_wstring(i)
#define vsai_stringdef 1
#endif

std::vector<String> splitString(String& str, char seperator);