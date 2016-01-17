#include "PyEngine.h"
#include "../common/common.h"
#include "../common/sys.h"
#include "commonpyfunc.h"
#include <boost/python.hpp>
#include <Python.h>
#include <boost/detail/lightweight_test.hpp>
#include "pywrap.h"
#include <iostream>
using namespace std;

namespace python = boost::python;

template <class T>
void safe_py_execute(T functor);


PyEngine::PyEngine()
{
	cout << "construct pyengine " << this << endl;
	init();
}


PyEngine::~PyEngine()
{
	//the Py_Finalize() call shuts the interpreter down
	Py_Finalize();
	wchar_t *program = Py_DecodeLocale(GetProgramName().c_str(), NULL);
	PyMem_RawFree(program);
	cout << "destruct  pyengine " << this << endl;
}


void PyEngine::init()
{
	wchar_t *program = Py_DecodeLocale(GetProgramName().c_str(), NULL);
	if (program == NULL) {
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}
	//The Py_SetProgramName() function should be called before Py_Initialize() to inform the interpreter about paths to Python run - time libraries.
	Py_SetProgramName(program);  /* optional but recommended */

	register_py_module();

	Py_Initialize();
	PyRun_SimpleString( "import sys\n" 
		"print(sys.version)\n"
		"print('python start!')");

}


void PyEngine::register_py_module()  // 在Py_Initialize之前调用
{
	registerPyFuncs();
}


string PyEngine::script_path()
{
	return ParserINI("config.ini", "script.pyscript");
}


void eval_py_expr(const char *expression, std::string *result)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object oResult = python::eval(expression, oPyMainNamespace);
	*result = python::extract<std::string>(oResult) BOOST_EXTRACT_WORKAROUND;
}


string PyEngine::eval(const char *expression)  // eval函数可以计算Python表达式，并返回结果
{
	std::string sValue = "";
	safe_py_execute(boost::bind(eval_py_expr, expression, &sValue));
	return sValue;
}


void exec_py_code(const char *code)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object oResult = python::exec(code, oPyMainNamespace);
}


void PyEngine::exec(const char *code)  // 通过exec可以执行动态Python代码，exec不返回结果
{
	safe_py_execute(boost::bind(exec_py_code, code));
}


void exec_py_file(const char *filename)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object result = python::exec_file(filename, oPyMainNamespace, oPyMainNamespace);
}


void PyEngine::exec_file(const char *filename)
{
	safe_py_execute(boost::bind(exec_py_file, filename));
}


template <class T>
void safe_py_execute(T functor)
{
	void check_pyerr(bool pyerr_expected = false);
	if (python::handle_exception(functor))
	{
		check_pyerr();
	}
};


void check_pyerr(bool pyerr_expected = false)
{
	if (PyErr_Occurred())
	{
		if (!pyerr_expected)
		{
			//BOOST_ERROR("Python错误");
			if (PyErr_ExceptionMatches(PyExc_SyntaxError))
			{
				void log_python_exception();
				log_python_exception();
			}
			else
			{
				PyErr_Print();
			}
		}
		else
			PyErr_Clear();
	}
	else
		BOOST_ERROR("一个C++表达式被抛出，这里没有表达式句柄被注册r.");
}


std::string strErrorMsg;

void log_python_exception()
{
	if (!Py_IsInitialized())
	{
		strErrorMsg = "Python运行环境没有初始化!";
		return;
	}
	if (PyErr_Occurred() != NULL)
	{
		PyObject *type_obj, *value_obj, *traceback_obj;
		PyErr_Fetch(&type_obj, &value_obj, &traceback_obj);
		if (value_obj == NULL)
			return;

		strErrorMsg.clear();
		PyErr_NormalizeException(&type_obj, &value_obj, 0);
		if (PyUnicode_Check(PyObject_Str(value_obj)))
		{
			strErrorMsg = _PyUnicode_AsString(PyObject_Str(value_obj));
		}

		if (traceback_obj != NULL)
		{
			strErrorMsg += "\nTraceback:";
			PyObject *pModuleName = PyUnicode_FromString("traceback");
			PyObject *pTraceModule = PyImport_Import(pModuleName);
			Py_XDECREF(pModuleName);
			if (pTraceModule != NULL)
			{
				PyObject *pModuleDict = PyModule_GetDict(pTraceModule);
				if (pModuleDict != NULL)
				{
					PyObject *pFunc = PyDict_GetItemString(pModuleDict, "format_exception");
					if (pFunc != NULL)
					{
						PyObject *errList = PyObject_CallFunctionObjArgs(pFunc, type_obj, value_obj, traceback_obj, NULL);
						if (errList != NULL)
						{
							Py_ssize_t listSize = PyList_Size(errList);
							for (Py_ssize_t i = 0; i < listSize; ++i)
							{
								strErrorMsg += _PyUnicode_AsString(PyList_GetItem(errList, i));
							}
						}
					}
				}
				Py_XDECREF(pTraceModule);
			}
		}
		Py_XDECREF(type_obj);
		Py_XDECREF(value_obj);
		Py_XDECREF(traceback_obj);
	}
	strErrorMsg.append("\n");
	cwrite(strErrorMsg.c_str(), "red_h");
}

