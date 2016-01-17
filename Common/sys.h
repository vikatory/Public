#pragma once
#include <string>

void SetEnviromentValue(std::string sKey, std::string sValue);  // 暂时函数首字母大写，成员函数首字母小写
void AddEnviromentValue(std::string sKey, std::string sValue);	// 追加环境变量

std::string GetCurrentPath();
void SetProgramName(std::string name);
std::string GetProgramName();
