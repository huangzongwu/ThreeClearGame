#include <cstdlib>
#include <time.h>
#include "stdafx.h"
#include "MyHelper.h"

MyHelper::MyHelper()
{
	std::srand(time(0));
}

MyHelper* MyHelper::Instance()
{
	static std::shared_ptr<MyHelper> spMgr;
	if (!spMgr.get()) {
		spMgr.reset(new MyHelper());
	}
	return spMgr.get();
}

MyHelper::~MyHelper()
{

}

// ��ȡ�����
// modular  �������������Χ��0��ʼ
// excepts  ���������������Χ�ڵĲ�����������������
int MyHelper::Random(int modular, std::vector<int> excepts)
{
	// �жϣ�excepts �Ƿ�ռ�������е� modular ��ֵ
	if (modular <= excepts.size()) return -1;
	// ����һ��ֵ
	int random = std::rand() % modular;
	// �жϸ�ֵ�Ƿ��޳������ǣ�����ǵĻ�����������һ���������ֱ�����ɵ������
	// ֵ���ڱ��޳�ֵ�ķ�Χ��֮�󣬲�ȷ��������ֵ
	while (std::find(excepts.cbegin(), excepts.cend(), random) != excepts.cend()) {
		random = std::rand() % modular;
	}
	return random;
}