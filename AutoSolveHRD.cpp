#include "AutoSolveHRD.h"

#include <string.h>
#include "ChessMoveQueue.h"
#include "ChessEncoded.h"
#include <stdlib.h>
#include "Chess.h"
#include <iostream>
#include <stdio.h>
using namespace std;

//chess内部存储棋盘数据 转换为 解华容道需要棋盘数据
int chessChange1[11] = {0,15,11,5,6,7,8,1,2,3,4};

//解华容道需要棋盘数据 转换为 chess内部存储棋盘数据
int chessChange2[16] = { KONGBAI, ZU1, ZU2, ZU3,
	ZU4, ZHANGFEI, ZHAOYUN, MACHAO,
	HUANGZHONG, -1, -1, GUANYU,
	-1, -1, -1, CAOCAO};

void PrintChess(char *chessData,int **data,int step,int allStep)  //打印棋盘
{
	int i,j ,k = 0;


	for(i = 1;i < MAX_ROW - 1;i++)
		for(j = 1;j < MAX_COLUMN - 1;j++)
		{
			data[i][j] = chessChange2[chessData[k++]];
		}
	cout<<"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆"<<endl;		
	cout<<"☆                                      ☆                                   ☆"<<endl;
	cout<<"☆                                      ☆              华容道               ☆"<<endl;

	string strTmp;
	for(i = 0;i < MAX_ROW;i++)
	{
		cout<<"☆        ";
		for(j = 0;j <MAX_COLUMN;j++)
		{
			if(i == 0 && data[i][j] == QIANG)
			{
				cout<<"--"<<"  ";
			}
			else if((j == 0 || j == MAX_COLUMN -1 )&& data[i][j] == QIANG)
				cout<<"| "<<"  ";
			else if(i == MAX_ROW - 1 && data[i][j] == QIANG)
				cout<<"--"<<"  ";
			else if(data[i][j] == KONGBAI)
				cout<<" "<<"   ";
			else
				cout<<data[i][j]<<"   ";
		}

		if(i == 2)
			strTmp = "    自动运行华容道中.            ";
		else if(i == 4)
		{
			sprintf((char *)strTmp.c_str(),"        第%03d步,共%03d步\t",step,allStep);
		}
		else
			strTmp = "                                 ";
		cout<<"      ☆  "<<strTmp<<"☆"<<endl;
	}
	cout<<"☆                                      ☆                                   ☆"<<endl;
	cout<<"☆                                      ☆                                   ☆"<<endl;
	cout<<"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆"<<endl;
	cout<<"回车键继续下一步..."<<endl;
}

void BFSSolveHRD(char *chessData,int dep) //参数为棋盘及搜索最大深度
{
	int i,k,bm; //ok表示是否找到

	int js = 0;   //遍历的节点数
	int js2 = 0;  //实际有用的节点数

	ChessEncoded cm(chessData); //建立编码器

	char *node = new char[cm.codeTotalNum]; 

	memset(node,0,cm.codeTotalNum);

	ChessMoveQueue cmq = ChessMoveQueue(cm.codeTotalNum / 10); //建立队

	for(cmq.QueuePush(chessData),i = 1;i <= dep;i++) //一层一层的搜索
	{
		k = cmq.queueLength;

		while(cmq.m < k) //广度优先
		{ 
			if(cmq.QueuePop(chessData) == 1)   //返回1说明是步集出队,不是步出队
				continue;   
			js++;
			if(chessData[17] == 15 && chessData[18] == 15) //曹操出来了
			{ 
				cmq.BackTo(i);
				goto end;
			}
			if(i == dep) //到了最后一层可以不再入队了
				continue; 
			bm = cm.Encoded(chessData);
			if(node[bm] == 0)
			{
				js2++ ;  //js搜索总次数计数和js2遍历的实结点个数
				node[bm]=1;
				node[cm.SymmetryEncoded(chessData)] = 1;//对节点及其对称点编码
				cmq.QueuePush(chessData);
			}
		}
	}
end:delete node;
	//printf("共遍历%d个节点,其中实结点%d.队长%d,搜索层数%d,任意键...\r\n",js,js2,cmq.queueLength,cmq.ren);
	if(!cmq.ren) 
	{ 
		printf("此局%d步内无解...",dep); 
		return; 
	}
	printf("\r\n共%d步解决此问题,展示请按任意键继续...",cmq.ren);


	int **data;
	data = new int *[MAX_ROW + 1];
	for(i = 0;i < MAX_ROW + 1;i++)
		data[i] = new int[MAX_COLUMN + 1];
	//围出墙体
	for(i = 0;i < MAX_ROW;i++)
	{
		data[i][0] = QIANG;
		data[i][MAX_COLUMN -1] = QIANG;
	}
	for(i = 0;i < MAX_ROW;i++)
	{
		data[0][i] = QIANG;
		data[MAX_ROW - 1][i] = QIANG;
	}
	//输出结果
	char tmp; //没有作用单纯只是获取一个字符进行下一步
	for(i=0;i<cmq.ren;i++) 
	{ 
		//_getch();   windows中用这个。
		cin.get(tmp);
		system("clear"); 
		PrintChess(cmq.GetRe(i), data,i + 1, cmq.ren);
	}
	for(int i = 0; i < MAX_ROW; i++)
		delete [] data[i];
	delete []data;
}

void SolveNowChess(int data[MAX_ROW][MAX_COLUMN])
{
	int i ,j, k = 0;
	char chess[20];
	//使用chessChange1实现 chess内部存储棋盘数据与解华容道需要棋盘数据之间的转换
	for(i = 1;i < MAX_ROW - 1;i++)
	{
		for(j = 1;j < MAX_COLUMN - 1;j++)
		{
			chess[k++] = chessChange1[data[i][j] + 1];
		}
	}
	//横刀立马为81层深度即可解决。
	BFSSolveHRD(chess, 200);
}
