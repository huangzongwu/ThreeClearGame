#include "stdafx.h"
#include "NetAdapter.h"

CNetAdapter::CNetAdapter(std::vector<std::vector<Grid>> vecNet)
{
	m_vecNet = vecNet;
	m_event = nullptr;
	m_nClickCount = 0;
}

CNetAdapter::~CNetAdapter()
{

}

// ���������¼�
void CNetAdapter::SetEvent(NetEvent* pEvent)
{
	if (pEvent != nullptr) m_event = pEvent;
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
	// ��¼��ǰ��ť��Ϣ
	assert(pItem->GetRoot());
	pItem->GetRoot()->SetUserData(position);
	// ��ʾͼ��ť
	PosPoint point = covertPostion2Grid(position);
	switch (m_vecNet[point.row][point.col].status)
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
	// ��հ�ťѡ��
	pButton->SetCheck(FALSE);
}

// ��ť���
bool CNetAdapter::OnButtonClick(EventArgs* pEvt)
{
	m_nClickCount++;
	SWindow* pTemplate = sobj_cast<SWindow>(pEvt->sender);
	assert(pTemplate);
	SButton* pButton = pTemplate->FindChildByName2<SButton>(L"btn_grid");
	assert(pButton);
	// ����ѡ��
	pButton->SetCheck(TRUE);
	// ��ȡ������Ϣ
	assert(pButton->GetRoot());
	INT position = pButton->GetRoot()->GetUserData();
	PosPoint point = covertPostion2Grid(position);
	SOUI::SStringW strPos;
	strPos.Format(L"���꣨%d��%d�������", point.row, point.col);
	MyHelper::Instance()->WriteLog(strPos);
	if (m_nClickCount == 2) {
		// ������������
		m_event->Change(m_preGrid, point);
		// ��ռ���
		m_nClickCount = 0;
		// ˢ����ʾ
		notifyDataSetChanged();
	} else {
		m_preGrid = point;
	}
	return true;
}

// �� tileview �� position ת��Ϊ Grid ����
PosPoint CNetAdapter::covertPostion2Grid(int position)
{
	return PosPoint(position / NET_COL_NUMBER, position % NET_COL_NUMBER);
}