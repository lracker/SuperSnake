#include "pch.h"
#include "CSnake.h"
#include "CConsole.h"
using std::cout;
using std::endl;

CSnake::CSnake():m_Health(3),m_Dir(0),m_Flag(0),m_Score(0)
{
}

CSnake::~CSnake()
{
}

/**************************************
**�� �ܣ���ʼ����
**
**
***************************************/
void CSnake::InitSnake(int n)
{
	SnakeBody.clear();
	COORD *pos = new COORD[g_InitLen];  //���ݳ���newһ������
	switch(n)
	{
	case 0:
		for (short i = 0; i < g_InitLen; i++)
		{
			pos[i] = { 10,20 - i };
			SnakeBody.push_back(pos[i]);  //������������ͷ
		}
		break;
	case 1:
		for (short i = 0; i < g_InitLen; i++)
		{
			pos[i] = { 40,20 - i };
			SnakeBody.push_back(pos[i]);  //������������ͷ
		}
		break;
	default:
		break;
	}
}

/**************************************
**�� �ܣ���ȡ�û�����ı䷽��
**
**
****************************************/
void CSnake::UserInput(CConsole *MyConsole, int WHO, char ch)
{
	if(WHO == 0)
	{
		switch (ch)
		{
		case 'w':
			m_Dir = UP;  //�� 
			break;
		case 's':
			m_Dir = DOWN;  //��
			break;
		case 'a':
			m_Dir = LEFT;  //��
			break;
		case 'd':
			m_Dir = RIGHT;  //��
			break;
		case 27:  //����escʱ�����ͣ
			system("cls");
			MyConsole->SuspendGame();
			system("pause>nul");
			break;
		default:
			break;
		}
	}
	else if(WHO == 1)
	{
		switch (ch)
		{
		case 'i':
			m_Dir = UP;  //�� 
			break;
		case 'k':
			m_Dir = DOWN;  //��
			break;
		case 'j':
			m_Dir = LEFT;  //��
			break;
		case 'l':
			m_Dir = RIGHT;  //��
			break;
		case 27:  //����escʱ�����ͣ
			system("cls");
			MyConsole->SuspendGame();
			system("pause>nul");
			break;
		default:
			break;
		}
	}

}

/**************************************
**�� �ܣ�����֮ǰ�ĺۼ�
**
**
****************************************/
void CSnake::CleanSnake()
{
	for (int i = 0; i < SnakeBody.size(); i++)
	{
		WriteChar(SnakeBody[i].X, SnakeBody[i].Y, " ");
	}

}

/*************************************
**���ܣ��������������Ϊ3
**
**
**************************************/
void CSnake::Snake_Area(vector<COORD> SnakeBody,CArea &MyArea)
{
	for (int i = 0; i < SnakeBody.size(); i++)
	{
		if (i == SnakeBody.size() - 1)
		{
			MyArea.Set_Map(SnakeBody[i].X, SnakeBody[i].Y, 5);
		}
		else
		{
			MyArea.Set_Map(SnakeBody[i].X, SnakeBody[i].Y, 3);  //�����ߵ�����Ϊ3
		}

	}
}

/*************************************
**���ܣ�����ײǽ��ʱ�����ԭ·����
**
**
**************************************/
void CSnake::Go_Back(CArea &MyArea, COORD &pos2, int &m_Dir)
{
	reverse(SnakeBody.begin(), SnakeBody.end());
	pos2.X = SnakeBody[SnakeBody.size() - 1].X;  //��ͷ
	pos2.Y = SnakeBody[SnakeBody.size() - 1].Y;  //��ͷ
	switch (m_Dir)
	{
	case 0:
		pos2.Y++;
		m_Dir = 1;
		break;
	case 1:
		pos2.Y--;
		m_Dir = 0;
		break;
	case 2:
		pos2.X++;
		m_Dir = 3;
		break;
	case 3:
		pos2.X--;
		m_Dir = 2;
		break;
	default:
		break;
	}
	MyArea.Set_Map(SnakeBody[0].X, SnakeBody[0].Y, 0);
	SnakeBody.erase(SnakeBody.begin());  //ɾ����β�������ƶ�����
	SnakeBody.push_back(pos2);  //�����µ���ͷ
}

