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


// ע�����boostʱpython�İ汾
void registerPyFuncs()
{
	// ע��ģ�鵽��������
	if (PyImport_AppendInittab(const_cast<char*>("cm"),
#if PY_VERSION_HEX >= 0x03000000 
		PyInit_cm
#else 
		initcm
#endif 
		) == -1)
		throw std::runtime_error("��cm��Ϊ�ڽ�ģ����ص�������ʧ��");
}


