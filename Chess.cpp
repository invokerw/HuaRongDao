#include "Chess.h"
#include <fstream>

Chess::Chess(int mode)
{ 
	//初始化棋盘
	
	IniChess(mode);
}


Chess::~Chess(void)
{
}

void Chess::IniChess(int mode)
{
	int i,j;
	for(i = 0;i < MAX_ROW;i++)
		for(j = 0;j < MAX_COLUMN;j++)
			m_chessData[i][j] = KONGBAI;
	//围出墙体
	for(i = 0;i < MAX_ROW;i++)
	{
		m_chessData[i][0] = QIANG;
		m_chessData[i][MAX_COLUMN -1] = QIANG;
	}
	for(i = 0;i < MAX_ROW;i++)
	{
		m_chessData[0][i] = QIANG;
		m_chessData[MAX_ROW - 1][i] = QIANG;
	}

	//设置游戏类型
	SetGameMode(mode);

	//初始化游戏步数
	m_step = 0;

	//根据m_chessManPoint所填写的位置填充棋子

	//曹操的棋子是正方形占四个格子
	m_chessData[m_chessManPoint[CAOCAO].x][m_chessManPoint[CAOCAO].y] = CAOCAO;
	m_chessData[m_chessManPoint[CAOCAO].x + 1][m_chessManPoint[CAOCAO].y] = CAOCAO;
	m_chessData[m_chessManPoint[CAOCAO].x][m_chessManPoint[CAOCAO].y + 1] = CAOCAO;
	m_chessData[m_chessManPoint[CAOCAO].x + 1][m_chessManPoint[CAOCAO].y + 1] = CAOCAO;

	//关羽是横向的占两个格子
	m_chessData[m_chessManPoint[GUANYU].x][m_chessManPoint[GUANYU].y] = GUANYU;
	m_chessData[m_chessManPoint[GUANYU].x][m_chessManPoint[GUANYU].y + 1] = GUANYU;

	//四位大将是竖向的所以用循环直接填充
	for(i = ZHANGFEI;i <= HUANGZHONG;i++)
	{
		m_chessData[m_chessManPoint[i].x][m_chessManPoint[i].y] = i;
		m_chessData[m_chessManPoint[i].x + 1][m_chessManPoint[i].y] = i;
	}

	//四个小卒只占一个位置
	for(i = ZU1;i <= ZU4;i++)
		m_chessData[m_chessManPoint[i].x][m_chessManPoint[i].y] = i;

}

