#include "stdafx.h"
#include "NetAdapter.h"

CNetAdapter::CNetAdapter(std::vector<std::vector<Grid>> vecNet)
{
	m_vecNet = vecNet;
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
	// �󶨰�ť�¼�
	SButton* pButton = pItem->FindChildByName2<SButton>(L"btn_grid");
	assert(pItem);
	pItem->GetEventSet()->subscribeEvent(SOUI::EVT_CMD,
		Subscriber(&CNetAdapter::OnButtonClick, this));
	// ��ʾͼ��ť
	std::pair<int, int> grid = covertPostion2Grid(position);
	switch (m_vecNet[grid.first][grid.second].status)
	{
	// ��
	case Grid_Star:
		pButton->SetAttribute(L"skin", SKIN_STAR);
	break;
	// ��
	case Grid_Heart:
		pButton->SetAttribute(L"skin", SKIN_HEART);
	break;
	// ��
	case Grid_Sword:
		pButton->SetAttribute(L"skin", SKIN_SWORD);
	break;
	// ��
	case Grid_SHIELD:
		pButton->SetAttribute(L"skin", SKIN_SHIELD);
	break;
	}
	pButton->RequestRelayout();
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

// �� tileview �� position ת��Ϊ Grid ����
std::pair<int, int> CNetAdapter::covertPostion2Grid(int position)
{
	return std::make_pair<int, int>(position / NET_COL_NUMBER, position % NET_COL_NUMBER);
}