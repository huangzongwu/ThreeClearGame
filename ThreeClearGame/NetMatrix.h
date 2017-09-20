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

class NetMatrix : public ChangeEvent
{
public:
	NetMatrix();
	virtual ~NetMatrix();

public:
	// ��ȡ�ڲ����ݽṹ
	std::vector<std::vector<Grid>> GetNet();

	// �������ݽṹ
	void SetNet(std::vector<std::vector<Grid>> vecNet);

	// ��ʼ���������
	// 1. �����������ͼ��ť
	// 2. ������ 3 ���������ϸ�������
	void Init();

	// ������������
	bool Change(PosPoint pre, PosPoint cur) override;

	// ���������������������䣩
	// �����Ƿ�������Զ�����
	bool AutoDelete();

	// ����ˢ���¼�ָ��
	void SetEvent(RefreshEvent* event);

	// ��ȡ����
	int GetScore();

	// ��������һ������
	// �����Ҫ�������䣬�����һ���������䲢���� true
	// �������Ҫ�򷵻� false
	bool LandOneGrid();

	// ����������
	void AddRandomGrid();

protected:
	// �������һ������
	void RandomNet(std::vector<std::vector<Grid>>& vecNet);

	// �Ƿ�Ϸ�����
	bool ValidNet(std::vector<std::vector<Grid>> vecNet);

	// ����������
	// point ���� point ���״̬������ͬ��
	// vecNet ����״̬
	std::vector<PosPoint> GetCancelPoints(PosPoint point, std::vector<std::vector<Grid>> vecNet);

private:
	// �洢����
	std::vector<std::vector<Grid>> m_vecNet;
	// ˢ���¼�
	RefreshEvent* m_event;
	// ��ǰ����
	INT m_nScore;
};