/*******************************************************************   
 *  �ļ�����: NetMatrix.h
 *  ��Ҫ����: ����������Ϸ�е�������Ϣ����
 *   
 *  ��������: 2017-9-18
 *  ��������: ��Ө
 *  ˵������: 
 *   
 *  �޸�����: 
 *  ��������: 
 *  ˵������: 
 ******************************************************************/  
#pragma once
#include "MyHelper.h"

class NetEvent {
public:
	// ��������
	virtual bool Change(PosPoint pre, PosPoint cur) = 0;
};

class NetMatrix : public NetEvent
{
public:
	NetMatrix();
	virtual ~NetMatrix();

public:
	// ��ȡ�ڲ����ݽṹ
	std::vector<std::vector<Grid>> getNet();

	// ��ʼ���������
	// 1. �����������ͼ��ť
	// 2. ������ 3 ���������ϸ�������
	void Init();

	// ��������
	bool Change(PosPoint pre, PosPoint cur) override;

protected:
	// �������һ������
	void RandomNet(std::vector<std::vector<Grid>>& vecNet);

	// �Ƿ�Ϸ�����
	bool ValidNet(std::vector<std::vector<Grid>> vecNet);

private:
	// �洢����
	std::vector<std::vector<Grid>> m_vecNet;
	// �¼�ָ��
	NetEvent* m_event;
};