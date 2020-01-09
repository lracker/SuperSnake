#pragma once
#include <time.h>
#include "DrawBase.h"
#include "DataBase.h"

class CArea
{
private:
	int m_FoodExist;  //食物是否存在，0为不存在，1为存在
	int m_SuperFoodExist;  //超级食物是否存在
	int m_Map[g_MaxX][g_MaxY];  //将场地想象成二维数组，里面0为空地，1为墙，2为食物，3为蛇身，4为障碍物，5为蛇头
	COORD m_FoodPos;  //食物的坐标  
	COORD m_SuperFoodPos;  //超级食物的坐标 
public:
	CArea();
	~CArea();
	void Draw_Map(int X, int Y);  //根据m_Map画出所有数据
	void Set_Map(int x, int y, int n);  //设置m_Map
	int Get_Map(int x, int y);  //获得m_Map[x][y]的数值
	void InitObject();  //初始化m_Map[x][y]为墙和空地
	int CreateFood();  //创建m_Map[x][y]为食物
	void Set_FoodExist(int n);  //设置食物是否存在
	int Get_FoodExist();  //获得食物是否存在
	int CreateRock();  //创建m_Map[x][y]为石头
	void ScoreBoard();  //画出计分板
	int Getm_FoodPosX();  //获得食物所在的坐标X
	int Getm_FoodPosY();  //获得食物所在的坐标Y
	void SetSuperFoodExit(int n);  //设置超级食物是否存在
	int CreateSuperFood();  //创造超级食物
	int Get_SuperFoodExist();  //获取超级食物是否存在
	COORD Getm_SuperFoodPos();  //获取超级食物坐标
	void DoubleFoodTips();  //画出食物提示
};

