#include "stdafx.h"
#include "NetMatrix.h"
#include "MyHelper.h"

NetMatrix::NetMatrix()
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		std::vector<Grid> row;
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			Grid grid(i, j);
			row.push_back(grid);
		}
		m_vecNet.push_back(row);
	}
	m_event = nullptr;
}

NetMatrix::~NetMatrix()
{
	m_vecNet.clear();
}

// ��ȡ�ڲ����ݽṹ
std::vector<std::vector<Grid>> NetMatrix::getNet()
{
	return m_vecNet;
}

// ��ʼ���������
void NetMatrix::Init()
{
	RandomNet(m_vecNet);
	while (!ValidNet(m_vecNet)) RandomNet(m_vecNet);
}

// ��������
bool NetMatrix::Change(PosPoint pre, PosPoint cur)
{
	// ������������
	auto vecNet = m_vecNet;
	std::swap(vecNet[pre.row][pre.col], vecNet[cur.row][cur.col]);
	// ����Ƿ��ܹ���ȥ
	if (!ValidNet(vecNet)) 
		MyHelper::Instance()->WriteLog(L"�����ɹ�!");
	else {
		MyHelper::Instance()->WriteLog(L"����ʧ��!");
		return false;
	}
	// �����ɹ������������Ϣ�������㶼��Ҫ���в�ѯ
	std::vector<PosPoint> prePoints = GetCancelPoints(pre, vecNet);
	std::vector<PosPoint> curPoints = GetCancelPoints(cur, vecNet);
	SOUI::SStringW strPoint, strPointsMsg, strCancelMsg;
	for (auto it = prePoints.begin(); it != prePoints.end(); ++it)
		strPointsMsg += strPoint.Format(L"(%d, %d) ", it->row, it->col);
	for (auto it = curPoints.begin(); it != curPoints.end(); ++it)
		strPointsMsg += strPoint.Format(L"(%d, %d) ", it->row, it->col);
	strCancelMsg.Format(L"���������µ㣺%s", strPointsMsg);
	MyHelper::Instance()->WriteLog(strCancelMsg);
	// ����ɾ���ĵ�Ϊɾ��Ƥ��
	for (int i = 0; i < prePoints.size(); ++i) {
		vecNet[prePoints[i].row][prePoints[i].col].status = Grid_Delete;
	}
	for (int i = 0; i < curPoints.size(); ++i) {
		vecNet[curPoints[i].row][curPoints[i].col].status = Grid_Delete;
	}
	m_vecNet = vecNet;
	m_event->RefreshNet(m_vecNet);
	// TODO: ������������������ƣ����������
	// TODO: ���������������Ȼ�п��������ĵ㣬���������ֱ����������Ϊֹ
	return true;
}

// ����ˢ���¼�ָ��
void NetMatrix::SetEvent(RefreshEvent* event)
{
	if (event != nullptr) m_event = event;
}

// �������һ������
void NetMatrix::RandomNet(std::vector<std::vector<Grid>>& vecNet)
{
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER; ++j) {
			int random = MyHelper::Instance()->Random(4);
			switch (random)
			{
			case 0: vecNet[i][j].status = Grid_Star; break;
			case 1: vecNet[i][j].status = Grid_Heart; break;
			case 2: vecNet[i][j].status = Grid_Sword; break;
			case 3: vecNet[i][j].status = Grid_Shield; break;
			}
		}
	}
}

// �Ƿ�Ϸ�����
bool NetMatrix::ValidNet(std::vector<std::vector<Grid>> vecNet)
{
	// �м���Ƿ������� 3 ��
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER - 2; ++j) {
			if (vecNet[i][j].status == vecNet[i][j + 1].status &&
				vecNet[i][j + 1].status == vecNet[i][j + 2].status) {
				return false;
			}
		}
	}
	// �м���Ƿ������� 3 ��
	for (int j = 0; j < NET_COL_NUMBER; ++j) {
		for (int i = 0; i < NET_ROW_NUMBER - 2; ++i) {
			if (vecNet[i][j].status == vecNet[i + 1][j].status &&
				vecNet[i + 1][j].status == vecNet[i + 2][j].status) {
				return false;
			}
		}
	}
	// ���ͨ��
	return true;
}

// ����������
std::vector<PosPoint> NetMatrix::GetCancelPoints(PosPoint point, std::vector<std::vector<Grid>> vecNet)
{
	// �ɴ���㿪ʼ��ɢ��ѯ
	std::vector<PosPoint> horizontalPoints, verticalPoints;
	GridStatus status = vecNet[point.row][point.col].status;
	// ����
	for (int left = point.col - 1; left >= 0; --left) {
		if (vecNet[point.row][left].status == status)
			horizontalPoints.push_back(PosPoint(point.row, left));
		else break;
	}
	// ����
	for (int right = point.col + 1; right < NET_COL_NUMBER; ++right) {
		if (vecNet[point.row][right].status == status)
			horizontalPoints.push_back(PosPoint(point.row, right));
		else break;
	}
	// ����
	for (int up = point.row - 1; up >= 0; --up) {
		if (vecNet[up][point.col].status == status)
			verticalPoints.push_back(PosPoint(up, point.col));
		else break;
	}
	// ����
	for (int down = point.row + 1; down < NET_ROW_NUMBER; ++down) {
		if (vecNet[down][point.col].status == status)
			verticalPoints.push_back(PosPoint(down, point.col));
		else break;
	}
	// ������Ƿ����
	// 1. ˮƽ����ֱ�����ϵĸ���С�ڵ��� 2����÷�����ֵ������֮������ 2������Ϊ
	// ��׼���������ϣ�
	if (horizontalPoints.size() < 2) horizontalPoints.clear();
	if (verticalPoints.size() < 2) verticalPoints.clear();
	// 2. ���������ϵĵ�ϲ�
	std::vector<PosPoint> results;
	for (auto h = horizontalPoints.begin(); h < horizontalPoints.end(); ++h)
			results.push_back(*h);
	for (auto v = verticalPoints.begin(); v < verticalPoints.end(); ++v)
			results.push_back(*v);
	if (horizontalPoints.size() >= 2 || verticalPoints.size() >= 2)
		results.push_back(point);
	return results;
}

// ��ʾ������Ϣ
void NetMatrix::ShowCancelMsg()
{

}
