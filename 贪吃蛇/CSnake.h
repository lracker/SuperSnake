#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include "DrawBase.h"
#include "DataBase.h"
#include "CArea.h"
using std::vector;
class CConsole;
class CSnake
{
private:
	int m_Health;  //�ߵ�����ֵ
	vector<COORD> SnakeBody;  //�߱���
	int m_Dir;  //����
	int m_OldDir;  //�ɵķ���
	int m_PreDir;  //��ȡ�ķ���
	int m_Score;  //�ɼ�
	int m_Flag;  //��־λ,�ж��Ƿ�Ҫ��ʼ����
	WORD m_Color;  //�ߵ���ɫ  
	int m_NowScore;  //��ǰ����
public:
	CSnake();
	~CSnake();
	void InitSnake(int n);  //��ʼ���ߵı���
	void UserInput(CConsole *MyConsole, int WHO,char ch);  //����û�������������ȥ
	void CleanSnake();  //������߹�ȥ�ĺۼ�
	int MovePos(CArea &MyArea, COORD &pos2, int n);  //�ƶ���ķ���
	void DrawSnake();  //����
	void SnakeMove(CConsole *MyConsole);  //�����ߵ��ƶ�  
	void Snake_Area(vector<COORD> SnakeBody, CArea &MyArea);  //�����ڵ�����Ϊ3
	void Go_Back(CArea &MyArea, COORD &pos2, int &m_Dir);  //ײ�������ͷ
	void Snake_Score(int n);  //�Ʒְ���ֵ��ʾ
	void Judge(CArea &MyArea, COORD &pos2);  //�жϷ���
	void ContinueSnake(CArea &MyArea);  //�Ѿ��������ļ��е���
	int GetHealth();  //��ȡ�ߵ�����ֵ
	int GetSCore();  //��ȡ�ߵķ���
	void SetHealth(int n);  //�����ߵ�����ֵ
	void SetSCore(int n);  //�����ߵĳɼ�
	void SetFlag(int n);  //���ñ�־λ���ж��Ƿ���Ҫ���¶���һ����
	int GetDir();  //��ȡ����
	void SetDir(int nDir);  //���÷���
	void SetColor(WORD color); // �����ߵ���ɫ
};
