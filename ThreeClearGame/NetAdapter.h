/*******************************************************************   
 *  �ļ�����: NetAdatper.h
 *  ��Ҫ����: ʵ�ֽ����������������ʾ
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

class CNetAdapter : public SAdapterBase
{
public:
	CNetAdapter(std::vector<std::vector<Grid>> vecNet);
	virtual ~CNetAdapter();

	// ������ʾ
	void UpdateNet(std::vector<std::vector<Grid>> vecNet);

	// ���������¼�
	void SetEvent(ChangeEvent* pEvent);
	
	// Ԫ�ظ���
	int getCount() override;

	// ���ý�����ʽ
	void getView(int position, SWindow * pItem, 
		pugi::xml_node xmlTemplate) override;

	// ��ť���
	bool OnButtonClick(EventArgs* pEvt);

protected:
	// �� tileview �� position ת��Ϊ Grid ����
	PosPoint covertPostion2Grid(int position);

private:
	// ����
	std::vector<std::vector<Grid>> m_vecNet;
	// �¼�
	ChangeEvent* m_event;
	// ѡ�м���
	INT m_nClickCount;
	// ��һ����
	PosPoint m_preGrid;
};