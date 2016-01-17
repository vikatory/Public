#pragma once
#include <string>

class PyEngine
{
public:
	PyEngine();
	~PyEngine();

	std::string script_path();

	std::string eval(const char *expression);
	void exec(const char *code);
	void exec_file(const char *filename);

private:
	void init();
	void register_py_module();
};

