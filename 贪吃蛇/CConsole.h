#pragma once
#include <Windows.h>
#include <iostream>
#include <stack>          // 使用栈stack
#include <time.h>
#include <io.h>
#include <direct.h>
#include "CSnake.h"
#include "DataBase.h"
#include "CArea.h"


class CConsole  //控制台
{
public:
	CArea MyArea;  //区域的类
	CSnake MySnake[2]; //蛇的类
	int m_Choice;  //选择
	int m_Hard;  //难度
	int m_Suspend; // 暂停时候的操作
	int m_GameOverChoice;   //游戏输了的时候的选择
public:
	CConsole();
	~CConsole();
	void Full_Screen(HANDLE hOutput);  //控制台全屏属性
	void Background_Music();  //背景音乐
	void PrintMenu();  //打印出开始菜单
	void SaveToFILE(const char *FileName);  //保存地图上的数据到文件中
	void PrintHardChoice();  //打印出难度选择
	void SuspendGame();  //打印出暂停的选择
	void GameOver();  //打印出游戏结束的选择
	void Begin();  //游戏一开始
	bool Load(char *FileName);  //读取备份
	void ReadyGame();  //开始游戏
	void GameBegin();  //继续游戏
	int GetHard();  //获取难度值
	void SetHard(int n);  //设置难度值
	void CustomMap();  //自定义地图
	bool LoadMap();  //加载地图列表
	void MapChoice();  //选择自定义地图还是直接开始游戏
	void SaveMapNametoFILE(char *tmp2);  //保存地图名字到一个文件中
	bool CreateFolder();  //创建文件夹来存放地图
	void DoubleSnake();  //双蛇
	void DoubleMove();  //双蛇开始移动的那个循环
	void WhichDir(char ch, char &ch2, int &WHO);  //判断哪条蛇的方向  
	void DoubleGameOver(int n);    //判断是哪条蛇输了
	void DoubleSuspendGame();  //双蛇作战暂停时候的
	bool DeleteMap();  //删除地图  
	int SetHighScore();  //设置最高分
	void GetHighSCore();  //查看最高分
};

