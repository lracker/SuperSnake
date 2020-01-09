#include "pch.h"
#include "CConsole.h"
using std::cout;
using std::endl;

CConsole::CConsole():m_Hard(400)
{
}


CConsole::~CConsole()
{
}

/***************************************
**功 能：打印出开始菜单
**
**
*****************************************/
void CConsole::PrintMenu()
{
	CreateFolder();  //创建文件夹来存放地图之类的
	while (true)
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY - 4, "1.开始游戏");
		WriteChar(Text_LOCX, Text_LOCY - 2, "2.继续游戏");
		WriteChar(Text_LOCX, Text_LOCY + 0, "3.自定义地图");
		WriteChar(Text_LOCX, Text_LOCY + 2, "4.双蛇大作战");
		WriteChar(Text_LOCX, Text_LOCY + 4, "5.删除地图");
		WriteChar(Text_LOCX, Text_LOCY + 6, "6.查看最高分");
		WriteChar(Text_LOCX, Text_LOCY + 8, "7.退出游戏");
		m_Choice = _getch();
		system("cls");
		SetHighScore();   //读取最高分
		switch (m_Choice)
		{
		case '1':
			MapChoice();  //选择了1就去选择地图
			break;
		case '2':
			if (!Load((char*)g_TEXT_LOC))  //读取属性
			{
				break;
			}
			MyArea.Set_FoodExist(1);  //食物存在设置为1
			GameBegin();  //进入游戏
			break;
		case '3':
			CustomMap();  //自定义地图
			break;
		case '4':
			DoubleSnake();  //双蛇大作战
			break;
		case '5':
			DeleteMap();  //删除地图
			break;
		case '6':
			GetHighSCore();  //获取历史最高成绩
			break;
		case '7':
			exit(0);  //退出游戏
			break;
		default:
			break;
		}
	}
}

/*************************
**功能：选择难度
**
**
***************************/
void CConsole::PrintHardChoice()
{
	int T = 1;  //退出循环标志
	while (T)
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "1.难度高");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.难度中");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.难度低");
		m_Hard = _getch();
		system("cls");
		switch (m_Hard)
		{
		case '1':
			m_Hard = 50;
			T = 0;
			break;
		case '2':
			m_Hard = 100;
			T = 0;
			break;
		case '3':
			m_Hard = 400;
			T = 0;
			break;
		default:
			break;
		}
	}
}

/********************************
**功能:打印出暂停的选择
**
**
**********************************/
void CConsole::SuspendGame()
{
	CConsole *Myconsole = new CConsole;
	int T = 1;
	while (T)
	{
		WriteChar(Text_LOCX, Text_LOCY, "1.继续游戏");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.保存游戏");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.回到菜单");
		m_Suspend = _getch();
		system("cls");
		switch (m_Suspend)
		{
		case '1':
			/*********重新打印刚才的数据**********/
			MyArea.Draw_Map(g_MaxX, g_MaxY);
			MyArea.ScoreBoard();
			MySnake[0].Snake_Score(0);
			T = 0;  //退出该循环
			break;
		case '2':
			SaveToFILE(g_TEXT_LOC);
			break;
		case '3':
			Myconsole->Begin();  //这一把不玩了，重新定义一个Myconsole，开始新的开始
			break;
		default:
			break;
		}
	}
}

/***************************
**功能：游戏失败后的选择
**
**
***************************/
void CConsole::GameOver()
{
	while (TRUE)
	{
		WriteChar(Text_LOCX, Text_LOCY, "你凉了");
		WriteChar(Text_LOCX, Text_LOCY + 2, "1.回到菜单");
		WriteChar(Text_LOCX, Text_LOCY + 4, "2.退出游戏");
		m_GameOverChoice = _getch();
		system("cls");
		CConsole *MyConsole = new CConsole;
		switch (m_GameOverChoice)
		{
		case '1':
			MyConsole->Begin();  //重新定义一个console来重新开始新的游戏
		case '2':
			exit(0);
		default:
			break;
		}
	}
}

