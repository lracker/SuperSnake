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
**功 能：初始化蛇
**
**
***************************************/
void CSnake::InitSnake(int n)
{
	SnakeBody.clear();
	COORD *pos = new COORD[g_InitLen];  //根据长度new一个数组
	switch(n)
	{
	case 0:
		for (short i = 0; i < g_InitLen; i++)
		{
			pos[i] = { 10,20 - i };
			SnakeBody.push_back(pos[i]);  //容器顶才是蛇头
		}
		break;
	case 1:
		for (short i = 0; i < g_InitLen; i++)
		{
			pos[i] = { 40,20 - i };
			SnakeBody.push_back(pos[i]);  //容器顶才是蛇头
		}
		break;
	default:
		break;
	}
}

/**************************************
**功 能：获取用户输入改变方向
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
			m_Dir = UP;  //上 
			break;
		case 's':
			m_Dir = DOWN;  //下
			break;
		case 'a':
			m_Dir = LEFT;  //左
			break;
		case 'd':
			m_Dir = RIGHT;  //右
			break;
		case 27:  //按下esc时候的暂停
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
			m_Dir = UP;  //上 
			break;
		case 'k':
			m_Dir = DOWN;  //下
			break;
		case 'j':
			m_Dir = LEFT;  //左
			break;
		case 'l':
			m_Dir = RIGHT;  //右
			break;
		case 27:  //按下esc时候的暂停
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
**功 能：清理之前的痕迹
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
**功能：设置蛇身的区域为3
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
			MyArea.Set_Map(SnakeBody[i].X, SnakeBody[i].Y, 3);  //设置蛇的区域为3
		}

	}
}

/*************************************
**功能：当蛇撞墙的时候可以原路返回
**
**
**************************************/
void CSnake::Go_Back(CArea &MyArea, COORD &pos2, int &m_Dir)
{
	reverse(SnakeBody.begin(), SnakeBody.end());
	pos2.X = SnakeBody[SnakeBody.size() - 1].X;  //蛇头
	pos2.Y = SnakeBody[SnakeBody.size() - 1].Y;  //蛇头
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
	SnakeBody.erase(SnakeBody.begin());  //删掉蛇尾，并且移动数组
	SnakeBody.push_back(pos2);  //插入新的蛇头
}

/**************************************
**功 能：计分板上的数值显示
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
		WriteChar(67.5, 2, "分数");
		WriteChar(68, 3, Score);
		WriteChar(67, 5, "生命值");
		WriteChar(68, 6, Health);
	}
	else if (n == 1)
	{
		char Score[10] = {};
		char Health[10] = {};
		sprintf_s(Score, 10, "%d", m_Score);
		sprintf_s(Health, 10, "%d", m_Health);
		WriteChar(67.5, 7, "分数");
		WriteChar(68, 8, Score);
		WriteChar(67, 10, "生命值");
		WriteChar(68, 11, Health);
	}
	

}
/**********************************
**功能：判断蛇改变方向后撞到什么了
**
**
*************************************/
void CSnake::Judge(CArea &MyArea, COORD &pos)
{
	//移动后判断碰到了什么
	if (MyArea.Get_Map(pos.X, pos.Y) == 0)  //碰到空地了  什么都不用做，继续下去
	{
		MyArea.Set_Map(SnakeBody[0].X, SnakeBody[0].Y, 0);
		SnakeBody.erase(SnakeBody.begin());  //删掉蛇尾，并且移动数组
		SnakeBody.push_back(pos);  //插入新的蛇头
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 1 || MyArea.Get_Map(pos.X, pos.Y) == 3 || MyArea.Get_Map(pos.X, pos.Y) == 4 || MyArea.Get_Map(pos.X, pos.Y) == 5)  //碰到墙了
	{
		m_Health--;
		Go_Back(MyArea, pos, m_Dir);
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 2)  //碰到食物了
	{
		MyArea.Set_FoodExist(0);
		MyArea.Set_Map(pos.X, pos.Y, 0);  //这里应该变为空地了
		SnakeBody.push_back(pos);  //插入新的蛇头
		m_Score++;
	}
	else if (MyArea.Get_Map(pos.X, pos.Y) == 6)  //吃到终极大奖了
	{
		MyArea.SetSuperFoodExit(0);
		MyArea.Set_Map(pos.X, pos.Y, 0);  //这里应该变为空地了
		SnakeBody.erase(SnakeBody.begin());  //删掉蛇尾，并且移动数组
		SnakeBody.push_back(pos);  //插入新的蛇头
		m_Health++;
	}
}

