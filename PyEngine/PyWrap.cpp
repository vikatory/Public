#include "PyWrap.h"
#include <boost/python.hpp>
#include <Python.h>
#include <iostream>
#include "CommonPyFunc.h"

using namespace boost::python;

BOOST_PYTHON_FUNCTION_OVERLOADS(cwrite_overloads, cwrite, 1, 3)

BOOST_PYTHON_MODULE(cm)
{
	def("cwrite", cwrite, cwrite_overloads());
	def("mkdir", mkdir);
}


// 注意编译boost时python的版本
void registerPyFuncs()
{
	// 注册模块到解释器中
	if (PyImport_AppendInittab(const_cast<char*>("cm"),
#if PY_VERSION_HEX >= 0x03000000 
		PyInit_cm
#else 
		initcm
#endif 
		) == -1)
		throw std::runtime_error("把cm作为内建模块加载到解释器失败");
}



