#pragma once
#include <string>

void SetEnviromentValue(std::string sKey, std::string sValue);  // ��ʱ��������ĸ��д����Ա��������ĸСд
void AddEnviromentValue(std::string sKey, std::string sValue);	// ׷�ӻ�������

std::string GetCurrentPath();
void SetProgramName(std::string name);
std::string GetProgramName();
