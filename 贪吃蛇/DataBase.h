#pragma once
#define g_MaxX 60  //Χǽ�ı߿�X
#define g_MaxY 44  //Χǽ�ı߿�Y
#define g_ScoreX 60  //�Ʒְ�ı߿�X
#define g_ScoreY 15  //�Ʒְ�ı߿�Y
#define g_InitLen 4  //�߳�ʼ���ĳ���
#define g_RockNum 40  //�ϰ��������
#define Text_LOCX 35  //��ʾ����λ�õ�X����  
#define Text_LOCY 22  //��ʾ����λ�õ�Y����
#define g_TEXT_LOC "Map\\Suspendgame.txt"  //������������Ϸ
#define UP 0  //��
#define DOWN 1  //��
#define LEFT 2   //��
#define RIGHT 3  //��

extern int g_HighScore;  //������߷�
const char g_Num[10][10] = { "1","2","3","4","5","6","7","8","9","10" };  //�������г���ͼ�б��ʱ�����12345....

const char s[][93] = {
"																			 ^",
"					@@@                                                     *@",
"					@3 u@                                                   u@",
"					@8   a@.                                                u@",
"					@8     a@                                               u@",
"					@8       a@  @       &@8                   @@@       @  u@       n@          .@@&",
"					@8           @     a@   @#               @@   @@     @  u@     ~@. + @.   @#",
"					@8           @   v@       @#           @@       @@   @  u@   ^@.         *@.       @$",
"					@8           @ ~@.          @#       @#           @@ @  u@ .@^         ~@.           @%",
"					@8           @@               @#   @@               @@  u@@~; @@$$$$$$$$$$$$$$@@n",
"			@^      @@           @                 @*   @o             #@@  u@@           @#",
"			  @~    @@           @                 @* + @-         $@  @  u# %@           @@",
"				@v  @@           @                 @*; @.     3@    @  u#   $@           @@      @@",
"				  @i%@           @                 @*        !@  !@      @  u#     #@           @@  @@",
"					@$           @                 u           #@        @  u#       @@           @@" };

