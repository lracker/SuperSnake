#pragma once
#include <Windows.h>
#include <iostream>


void WriteChar(int x, int y, const char* s, WORD att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);  //用来在控制台指定坐标上输出，颜色默认是白色