#pragma once

//饿汉模式：即无论是否调用该类的实例，在程序开始时就会产生一个该类的实例，并在以后仅返回此实例。
//由静态初始化实例保证其线程安全性，WHY？因为静态实例初始化在程序开始时进入主函数之前就由主线程以单线程方式完成了初始化，不必担心多线程问题。
//故在性能需求较高时，应使用这种模式，避免频繁的锁争夺。

class SingletonStatic
{
private:
	static const SingletonStatic* m_instance;
	SingletonStatic() {}
public:
	static const SingletonStatic* getInstance()
	{
		return m_instance;
	}
};

//外部初始化 before invoke main
const SingletonStatic* SingletonStatic::m_instance = new SingletonStatic;


