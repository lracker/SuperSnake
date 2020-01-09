#pragma once
#include <time.h>
#include "DrawBase.h"
#include "DataBase.h"

class CArea
{
private:
	int m_FoodExist;  //ʳ���Ƿ���ڣ�0Ϊ�����ڣ�1Ϊ����
	int m_SuperFoodExist;  //����ʳ���Ƿ����
	int m_Map[g_MaxX][g_MaxY];  //����������ɶ�ά���飬����0Ϊ�յأ�1Ϊǽ��2Ϊʳ�3Ϊ����4Ϊ�ϰ��5Ϊ��ͷ
	COORD m_FoodPos;  //ʳ�������  
	COORD m_SuperFoodPos;  //����ʳ������� 
public:
	CArea();
	~CArea();
	void Draw_Map(int X, int Y);  //����m_Map������������
	void Set_Map(int x, int y, int n);  //����m_Map
	int Get_Map(int x, int y);  //���m_Map[x][y]����ֵ
	void InitObject();  //��ʼ��m_Map[x][y]Ϊǽ�Ϳյ�
	int CreateFood();  //����m_Map[x][y]Ϊʳ��
	void Set_FoodExist(int n);  //����ʳ���Ƿ����
	int Get_FoodExist();  //���ʳ���Ƿ����
	int CreateRock();  //����m_Map[x][y]Ϊʯͷ
	void ScoreBoard();  //�����Ʒְ�
	int Getm_FoodPosX();  //���ʳ�����ڵ�����X
	int Getm_FoodPosY();  //���ʳ�����ڵ�����Y
	void SetSuperFoodExit(int n);  //���ó���ʳ���Ƿ����
	int CreateSuperFood();  //���쳬��ʳ��
	int Get_SuperFoodExist();  //��ȡ����ʳ���Ƿ����
	COORD Getm_SuperFoodPos();  //��ȡ����ʳ������
	void DoubleFoodTips();  //����ʳ����ʾ
};

