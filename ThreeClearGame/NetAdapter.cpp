#include "stdafx.h"
#include "NetAdapter.h"

CNetAdapter::CNetAdapter()
{

}

CNetAdapter::~CNetAdapter()
{

}

// Ԫ�ظ���
int CNetAdapter::getCount()
{
	return NET_ROW_NUMBER * NET_COL_NUMBER;
}

// ���ý�����ʽ
void CNetAdapter::getView(int position, SWindow * pItem,
	pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0) {
		pItem->InitFromXml(xmlTemplate);
	}
	SButton* pButton = pItem->FindChildByName2<SButton>(L"btn_grid");
	assert(pItem);
	pItem->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
		Subscriber(&CNetAdapter::OnButtonClick, this));
}

// ��ť���
bool CNetAdapter::OnButtonClick(EventArgs* pEvt)
{
	// SMessageBox(NULL, L"�������", L"��ʾ", MB_OK);
	SWindow* pTemplate = sobj_cast<SWindow>(pEvt->sender);
	assert(pTemplate);
	SButton* pButton = pTemplate->FindChildByName2<SButton>(L"btn_grid");
	assert(pButton);
	pButton->SetCheck(TRUE);
	return true;
}