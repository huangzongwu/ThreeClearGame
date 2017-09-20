#include "stdafx.h"
#include "NetMatrix.h"
#include "MyHelper.h"

NetMatrix::NetMatrix() : m_nScore(0)
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
std::vector<std::vector<Grid>> NetMatrix::GetNet()
{
	return m_vecNet;
}

// �������ݽṹ
void NetMatrix::SetNet(std::vector<std::vector<Grid>> vecNet)
{
	m_vecNet = vecNet;
}

// ��ʼ���������
void NetMatrix::Init()
{
	m_nScore = 0;
	RandomNet(m_vecNet);
	while (!ValidNet(m_vecNet)) RandomNet(m_vecNet);
}

// ��������
bool NetMatrix::Change(PosPoint pre, PosPoint cur)
{
	// ��ʱ���洦������
	auto vecNet = m_vecNet;
	// ���������������һ������ɾ��״̬��ֱ�ӷ��ز�����
	if (vecNet[pre.row][pre.col].status == Grid_Delete ||
		vecNet[cur.row][cur.col].status == Grid_Delete) {
		MyHelper::Instance()->WriteLog(L"ɾ����ť��������");
		return false;
	}
	// ������������
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
	// ���������ÿ����һ���� 1 ��
	m_nScore += (prePoints.size() + curPoints.size());
	// ����ɾ���ĵ�Ϊɾ��Ƥ��
	for (int i = 0; i < prePoints.size(); ++i) {
		vecNet[prePoints[i].row][prePoints[i].col].status = Grid_Delete;
	}
	for (int i = 0; i < curPoints.size(); ++i) {
		vecNet[curPoints[i].row][curPoints[i].col].status = Grid_Delete;
	}
	m_vecNet = vecNet;
	// ˢ�½���
	m_event->RefreshNet(m_vecNet);
	return true;
}

// ���������������������䣩
bool NetMatrix::AutoDelete()
{
	// ��¼����������ĵ�
	std::vector<PosPoint> points;
	// �м���Ƿ������� 3 ��
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER - 2; ++j) {
			if (m_vecNet[i][j].status == m_vecNet[i][j + 1].status	   &&
				m_vecNet[i][j + 1].status == m_vecNet[i][j + 2].status &&
				m_vecNet[i][j].status != Grid_Delete) {
				points.push_back(PosPoint(i, j));
				j += 3;
			}
		}
	}
	// �м���Ƿ������� 3 ��
	for (int j = 0; j < NET_COL_NUMBER; ++j) {
		for (int i = 0; i < NET_ROW_NUMBER - 2; ++i) {
			if (m_vecNet[i][j].status == m_vecNet[i + 1][j].status	   &&
				m_vecNet[i + 1][j].status == m_vecNet[i + 2][j].status &&
				m_vecNet[i][j].status != Grid_Delete) {
				points.push_back(PosPoint(i, j));
				i += 3;
			}
		}
	}
	// ���û���ҵ������ĵ㣬��֤��û�б�����������
	if (points.size() == 0) return false;
	// ���ݵ��ȡ������
	std::set<PosPoint> cancelPoints;
	for (int i = 0; i < points.size(); ++i) {
		std::vector<PosPoint> tempPoints = GetCancelPoints(points[i], m_vecNet);
		cancelPoints.insert(tempPoints.begin(), tempPoints.end());
	}
	// ����Զ����������Ϣ
	SOUI::SStringW strAutoCancelPoints, strAutoCancelMsg;
	for (auto it = cancelPoints.begin(); it != cancelPoints.end(); ++it) {
		SOUI::SStringW strPoint;
		strPoint.Format(L"(%d, %d)", it->row, it->col);
		strAutoCancelPoints += strPoint;
	}
	strAutoCancelMsg.Format(L"ִ���Զ�������%s", strAutoCancelPoints);
	MyHelper::Instance()->WriteLog(strAutoCancelMsg);
	// �������ϵ�Ϊɾ��״̬
	for (auto it = cancelPoints.begin(); it != cancelPoints.end(); ++it) {
		m_vecNet[it->row][it->col].status = Grid_Delete;
	}
	m_event->RefreshNet(m_vecNet);
	return true;
}

// ����ˢ���¼�ָ��
void NetMatrix::SetEvent(RefreshEvent* event)
{
	if (event != nullptr) m_event = event;
}

// ��ȡ����
int NetMatrix::GetScore()
{
	return m_nScore;
}

// ��������
bool NetMatrix::LandOneGrid()
{
	// ����Ƿ�������������
	bool bNeedLand = false;
	// ����ÿ��
	for (int col = 0; col < NET_COL_NUMBER; ++col) {
		// ���¿�ʼ����ÿ��
		for (int row = NET_ROW_NUMBER - 1; row >= 1; --row) {
			// ��ɾ����ð����ȥ
			if (m_vecNet[row][col].status == Grid_Delete   &&
				m_vecNet[row - 1][col].status != Grid_Delete) {
				// ��Ƿ�������������
				bNeedLand = true;
				// ����Ų��ɾ������ȥ
				int count = row;
				do {
					std::swap(m_vecNet[count][col], m_vecNet[count - 1][col]);
				} while (--count >= 1 && m_vecNet[count - 1][col].status != Grid_Delete);
				break;
			}
		}
	}
	return bNeedLand;
}

// ����������
void NetMatrix::AddRandomGrid()
{
	// ��ʱ��m_vecNet �Ѿ���Ϊ��һ��ɾ����ťȫ��������
	// ͼ��ťȫ��������ľ����ˣ���ʱֻ��Ҫ�������ť
	// ���伴��
	for (int i = 0; i < NET_ROW_NUMBER; ++i) {
		for (int j = 0; j < NET_COL_NUMBER; ++j) {

		}
	}
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
			if (vecNet[i][j].status == vecNet[i][j + 1].status		&&
				vecNet[i][j + 1].status == vecNet[i][j + 2].status  &&
				vecNet[i][j].status != Grid_Delete) {
				return false;
			}
		}
	}
	// �м���Ƿ������� 3 ��
	for (int j = 0; j < NET_COL_NUMBER; ++j) {
		for (int i = 0; i < NET_ROW_NUMBER - 2; ++i) {
			if (vecNet[i][j].status == vecNet[i + 1][j].status	   &&
				vecNet[i + 1][j].status == vecNet[i + 2][j].status &&
				vecNet[i][j].status != Grid_Delete) {
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
	// �����ѯ״̬Ϊɾ��״̬����ֱ�ӷ��أ��Ѿ������˵ĵ㲻���ٴ�������
	if (status == Grid_Delete) return std::vector<PosPoint>();
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
