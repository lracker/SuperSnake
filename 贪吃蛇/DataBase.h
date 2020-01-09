#pragma once
#define g_MaxX 60  //围墙的边框X
#define g_MaxY 44  //围墙的边框Y
#define g_ScoreX 60  //计分板的边框X
#define g_ScoreY 15  //计分板的边框Y
#define g_InitLen 4  //蛇初始化的长度
#define g_RockNum 40  //障碍物的数量
#define Text_LOCX 35  //显示文字位置的X坐标  
#define Text_LOCY 22  //显示蚊子位置的Y坐标
#define g_TEXT_LOC "Map\\Suspendgame.txt"  //保存下来的游戏
#define UP 0  //上
#define DOWN 1  //下
#define LEFT 2   //左
#define RIGHT 3  //右

extern int g_HighScore;  //定义最高分
const char g_Num[10][10] = { "1","2","3","4","5","6","7","8","9","10" };  //用于在列出地图列表的时候输出12345....

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

