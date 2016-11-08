#include "ChessMoveQueue.h"
#include "ChessEncoded.h"
#include <iostream>
using namespace std;

ChessMoveQueue::ChessMoveQueue(int k)
{
	cmQueue = new char[k][20]; 
	hs = new int[k * 2 + 500]; 
	hss = hs + k;
	res = hss + k;
	max = k;
	queueLength = 0; 
	m = 0,
	cur = -1; 
	hss[queueLength] = -1; 
	ren = 0;
}


ChessMoveQueue::~ChessMoveQueue(void)
{
	delete[] cmQueue; 
	delete[] hs;
}

#define spacecheck(i)  (i == space1 || i == space2)     //空格判断宏
#define spacecheck1(i) (i == space1 && spaceType == 1)  //竖联空格判断宏
#define spacecheck2(i) (i == space1 && spaceType == 2)  //横联空格判断宏
#define savemove(des) cm->nowDir[cm->stepNum] = i,cm->targetDir[cm->stepNum] = des,cm->stepNum++ //保存步法宏


//以下define用于棋盘复制,不要用环循,实地址直接引用要快
#define qpcpy(q1,q2) {/*复制棋盘*/\
	int *data1 = (int*)q1,*data2 = (int*)q2;\
	data1[0] = data2[0], data1[1] = data2[1], data1[2] = data2[2], data1[3] = data2[3], data1[4] = data2[4];\
}

void ChessMoveQueue::AnalyzeMove(char *chessData,ChessMove *cm)//分析当前可能的步法,并将所有可能的步法保存在cmQueue中
{ 
	int i;
	int col;//列
	int space1 = 0;//空格1位置
	int space2 = 0;//空格2位置
	int spaceType = 0; //两空格的联合类型  包括空格竖联合与空格横联合
	char c, lx;
	char f[16] = {0}; //f[]记录已判断过的棋字
	cm->stepNum = 0;  //计步复位

	for(i = 0;i < 20;i++)
	{
		if(!chessData[i]) 
		{
			space1 = space2;
			space2 = i; //查空格的位置
		}
	}

	if(space1 + 4 == space2) 
		spaceType = 1;            //空格竖联合
	if(space1 + 1 == space2 && COL[space1] < 3) 
		spaceType = 2;            //空格横联合

	for(i = 0;i < 20;i++)
	{
		c = chessData[i];
		lx = U[c];
		col = COL[i];

		if(f[c]) 
			continue;

		switch(lx)
		{
		case 'M': //曹操可能的走步
			if(spacecheck2(i + 8))            savemove(i + 4);  //向下
			if(spacecheck2(i - 4))            savemove(i - 4);  //向上
			if(col < 2 && spacecheck1(i + 2)) savemove(i + 1);  //向右
			if(col  && spacecheck1(i - 1))    savemove(i - 1);  //向左
			f[c] = 1; 
			break;

		case 'H': //关羽可能的走步
			if(spacecheck2(i + 4))        savemove(i + 4);  //向下
			if(spacecheck2(i - 4))        savemove(i - 4);  //向上
			if(col < 2 && spacecheck(i + 2))           //向右
			{
				savemove(i + 1); 
				if(spaceType == 2) 
					savemove(space1); 
			}  
			if(col > 0 && spacecheck(i - 1))           //向左
			{
				savemove(i - 1);
				if(spaceType == 2)
					savemove(space1); 
			}
			f[c] = 1; 
			break;

		case 'C': //张飞,马超,赵云,黄忠可能的走步
			if(spacecheck(i + 8))                  //向下       
			{
				savemove(i + 4); 
				if(spaceType == 1)
					savemove(space1); 
			} 			
			if(spacecheck(i - 4))                  //向上
			{
				savemove(i - 4);
				if(spaceType == 1)
					savemove(space1); 
			}  
			if(col < 3 && spacecheck1(i + 1))      //向右
				savemove(i + 1);  
			if(col > 0 && spacecheck1(i - 1))      //向左
				savemove(i - 1);  
			f[c] = 1; 
			break;
		case 'B': //小兵可能的走步
			if(spacecheck(i + 4))
			{ 
				if(spaceType)
				{
					savemove(space1);
					savemove(space2);
				}
				else 
					savemove(i + 4);
			} //向上
			if(spacecheck(i - 4))
			{ 
				if(spaceType)
				{
					savemove(space1);
					savemove(space2);
				} 
				else 
					savemove(i - 4);
			} //向下
			if(col < 3 && spacecheck(i + 1)) 
			{ 
				if(spaceType)
				{
					savemove(space1);
					savemove(space2);
				} 
				else 
					savemove(i + 1); 
			} //向右
			if(col > 0 &&spacecheck(i - 1)) 
			{ 
				if(spaceType)
				{
					savemove(space1);
					savemove(space2);
				} 
				else 
					savemove(i - 1); 
			} //向右
			break;
		}
	}
}

void ChessMoveQueue::MoveFromTo(char *chessData,int nowDir,int targetDir)
{ //走一步函数
	char c = chessData[nowDir];
	char lx = U[c];
	switch(lx)
	{
	case 'B': 
		{
			chessData[nowDir] = 0;        
			chessData[targetDir] = c;          
			break; 
		}
	case 'C': 
		{
			chessData[nowDir] = chessData[nowDir + 4]=0; 
			chessData[targetDir] = chessData[targetDir + 4] = c;   
			break; 
		}
	case 'H': 
		{ 
			chessData[nowDir] = chessData[nowDir + 1] = 0;
			chessData[targetDir] = chessData[targetDir + 1] = c; 
			break;
		}
	case 'M': 
		{
			chessData[nowDir] = chessData[nowDir + 1] = chessData[nowDir + 4] = chessData[nowDir + 5] = 0;
			chessData[targetDir] = chessData[targetDir + 1] = chessData[targetDir + 4] = chessData[targetDir + 5] = c;
			break;
		}
	}
}

int ChessMoveQueue::QueuePop(char *chessData) //走步出队
{
	if(cur == -1) 
		AnalyzeMove(cmQueue[m], &cm);
	cur++; 
	if(cur >= cm.stepNum) //步集游标控制
	{
		m++;
		cur = -1; 
		return 1;
	} 

	if(hss[m] == cm.nowDir[cur]) //和上次移动同一个棋子时不搜索
		return 1;

	qpcpy(chessData, cmQueue[m]); 

	MoveFromTo(chessData, cm.nowDir[cur], cm.targetDir[cur]); //走步后产生新节点,结果放在chessData中
	return 0;
}
void ChessMoveQueue::QueuePush(char *chessData)//走步入队
{ 
	if(queueLength >= max) 
	{ 
		cout<<"队溢出."<<endl; 
		return; 
	}
	qpcpy(cmQueue[queueLength], chessData); //入队
	if(cur >= 0) 
		hss[queueLength] = cm.targetDir[cur]; //记录移动的子(用于回溯)
	hs[queueLength++] = m; //记录回溯点
}

void ChessMoveQueue::BackTo(int cs) //参数:层数
{ 
	int k = cs - 2; 
	ren=cs;
	res[cs - 1] = m;
	for(;k >= 0;k--) 
		res[k] = hs[res[k + 1]]; //回溯
}
char* ChessMoveQueue::GetRe(int n)//取第n步棋盘数据
{ 
	return cmQueue[res[n]];
} 
