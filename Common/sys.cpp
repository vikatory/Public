#include "sys.h"
#include "platform.h"
#include <boost/filesystem.hpp>
#include <iostream>

#if PE_PLATFORM == PLATFORM_WIN32
#include <windows.h>
#include<tchar.h>
#endif

using namespace std;
namespace bf = boost::filesystem;				// 简单别名


#define PATH_LENGTH 1024


void SetEnviromentValue(string sKey, string sValue)
{
#if PE_PLATFORM == PLATFORM_WIN32
	WCHAR wsKey[PATH_LENGTH];
	memset(wsKey, 0, sizeof(wsKey));
	MultiByteToWideChar(CP_ACP, 0, sKey.c_str(), (int)strlen(sKey.c_str()) + 1, wsKey, int(sizeof(wsKey) / sizeof(wsKey[0])));
	WCHAR wsValue[PATH_LENGTH];
	memset(wsValue, 0, sizeof(wsValue));
	MultiByteToWideChar(CP_ACP, 0, sValue.c_str(), (int)strlen(sValue.c_str()) + 1, wsValue, int(sizeof(wsValue) / sizeof(wsValue[0])));
	SetEnvironmentVariable(wsKey, wsValue);
#endif
}

void AddEnviromentValue(string sKey, string sValue)
{
#if PE_PLATFORM == PLATFORM_WIN32
	WCHAR wsKey[PATH_LENGTH];
	memset(wsKey, 0, sizeof(wsKey));
	MultiByteToWideChar(CP_ACP, 0, sKey.c_str(), (int)strlen(sKey.c_str()) + 1, wsKey, int(sizeof(wsKey) / sizeof(wsKey[0])));

	WCHAR wsOldValue[PATH_LENGTH];
	GetEnvironmentVariable(wsKey, wsOldValue, sizeof(wsOldValue));

	WCHAR wsValue[PATH_LENGTH];
	memset(wsValue, 0, sizeof(wsValue));
	MultiByteToWideChar(CP_ACP, 0, sValue.c_str(), (int)strlen(sValue.c_str()) + 1, wsValue, int(sizeof(wsValue) / sizeof(wsValue[0])));

	wstring wsNewValue = wstring(wsOldValue) + wstring(L";") + wstring(wsValue);
	SetEnvironmentVariable(wsKey, wsNewValue.c_str());
#endif
}


std::string GetCurrentPath()
{
	bf::path oCurPath = bf::current_path();		// 取得当前目录, 一般是cpp文件夹，若把exe拿出来运行，就是exe所在的文件夹
	std::string sCurPath = oCurPath.string();
	return sCurPath;
}


static string g_ProgramName = "";


void SetProgramName(string name)
{
	g_ProgramName = name;
}


string GetProgramName()
{
	return g_ProgramName;
}