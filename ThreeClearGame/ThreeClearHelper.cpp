#include <cstdlib>
#include <time.h>
#include "stdafx.h"
#include "ThreeClearHelper.h"

// ��ʼ���������
int TreeClearHelper::seed = time(0);

TreeClearHelper::TreeClearHelper()
{

}

TreeClearHelper* TreeClearHelper::Instance()
{
	static std::shared_ptr<TreeClearHelper> spMgr;
	if (!spMgr.get()) {
		spMgr.reset(new TreeClearHelper());
	}
	return spMgr.get();
}

TreeClearHelper::~TreeClearHelper()
{

}

// ��ȡ�����
// modular  �������������Χ��0��ʼ
// excepts  ���������������Χ�ڵĲ�����������������
int TreeClearHelper::produceRadomNumber(int modular, std::vector<int> excepts)
{
	// �жϣ�excepts �Ƿ�ռ�������е� modular ��ֵ
	if (modular <= excepts.size()) return -1;
	// ����һ��ֵ
	std::srand(seed++);
	int random = std::rand() % modular;
	// �жϸ�ֵ�Ƿ��޳������ǣ�����ǵĻ�����������һ���������ֱ�����ɵ������
	// ֵ���ڱ��޳�ֵ�ķ�Χ��֮�󣬲�ȷ��������ֵ
	while (std::find(excepts.cbegin(), excepts.cend(), random) != excepts.cend()) {
		std::srand(seed++);
		random = std::rand() % modular;
	}
	return random;
}