/******************************
**功能：选择默认地图还是自定义地图
**
**
******************************/
void CConsole::MapChoice()
{
	CConsole *Myconsole = new CConsole;
	while (TRUE)
	{
		system("cls");
		WriteChar(Text_LOCX, Text_LOCY, "1.使用默认地图");
		WriteChar(Text_LOCX, Text_LOCY + 2, "2.使用自定义地图");
		WriteChar(Text_LOCX, Text_LOCY + 4, "3.回到菜单");
		m_Choice = _getch();
		switch (m_Choice)
		{
		case '1':
			ReadyGame();  //使用默认地图，游戏准备开始
			break;
		case '2':
			LoadMap();  //使用自定义地图
			break;
		case '3':
			Myconsole->Begin();  //这一把不玩了，重新定义一个Myconsole，开始新的开始
		default:
			break;
		}
	}
}

/**************************************
**功 能：播放音乐
**
**
***************************************/
void CConsole::Background_Music()
{
	PlaySoundA("sound\\begin.wav", NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP); // 播放音乐
}


/*************************************
**功 能：设置控制台形态（全屏、无光标、无滚动条)
**
**
***************************************/
SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput) 
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &info);
	return info.srWindow;
}
void CConsole::Full_Screen(HANDLE hOutput)
{
	/************设置全屏************/
	HWND hWnd = GetForegroundWindow();  //获取前景窗口句柄  
	int nCx = GetSystemMetrics(SM_CXSCREEN);  //检索屏幕宽度  
	int nCy = GetSystemMetrics(SM_CYSCREEN);  //检索屏幕高度  
	LONG l_WinStyle = GetWindowLong(hWnd, GWL_STYLE);  //窗口样式  
	SetWindowLong(hWnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);  // 设置窗口信息 最大化 取消标题栏及边框
	SetWindowPos(hWnd, HWND_TOP, 0, 0, nCx, nCy, 0);
	/************设置无光标************/

	CONSOLE_CURSOR_INFO cci;  //设置光标信息的结构体
	cci.dwSize = 1;  //一定要赋值才嫩隐藏
	cci.bVisible = FALSE;  //设置为不可见
	SetConsoleCursorInfo(hOutput, &cci);  //设置光标信息
	/************设置无滚动条************/
	CONSOLE_SCREEN_BUFFER_INFO info;  //设置缓冲区信息的结构体
	GetConsoleScreenBufferInfo(hOutput, &info);
	SMALL_RECT rect = SizeOfWindow(hOutput);  //、/获取窗口size
	COORD size = { rect.Right + 1,rect.Bottom + 1 };	//定义缓冲区大小 
	SetConsoleScreenBufferSize(hOutput, size);
	/**************一开始设置输入法为英文***************/
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);  //切换英文
	/***********************************/
}

/******************************
**功能：游戏一开始
**
**
********************************/
void CConsole::Begin()
{
	system("cls");
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //获取句柄
	/*定义一个控制台的类*/
	Full_Screen(hOutput);  //全屏
	Background_Music();  //播放背景音乐
	COORD position = {};
	SetConsoleCursorPosition(hOutput, position);
	SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << " ■■■  ■      ■        ■        ■       ■ ■■■■■           " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "■    ■ ■■    ■      ■  ■      ■     ■   ■     " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "■       ■ ■   ■     ■    ■     ■   ■     ■                       " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << " ■■■  ■  ■  ■    ■■■■■    ■■        ■■■■■ " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "      ■ ■   ■ ■   ■        ■   ■   ■     ■              " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "■    ■ ■    ■■  ■          ■  ■     ■   ■            " << endl;

	SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << " ■■■  ■      ■ ■            ■ ■       ■ ■■■■■             " << endl;

	Sleep(1000);
	PrintMenu();  //打印出一开始的菜单
	CloseHandle(hOutput);  //关闭句柄
}

