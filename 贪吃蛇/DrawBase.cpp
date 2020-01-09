#include "pch.h"
#include "DrawBase.h"
using std::cout;

/**************************************
**功 能：用于在指定的坐标上打印出指定的字符串
**
**
***************************************/

void WriteChar(int x, int y, const char* s, WORD att)  //画出字符串
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos = { 2 * x,y };
	SetConsoleCursorPosition(hOutPut, cPos);
	SetConsoleTextAttribute(hOutPut, att);
	cout << s;
}

