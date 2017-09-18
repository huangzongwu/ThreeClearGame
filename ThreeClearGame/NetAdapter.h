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
#include "ThreeClearHelper.h"

class CNetAdapter : public SAdapterBase
{
public:
	CNetAdapter(std::vector<std::vector<Grid>> vecNet);
	virtual ~CNetAdapter();
	
	// Ԫ�ظ���
	int getCount() override;

	// ���ý�����ʽ
	void getView(int position, SWindow * pItem, 
		pugi::xml_node xmlTemplate) override;

	// ��ť���
	bool OnButtonClick(EventArgs* pEvt);

protected:
	// �� tileview �� position ת��Ϊ Grid ����
	std::pair<int, int> covertPostion2Grid(int position);

private:
	std::vector<std::vector<Grid>> m_vecNet;
};