/*************************
**功能：保存地图上的数据到文件中
**
**
**************************/
void CConsole::SaveToFILE(const char *FileName)  //保存地图上的数据到文件中
{
	FILE *pFile = NULL;
	fopen_s(&pFile, FileName, "wb+");
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			fprintf(pFile, "%d ", MyArea.Get_Map(i, j));
		}
	}
	fprintf(pFile, "%d ", MySnake[0].GetHealth());  //保存生命值
	fprintf(pFile, "%d ", MySnake[0].GetSCore());  //保存分数
	fprintf(pFile, "%d ", MySnake[0].GetDir());  //保存方向
	fprintf(pFile, "%d ", GetHard());  //保存难度
	fclose(pFile);
}

/**********************************
**功能：根据文件读取物体数据
**
**
***************************************/
bool CConsole::Load(char *FileName)  //根据文件读取数据
{
	FILE *pFile = NULL;
	fopen_s(&pFile, FileName, "rb+");
	if (!pFile)  //如果之前没有保存过的话
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先开始一把游戏");
		Sleep(1000);
		return false;
	}
	for (int i = 0; i < g_MaxX; i++)
	{
		for (int j = 0; j < g_MaxY; j++)
		{
			int Temp = 0;
			fscanf_s(pFile, "%d ", &Temp);
			MyArea.Set_Map(i, j, Temp);
		}
	}
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	fscanf_s(pFile, "%d ", &a);  
	fscanf_s(pFile, "%d ", &b);
	fscanf_s(pFile, "%d ", &c);
	fscanf_s(pFile, "%d ", &d);
	MySnake[0].SetHealth(a);  //设置生命值
	MySnake[0].SetSCore(b);  //设置成绩
	MySnake[0].SetDir(c);  //设置方向
	SetHard(d);  //设置难度
	fclose(pFile);
	MySnake[0].SetFlag(1);  //设置蛇的标志位为1代表不用初始化它了
}

/***************************
**功能：游戏准备开始
**
**
*****************************/
void CConsole::ReadyGame()
{
	system("cls");
	/*难度选择*/
	PrintHardChoice();
	/*设置为墙和空地*/
	MyArea.InitObject();
	/*设置食物和石头*/
	MyArea.CreateFood();
	MyArea.CreateRock();
	/*开始游戏并根据坐标画出物体*/
	GameBegin();
}

/*****************
**功能:游戏开始并画出物体
**
**
******************/
void CConsole::GameBegin()
{
	system("cls");
	/*根据坐标画出物体*/
	MyArea.Draw_Map(g_MaxX, g_MaxY);
	/*画出计分板*/
	MyArea.ScoreBoard();
	/*制造一条蛇在这里动*/
	MySnake[0].SnakeMove(this);   //蛇开始移动了
}

/**********************************
**功能:获得难度
**
**
**********************************/
int CConsole::GetHard()
{
	return m_Hard;
}

/*******************************
**功能：设置难度
**
**
*******************************/
void CConsole::SetHard(int n)  //设置难度
{
	m_Hard = n;
}

