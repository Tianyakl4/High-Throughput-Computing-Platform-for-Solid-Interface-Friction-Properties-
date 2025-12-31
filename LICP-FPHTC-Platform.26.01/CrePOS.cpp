/*
   This program can handle the Orthogonal system and the Skew System (c must be perpendicular to a and b).
   The interface must be perpendicular to c.
   The k is defined as b/a in the moving path y=k*x.
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include<io.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "CInterface.h"
using namespace std;

struct Atom
{
	string sAtom;
	double x, y, z;
	string Sx, Sy, Sz;
};

int CInterface::CrePOS()
{
	int i, j, k, l, m, n;
	int iIfCar = 0;  //0:Direct  1:Cartesion 10:Selective Direct   11:Selective Cartesion
	int iIfBoundary = 0;
	int iIfEqual = 0;
	int iIfCompress = 0;
	int iNofAtoms = 0, iNofMoveAtoms = 0;
	int iNofLayer = 0;
	double ftemp;
	double FSITEOFFACE[100];//jiemian weizhi dayu cizhi de yuanzi bei yidong, Direct zuobiao de zhi
        double fSiteofFace_Move;
	double INOFSTEP_Z; //neng bei 3zhengzhu
	double MOVE_DISTANCE_X, MOVE_DISTANCE_Y;  //x,y fangxiang mei yi bu yidong de juli, danwei A
	double FSTEP_Z_REAL_DOWN, FSTEP_Z_REAL_UP;  //z fanxiang meiyibuyidong de juli, danwei A
	//string temp1[20];
	string filename, temp;
	fstream inall, inall1, outall, logout;
	stringstream  inputss, ss;
	Atom atom_initial[400], atom_final[400], atom_initial_move[400], atom_final_move[400];
	for (i = 0; i < 400; i++)
	{
		atom_initial[i].sAtom = ' ';
		atom_initial[i].x = 0;
		atom_initial[i].y = 0;
		atom_initial[i].z = 0;
		atom_initial[i].Sx = ' ';
		atom_initial[i].Sy = ' ';
		atom_initial[i].Sz = ' ';

		atom_final[i].sAtom = ' ';
		atom_final[i].x = 0;
		atom_final[i].y = 0;
		atom_final[i].z = 0;
		atom_final[i].Sx = ' ';
		atom_final[i].Sy = ' ';
		atom_final[i].Sz = ' ';

		atom_initial_move[i].sAtom = ' ';
		atom_initial_move[i].x = 0;
		atom_initial_move[i].y = 0;
		atom_initial_move[i].z = 0;
		atom_initial_move[i].Sx = ' ';
		atom_initial_move[i].Sy = ' ';
		atom_initial_move[i].Sz = ' ';

		atom_final_move[i].sAtom = ' ';
		atom_final_move[i].x = 0;
		atom_final_move[i].y = 0;
		atom_final_move[i].z = 0;
		atom_final_move[i].Sx = ' ';
		atom_final_move[i].Sy = ' ';
		atom_final_move[i].Sz = ' ';
	}
	for (i = 0; i < 100; i++)
		FSITEOFFACE[i] = 0;

	inall1.open("in.dat", ios::in);
	inall1 >> iNofLayer;
	inall1 >> iIfCompress;
	for (i = 0; i < iNofLayer - 1; i++)
		inall1 >> FSITEOFFACE[i];
        inall1 >> fSiteofFace_Move;
        
	inall1 >> INOFSTEP_Z;
	iNofStep_z = INOFSTEP_Z;
	inall1 >> iNofStep_z_Down;
	inall1 >> iNofStep_z_Up;
	inall1 >> z_initial;
	//cout<<"  " <<z_initial;
	inall1 >> iNofStep_x;
	inall1 >> iNofStep_y;
	inall1 >> FSTEP_Z_REAL_DOWN;
	inall1 >> FSTEP_Z_REAL_UP;
	fStep_z_real_down = FSTEP_Z_REAL_DOWN;
	fStep_z_real_up = FSTEP_Z_REAL_UP;
	inall1.close();


	inall.open("POSCAR", ios::in);
	getline(inall, temp);
	inall >> constant;
	inall >> ax; inall >> ay; inall >> az;
	inall >> bx; inall >> by; inall >> bz;
	inall >> cx; inall >> cy; inall >> cz;
	a = sqrt(ax * ax + ay * ay + az * az) * constant;
	b = sqrt(bx * bx + by * by + bz * bz) * constant;
	c = sqrt(cx * cx + cy * cy + cz * cz) * constant;
	theta_ab = acos((ax * bx + ay * by + az * bz) / (sqrt(ax * ax + ay * ay + az * az) * sqrt(bx * bx + by * by + bz * bz)));
	fArea_Interface = a * b * sin(theta_ab) / 2;

	cout << "    The informations of the POSCAR head." << '\n';

	cout << "    " << temp << '\n';
	cout << "    " << constant << '\n';
	cout << "    " << ax << ' ' << ay << ' ' << az << ' ' << '\n';
	cout << "    " << bx << ' ' << by << ' ' << bz << ' ' << '\n';
	cout << "    " << cx << ' ' << cy << ' ' << cz << ' ' << '\n';

	logout.open("log.out", ios::out | ios::app);
	logout << '\n';
	logout << "    The informations of the POSCAR head." << '\n';
	logout << "    " << temp << '\n';
	logout << "    " << constant << '\n';
	logout << "    " << ax << ' ' << ay << ' ' << az << ' ' << '\n';
	logout << "    " << bx << ' ' << by << ' ' << bz << ' ' << '\n';
	logout << "    " << cx << ' ' << cy << ' ' << cz << ' ' << '\n';
	logout << '\n';
	logout.close();


	//duqu yuansu fuhao
	while (inall.get() != 10)
	{
		;
	}

	getline(inall, temp);
	inputss << temp;
	i = 0;
	while (inputss >> atomname[i])
	{
		//cout << atomname[i] << ' '; //ceshi
		i++;
	}
	//cout << '\n';
	iNofElement = i;

	//duqu yuansu geshu
	for (i = 0; i < iNofElement; i++)
	{
		inall >> iNofAtom[i];
		//cout << iNofAtom[i] << ' ';  //ceshi
		iNofAtoms = iNofAtoms + iNofAtom[i];
	}
	//cout << '\n';
	while (inall.get() != 10)
	{
		;
	}
	getline(inall, temp);  //Selective dynamics or not
	inputss.str("");
	inputss.clear();
	inputss << temp;
	inputss >> temp;
	if (temp == "Selective" || temp == "selective")
	{
		//cout << "jinlaile"; //ceshi
		//cin >> i;
		getline(inall, temp);  //Selective dynamics or not
		//cout << temp << '\n'; //ceshi
		inputss.str("");
		inputss.clear();
		inputss << temp;
		inputss >> temp;
		if (temp == "Direct" || temp == "direct")

			//duqu meige yuanzi zuobiao
		{
			//cout << "jinlaile1"; //ceshi
			//cin >> i;

			iIfCar = 10;
			j = 0;
			k = iNofAtom[j];
			for (i = 0; i < iNofAtoms; i++)
			{
				inall >> atom_initial[i].x;
				if (atom_initial[i].x < 0)
					atom_initial[i].x++;
				if (atom_initial[i].x > 1)
					atom_initial[i].x--;
				inall >> atom_initial[i].y;
				if (atom_initial[i].y < 0)
					atom_initial[i].y++;
				if (atom_initial[i].y > 1)
					atom_initial[i].y--;
				inall >> atom_initial[i].z;
				if (atom_initial[i].z < 0)
					atom_initial[i].z++;
				if (atom_initial[i].z > 1)
					atom_initial[i].z--;
				atom_initial[i].sAtom = atomname[j];

				if ((i + 1) % k == 0)
				{
					j++;
					k = k + iNofAtom[j];
				}
				inall >> atom_initial[i].Sx;
				inall >> atom_initial[i].Sy;
				inall >> atom_initial[i].Sz;

				//cout << atom_initial[i].sAtom << ' ' << atom_initial[i].x << ' ' << atom_initial[i].y << ' ' << atom_initial[i].z << ' '; //ceshi
				//cout << atom_initial[i].Sx << ' ' << atom_initial[i].Sy << ' ' << atom_initial[i].Sz << '\n'; //ceshi
			}
			//cout << '\n';

			//cin >> i;


		}

		else if (temp == "Cartesion" || temp == "cartesion")  //quanbu zhuanhua wei Direct xingshi
		{
			iIfCar = 11;
			j = 0;
			k = iNofAtom[j];
			for (i = 0; i < iNofAtoms; i++)
			{
				inall >> atom_initial[i].x;
				atom_initial[i].x = atom_initial[i].x / a;
				if (atom_initial[i].x < 0)
					atom_initial[i].x++;
				if (atom_initial[i].x > 1)
					atom_initial[i].x--;
				inall >> atom_initial[i].y;
				atom_initial[i].y = atom_initial[i].y / b;
				if (atom_initial[i].y < 0)
					atom_initial[i].y++;
				if (atom_initial[i].y > 1)
					atom_initial[i].y--;
				inall >> atom_initial[i].z;
				atom_initial[i].z = atom_initial[i].z / c;
				if (atom_initial[i].z < 0)
					atom_initial[i].z++;
				if (atom_initial[i].z > 1)
					atom_initial[i].z--;
				atom_initial[i].sAtom = atomname[j];

				if ((i + 1) % k == 0)
				{
					j++;
					k = k + iNofAtom[j];
				}
				inall >> atom_initial[i].Sx;
				inall >> atom_initial[i].Sy;
				inall >> atom_initial[i].Sz;

				//cout << atom_initial[i].sAtom << ' ' << atom_initial[i].x << ' ' << atom_initial[i].y << ' ' << atom_initial[i].z << ' '; //ceshi
				//cout << atom_initial[i].Sx << ' ' << atom_initial[i].Sy << ' ' << atom_initial[i].Sz << '\n'; //ceshi

			}
		}
	}


	else if (temp == "Direct" || temp == "direct")
	{
		iIfCar = 0;
		j = 0;
		k = iNofAtom[j];
		for (i = 0; i < iNofAtoms; i++)
		{
			inall >> atom_initial[i].x;
			if (atom_initial[i].x < 0)
				atom_initial[i].x++;
			if (atom_initial[i].x > 1)
				atom_initial[i].x--;
			inall >> atom_initial[i].y;
			if (atom_initial[i].y < 0)
				atom_initial[i].y++;
			if (atom_initial[i].y > 1)
				atom_initial[i].y--;
			inall >> atom_initial[i].z;
			if (atom_initial[i].z < 0)
				atom_initial[i].z++;
			if (atom_initial[i].z > 1)
				atom_initial[i].z--;
			atom_initial[i].sAtom = atomname[j];

			if ((i + 1) % k == 0)
			{
				j++;
				k = k + iNofAtom[j];
			}

			//cout << atom_initial[i].sAtom << ' ' << atom_initial[i].x << ' ' << atom_initial[i].y << ' ' << atom_initial[i].z << '\n'; //ceshi
		}
		//cout << '\n';
	}
	else if (temp == "Cartesion" || temp == "cartesion")  //quanbu zhuanhua wei Direct xingshi
	{
		iIfCar = 1;
		j = 0;
		k = iNofAtom[j];
		for (i = 0; i < iNofAtoms; i++)
		{
			inall >> atom_initial[i].x;
			atom_initial[i].x = atom_initial[i].x / a;
			if (atom_initial[i].x < 0)
				atom_initial[i].x++;
			if (atom_initial[i].x > 1)
				atom_initial[i].x--;
			inall >> atom_initial[i].y;
			atom_initial[i].y = atom_initial[i].y / b;
			if (atom_initial[i].y < 0)
				atom_initial[i].y++;
			if (atom_initial[i].y > 1)
				atom_initial[i].y--;
			inall >> atom_initial[i].z;
			atom_initial[i].z = atom_initial[i].z / c;
			if (atom_initial[i].z < 0)
				atom_initial[i].z++;
			if (atom_initial[i].z > 1)
				atom_initial[i].z--;
			atom_initial[i].sAtom = atomname[j];

			if ((i + 1) % k == 0)
			{
				j++;
				k = k + iNofAtom[j];
			}
			//cout << atom_initial[i].sAtom << ' ' << atom_initial[i].x << ' ' << atom_initial[i].y << ' ' << atom_initial[i].z << '\n'; //ceshi

		}
		//cout << '\n';
	}

	inall.close();


	//tongji yidong de yuanzi geshu
	iNofMoveAtoms = 0;
	for (i = 0; i < iNofAtoms; i++)
	{
		//if (atom_initial[i].z >= FSITEOFFACE[iNofLayer - 2])
		if (atom_initial[i].z >= fSiteofFace_Move)
                {
			atom_initial_move[iNofMoveAtoms] = atom_initial[i];
			atom_initial_move[iNofMoveAtoms].x = atom_initial_move[iNofMoveAtoms].x * a;
			atom_initial_move[iNofMoveAtoms].y = atom_initial_move[iNofMoveAtoms].y * b;
			atom_initial_move[iNofMoveAtoms].z = atom_initial_move[iNofMoveAtoms].z * c;
			iNofMoveAtoms++;
		}
	}

	//cout << "Number of atom moved:" << iNofMoveAtoms << '\n';

	for (i = 0; i < iNofMoveAtoms; i++)
		//cout << atom_initial_move[i].x << ' ' << atom_initial_move[i].y << ' ' << atom_initial_move[i].z << '\n';

	//jia yidong xunzhao zhouqixing tiaojian
		double fNofStep_x, fNofStep_y, fNofStep_z;
	double fArea;
	double fStep_x, fStep_y;
	double FSTEP_REAL_X, FSTEP_REAL_Y, FSTEP_REAL_Z;   //Goujian POSCAR yidong juli danwei A
	double FSLOPE_X = 0, FSLOPE_y = -1;    //yidong fangxiang y=k*x zhong de k. 0 along x,-1 along y.
	double FSLOPE = 0;  //²âÊÔ

	/*
	//genju y=kx suanchu x y fangxiang yidong de juli
	if (FSLOPE > 0)
	{
		fStep_x = FSTEP * sqrt(1.0 / (1.0 + FSLOPE * FSLOPE - 2.0 * FSLOPE * cos(theta_ab)));
		fStep_y = FSLOPE * fStep_x;
		fStep_x_real = FSTEP_REAL * sqrt(1.0 / (1.0 + FSLOPE * FSLOPE - 2.0 * FSLOPE * cos(theta_ab)));
		fStep_y_real = FSLOPE * fStep_x_real;
		if (FSLOPE <= b / a)
			fDistance = a * sqrt(1.0 + FSLOPE * FSLOPE - 2.0 * FSLOPE * cos(theta_ab));
		else
			fDistance = b * sqrt(1.0 + 1.0 / (FSLOPE * FSLOPE) - 2.0 * (1.0 / FSLOPE) * cos(theta_ab));
	}
	else if (FSLOPE == 0)
	{
		fStep_x = FSTEP;
		fStep_y = 0;
		fStep_x_real = FSTEP_REAL;
		fStep_y_real = 0;
		fDistance = a;
	}
	else
	{
		fStep_x = 0;
		fStep_y = FSTEP;
		fStep_x_real = 0;
		fStep_y_real = FSTEP_REAL;
		fDistance = b;
	}
	//*/

	m = 0;
	fStep_x = FSTEP;
	fStep_y = 0;
	fDistance_x = a;
	for (j = 0.1 / FSTEP; j * FSTEP <= fDistance_x; j++)
	{
		//cout << j;
		//cin >> i;

		for (i = 0; i < iNofMoveAtoms; i++)
		{
			atom_final_move[i] = atom_initial_move[i];
			atom_final_move[i].x = atom_initial_move[i].x + j * fStep_x;
			if (atom_final_move[i].x >= a)
				atom_final_move[i].x = atom_final_move[i].x - a;
			if (atom_final_move[i].x < 0)
				atom_final_move[i].x = atom_final_move[i].x + a;
			atom_final_move[i].y = atom_initial_move[i].y + j * fStep_y;
			if (atom_final_move[i].y >= b)
				atom_final_move[i].y = atom_final_move[i].y - b;
			if (atom_final_move[i].y < 0)
				atom_final_move[i].y = atom_final_move[i].y + b;
		}
		for (k = 0; k < iNofMoveAtoms; k++)
		{
			for (l = 0; l < iNofMoveAtoms; l++)
			{
				// calculating the distance atom k and atom l in skew coordinate system.
				ftemp = pow(atom_final_move[k].x - atom_initial_move[l].x, 2) + pow(atom_final_move[k].y - atom_initial_move[l].y, 2);
				ftemp = ftemp - 2 * (atom_final_move[k].x - atom_initial_move[l].x) * (atom_final_move[k].y - atom_initial_move[l].y) * cos(theta_ab);
				ftemp = sqrt(ftemp + pow(atom_final_move[k].z - atom_initial_move[l].z, 2));
				if (ftemp < DIFF)
					break;
			}
			if (l == iNofMoveAtoms)
				break;
		}
		m++;
		//cout << k << ' ' << m << '\n';
		if (k == iNofMoveAtoms)
		{
			iIfBoundary = 1;
			fDistance_x = j * FSTEP;
			break;
		}
	}

	//cout << "fDistance_x:" << fDistance_x << '\n'; //ceshi
	// cin >> i;

	m = 0;
	fStep_x = 0;
	fStep_y = FSTEP;
	fDistance_y = b;
	for (j = 0.1 / FSTEP; j * FSTEP <= fDistance_y; j++)
	{
		//cout << j;
		//cin >> i;

		for (i = 0; i < iNofMoveAtoms; i++)
		{
			atom_final_move[i] = atom_initial_move[i];
			atom_final_move[i].x = atom_initial_move[i].x + j * fStep_x;
			if (atom_final_move[i].x >= a)
				atom_final_move[i].x = atom_final_move[i].x - a;
			if (atom_final_move[i].x < 0)
				atom_final_move[i].x = atom_final_move[i].x + a;
			atom_final_move[i].y = atom_initial_move[i].y + j * fStep_y;
			if (atom_final_move[i].y >= b)
				atom_final_move[i].y = atom_final_move[i].y - b;
			if (atom_final_move[i].y < 0)
				atom_final_move[i].y = atom_final_move[i].y + b;
		}
		for (k = 0; k < iNofMoveAtoms; k++)
		{
			for (l = 0; l < iNofMoveAtoms; l++)
			{
				// calculating the distance atom k and atom l in skew coordinate system.
				ftemp = pow(atom_final_move[k].x - atom_initial_move[l].x, 2) + pow(atom_final_move[k].y - atom_initial_move[l].y, 2);
				ftemp = ftemp - 2 * (atom_final_move[k].x - atom_initial_move[l].x) * (atom_final_move[k].y - atom_initial_move[l].y) * cos(theta_ab);
				ftemp = sqrt(ftemp + pow(atom_final_move[k].z - atom_initial_move[l].z, 2));
				if (ftemp < DIFF)
					break;
			}
			if (l == iNofMoveAtoms)
				break;
		}
		m++;
		//cout << k << ' ' << m << '\n';
		if (k == iNofMoveAtoms)
		{
			iIfBoundary = 1;
			fDistance_y = j * FSTEP;
			break;
		}
	}

	//jisuan zuixiao zhouqi de mianji,genju chadian mian midu queding liangge fangxiang shang chadian geshu
	fArea = fDistance_x * fDistance_y * fabs(sin(theta_ab));
	//iNofStep_x = round(sqrt(DENSITY * fArea * fDistance_x / fDistance_y));
	//iNofStep_y = round(sqrt(DENSITY * fArea * fDistance_y / fDistance_x));

	/*
	iNofStep_x = round(fDistance_x / MOVE_DISTANCE_X);
	if (iNofStep_x % 2 != 0)
		iNofStep_x++;
	//fDistance_y = fDistance_y* fabs(sin(theta_ab));//Important: touying dao chuizhiyu x de fangxiang.
	iNofStep_y = round(fDistance_y / MOVE_DISTANCE_Y);
	if (iNofStep_y % 2 != 0)
		iNofStep_y++;
	*/

	fStep_x_real = fDistance_x / iNofStep_x;
	fStep_y_real = fDistance_y / iNofStep_y;

	/*
	cout << '\n'; //ceshi
	cout << "mianji:" << fArea << '\n'; //ceshi
	cout << "fDistance_x:" << fDistance_x << '\n'; //ceshi
	cout << "fDistance_y:" << fDistance_y << '\n'; //ceshi
	cout << "iNofStep_x:" << iNofStep_x  << '\n'; //ceshi
	cout << "iNofStep_y:" << iNofStep_y << '\n'; //ceshi
	cout << "fStep_x_real:" << fStep_x_real << '\n'; //ceshi
	cout << "fStep_y_real:" << fStep_y_real << '\n'; //ceshi

	cout << "chadian midu" << iNofStep_x * iNofStep_y / fArea << '\n'; //ceshi
	cin >> i;
	//*/

	//zhen yidong

	/*
	   for (k = 0; k < INOFSTEP_Z; k++)
	{
		if (k - 4.0 * INOFSTEP_Z / 5.0 + 1 < -0.0001)
			z[k] = FSTEP_Z_REAL_DOWN * (k - 4.0 * INOFSTEP_Z / 5.0 + 1);
		else
			z[k] = FSTEP_Z_REAL_UP * (k - 4.0 * INOFSTEP_Z / 5.0 + 1);
	}
		//*/

	for (k = 0; k < INOFSTEP_Z; k++)
	{
		if (k < iNofStep_z_Down)
			z[k] = FSTEP_Z_REAL_DOWN * (k - iNofStep_z_Down + 1);
		else
			z[k] = FSTEP_Z_REAL_UP * (k - iNofStep_z_Down + 1);
	}



	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < INOFSTEP_Z; k++)
			{
				for (l = 0; l < iNofAtoms; l++)
				{
					atom_final[l] = atom_initial[l];
					 //if (atom_initial[l].z > FSITEOFFACE[iNofLayer - 2])
					 if (atom_initial[l].z >= fSiteofFace_Move)
					{
						//atom_final[l].x = atom_initial[l].x + (i * fStep_x_real-j*1.0/tan(theta_ab)* fStep_y_real) / a;
						atom_final[l].x = atom_initial[l].x + i * fStep_x_real / a;
						if (atom_final[l].x < 0)
							atom_final[l].x++;
						else if (atom_final[l].x > 1)
							atom_final[l].x--;
						atom_final[l].y = atom_initial[l].y + j * fStep_y_real / b;
						if (atom_final[l].y < 0)
							atom_final[l].y++;
						else if (atom_final[l].y > 1)
							atom_final[l].y--;
					}
					if (iIfCompress == 1)
					{
						for (m = 0; m < iNofLayer - 1; m++)
						{
							if (atom_initial[l].z > FSITEOFFACE[m])
							{
								atom_final[l].z = atom_final[l].z + z[k] / c;
								if (atom_final[l].z < 0)
									atom_final[l].z++;
								else if (atom_final[l].z > 1)
									atom_final[l].z--;
							}
						}
					}
					else if (iIfCompress == 0)
					{
						//if (atom_initial[l].z > FSITEOFFACE[iNofLayer - 2])
						if (atom_initial[l].z >= fSiteofFace_Move)
						{
							atom_final[l].z = atom_final[l].z + z[k] / c;
							if (atom_final[l].z < 0)
								atom_final[l].z++;
							else if (atom_final[l].z > 1)
								atom_final[l].z--;
						}
					}
				}

				//shuchu
				ss << i;
				temp = ss.str();
				ss.str("");
				ss.clear();
				filename = "POSCAR_" + temp + '_';
				ss << j;
				temp = ss.str();
				ss.str("");
				ss.clear();
				filename = filename + temp + '_';
				ss << k;
				temp = ss.str();
				ss.str("");
				ss.clear();
				filename = filename + temp;
				outall.open(filename, ios::out);
				outall << "# data file written by LICM-HTC\n";
				outall << constant << " \n";
				outall << ax << ' ' << ay << ' ' << az << " \n";
				outall << bx << ' ' << by << ' ' << bz << " \n";
				outall << cx << ' ' << cy << ' ' << cz << " \n";
				for (m = 0; m < iNofElement; m++)
					outall << atomname[m] << ' ';
				outall << '\n';
				for (m = 0; m < iNofElement; m++)
					outall << iNofAtom[m] << ' ';
				outall << "\n";

				if (iIfCar == 0 || iIfCar == 1)
				{
					outall << "Direct\n";
					for (m = 0; m < iNofAtoms; m++)
					{
						outall << atom_final[m].x << ' ';
						outall << atom_final[m].y << ' ';
						outall << atom_final[m].z << '\n';
					}
				}

				else if (iIfCar == 10 || iIfCar == 11)
				{
					outall << "Selective dynamics\n" << "Direct\n";
					for (m = 0; m < iNofAtoms; m++)
					{
						outall << atom_final[m].x << ' ';
						outall << atom_final[m].y << ' ';
						outall << atom_final[m].z << ' ';
						outall << atom_final[m].Sx << ' ';
						outall << atom_final[m].Sy << ' ';
						outall << atom_final[m].Sz << '\n';
					}
				}
				outall.close();
			}

	//cout<<"  " <<z_initial<<'\n';
	//cout << "All step:" << iNofStep_x* iNofStep_y*INOFSTEP_Z; //ceshi

		/*
	for (k = 0; k < iNofStep_z; k++)
	{
		if (k - 4.0 * INOFSTEP_Z / 5.0 + 1 < -0.0001)
			z[k] = z_initial + FSTEP_Z_REAL_DOWN * (k - 4.0 * INOFSTEP_Z / 5.0 + 1);
		else
			z[k] = z_initial + FSTEP_Z_REAL_UP * (k - 4.0 * INOFSTEP_Z / 5.0 + 1);
	}
		//*/

	if (iIfCompress == 1)
		for (k = 0; k < INOFSTEP_Z; k++)
		{
			if (k < iNofStep_z_Down)
				z[k] = z_initial + FSTEP_Z_REAL_DOWN * (k - iNofStep_z_Down + 1) * (iNofLayer - 1);
			else
				z[k] = z_initial + FSTEP_Z_REAL_UP * (k - iNofStep_z_Down + 1) * (iNofLayer - 1);
		}
	else if (iIfCompress == 0)
		for (k = 0; k < INOFSTEP_Z; k++)
		{
			if (k < iNofStep_z_Down)
				z[k] = z_initial + FSTEP_Z_REAL_DOWN * (k - iNofStep_z_Down + 1);
			else
				z[k] = z_initial + FSTEP_Z_REAL_UP * (k - iNofStep_z_Down + 1);
		}



	//cout<<"  " <<z_initial<<'\n';

	i_start = j_start = 0;
	i_stop = iNofStep_x;
	j_stop = iNofStep_y;

	outall.open("temp.dat", ios::out);
	outall << "The in_file for the LICP-FPHTC-Platform. ( Please dont remove this line.)" << '\n';

	outall << iNofStep_x << '\n';
	outall << iNofStep_y << '\n';
	outall << iNofStep_z << '\n';

	outall << a << '\n';
	outall << b << '\n';
	outall << c << '\n';
	outall << theta_ab << '\n';

	outall << fStep_x_real << '\n';
	outall << fStep_y_real << '\n';
	outall << FSTEP_Z_REAL_DOWN << '\n';
	outall << FSTEP_Z_REAL_UP << '\n';

        outall << fDistance_x <<"  " << fDistance_y << "  " << fDistance_z << '\n';

	outall << '\n';

	for (k = 0; k < INOFSTEP_Z; k++)
	{
		outall << "  " << z[k];
		//cout<<"  " <<z_initial<<"  "<< z[k];
		if ((k + 1) % 5 == 0)
			outall << '\n';
	}

	outall.close();
	return 0;
}
