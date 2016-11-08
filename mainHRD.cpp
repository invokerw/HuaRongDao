/*************************************************************************
	> File Name: mainHRD.cpp
	> Author: 魏菲
	> Created Time: 2016年11月07日 星期一 19时17分17秒
	> Function : 执行华容道的主程序 ************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "AutoSolveHRD.h"
#include "Chess.h"
#include <curses.h> //
using namespace std;

//功能：显示控制台上的信息，包括棋盘提示游戏类型等。
void ShowChess(int data[MAX_ROW][MAX_COLUMN],string strGameMode,int step)
{
	cout<<"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆"<<endl;
	cout<<"☆                                      ☆                                  ☆"<<endl;
	cout<<"☆                                      ☆              华容道              ☆"<<endl;
	int i ,j;
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

		if(i == 0)
			strTmp = "   回味经典华容道.          ";
		else if(i == 1)
			strTmp = "   开局类型: "+ strGameMode + "      ";
		else if(i == 2)
			strTmp = "   操作指南：本游戏完全由键 ";
		else if(i == 3)
			strTmp = "     盘操控,0-9选择武将，w  ";
		else if(i == 4)
			strTmp = "     a s d控制武将上下左右  ";
		else if(i == 5)
			strTmp = "     q  键更换游戏开局类型  ";
		else
			strTmp = "                            ";
		cout<<"      ☆  "<<strTmp<<"    ☆"<<endl;
	}
	cout<<"☆                                      ☆     e键自动完成本状态华容道      ☆"<<endl;
	sprintf((char *)strTmp.c_str(),"      第%03d步",step);
	cout<<"☆          "<<strTmp<<"   ☆     f保存数据    r读取数据       ☆"<<endl;
	cout<<"☆                                      ☆                                  ☆"<<endl;
	cout<<"☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆\
☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆"<<endl;}

int main()
{
	Chess cs(0);
	int select = 0;
	char cmd; //用户命令操作
	string strTips = "提示：0 - 9选择武将，上下左右箭头控制武将移动 ";
	string strTmp;
	while(1)
	{
		system("clear");
		cs.GetNowGameMode(strTmp);
		ShowChess(cs.m_chessData, strTmp, cs.m_step);
		if(cs.isWin())
		{
			cout<<"恭喜完成游戏 >.<";
			break;
		}
		cout<<"当前选中的为【"<<select<<"】"<<endl;
		cout<<strTips<<endl;
		//cmd = _getch();
		cmd = getchar();
		//cout<<"你输入的是:"<<cmd<<endl;
		if(cmd >= 0x30 && cmd <= 0x39) //数字0 -9
		{
			select = cmd - 0x30;
			strTips = "提示：改变选中武将成功";
		}
		else if(cmd == 'q' || cmd == 'Q') //q键被按下
		{
			cs.ChangeMode();
		}
		else if(cmd == 'e' || cmd == 'E') //e键被按下
		{
			SolveNowChess(cs.m_chessData);
		}
		else if(cmd == 'f' || cmd == 'F') //f键被按下
		{
			cs.SaveToFile();
			strTips = "提示：保存成功.";
		}
		else if(cmd == 'r' || cmd == 'R') //r键被按下
		{
			if(cs.ReadFromFile())
			{
				strTips = "提示：读取成功.";
			}
			else
				strTips = "提示：读取失败，文件可能不存在或被损坏。";
		}
		//else if(cmd == 224) //判断上下左右箭头
		//{
			//cmd = _getch();
		//	cmd = getchar();
		else if (cmd == 'w' || cmd == 'W')      //是  w 代替上箭头
		{
			if(cs.GoUp(select))
				strTips = "提示：棋子向上移动成功";
			else
				strTips = "提示：棋子向上移动失败";
		}
		else if (cmd== 's' || cmd == 'S')  //  是  s 代替下箭头
		{
			if(cs.GoDown(select))
				strTips = "提示：棋子向下移动成功";
			else
				strTips = "提示：棋子向下移动失败";
		}
		else if (cmd== 'a' || cmd == 'A')  // 是 a代替左箭头；
		{
			if(cs.GoLeft(select))
				strTips = "提示：棋子向左移动成功";
			else
				strTips = "提示：棋子向左移动失败";
		}
		else if (cmd== 'd' || cmd == 'D')  // 是 d代替右箭头
		{
			if(cs.GoRight(select))
				strTips = "提示：棋子向右移动成功";
			else
				strTips = "提示：棋子向右移动失败";
		}
		

		//}
	}
	
	//system("pause");
	return 0;
}

