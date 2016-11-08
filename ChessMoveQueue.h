#pragma once

////////////////////////////////////////////////////////////////
//              文件名称：ChessMoveQueue.h 
//              功    能: 华容道棋盘变化队列类
//				创建时间：2016年11月6日
//				创建  人：魏菲
////////////////////////////////////////////////////////////////



struct ChessMove      //棋盘走步集合
{ 
	char nowDir[10];	//原位置
	char targetDir[10]; //目标位置  最多只会有10步
	int stepNum;      //总步数
};

class ChessMoveQueue
{
public:
	//功能：华容道棋盘变化队列类的构造函数
	//传入参数: int k  队列的可用总长度
	ChessMoveQueue(int k);

	~ChessMoveQueue();

	//功能：分析当前棋盘的状态选出可以移动的位置存入到ChessMove中
	//传入参数: char *chessData  棋盘数据，ChessMove *cm 要存入的可移动位置的结构体
	void AnalyzeMove(char *chessData,ChessMove *cm);

	//功能：根据当前位置与移动位置移动棋盘上的数据
	//传入参数: char *chessData  棋盘数据，int nowDir;棋盘上要移动的点，int targetDir移动到的位置
	void MoveFromTo(char *chessData,int nowDir,int targetDir);

	//功能：取出队列中的一个元素并进行分析
	//传入参数: char *chessData  分析移动后的棋盘数据作为返回
	//返回： int  0为步出队 1为步集出队不用处理
	int QueuePop(char *chessData); //走步出队

	//功能：将chessData放入队列尾部
	//传入参数: char *chessData  棋盘数据
	void QueuePush(char *chessData); //走步入队

	//功能：回溯找到存储自己的上一层直到顶层
	//传入参数: cs  层数，从第cs层开始至首层
	void BackTo(int cs);  

	//功能：回溯找到存储自己的上一层直到顶层
	//传入参数: cs  层数，从第cs层开始至首层
	char* GetRe(int n);//取第n步盘面

	char (*cmQueue)[20];   //队列
	ChessMove cm;
	int queueLength;       //队长度
	int *hs,*hss;		   //回溯用的指针及棋子
	int m,cur;             //队头及队头内步集游标,用于广度搜索
	int max;               //最大队长
	int *res,ren;          //结果
};