/**************************************
**�� �ܣ��Ʒְ��ϵ���ֵ��ʾ
**
**
****************************************/
void CSnake::Snake_Score(int n)
{
	if (n == 0)
	{
		char Score[10] = {};
		char Health[10] = {};
		sprintf_s(Score, 10, "%d", m_Score);
		sprintf_s(Health, 10, "%d", m_Health);
		WriteChar(67.5, 2, "����");
		WriteChar(68, 3, Score);
		WriteChar(67, 5, "����ֵ");
		WriteChar(68, 6, Health);
	}
	else if (n == 1)
	{
		char Score[10] = {};
		char Health[10] = {};
		sprintf_s(Score, 10, "%d", m_Score);
		sprintf_s(Health, 10, "%d", m_Health);
		WriteChar(67.5, 7, "����");
		WriteChar(68, 8, Score);
		WriteChar(67, 10, "����ֵ");
		WriteChar(68, 11, Health);
	}
	

}
/**********************************
**���ܣ��ж��߸ı䷽���ײ��ʲô��
**
**
*************************************/
void CSnake::Judge(CArea &MyArea, COORD &pos)
{
	//�ƶ����ж�������ʲô
	if (MyArea.Get_Map(pos.X, pos.Y) == 0)  //�����յ���  ʲô����������������ȥ
	{
		MyArea.Set_Map(SnakeBody[0].X, SnakeBody[0].Y, 0);
		SnakeBody.erase(SnakeBody.begin());  //ɾ����β�������ƶ�����
		SnakeBody.push_back(pos);  //�����µ���ͷ
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 1 || MyArea.Get_Map(pos.X, pos.Y) == 3 || MyArea.Get_Map(pos.X, pos.Y) == 4 || MyArea.Get_Map(pos.X, pos.Y) == 5)  //����ǽ��
	{
		m_Health--;
		Go_Back(MyArea, pos, m_Dir);
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 2)  //����ʳ����
	{
		MyArea.Set_FoodExist(0);
		MyArea.Set_Map(pos.X, pos.Y, 0);  //����Ӧ�ñ�Ϊ�յ���
		SnakeBody.push_back(pos);  //�����µ���ͷ
		m_Score++;
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 6)  //�Ե��ռ�����
	{
		MyArea.SetSuperFoodExit(0);
		MyArea.Set_Map(pos.X, pos.Y, 0);  //����Ӧ�ñ�Ϊ�յ���
		SnakeBody.erase(SnakeBody.begin());  //ɾ����β�������ƶ�����
		SnakeBody.push_back(pos);  //�����µ���ͷ
		m_Health++;
	}
}

/***************************************************
**���ܣ��������Ҫ��ʼ���ߵĻ��������ļ�������������
**
**
***************************************************/
void CSnake::ContinueSnake(CArea &MyArea)
{
	SnakeBody.clear();  //������������Ԫ��
	int Num = GetSCore()+3;  //��Ϊһ��ʼ����ĳ��Ⱦ���4�ˣ����Խ������ߵĳ����ǳɼ�+4
	COORD *pos = new COORD[Num];  //���ݳ���newһ������
	COORD H_pos;  //������ͷ
	int K = 0;
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (MyArea.Get_Map(i, j) == 3) //3������
			{
				pos[K] = { (short)i,(short)j };
				K++;
			}
			else if (MyArea.Get_Map(i, j) == 5)
			{
				H_pos = { (short)i,(short)j };  //5����ͷ
			}
		}
	}
	for (int i = 0; i < K; i++)  //ѹ����������
	{
		SnakeBody.push_back(pos[i]);  
	}
	SnakeBody.push_back(H_pos);//������������ͷ
}
/**********************
**���ܣ���ȡ�ߵ�����ֵ
**
**
**********************/
int CSnake::GetHealth()
{
	return m_Health;
}

/*************************
**���ܣ���ȡ�ߵĳɼ�
**
**
*************************/
int CSnake::GetSCore()
{
	return m_Score;
}

/*******************************
**���ܣ������ߵ�����
**
**
*******************************/
void CSnake::SetHealth(int n)
{
	m_Health = n;
}

/******************************
**���ܣ������ߵĳɼ�
**
**
******************************/
void CSnake::SetSCore(int n)
{
	m_Score = n;
}

/************************************
**���ܣ����ñ�־λ���Ƿ���Ҫ��ʼ���ߣ�
**
**
*************************************/
void CSnake::SetFlag(int n)
{
	m_Flag = n;
}


/***********************************
**���ܣ���ȡ��ǰ����
**
**
**************************************/
int CSnake::GetDir()
{
	return m_Dir;
}

