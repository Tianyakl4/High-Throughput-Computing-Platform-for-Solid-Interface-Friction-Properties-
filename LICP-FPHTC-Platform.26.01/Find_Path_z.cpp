/* This program aims to solve Energy based on Fz*/
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include<sstream>
#include<io.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "CInterface.h"
#define MAXSIZE 16000 //栈的最大容量

using namespace std;

struct Name   //结点结构
{
	int i, j;
};

struct Node   //结点结构
{
	Name name;
	Node * nextarc;
	double energy;
	int state;  //1：入栈，0：未入栈
};

typedef struct
{
	Node* base;//栈底指针
	Node* top;//栈顶指针
	int stacksize;//栈可用的最大容量
}SqStack;



//栈操作函数
void InitStack(SqStack&);     //栈初始化
bool Push(SqStack&, Node);   //入栈
bool Pop(SqStack&);   //出栈
Node* GetTop(SqStack);          //输出栈顶元素
bool isEmpty(SqStack);        //判断是否为空栈
//void StackInput(SqStack& );  //批量入栈
void StackOut(SqStack&);      //输出栈中所有元素
int Release(Node);
void Free(SqStack* S);



int CInterface::Find_Path_z(int kk)
{

	int i, j, k, l, m, n;
	double Energy_sandle_Fz_temp;
	int x_sandle_Fz_temp, y_sandle_Fz_temp;
	double Energy_min_Fz_temp;
	int x_min_Fz_temp, y_min_Fz_temp;
	double  delta_potential, delta_potential_temp;
	double Distance_temp = 0.0;
	fstream logout;
	Node Head[STEPX][STEPY];
	Node *Cur_Node;
	int iNofNode;
        for (i = 0; i < iNofStep_x+1; i++)
                for (j = 0; j < iNofStep_y+1; j++)
                {
                        fEnergy_Fz[i][j]=fEnergy[i][j][kk];
                }

	for (i = 0; i < STEPX; i++)
		for (j = 0; j < STEPY; j++)
		{
			Head[i][j].name.i = i;
			Head[i][j].name.j = j;
			Head[i][j].energy = 0.0;
			Head[i][j].nextarc = NULL;
			Head[i][j].state = 0;
		}

    Energy_min_Fz = fEnergy_Fz[0][0];
    Energy_min_Fz_temp = fEnergy_Fz[1][1];
    i_start = 0;
    j_start = 0;
    i_stop = iNofStep_x;
    j_stop = iNofStep_y;
    for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
		    if(fEnergy_Fz[i][j] < Energy_min_Fz)
		    {
		        Energy_min_Fz = fEnergy_Fz[i][j];
		        i_start = i;
                j_start = j;
		    }
		}
    for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
		    if(i != i_start && j != j_start && fEnergy_Fz[i][j] < Energy_min_Fz_temp)
		    {
		        Energy_min_Fz_temp = fEnergy_Fz[i][j];
		        i_stop = i;
                j_stop = j;
		    }
		}
	/*建立邻接链表*/
	if(i_start <= i_stop && j_start <= j_stop)
      for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
			iNofNode = 0;
			Head[i][j].name.i = i;
			Head[i][j].name.j = j;
			Head[i][j].energy = fEnergy_Fz[i][j];
			Head[i][j].state = 0;
			/*
			if (i > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i - 1][j];
				Cur_Node->name.i = i - 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			if (j > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j - 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j - 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			*/
			if (i < iNofStep_x)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i + 1][j];
				Cur_Node->name.i = i + 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			if (j < iNofStep_y)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j + 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j + 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}

			if (iNofNode == 0)
				Head[i][j].nextarc = NULL;
			else
				Cur_Node->nextarc = NULL;
			//cout << '\n';
		}
    else if(i_start > i_stop && j_start > j_stop)
      for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
			iNofNode = 0;
			Head[i][j].name.i = i;
			Head[i][j].name.j = j;
			Head[i][j].energy = fEnergy_Fz[i][j];
			Head[i][j].state = 0;
            ///*
			if (i > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i - 1][j];
				Cur_Node->name.i = i - 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			if (j > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j - 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j - 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			//*/
			/*
			if (i < iNofStep_x)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i + 1][j];
				Cur_Node->name.i = i + 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			if (j < iNofStep_y)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j + 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j + 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
            */
			if (iNofNode == 0)
				Head[i][j].nextarc = NULL;
			else
				Cur_Node->nextarc = NULL;
			//cout << '\n';
		}

    else if(i_start <= i_stop && j_start > j_stop)
      for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
			iNofNode = 0;
			Head[i][j].name.i = i;
			Head[i][j].name.j = j;
			Head[i][j].energy = fEnergy_Fz[i][j];
			Head[i][j].state = 0;
			/*
			if (i > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i - 1][j];
				Cur_Node->name.i = i - 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			*/
			if (j > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j - 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j - 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}

			if (i < iNofStep_x)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i + 1][j];
				Cur_Node->name.i = i + 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			/*
			if (j < iNofStep_y)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j + 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j + 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
            */
			if (iNofNode == 0)
				Head[i][j].nextarc = NULL;
			else
				Cur_Node->nextarc = NULL;
			//cout << '\n';
		}

    else if(i_start > i_stop && j_start <= j_stop)
      for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
			iNofNode = 0;
			Head[i][j].name.i = i;
			Head[i][j].name.j = j;
			Head[i][j].energy = fEnergy_Fz[i][j];
			Head[i][j].state = 0;

			if (i > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i - 1][j];
				Cur_Node->name.i = i - 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			/*
			if (j > 0)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j - 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j - 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			if (i < iNofStep_x)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i + 1][j];
				Cur_Node->name.i = i + 1;
				Cur_Node->name.j = j;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}
			*/
			if (j < iNofStep_y)
			{
				if (iNofNode == 0)
				{
					Head[i][j].nextarc = new Node;
					Cur_Node = Head[i][j].nextarc;
					iNofNode++;
				}
				else
				{
					Cur_Node->nextarc = new Node;
					Cur_Node = Cur_Node->nextarc;
					iNofNode++;
				}
				Cur_Node->energy = fEnergy_Fz[i][j + 1];
				Cur_Node->name.i = i;
				Cur_Node->name.j = j + 1;
				Cur_Node->state = 0;
				//cout << Cur_Node->name << "      ";
			}

			if (iNofNode == 0)
				Head[i][j].nextarc = NULL;
			else
				Cur_Node->nextarc = NULL;
			//cout << '\n';
		}

	/*
	for (i = 0; i <=iNofStep_x; i++)
		for (j = 0; j <= iNofStep_y; j++)
		{
			cout << '(' << Head[i][j].name.i << ',' << Head[i][j].name.j << ')' << ' ';
			if (Head[i][j].nextarc == NULL)
				;
			else
			{
				Cur_Node = Head[i][j].nextarc;
				while (1)
				{
					cout << '(' << Cur_Node->name.i << ',' << Cur_Node->name.j << ')' << ' ';
					if (Cur_Node->nextarc == NULL)
						break;
					else
						Cur_Node = Cur_Node->nextarc;
				}
			}
			cout << '\n';
		}
		cout << "邻接链表建立完毕";
		cin >> k;
	//*/
	/*邻接链表建立完毕*/

	//*搜索能垒最低路径

	SqStack S;
	InitStack(S);//初始化堆栈
	int i_temp, j_temp;
	int iNofPath;
	Node *Node_temp, *Node_temp1;
	iNofPath = 0;

	Push(S, Head[i_start][j_start]);
	Head[i_start][j_start].state = 1;

	Energy_min_Fz = Head[i_start][j_start].energy;
	x_min_Fz = i_start;
	y_min_Fz = j_start;
	Energy_sandle_Fz = Head[i_start][j_start].energy;
	x_sandle_Fz = i_start;
	y_sandle_Fz = j_start;

	delta_potential = 100000;
	Distance_min_sandle = 0;

	while (!isEmpty(S))
	{

		Cur_Node = GetTop(S);//获得栈顶元素
		i_temp = Cur_Node->name.i;
		j_temp = Cur_Node->name.j;
		Cur_Node = &Head[i_temp][j_temp];

		//cout << '(' << Cur_Node->name.i << ',' << Cur_Node->name.j << ')' << ' ';
		//cin>>k;

		if (Cur_Node->name.i == i_stop && Cur_Node->name.j == j_stop)//找到了一条路径
		{

			iNofPath++;

			//Energy_min_Fz_temp = Head[i_start][j_start].energy;
			//x_min_Fz_temp = i_start;
			//y_min_Fz_temp = j_start;
			Energy_sandle_Fz_temp = Head[i_start][j_start].energy;
			x_sandle_Fz_temp = i_start;
			y_sandle_Fz_temp = j_start;

			//cout << '\n' <<"Find the "<< iNofPath <<"th path."<<'\n';//输出路径
			Node_temp = S.base;

			//Energy_sandle_Fz_temp = Energy_min_Fz;
			//x_sandle_Fz_temp = x_min_Fz;
			//y_sandle_Fz_temp = x_min_Fz;

			while (Node_temp != S.top)
			{
				//cout << '(' << Node_temp->name.i << ',' << Node_temp->name.j << ')' << ' ';

				if (Node_temp->energy > Energy_sandle_Fz_temp)
				{
					Energy_sandle_Fz_temp = Node_temp->energy;
					x_sandle_Fz_temp = Node_temp->name.i;
					y_sandle_Fz_temp = Node_temp->name.j;
				}
				/*
				if (Node_temp->energy < Energy_min_Fz_temp)
				{
					Energy_min_Fz_temp = Node_temp->energy;
					x_min_Fz_temp = Node_temp->name.i;
					y_min_Fz_temp = Node_temp->name.j;
				}
				*/
				Node_temp++;
			}

			delta_potential_temp = Energy_sandle_Fz_temp - Energy_min_Fz_temp;

			//cin >> k;
			if (delta_potential_temp < delta_potential)
			{
				delta_potential = delta_potential_temp;
				Energy_sandle_Fz = Energy_sandle_Fz_temp;
				x_sandle_Fz = x_sandle_Fz_temp;
				y_sandle_Fz = y_sandle_Fz_temp;
				//Energy_min_Fz = Energy_min_Fz_temp;
				//x_min_Fz = x_min_Fz_temp;
				//y_min_Fz = y_min_Fz_temp;
			}

			Head[Cur_Node->name.i][Cur_Node->name.j].state = 0;
			Pop(S);//移除栈顶元素
		}

		else
		{
			while (1)
			{
				if (Cur_Node->nextarc == NULL)
				{
					Cur_Node = GetTop(S);//获得栈顶元素

					/*释放此邻接表对应的所有入栈信息*/
					Head[Cur_Node->name.i][Cur_Node->name.j].state = 0;
					Cur_Node = &Head[Cur_Node->name.i][Cur_Node->name.j];
					while (Cur_Node->nextarc != NULL)
					{
						Cur_Node = Cur_Node->nextarc;
						Cur_Node->state = 0;
					}

					//cout << '\n' << "进来了NULL";//输出路径
					//cin >> k;
					Pop(S);//移除栈顶元素
					break;
				}
				else
				{
					Cur_Node = Cur_Node->nextarc;

					if (Cur_Node->state == 0 && Head[Cur_Node->name.i][Cur_Node->name.j].state == 0)
					{
						Push(S, *Cur_Node);
						Head[Cur_Node->name.i][Cur_Node->name.j].state = 1;
						Cur_Node->state = 1;

						//cout << '\n' << "进来了 ";
						//cout << '(' << Cur_Node->name.i << ',' << Cur_Node->name.j << ')' << ' ';
						//cin >> k;

						break;
					}
					else
						;
				}
			}
		}
	}

	Distance_min_sandle = sqrt(pow((x_sandle_Fz - x_min_Fz)*fStep_x_real, 2) + pow((y_sandle_Fz - y_min_Fz)*fStep_y_real, 2) + 2 * (x_sandle_Fz - x_min_Fz)*fStep_x_real*(y_sandle_Fz - y_min_Fz)*fStep_y_real*cos(theta_ab));

	//cout << '\n';
	cout << "    Found " << iNofPath << " pathes." << '\n';//输出路径
	//cout << "    全部路径搜索完毕!" << '\n';
	cout << "    The start point (with the lowest energy) and  corresponding energy are:    " << '(' << x_min_Fz << ',' << y_min_Fz << ')' << ",  " << Head[x_min_Fz][y_min_Fz].energy << " eV" << '\n';
	cout << "    The sandle point and corresponding energy are:  " << '(' << x_sandle_Fz << ',' << y_sandle_Fz << ')' << ",  " << Head[x_sandle_Fz][y_sandle_Fz].energy << " eV" << '\n';
	cout << "    The start point (with the lowest energy) and  corresponding energy are:    " << '(' << i_stop << ',' << j_stop << ')' << ",  " << Head[i_stop][j_stop].energy << " eV" << '\n';
	//cout << "    The final point and  corresponding energy are:  " << '(' << i_stop << ',' << j_stop << ')' << ",  " << Head[i_stop][j_stop].energy << " eV" << '\n';
	//cout << '\n';

	//cin>>k;

	logout.open("log.out", ios::out | ios::app);
	logout << '\n';
	logout << "    Found " << iNofPath << " pathes." << '\n';//输出路径
	logout << "    全部路径搜索完毕!" << '\n';
	logout << "    The min point and  corresponding energy are:    " << '(' << x_min_Fz << ',' << y_min_Fz << ')' << ",  " << Head[x_min_Fz][y_min_Fz].energy << " eV" << '\n';
	logout << "    The sandle point and corresponding energy are:  " << '(' << x_sandle_Fz << ',' << y_sandle_Fz << ')' << ",  " << Head[x_sandle_Fz][y_sandle_Fz].energy << " eV" << '\n';
	logout << "    The start point (with the lowest energy) and  corresponding energy are:    " << '(' << i_stop << ',' << j_stop << ')' << ",  " << Head[i_stop][j_stop].energy << " eV" << '\n';
	logout << '\n';
	logout.close();

	void Free(SqStack &S);

	/*能垒最低路径搜索完毕*/
	return 0;
}

