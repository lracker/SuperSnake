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
	int m_Health;  //蛇的生命值
	vector<COORD> SnakeBody;  //蛇本体
	int m_Dir;  //方向
	int m_OldDir;  //旧的方向
	int m_PreDir;  //读取的方向
	int m_Score;  //成绩
	int m_Flag;  //标志位,判断是否要初始化蛇
	WORD m_Color;  //蛇的颜色  
	int m_NowScore;  //当前分数
public:
	CSnake();
	~CSnake();
	void InitSnake(int n);  //初始化蛇的本体
	void UserInput(CConsole *MyConsole, int WHO,char ch);  //获得用户输入来动来动去
	void CleanSnake();  //清理掉蛇过去的痕迹
	int MovePos(CArea &MyArea, COORD &pos2, int n);  //移动后的方向
	void DrawSnake();  //画蛇
	void SnakeMove(CConsole *MyConsole);  //控制蛇的移动  
	void Snake_Area(vector<COORD> SnakeBody, CArea &MyArea);  //蛇所在的区域为3
	void Go_Back(CArea &MyArea, COORD &pos2, int &m_Dir);  //撞东西后调头
	void Snake_Score(int n);  //计分板数值显示
	void Judge(CArea &MyArea, COORD &pos2);  //判断方向
	void ContinueSnake(CArea &MyArea);  //已经保存在文件中的蛇
	int GetHealth();  //获取蛇的生命值
	int GetSCore();  //获取蛇的分数
	void SetHealth(int n);  //设置蛇的生命值
	void SetSCore(int n);  //设置蛇的成绩
	void SetFlag(int n);  //设置标志位，判断是否需要重新定义一条蛇
	int GetDir();  //获取方向
	void SetDir(int nDir);  //设置方向
	void SetColor(WORD color); // 设置蛇的颜色
};