/*****************************************
**���ܣ����ļ��ж�ȡ�������õ���ǰ������
**
**
******************************************/
void CSnake::SetDir(int nDir)
{
	m_PreDir = nDir;
	m_OldDir = m_PreDir;
	m_Dir = m_OldDir;
}

void CSnake::SetColor(WORD color)
{
	m_Color = color;
}

/**************************************
**�� �ܣ����ƶ�
**
**
****************************************/

int CSnake::MovePos(CArea &MyArea, COORD &pos, int n)
{
	if (!m_Health)  //�����Ժ�
	{
		if (m_Score > g_HighScore)  //�����Ժ�Ƚ���߳ɼ����Ҽ�¼��ߵ�
		{
			g_HighScore = m_Score;
		}
		FILE *pFile = NULL;
		fopen_s(&pFile, "Map//HighScore.txt", "wb");
		fprintf(pFile, "%d", g_HighScore);
		fclose(pFile);
		return 0;
	}
	Snake_Score(n);  //�Ʒְ���ʾ
	pos.X = SnakeBody[SnakeBody.size() - 1].X;  //��ͷ
	pos.Y = SnakeBody[SnakeBody.size() - 1].Y;  //��ͷ
	switch (m_Dir)
	{
	case UP:  //��
		if (m_OldDir == 1)  //���֮ǰ���µĻ�
		{
			m_Dir = m_OldDir;
			pos.Y++;
		}
		else
		{
			pos.Y--;
		}

		break;
	case DOWN:   //��
		if (m_OldDir == 0)
		{
			m_Dir = m_OldDir;
			pos.Y--;
		}
		else
		{
			pos.Y++;
		}

		break;
	case LEFT:  //��
		if (m_OldDir == 3)
		{
			m_Dir = m_OldDir;
			pos.X++;
		}
		else
		{
			pos.X--;
		}

		break;
	case RIGHT:  //��
		if (m_OldDir == 2)  //��
		{
			m_Dir = m_OldDir;
			pos.X--;
		}
		else
		{
			pos.X++;
		}
		break;
	default:
		break;
	}
	Judge(MyArea, pos);  //�ж�ײ��ʲô��
	Snake_Area(SnakeBody, MyArea);  //�����߾����ĵط�Ϊ3
	m_OldDir = m_Dir; //�ѵ�ǰ����ŵ��ɵķ�����
	return 1;
}

/**************************************
**�� �ܣ���������
**
**
****************************************/

void CSnake::DrawSnake()
{
	for (int i = 0; i < SnakeBody.size(); i++)
	{
		WriteChar (SnakeBody[i].X, SnakeBody[i].Y, "�d", m_Color);
		if (i == SnakeBody.size() - 1)
		{
			WriteChar(SnakeBody[i].X, SnakeBody[i].Y, "��", m_Color | FOREGROUND_INTENSITY);
		}
	}
}



/**************************************
**�� �ܣ���Ϸ��ʼ����Ҫ�ƶ��Ĺ���
**
**
****************************************/

void CSnake::SnakeMove(CConsole *MyConsole)
{
	SetColor(FOREGROUND_GREEN);
	if (m_Flag == 0)  //�����Ƿ���Ҫ��ʼ����
	{
		InitSnake(0);  //��ʼ����
	}
	else
	{
		ContinueSnake(MyConsole->MyArea);  //����Ҫ��ʼ����
	}
	bool nLive = true;
	while (nLive)
	{
		if (m_Flag == 0)  //��Ϊ��������һ���ǲ���Ҫ�жϷ���������ԭ�еķ���
		{//�û�����
			char ch = '0';
			if (_kbhit() == 1)
			{
				ch = _getch();
			}
			UserInput(MyConsole, 0, ch);  //��ȡ�û�����
		}
		//������һ��λ�����
		CleanSnake();
		//���Ʒ���
		int X = 0;
		int Y = 0;
		COORD pos = { X,Y };
		if (MovePos(MyConsole->MyArea,pos, 0) == false)  //�ж��ƶ��Ժ�
		{
			nLive = false;
			break;
		}
		//���»�����
		DrawSnake();
		//����ʳ��
		if (MyConsole->MyArea.Get_FoodExist() == 0)  //���ʳ�ﲻ����
		{
			MyConsole->MyArea.CreateFood();  //����ʳ��
			WriteChar(MyConsole->MyArea.Getm_FoodPosX(), MyConsole->MyArea.Getm_FoodPosY(), "��", FOREGROUND_RED);
		}
		Sleep(MyConsole->m_Hard);
		m_Flag = 0;
	}
	system("cls");
	MyConsole->GameOver();
}

