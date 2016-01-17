#include "CommonPyFunc.h"
#include "../common/customconsole.h"
#include <boost/locale/conversion.hpp>
#include <boost/locale/encoding.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


void cwrite(const char *sMsg, const char *sTextColor, const char *sBackColor)  //py²ãutf8, c++²ãgbk
{
	printc(boost::locale::conv::between(sMsg, "gbk", "utf8").c_str(), sTextColor, sBackColor);
}

void mkdir(const char *path)
{
	boost::filesystem::create_directories(boost::locale::conv::between(path, "gbk", "utf8"));
}

