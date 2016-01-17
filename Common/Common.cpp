#include "Common.h"
#include <string>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>
#include <boost/locale/conversion.hpp>
#include <boost/locale/encoding.hpp>
#include <iostream>
using namespace std;


std::string operator * (const std::string &str, int times)
{
	string result;
	result.reserve(str.length() * times);		// 避免重复的重新分配
	for (int i = 0; i < times; i++)
		result.append(str);
	return result;
}


std::string ParserINI(const char* filename, const char* key)
{
	string sResult;
	try
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(filename, pt);
		sResult = pt.get<std::string>(key);
	}
	catch (std::exception &ex)
	{
		std::cout << "Error:" << ex.what() << std::endl;
		sResult.clear();
	}
	return sResult;
}

std::string GBK_TO_UTF8(const char* text)
{
	return boost::locale::conv::between(text, "utf8", "gbk");
}

std::string UTF8_TO_GBK(const char* text)
{
	return boost::locale::conv::between(text, "gbk", "utf8");
}