/**********************************
**功能:自定义地图
**
**
***********************************/
void CConsole::CustomMap()  //自定义地图
{
	/***********画出边框和计分板*****************/
	MyArea.InitObject();  
	MyArea.Draw_Map(g_MaxX, g_MaxY);  
	for (int i = g_ScoreX; i < 75; i++)
	{
		for (int j = 0; j < g_ScoreY; j++)
		{
			if (i == g_ScoreX || i == 74 || j == 0 || j == g_ScoreY - 1)
			{
				WriteChar(i, j, "※", FOREGROUND_GREEN | FOREGROUND_RED);
			}
			if (i == (g_ScoreX + 3) && j == 3)
			{
				WriteChar(i, j, "回车：保存");
				WriteChar(i, j+2, "ESC：撤销绘图");
				WriteChar(i, j + 4, "绿色是蛇初始位置");
			}
		}
	}
	/**********获取鼠标事件和键盘事件****************/
	HANDLE hInPut = GetStdHandle(STD_INPUT_HANDLE);  //获取句柄
	INPUT_RECORD ir = {};  //设置结构体
	DWORD dwCount = 0;
	SetConsoleMode(hInPut, ENABLE_MOUSE_INPUT);
	while (true)
	{
		ReadConsoleInput(hInPut, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)  //获取鼠标事件
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)  //设置障碍物
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X / 2 > g_MaxX - 2 || pos.X / 2 < 1 || pos.Y > g_MaxY - 2 || pos.Y < 1 || MyArea.Get_Map(pos.X/2,pos.Y) == 3 || MyArea.Get_Map(pos.X/2, pos.Y) == 5)  //范围判断
				{
					continue;
				}
				WriteChar(pos.X / 2, pos.Y , "■", FOREGROUND_BLUE | FOREGROUND_GREEN);
				MyArea.Set_Map(pos.X / 2, pos.Y, 4);
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)  //设置空地，撤销障碍物
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				WriteChar(pos.X / 2, pos.Y, " ");
				MyArea.Set_Map(pos.X / 2, pos.Y, 0);
			}
		}
		if (ir.EventType == KEY_EVENT)  //获取键盘事件
		{
			if (ir.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
			{
				struct tm t;   //tm结构指针
				time_t now;  //声明time_t类型指针
				time(&now);
				localtime_s(&t, &now);
				char tmp[64];
				char tmp2[64];
				strftime(tmp, sizeof(tmp), "Map\\%Y年%m月%d日%H点%M分%S秒",&t);  //用时间来做文件名
				strftime(tmp2, sizeof(tmp2), "Map\\%Y年%m月%d日%H点%M分%S秒", &t);
				SaveToFILE(tmp);  //保存地图
				SaveMapNametoFILE(tmp2);  //保存地图名
				system("cls");
				break;
			}
			else if (ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)  //不保存
			{
				system("cls");
				break;
			}
		}	
	}
}

/*******************************
**功能：加载地图列表
**
**
**********************************/
bool CConsole::LoadMap()
{
	char m_FileName[10][64] = {};  //十个图的名字
	system("cls");
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "rb+");

	if (!pFile)  //如果没有自定义地图的话会提示
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		return false;
	}
	char ch = fgetc(pFile);  //来检查第一个是不是FF，避免后面eof出错
	if (ch == -1)
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		fclose(pFile);
		return false;
	}
	int i = 0;  //获取地图数量
	
	rewind(pFile);  //又指向文件头了
	while (!feof(pFile))
	{
		fscanf_s(pFile, "%s ", m_FileName[i], 64);
		i++;
	}
	fclose(pFile);
	do
	{
		system("cls");
		for (int j = 0; j < i; j++)  //打印出地图例表中的地图名
		{
			WriteChar(Text_LOCX - 5, Text_LOCY + 2 * j, g_Num[j]);
			WriteChar(Text_LOCX - 3, Text_LOCY + 2 * j, (const char*)m_FileName[j]);
		}
		m_Choice = _getch() - 0x31;  //将数字的字符转换为数字-1
	} while (m_Choice > i-1);
	Load(m_FileName[m_Choice]);
	MySnake[0].SetHealth(3);  //因为只是加载地图而已，生命肯定为3
	MySnake[0].SetFlag(0);  //第一次
	PrintHardChoice();  //打印出难度
	MyArea.CreateFood();  //创造食物
	GameBegin();  //游戏开始
}

/**********************************
**功能：保存地图名到一个文件里面
**
**
***********************************/
void CConsole::SaveMapNametoFILE(char *tmp2)
{
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "ab+");
	fprintf(pFile, "%s ", tmp2);
	fclose(pFile);
}

/****************************
**功能:创建文件夹来存放地图
**
**
*******************************/
bool CConsole::CreateFolder()
{
	//文件夹名称
	char folderName[] = "Map";
	// 文件夹不存在则创建文件夹
	if (_access(folderName, 0) == -1)
	{
		_mkdir(folderName);
	}
	return false;
}