void Chess::ChangeMode()
{
	if(m_nowMode == MAX_CHESS_MODE - 1)
		m_nowMode = HENGDAOLIMA1;
	else
		m_nowMode++;
	IniChess(m_nowMode);
}
int Chess::GetNowGameMode(string &strName)
{

	if(m_nowMode == HENGDAOLIMA1)
		strName = "横刀立马1";
	else if(m_nowMode == HENGDAOLIMA2)
		strName = "横刀立马2";
	else if(m_nowMode == QITOUBINGJIN)
		strName = "齐头并进 ";
	else if(m_nowMode == BINGFENSANLU)
		strName = "兵分三路 ";
	else
		strName = "         ";
	return m_nowMode;
}
void Chess::SetGameMode(int mode)
{
	m_nowMode = mode;
	switch (m_nowMode)
	{
	case HENGDAOLIMA1:  //模式横刀立马1 初始化各个棋子的点
		{
			m_chessManPoint[CAOCAO].x = 1;
			m_chessManPoint[CAOCAO].y = 2;

			m_chessManPoint[GUANYU].x = 3;
			m_chessManPoint[GUANYU].y = 2;

			m_chessManPoint[ZHANGFEI].x = 1;
			m_chessManPoint[ZHANGFEI].y = 1;

			m_chessManPoint[ZHAOYUN].x = 1;
			m_chessManPoint[ZHAOYUN].y = 4;

			m_chessManPoint[MACHAO].x = 3;
			m_chessManPoint[MACHAO].y = 1;

			m_chessManPoint[HUANGZHONG].x = 3;
			m_chessManPoint[HUANGZHONG].y = 4;

			m_chessManPoint[ZU1].x = 5;
			m_chessManPoint[ZU1].y = 1;

			m_chessManPoint[ZU2].x = 4;
			m_chessManPoint[ZU2].y = 2;

			m_chessManPoint[ZU3].x = 4;
			m_chessManPoint[ZU3].y = 3;

			m_chessManPoint[ZU4].x = 5;
			m_chessManPoint[ZU4].y = 4;
		}
		break;
	case HENGDAOLIMA2:  //模式横刀立马2
		{
			m_chessManPoint[CAOCAO].x = 1;
			m_chessManPoint[CAOCAO].y = 2;

			m_chessManPoint[GUANYU].x = 3;
			m_chessManPoint[GUANYU].y = 2;

			m_chessManPoint[ZHANGFEI].x = 1;
			m_chessManPoint[ZHANGFEI].y = 1;

			m_chessManPoint[ZHAOYUN].x = 1;
			m_chessManPoint[ZHAOYUN].y = 4;

			m_chessManPoint[MACHAO].x = 4;
			m_chessManPoint[MACHAO].y = 1;

			m_chessManPoint[HUANGZHONG].x = 4;
			m_chessManPoint[HUANGZHONG].y = 4;

			m_chessManPoint[ZU1].x = 3;
			m_chessManPoint[ZU1].y = 1;

			m_chessManPoint[ZU2].x = 4;
			m_chessManPoint[ZU2].y = 2;

			m_chessManPoint[ZU3].x = 4;
			m_chessManPoint[ZU3].y = 3;

			m_chessManPoint[ZU4].x = 3;
			m_chessManPoint[ZU4].y = 4;
		}
		break;
	case QITOUBINGJIN:  //模式齐头并进
		{
			m_chessManPoint[CAOCAO].x = 1;
			m_chessManPoint[CAOCAO].y = 2;

			m_chessManPoint[GUANYU].x = 4;
			m_chessManPoint[GUANYU].y = 2;

			m_chessManPoint[ZHANGFEI].x = 1;
			m_chessManPoint[ZHANGFEI].y = 1;

			m_chessManPoint[ZHAOYUN].x = 1;
			m_chessManPoint[ZHAOYUN].y = 4;

			m_chessManPoint[MACHAO].x = 4;
			m_chessManPoint[MACHAO].y = 1;

			m_chessManPoint[HUANGZHONG].x = 4;
			m_chessManPoint[HUANGZHONG].y = 4;

			m_chessManPoint[ZU1].x = 3;
			m_chessManPoint[ZU1].y = 1;

			m_chessManPoint[ZU2].x = 3;
			m_chessManPoint[ZU2].y = 2;

			m_chessManPoint[ZU3].x = 3;
			m_chessManPoint[ZU3].y = 3;

			m_chessManPoint[ZU4].x = 3;
			m_chessManPoint[ZU4].y = 4;
		}
		break;
	case BINGFENSANLU:  //模式兵分三路
		{
			m_chessManPoint[CAOCAO].x = 1;
			m_chessManPoint[CAOCAO].y = 2;

			m_chessManPoint[GUANYU].x = 3;
			m_chessManPoint[GUANYU].y = 2;

			m_chessManPoint[ZHANGFEI].x = 2;
			m_chessManPoint[ZHANGFEI].y = 1;

			m_chessManPoint[ZHAOYUN].x = 2;
			m_chessManPoint[ZHAOYUN].y = 4;

			m_chessManPoint[MACHAO].x = 4;
			m_chessManPoint[MACHAO].y = 1;

			m_chessManPoint[HUANGZHONG].x = 4;
			m_chessManPoint[HUANGZHONG].y = 4;

			m_chessManPoint[ZU1].x = 1;
			m_chessManPoint[ZU1].y = 1;

			m_chessManPoint[ZU2].x = 4;
			m_chessManPoint[ZU2].y = 2;

			m_chessManPoint[ZU3].x = 4;
			m_chessManPoint[ZU3].y = 3;

			m_chessManPoint[ZU4].x = 1;
			m_chessManPoint[ZU4].y = 4;
		}
		break;
	default:
		break;
	}
}

