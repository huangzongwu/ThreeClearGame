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

class CNetAdapter : public SAdapterBase
{
public:
	CNetAdapter();
	virtual ~CNetAdapter();
	
	// Ԫ�ظ���
	int getCount() override;

	// ���ý�����ʽ
	void getView(int position, SWindow * pItem, 
		pugi::xml_node xmlTemplate) override;

	// ��ť���
	bool OnButtonClick(EventArgs* pEvt);
};