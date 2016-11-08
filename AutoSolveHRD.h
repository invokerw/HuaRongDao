#pragma once

////////////////////////////////////////////////////////////////
//              文件名称：AutoSolveHRD.h 
//              功    能: 使用BFS解决华容道移动问题
//				创建时间：2016年11月6日
//				创建  人：魏菲
////////////////////////////////////////////////////////////////
#include "Chess.h"

//函数功能：打印棋盘
//输入参数：chessData 5 * 4棋盘数据
//int data[][]  为优化简便将已经初始化好的棋盘传入
//int step 当前第多少步
//int allStep总共有多少步
extern void PrintChess(char *chessData,int **data,int step,int allStep);  

//函数功能：广度优先遍历计算华容道结果
//输入参数：chessData 当前5 * 4棋盘数据 dep搜索最大深度
extern void BFSSolveHRD(char *chessData,int dep); 


//函数功能：实现本身棋盘数据到解决问题棋盘数据的转换
//输入参数：int data[MAX_ROW][MAX_COLUMN]棋盘类Chess中棋盘数据
extern void SolveNowChess(int data[MAX_ROW][MAX_COLUMN]);
