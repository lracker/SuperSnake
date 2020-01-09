#pragma once
#include <Windows.h>
#include <iostream>
#include <stack>          // ʹ��ջstack
#include <time.h>
#include <io.h>
#include <direct.h>
#include "CSnake.h"
#include "DataBase.h"
#include "CArea.h"


class CConsole  //����̨
{
public:
	CArea MyArea;  //�������
	CSnake MySnake[2]; //�ߵ���
	int m_Choice;  //ѡ��
	int m_Hard;  //�Ѷ�
	int m_Suspend; // ��ͣʱ��Ĳ���
	int m_GameOverChoice;   //��Ϸ���˵�ʱ���ѡ��
public:
	CConsole();
	~CConsole();
	void Full_Screen(HANDLE hOutput);  //����̨ȫ������
	void Background_Music();  //��������
	void PrintMenu();  //��ӡ����ʼ�˵�
	void SaveToFILE(const char *FileName);  //�����ͼ�ϵ����ݵ��ļ���
	void PrintHardChoice();  //��ӡ���Ѷ�ѡ��
	void SuspendGame();  //��ӡ����ͣ��ѡ��
	void GameOver();  //��ӡ����Ϸ������ѡ��
	void Begin();  //��Ϸһ��ʼ
	bool Load(char *FileName);  //��ȡ����
	void ReadyGame();  //��ʼ��Ϸ
	void GameBegin();  //������Ϸ
	int GetHard();  //��ȡ�Ѷ�ֵ
	void SetHard(int n);  //�����Ѷ�ֵ
	void CustomMap();  //�Զ����ͼ
	bool LoadMap();  //���ص�ͼ�б�
	void MapChoice();  //ѡ���Զ����ͼ����ֱ�ӿ�ʼ��Ϸ
	void SaveMapNametoFILE(char *tmp2);  //�����ͼ���ֵ�һ���ļ���
	bool CreateFolder();  //�����ļ�������ŵ�ͼ
	void DoubleSnake();  //˫��
	void DoubleMove();  //˫�߿�ʼ�ƶ����Ǹ�ѭ��
	void WhichDir(char ch, char &ch2, int &WHO);  //�ж������ߵķ���  
	void DoubleGameOver(int n);    //�ж�������������
	void DoubleSuspendGame();  //˫����ս��ͣʱ���
	bool DeleteMap();  //ɾ����ͼ  
	int SetHighScore();  //������߷�
	void GetHighSCore();  //�鿴��߷�
};

