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
#include "ThreeClearHelper.h"

class NetMatrix
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
	bool Change(Grid first, Grid second);

private:
	// �洢����
	std::vector<std::vector<Grid>> m_vecNet;
};