#pragma once
#include <string>

#define RETURN_IF(condition) if(condition) return;

std::string operator * (const std::string &str, int times);
std::string ParserINI(const char* filename, const char* key);
std::string GBK_TO_UTF8(const char* text);
std::string UTF8_TO_GBK(const char* text);


