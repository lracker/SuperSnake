#include "pch.h"
#include "DrawBase.h"
using std::cout;

/**************************************
**�� �ܣ�������ָ���������ϴ�ӡ��ָ�����ַ���
**
**
***************************************/

void WriteChar(int x, int y, const char* s, WORD att)  //�����ַ���
{
	HANDLE hOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos = { 2 * x,y };
	SetConsoleCursorPosition(hOutPut, cPos);
	SetConsoleTextAttribute(hOutPut, att);
	cout << s;
}

