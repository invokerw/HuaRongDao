#include "ChessEncoded.h"


ChessEncoded::ChessEncoded(char *chessData)
{
	//初始化编码表
	Hz = new short int[4096*3]; 
	Sz = Hz + 4096; 
	Bz = Hz + 4096 * 2;
	
	Hw = new int[792 * 2];  
	Sw = Hw + 792;  //C12取5=792
	int i,j,k;

	int Hn = 0; //横将的数量  一般为1 
	int Bn = 0; //小兵的数量  一般为4
	int	Sn = 0; //竖将的数量  一般为4

	for(i = 0;i < 20;i++) //计算各种棋子的个数
	{  
		if(U[chessData[i]] == 'B') Bn++;
		if(U[chessData[i]] == 'H') Hn++;
		if(U[chessData[i]] == 'C') Sn++;
	}
	//横将与竖将均占两个棋盘位置
	Hn /= 2;
	Sn /= 2;

	int Hmax = WQ2[11];
	int Smax = WQ2[12 - Hn * 2];
	int Bmax = WQ2[16 - (Hn + Sn) * 2]; //各种子的最大二进位数

	int Hx = 0;
	int Sx = 0;
	int Bx = 0; //各种棋子组合的最大序号
	for(i = 0;i < 4096;i++){  //初始化组合序号表
		for(j = 0,k = 0;j < 12;j++) 
			if(i & WQ2[j]) 
				k++; //计算1的个数
		if(k == Hn && i < Hmax) Hz[i] = Hx++;
		if(k == Sn && i < Smax) Sz[i] = Sx++;
		if(k == Bn && i < Bmax) Bz[i] = Bx++;
	}
	int Sq = Bx, Hq = Bx * Sx,Mq = Bx * Sx * Hx; //竖将位权,横将位权,曹操位权

	for(i = 0;i < 12;i++) Mw[i] = i * Mq; //初始化大王权值表
	for(i = 0;i < Hx;i++) Hw[i] = i * Hq; //初始化横将权值表
	for(i = 0;i < Sx;i++) Sw[i] = i * Sq; //初始化竖将权值表

	codeTotalNum = Mq * 12;
}


ChessEncoded::~ChessEncoded(void)
{
	delete[] Hz,Hw;
}


int ChessEncoded::Encoded(char *chessData)
{
	//盘面编码
	int Bb = 0,Bd = -1; //空位序号记录器
	int Sb = 0,Sd = -1; //竖条序号记录器
	int Hb = 0,Hd = -1; //横条序号记录器
	int Mb;             //曹操序号记录器
	char c,lx,f[16]={0};   //其中f[]标记几个棋子是否已确定位置序号
	int i;
	for(i = 0;i < 20;i++)
	{
		c = chessData[i], lx = U[c]; //当前的值
		if(lx == 'M')    //大王定序
		{ 
			if(!f[c])
				Mb = i - ROW[i], f[c] = 1;
			continue;
		}
		if(COL[i] < 3 && U[chessData[i+1]] <= 'H')   Hd++; //横条位置序号(编号)
		if(lx == 'H')    //横将定序,转为二进制进行询址得Hb 
		{
			if(!f[c]) 
				Hb += WQ2[Hd],f[c]=1;
			continue;
		}
		if(ROW[i] < 4 && U[chessData[i+4]] <= 'C') 
			Sd++; //竖将位置序号(编号)
		if(lx == 'C')  //竖条定序,转为二进制进行询址得Sb
		{
			if(!f[c]) 
				Sb += WQ2[Sd],f[c] = 1;
			continue;
		}
		if(lx <= 'B')//小兵位置序号(编号)
 			Bd++;  		
		if(lx == 'B') //小兵定序,转为二进制进行询址得Bb
			Bb += WQ2[Bd]; 
	}
	//Hb,Sb,Bb为组合序号,"横刀立马"最大值为小兵C(6,4)-1=15-1,竖条C(10,4)-1=210-1
	Bb = Bz[Bb],Sb = Sz[Sb],Hb = Hz[Hb];//询址后得得Bb,Sb,Hb组合序号

	return Bb + Sw[Sb] + Hw[Hb] + Mw[Mb]; //用位权编码,其中Bb的位权为1
}


int ChessEncoded::SymmetryEncoded(char *chessData)
{
	char i,symmetryChessData[20];
	for(i = 0;i < 20;i += 4) 
	{
		symmetryChessData[i] = chessData[i+3];
		symmetryChessData[i+1] = chessData[i+2];
		symmetryChessData[i+2] = chessData[i+1];
		symmetryChessData[i+3] = chessData[i];
	}
	return Encoded(symmetryChessData);
}