bool Chess::GoUp(int chessMan)
{
	if(chessMan == CAOCAO)
	{
		if(m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//曹操可以向上走
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan == GUANYU)
	{
		if(m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//关羽可以向上走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= HUANGZHONG && chessMan >= ZHANGFEI)
	{
		if(m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y] == KONGBAI)
		{
			//四个竖着的棋子可以向上走
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= ZU4 && chessMan >= ZU1)
	{
		if(m_chessData[m_chessManPoint[chessMan].x - 1][m_chessManPoint[chessMan].y] == KONGBAI)
		{
			//四个小卒可以向上走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
}

bool Chess::GoDown(int chessMan)
{
	if(chessMan == CAOCAO)
	{
		if(m_chessData[m_chessManPoint[chessMan].x + 2][m_chessManPoint[chessMan].y] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 2][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//曹操可以向下走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x++;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan == GUANYU)
	{
		if(m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//关羽可以向下走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x++;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;
			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= HUANGZHONG && chessMan >= ZHANGFEI)
	{
		if(m_chessData[m_chessManPoint[chessMan].x + 2][m_chessManPoint[chessMan].y] == KONGBAI)
		{
			//四个竖着的棋子可以向下走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x++;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = chessMan;
			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= ZU4 && chessMan >= ZU1)
	{
		if(m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] == KONGBAI)
		{
			//四个小卒可以向下走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].x++;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;
			m_step++;
			return true;
		}
		else
			return false;
	}
}

bool Chess::GoLeft(int chessMan)
{
	if(chessMan == CAOCAO)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y - 1] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y - 1] == KONGBAI)
		{
			//曹操可以向左走
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = KONGBAI;

			m_chessManPoint[chessMan].y--;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan == GUANYU)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y - 1] == KONGBAI)
		{
			//关羽可以向左走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = KONGBAI;

			m_chessManPoint[chessMan].y--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= HUANGZHONG && chessMan >= ZHANGFEI)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y - 1] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y - 1] == KONGBAI)
		{
			//四个竖着的棋子可以向左走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= ZU4 && chessMan >= ZU1)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y - 1] == KONGBAI)
		{
			//四个小卒可以向左走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y--;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
}

bool Chess::GoRight(int chessMan)
{
	if(chessMan == CAOCAO)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 2] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 2] == KONGBAI)
		{
			//曹操可以向右走
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y++;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan == GUANYU)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 2] == KONGBAI)
		{
			//关羽可以向右走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y++;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= HUANGZHONG && chessMan >= ZHANGFEI)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] == KONGBAI
			&& m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//四个竖着的棋子可以向右走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y++;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;
			m_chessData[m_chessManPoint[chessMan].x + 1][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
	else if(chessMan <= ZU4 && chessMan >= ZU1)
	{
		if(m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y + 1] == KONGBAI)
		{
			//四个小卒可以向右走
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = KONGBAI;

			m_chessManPoint[chessMan].y++;
			m_chessData[m_chessManPoint[chessMan].x][m_chessManPoint[chessMan].y] = chessMan;

			m_step++;
			return true;
		}
		else
			return false;
	}
}

bool Chess::isWin()
{
	//如果曹操到达4 2 位置时，游戏结束
	if(m_chessManPoint[CAOCAO].x == 4 &&
		m_chessManPoint[CAOCAO].y == 2)
		return true;
	else
		return false;
}


//写入棋盘数据到文件中
bool Chess::SaveToFile()
{
	ofstream os(FILE_NAME, ios_base::out | ios_base::binary);
	os.write(reinterpret_cast<char *>( &m_nowMode), sizeof(m_nowMode));
	os.write(reinterpret_cast<char *>( &m_step), sizeof(m_nowMode));
	os.write(reinterpret_cast<char *>( &m_chessData), MAX_COLUMN * MAX_ROW * sizeof(int));
	os.write(reinterpret_cast<char *>( &m_chessManPoint), MAX_CHESSMAN * sizeof(POINT));
    os.close();
	return true;
}

//读取文件数据
bool Chess::ReadFromFile()
{
	ifstream is(FILE_NAME, ios_base::in | ios_base::binary);
    streampos pos = is.tellg();     //  保存当前位置
    is.seekg(0, ios::end);
    int length = is.tellg();
	if(length <= 0)
		return false;
    is.seekg(pos);     //  返回之前的位置
	is.read(reinterpret_cast<char *>( &m_nowMode), sizeof(m_nowMode));
	is.read(reinterpret_cast<char *>( &m_step), sizeof(m_nowMode));
	is.read(reinterpret_cast<char *>( &m_chessData), MAX_COLUMN * MAX_ROW * sizeof(int));
	is.read(reinterpret_cast<char *>( &m_chessManPoint), MAX_CHESSMAN * sizeof(POINT));
	is.close();
	return true;
}
