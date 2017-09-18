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

// һ������
struct Grid {
	Grid() : row(0), col(0), status(Grid_None) {}
	Grid(int row, int col, GridStatus status = Grid_None) : 
		row(row), col(col), status(status) {}
	int row;
	int col;
	GridStatus status;
};

// ����������
class TreeClearHelper
{
protected:
	TreeClearHelper();

public:
	static TreeClearHelper* Instance();
	virtual ~TreeClearHelper();

public:
	// ��ȡ�����
	// modular  �������������Χ��0��ʼ
	// excepts  ���������������Χ�ڵĲ�����������������
	int produceRadomNumber(int modular, std::vector<int> excepts = std::vector<int>());

private:
	// �������
	static int seed;
};