/***************************************************
**功能：如果不需要初始化蛇的化，根据文件内容来设置蛇
**
**
***************************************************/
void CSnake::ContinueSnake(CArea &MyArea)
{
	SnakeBody.clear();  //清理掉容器里的元素
	int Num = GetSCore()+3;  //因为一开始蛇身的长度就是4了，所以接下来蛇的长度是成绩+4
	COORD *pos = new COORD[Num];  //根据长度new一个数组
	COORD H_pos;  //设置蛇头
	int K = 0;
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (MyArea.Get_Map(i, j) == 3) //3是蛇身
			{
				pos[K] = { (short)i,(short)j };
				K++;
			}
			else if (MyArea.Get_Map(i, j) == 5)
			{
				H_pos = { (short)i,(short)j };  //5是蛇头
			}
		}
	}
	for (int i = 0; i < K; i++)  //压入蛇身到容器
	{
		SnakeBody.push_back(pos[i]);  
	}
	SnakeBody.push_back(H_pos);//容器顶才是蛇头
}
/**********************
**功能：获取蛇的生命值
**
**
**********************/
int CSnake::GetHealth()
{
	return m_Health;
}

/*************************
**功能：获取蛇的成绩
**
**
*************************/
int CSnake::GetSCore()
{
	return m_Score;
}

/*******************************
**功能：设置蛇的生命
**
**
*******************************/
void CSnake::SetHealth(int n)
{
	m_Health = n;
}

/******************************
**功能：设置蛇的成绩
**
**
******************************/
void CSnake::SetSCore(int n)
{
	m_Score = n;
}

/************************************
**功能：设置标志位（是否需要初始化蛇）
**
**
*************************************/
void CSnake::SetFlag(int n)
{
	m_Flag = n;
}


/***********************************
**功能：获取当前方向
**
**
**************************************/
int CSnake::GetDir()
{
	return m_Dir;
}

/*****************************************
**功能：从文件中读取方向并设置到当前方向上
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
**功 能：蛇移动
**
**
****************************************/

int CSnake::MovePos(CArea &MyArea, COORD &pos, int n)
{
	if (!m_Health)  //死了以后
	{
		if (m_Score > g_HighScore)  //死了以后比较最高成绩并且记录最高的
		{
			g_HighScore = m_Score;
		}
		FILE *pFile = NULL;
		fopen_s(&pFile, "Map//HighScore.txt", "wb");
		fprintf(pFile, "%d", g_HighScore);
		fclose(pFile);
		return 0;
	}
	Snake_Score(n);  //计分板显示
	pos.X = SnakeBody[SnakeBody.size() - 1].X;  //蛇头
	pos.Y = SnakeBody[SnakeBody.size() - 1].Y;  //蛇头
	switch (m_Dir)
	{
	case UP:  //上
		if (m_OldDir == 1)  //如果之前是下的话
		{
			m_Dir = m_OldDir;
			pos.Y++;
		}
		else
		{
			pos.Y--;
		}

		break;
	case DOWN:   //下
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
	case LEFT:  //左
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
	case RIGHT:  //右
		if (m_OldDir == 2)  //左
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
	Judge(MyArea, pos);  //判断撞到什么了
	Snake_Area(SnakeBody, MyArea);  //设置蛇经过的地方为3
	m_OldDir = m_Dir; //把当前方向放到旧的方向里
	return 1;
}

/**************************************
**功 能：画出蛇身
**
**
****************************************/

void CSnake::DrawSnake()
{
	for (int i = 0; i < SnakeBody.size(); i++)
	{
		WriteChar (SnakeBody[i].X, SnakeBody[i].Y, "卍", m_Color);
		if (i == SnakeBody.size() - 1)
		{
			WriteChar(SnakeBody[i].X, SnakeBody[i].Y, "◎", m_Color | FOREGROUND_INTENSITY);
		}
	}
}



/**************************************
**功 能：游戏开始，蛇要移动的过程
**
**
****************************************/

void CSnake::SnakeMove(CConsole *MyConsole)
{
	SetColor(FOREGROUND_GREEN);
	if (m_Flag == 0)  //看看是否需要初始化蛇
	{
		InitSnake(0);  //初始化蛇
	}
	else
	{
		ContinueSnake(MyConsole->MyArea);  //不需要初始化蛇
	}
	bool nLive = true;
	while (nLive)
	{
		if (m_Flag == 0)  //因为读档的下一刻是不需要判断方向来保持原有的方向
		{//用户输入
			char ch = '0';
			if (_kbhit() == 1)
			{
				ch = _getch();
			}
			UserInput(MyConsole, 0, ch);  //获取用户输入
		}
		//把蛇上一个位置清掉
		CleanSnake();
		//控制方向
		int X = 0;
		int Y = 0;
		COORD pos = { X,Y };
		if (MovePos(MyConsole->MyArea,pos, 0) == false)  //判断移动以后
		{
			nLive = false;
			break;
		}
		//重新绘制蛇
		DrawSnake();
		//创建食物
		if (MyConsole->MyArea.Get_FoodExist() == 0)  //如果食物不存在
		{
			MyConsole->MyArea.CreateFood();  //创建食物
			WriteChar(MyConsole->MyArea.Getm_FoodPosX(), MyConsole->MyArea.Getm_FoodPosY(), "★", FOREGROUND_RED);
		}
		Sleep(MyConsole->m_Hard);
		m_Flag = 0;
	}
	system("cls");
	MyConsole->GameOver();
}

