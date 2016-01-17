#pragma once

//����ģʽ���������Ƿ���ø����ʵ�����ڳ���ʼʱ�ͻ����һ�������ʵ���������Ժ�����ش�ʵ����
//�ɾ�̬��ʼ��ʵ����֤���̰߳�ȫ�ԣ�WHY����Ϊ��̬ʵ����ʼ���ڳ���ʼʱ����������֮ǰ�������߳��Ե��̷߳�ʽ����˳�ʼ�������ص��Ķ��߳����⡣
//������������ϸ�ʱ��Ӧʹ������ģʽ������Ƶ���������ᡣ

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

//�ⲿ��ʼ�� before invoke main
const SingletonStatic* SingletonStatic::m_instance = new SingletonStatic;


