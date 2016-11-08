#pragma once
///////////////////////////////////////////////////////////////////////
//              文件名称：Chess.h
//              功    能: 华容道棋盘类,包括华容道棋盘初始化以及棋子移动
//				创建时间：2016年11月4日22:22:36
//				创建  人：魏菲
///////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;
#define MAX_ROW        7   //最大行数为7行，包括两面墙。
#define MAX_COLUMN     6   //最大列数为6列，包括两面墙。

#define MAX_CHESSMAN   10  //定义最大的棋子数为10

#define MAX_CHESS_MODE  4  //定义最大的游戏开局模式

#define FILE_NAME    "data.chess"  //保存的文件名字
enum ChessMan             //棋子
{
	QIANG = -2,   //墙体
	KONGBAI,      //空白位置
	CAOCAO,       //曹操
	GUANYU,       //关羽
	ZHANGFEI ,    //张飞
	ZHAOYUN,	  //赵云
	MACHAO,		  //马超
	HUANGZHONG,   //黄忠
	ZU1,		  //小卒1
	ZU2,		  //小卒2
	ZU3,          //小卒3
	ZU4           //小卒4
};

enum GameMode  //游戏开局类型
{
	HENGDAOLIMA1 = 0,  //横刀立马1
	HENGDAOLIMA2,      //横刀立马2
	QITOUBINGJIN,      //齐头并进
	BINGFENSANLU,      //兵分三路
};

typedef struct POINT
{
	int x; //x点坐标
	int y; //y点坐标
}Point,*PPoint;

class Chess
{
public:
	Chess(int mode = 0); //mode 设置方式
	~Chess(void);

	//功能：初始化棋盘数据，放置棋子的位置。
	//传入参数：int mode  int类型的数据代表游戏类型。
	void IniChess(int mode);

	//功能：棋子向上走 
	//传入参数： chessMan  棋子的种类
	bool GoUp(int chessMan);

	//功能：棋子向下走 
	//传入参数： chessMan  棋子的种类
	bool GoDown(int chessMan);

	//功能：棋子向左走 
	//传入参数： chessMan  棋子的种类
	bool GoLeft(int chessMan);

	//功能：棋子向右走 
	//传入参数： chessMan  棋子的种类
	bool GoRight(int chessMan);

	//功能：改变游戏的模式，游戏总共有n种模式，每次切换mode+1 到n直接变为0
	void ChangeMode();

	//功能：获取当前游戏的模式。
	//返回：模式所对应的int 名字由string类型引用传回，请见enum GameMode
	int GetNowGameMode(string &strName);

	//功能:判断曹操是否逃出生天
	bool isWin();

	//////////////////////////////////////////////
	//以C++标准流写入数据至
	//数据写入顺序：
	//       当前游戏类型：m_nowMode
	//       走的步数    ：m_setp
	//       棋盘数据    ：m_chessData
	//       棋子位置点  ：m_chessManPoint
	//读取相同
	//////////////////////////////////////////////
	//写入棋盘数据到文件中
	bool SaveToFile();

	//读取文件数据
	bool ReadFromFile();

	//棋盘数据
	int m_chessData[MAX_ROW][MAX_COLUMN];

	//已走步数
	int m_step; 

private:
	//功能：设置游戏类型  如横刀立马1 横刀立马2
	//传入参数：int mode  int类型的数据代表游戏类型。
	void SetGameMode(int mode);

	int m_nowMode;  //当前的游戏类型  
	Point m_chessManPoint[MAX_CHESSMAN];//棋盘上棋子的初始点左上角



};

