﻿// 贪吃蛇.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "CConsole.h"
#pragma comment (lib ,"winmm.lib")

int main()
{
	CConsole *MyConsole = new CConsole;
	MyConsole->Begin();
	return 0;
}