#include "pch.h"
#include "CArea.h"
CArea::CArea() :m_FoodExist(0) //初始化食物不再
{
}

CArea::~CArea()
{
}

/***************************************
**功 能：根据是否是墙来画地图
**s
**
*****************************************/
void CArea::Draw_Map(int X, int Y)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (m_Map[i][j] == 0)  //空地
			{
				WriteChar(i, j, " ");
			}
			else if (m_Map[i][j] == 1)  //墙
			{
				WriteChar(i, j, "▓", FOREGROUND_INTENSITY);
			}
			else if (m_Map[i][j] == 2)  //食物
			{
				WriteChar(i, j, "★", FOREGROUND_RED);
			}
			else if (m_Map[i][j] == 3)  //蛇身体
			{
				WriteChar(i, j, "卍", FOREGROUND_GREEN);
			}

			else if (m_Map[i][j] == 4)  //障碍物
			{
				WriteChar(i, j, "■", FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (m_Map[i][j] == 5)  //蛇头
			{
				WriteChar(i, j, "◎", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else if (m_Map[i][j] == 6) //超级食物  
			{
				WriteChar(i, j, "☆", FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
		}
	}
}

void CArea::Set_Map(int x, int y, int n)
{
	m_Map[x][y] = n;
}

int CArea::Get_Map(int x, int y)
{
	return m_Map[x][y];
}

/***************************************
**功 能：设置物体坐标为墙和空地
**
**
*************************/
void CArea::InitObject()
{
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			if (i == 0 || i == g_MaxX - 1 || j == 0 || j == g_MaxY - 1)
			{
				m_Map[i][j] = 1;  //1表示墙
			}
			else
			{
				m_Map[i][j] = 0;  //0表示空格
			}
		}
	}
	//隐藏属性，因为一开始蛇的位置固定为（10，17）（10，18）（10，19）（10，20）了，避免接下来食物会在蛇的身体上创建出来这种情况（懒
	m_Map[10][17] = 5;  //蛇头
	for (int i = 18; i < 21; i++)
		m_Map[10][i] = 3;  //蛇身
}
/**********************
**功能：设置物体坐标为食物
**
**
**********************/
int CArea::CreateFood()
{
	srand((int)time(NULL));
	while (true)
	{
		int X = rand() % g_MaxX/2;
		int Y = rand() % g_MaxY;
		if (m_Map[X][Y] == 0)  //如果是空地
		{
			m_Map[X][Y] = 2;
			m_FoodPos.X = X;
			m_FoodPos.Y = Y;
			m_FoodExist = 1;
			return 0;
		}
	}
}

/***************************************
**功 能：设置物体坐标为障碍物
**
**
*************************/
int CArea::CreateRock()
{
	srand((int)time(NULL));
	int X, Y;
	for(int i = 0; i < g_RockNum; i++)
	{
		while (true)
		{
			X = rand() % (g_MaxX-2) + 1;
			Y = rand() % (g_MaxY-2) + 1;
			if (m_Map[X][Y] == 0)
			{
				m_Map[X][Y] = 4;
				break;
			}
		}
	}
	return 0;
}

/******************************
**功能:设置食物是否存在
**
**
********************************/
void CArea::Set_FoodExist(int n)
{
	m_FoodExist =n ;
}

/********************************
**功能:获取食物是否存在
**
**
*********************************/
int CArea::Get_FoodExist()
{
	return m_FoodExist;
}

/***************************************
**功 能：设置计分板
**s
**
*****************************************/

void CArea::ScoreBoard()
{
	for (int i = g_ScoreX; i < 75; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY-1)
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}
}

/*******************************
**功能：获取食物的坐标X
**
**
*********************************/
int CArea::Getm_FoodPosX()
{
	return m_FoodPos.X;
}

/*******************************
**功能：获取食物的坐标Y
**
**
*********************************/
int CArea::Getm_FoodPosY()
{
	return m_FoodPos.Y;
}

/*************************************
**功能:设置超级食物是否存在
**
**
************************************/
void CArea::SetSuperFoodExit(int n)
{
	m_SuperFoodExist = n;
}

/*****************************
**功能:创造超级食物
**
**
******************************/
int CArea::CreateSuperFood()
{
	srand((int)time(NULL));
	while (true)
	{
		int X = rand() % g_MaxX / 2;
		int Y = rand() % g_MaxY;
		if (m_Map[X][Y] == 0)  //如果是空地
		{
			m_Map[X][Y] = 6;  //设置为超级食物
			m_SuperFoodPos.X = X;
			m_SuperFoodPos.Y = Y;
			m_SuperFoodExist = 1;
			return 0;
		}
	}
}

/******************************
**功能：获取超级食物是否存在
**
**
********************************/
int CArea::Get_SuperFoodExist()
{
	return m_SuperFoodExist;
}

/***************************
**功能：获取超级食物的坐标
**
**
*******************************/
COORD CArea::Getm_SuperFoodPos()
{
	return m_SuperFoodPos;
}

/***************************
**功能：双蛇大战的时候设置食物提示
**
**
****************************/
void CArea::DoubleFoodTips()
{
	for (int i = g_ScoreX; i < 75; i++)
	{
		for (int j = g_ScoreY; j < g_ScoreY+10; j++)
		{
			if (i == g_ScoreX || i == 74 || j == g_ScoreY || j == g_ScoreY + 9)
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
	}
	WriteChar(63.5, g_ScoreY + 3, "★是加分的",FOREGROUND_RED);  
	WriteChar(63.5, g_ScoreY + 5, "☆是加生命值的", FOREGROUND_RED | FOREGROUND_INTENSITY);
}