/**********************************
**功能：双蛇作战的时候开始初始化场地
**
**
*****************************/
void CConsole::DoubleSnake()
{
	system("cls");
	/*难度选择*/
	PrintHardChoice();
	/*设置为墙和空地*/
	MyArea.InitObject();
	/*设置食物和石头和超级食物*/
	MyArea.CreateFood();
	MyArea.CreateRock();
	MyArea.CreateSuperFood();
	/*根据坐标画出物体*/
	MyArea.Draw_Map(g_MaxX, g_MaxY);
	/*画出计分板*/
	MyArea.ScoreBoard();
	/*画出食物tips*/
	MyArea.DoubleFoodTips();
	/*双蛇开始移动了*/
	DoubleMove();
}

/***************************
**功能：双蛇开始移动
**
**
***************************/
void CConsole::DoubleMove()
{
	int T;
	MySnake[0].InitSnake(0);  //初始化第一条的
	MySnake[0].SetColor(FOREGROUND_GREEN);
	MySnake[1].InitSnake(1);  //初始化第二条的
	MySnake[1].SetColor(FOREGROUND_RED | FOREGROUND_GREEN);
	bool nLive = true;
	while (nLive)
	{
		char ch = '0';
		char ch2 = '0';
		int WHO;
		if (_kbhit() == 1)
		{
			ch = _getch();
		}
		WhichDir(ch, ch2, WHO);  //判断按键是哪条蛇要移动
		if (WHO == 0)  //如果是awsd则是第一条
		{
			MySnake[0].UserInput(this, 0, ch2);
		}
		else if (WHO == 1)  //如果是jkli则是第二条
		{
			MySnake[1].UserInput(this, WHO, ch2);
		}
		else if (ch == 27)  //ESC的时候
		{
			system("cls");
			DoubleSuspendGame();
		}
		MySnake[0].CleanSnake();
		MySnake[1].CleanSnake();
		int X1 = 0;
		int Y1 = 0;
		int X2 = 0;
		int Y2 = 0;
		COORD pos[2] = { { X1,Y1 },{X2,Y2} };
		if (MySnake[0].MovePos(MyArea, pos[0], 0) == false)
		{
			T = 0;
			nLive = false;
			break;
		}
		if (MySnake[1].MovePos(MyArea, pos[1], 1) == false)
		{
			T = 1;
			nLive = false;
			break;
		}
		MySnake[0].DrawSnake();
		MySnake[1].DrawSnake();
		if (MyArea.Get_FoodExist() == 0)
		{
			MyArea.CreateFood();
			WriteChar(MyArea.Getm_FoodPosX(),MyArea.Getm_FoodPosY(), "★", FOREGROUND_RED);
		}
		if (MyArea.Get_SuperFoodExist() == 0)
		{
			MyArea.CreateSuperFood();
			WriteChar(MyArea.Getm_SuperFoodPos().X, MyArea.Getm_SuperFoodPos().Y, "☆", FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		Sleep(m_Hard);
	}
	system("cls");
	DoubleGameOver(T);
}

/******************************
**功能：判断方向按钮是哪条蛇的
**
**
*****************************/
void CConsole::WhichDir(char ch,char &ch2, int &WHO)
{
	if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd')
	{
		ch2 = ch;
		WHO = 0;
	}
	else if(ch == 'i' || ch == 'k' || ch == 'j' || ch == 'l')
	{
		ch2 = ch;
		WHO = 1;
	}
}

/****************************
**
**
**
**************************/
void CConsole::DoubleGameOver(int n)
{
	while (TRUE)
	{
		char Name[10] = {};
		sprintf_s(Name, 10, "%d", n+1);
		WriteChar(Text_LOCX, Text_LOCY, Name);
		WriteChar(Text_LOCX+1, Text_LOCY, "号输了");
		WriteChar(Text_LOCX, Text_LOCY + 2, "1.回到菜单");
		WriteChar(Text_LOCX, Text_LOCY + 4, "2.退出游戏");
		m_GameOverChoice = _getch();
		system("cls");
		CConsole *MyConsole = new CConsole;
		switch (m_GameOverChoice)
		{
		case '1':
			MyConsole->Begin();  //重新定义一个console来重新开始新的游戏
		case '2':
			exit(0);
		default:
			break;
		}
	}
}

/********************************
**功能:打印出暂停的选择
**
**
**********************************/
void CConsole::DoubleSuspendGame()
{
	int T = 1;
	char Suspend = '0';
	while (T)
	{
		WriteChar(Text_LOCX, Text_LOCY, "1.继续游戏");
		WriteChar(Text_LOCX, Text_LOCY + 4, "2.回到菜单");
		CConsole *Myconsole = new CConsole;
		Suspend = _getch();
		system("cls");
		switch (Suspend)
		{
		case '1':
			/*********重新打印刚才的数据**********/
			MyArea.Draw_Map(g_MaxX, g_MaxY);
			MyArea.ScoreBoard();
			MySnake[0].Snake_Score(0);
			MySnake[1].Snake_Score(1);
			T = 0;  //退出该循环
			break;
		case '2':
			Myconsole->Begin();  //这一把不玩了，重新定义一个Myconsole，开始新的开始
			break;
		default:
			break;
		}
	}
}

/**********************************************
**功能:删除地图索引
**
**
**********************************************/
bool CConsole::DeleteMap()
{
	char m_FileName[10][64];  //十个图的名字
	vector<char*> DeleteName;
	char FileName2[10][64] = { 0 };
	system("cls");
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map\\MapName.txt", "rb+");
	if (!pFile)  //如果没有自定义地图的话会提示  
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		return false;
	}
	char ch = fgetc(pFile);  //来检查第一个是不是FF，避免后面eof出错
	if (ch == -1)
	{
		WriteChar(Text_LOCX, Text_LOCY, "请先自定义地图");
		Sleep(1000);
		fclose(pFile);
		return false;
	}
	int i = 0;  //获取地图数量
	
	rewind(pFile);  //又指向文件头了
	while (!feof(pFile))
	{
		fscanf_s(pFile, "%s ", m_FileName[i], 64);
		DeleteName.push_back(m_FileName[i]);
		i++;
	}
	fclose(pFile);
	do
	{
		system("cls");
		WriteChar(Text_LOCX - 5, Text_LOCY -2, "输入要删除地图的数字");
		for (int j = 0; j < i; j++)  //打印出地图例表中的地图名
		{
			WriteChar(Text_LOCX - 5, Text_LOCY + 2 * j, g_Num[j]);
			WriteChar(Text_LOCX - 3, Text_LOCY + 2 * j, (const char*)m_FileName[j]);
		}
		m_Choice = _getch() - 0x31;  //将数字的字符转换为数字-1
	} while (m_Choice > i - 1);
	DeleteName.erase(DeleteName.begin() + m_Choice);  //删除第几个元素
	for (int i = 0; i < DeleteName.size(); i++)
	{
		strcpy_s(FileName2[i], 64, DeleteName[i]);
	}
	FILE *pFile1 = NULL;
	fopen_s(&pFile1, "Map\\MapName.txt", "wb+");
	for (int i = 0; i < DeleteName.size(); i++)
	{
		fprintf(pFile, "%s ", FileName2[i]);
	}
	fclose(pFile1);
}

/*************************************
**功能：设置最高分数
**
**
***************************************/
int CConsole::SetHighScore()
{
	FILE *pFile = NULL;
	fopen_s(&pFile, "Map//HighScore.txt", "rb");
	if (!pFile)
	{
		g_HighScore = 0;
		//fclose(pFile);
		return 0;
	}
	fscanf_s(pFile, "%d", &g_HighScore);
	fclose(pFile);
	return 0;
}

/*****************************
**功能：获取最高分数
**
**
*******************************/
void CConsole::GetHighSCore()
{
	system("cls");
	char Score[10] = {};
	sprintf_s(Score, 10, "%d", g_HighScore);
	WriteChar(Text_LOCX, Text_LOCY, "历史最高分数为:");
	WriteChar(Text_LOCX+7, Text_LOCY, Score);
	Sleep(1500);
}
