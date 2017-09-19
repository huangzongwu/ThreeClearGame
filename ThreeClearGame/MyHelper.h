/*******************************************************************   
 *  �ļ�����: ThreeClearHelper.h
 *  ��Ҫ����: ������һЩ���õİ��������ŵ�����
 *   
 *  ��������: 2017-9-18
 *  ��������: ��Ө
 *  ˵������: �����ʵ�ֽ���Ϊһ������ģʽ����
 *   
 *  �޸�����: 
 *  ��������: 
 *  ˵������: 
 ******************************************************************/  
#pragma once

// һ�����ӵ�һ��״̬
enum GridStatus {
	Grid_None = 0,
	Grid_Star = 1,
	Grid_Heart = 2,
	Grid_Sword = 3,
	Grid_SHIELD = 4
};

// һ�������
struct PosPoint
{
	PosPoint() : row(0), col(0) {}
	PosPoint(int row, int col) : row(row), col(col) {}
	int row;
	int col;
};

// һ������
struct Grid {
	Grid() : point(0, 0), status(Grid_None) {}
	Grid(int row, int col, GridStatus status = Grid_None) : 
		point(row, col), status(status) {}
	PosPoint point;
	GridStatus status;
};

// ����������
class MyHelper
{
protected:
	MyHelper();

public:
	static MyHelper* Instance();
	virtual ~MyHelper();

public:
	// ��ȡ�����
	// modular  �������������Χ��0��ʼ
	// excepts  ���������������Χ�ڵĲ�����������������
	int Random(int modular, std::vector<int> excepts = std::vector<int>());
};