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
#include "CDiffCHG.h"
using namespace std;

struct Atom
{
	string sAtom;
	double x, y, z;
	string Sx, Sy, Sz;
	int iIfup;
};

int CDiffCHG::CrePOS()
{
	int i, j, k, l, m, n, ii, mm;
	int iIfCar = 0;  //0:Direct  1:Cartesion 10:Selective Direct   11:Selective Cartesion
	int iIfBoundary = 0;
	int iIfEqual = 0;
	int iIfCompress = 0;
	int iNofAtoms = 0, iNofMoveAtoms = 0, iNofUp, iNofDown, iNofAtoms_up;
	int iNofLayer = 0;
	double ftemp;
	double FSITEOFFACE[20];//jiemian weizhi dayu cizhi de yuanzi bei yidong, Direct zuobiao de zhi
        double fSiteofFace_Move;
	double INOFSTEP_Z; //neng bei 3zhengzhu
	int iNofAtom_up[i];
	double MOVE_DISTANCE_X, MOVE_DISTANCE_Y;  //x,y fangxiang mei yi bu yidong de juli, danwei A
	double FSTEP_Z_REAL_DOWN, FSTEP_Z_REAL_UP;  //z fanxiang meiyibuyidong de juli, danwei A
	string filename, temp;
	char command[100];
	string sTemp1 = "1111";
	string sTemp2 = "1111";
	string line, name;
	fstream inall, inall1, outall, logout;
	stringstream  inputss, ss;
	Atom atom_initial[200], atom_final[200];
	for (i = 0; i < 200; i++)
	{
		atom_initial[i].sAtom = ' ';
		atom_initial[i].x = 0;
		atom_initial[i].y = 0;
		atom_initial[i].z = 0;
		atom_initial[i].Sx = ' ';
		atom_initial[i].Sy = ' ';
		atom_initial[i].Sz = ' ';
		atom_initial[i].iIfup = 0;

	}
	for (i = 0; i < 20; i++)
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
		i++;
	}
	iNofElement = i;

	for (i = 0; i < iNofElement; i++)
	{
		inall >> iNofAtom[i];
		iNofAtoms = iNofAtoms + iNofAtom[i];
	}
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
		getline(inall, temp);  //Selective dynamics or not
		inputss.str("");
		inputss.clear();
		inputss << temp;
		inputss >> temp;
		if (temp == "Direct" || temp == "direct")

		{
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
				//if (atom_initial[i].z > FSITEOFFACE[iNofLayer - 2])
				if (atom_initial[i].z > fSiteofFace_Move)
					atom_initial[i].iIfup = 1;

				if ((i + 1) % k == 0)
				{
					j++;
					k = k + iNofAtom[j];
				}
				inall >> atom_initial[i].Sx;
				inall >> atom_initial[i].Sy;
				inall >> atom_initial[i].Sz;
			}
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
				//if (atom_initial[i].z > FSITEOFFACE[iNofLayer - 2])
				if (atom_initial[i].z > fSiteofFace_Move)
					atom_initial[i].iIfup = 1;
				atom_initial[i].sAtom = atomname[j];

				if ((i + 1) % k == 0)
				{
					j++;
					k = k + iNofAtom[j];
				}
				inall >> atom_initial[i].Sx;
				inall >> atom_initial[i].Sy;
				inall >> atom_initial[i].Sz;

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
			//if (atom_initial[i].z > FSITEOFFACE[iNofLayer - 2])
			if (atom_initial[i].z > fSiteofFace_Move)
				atom_initial[i].iIfup = 1;
			if ((i + 1) % k == 0)
			{
				j++;
				k = k + iNofAtom[j];
			}
		}
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
			//if (atom_initial[i].z > FSITEOFFACE[iNofLayer - 2])
			if (atom_initial[i].z > fSiteofFace_Move)
				atom_initial[i].iIfup = 1;
			if ((i + 1) % k == 0)
			{
				j++;
				k = k + iNofAtom[j];
			}
		}
	}

	inall.close();

	iNofAtoms_up = 0;
	for (i = 0; i < iNofElement; i++)
		iNofAtom_up[i] = 0;
	for (i = 0; i < iNofAtoms; i++)
	{
		if (atom_initial[i].iIfup == 1)
			for (j = 0; j < iNofElement; j++)
				if (atom_initial[i].sAtom == atomname[j])
				{
					iNofAtom_up[j]++;
					iNofAtoms_up++;
				}
	}
	for (j = 0; j < iNofElement; j++)
		cout << iNofAtom_up[j] << '\n';
	cout << iNofAtoms_up << '\n';




	for (l = 0; l < iNofStep_x; l++)
		for (mm = 0; mm < iNofStep_y; mm++)
			for (n = 0; n < iNofStep_z; n++)
			{

				temp = "cp " + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/CONTCAR ./";
				strcpy(command, temp.c_str());
				system(command);
				inall.open("CONTCAR", ios::in);
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
					i++;
				}
				//iNofElement = i;

				for (i = 0; i < iNofElement; i++)
				{
					inall >> iNofAtom[i];
					//iNofAtoms = iNofAtoms + iNofAtom[i];
				}
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
					getline(inall, temp);  //Selective dynamics or not
					inputss.str("");
					inputss.clear();
					inputss << temp;
					inputss >> temp;
					if (temp == "Direct" || temp == "direct")

					{
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
						}
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
					}
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
					}
				}

				inall.close();



				filename = "POSCAR_up";
				outall.open(filename, ios::out);
				outall << "# data file written by LICM-HTC\n";
				outall << constant << " \n";
				outall << ax << ' ' << ay << ' ' << az << " \n";
				outall << bx << ' ' << by << ' ' << bz << " \n";
				outall << cx << ' ' << cy << ' ' << cz << " \n";
				//cout << "caonm" << iNofElement << '\n';
				for (m = 0; m < iNofElement; m++)
				{
					// cout << "caonm" << iNofAtom_up[m] << '\n';
					  //   cin >> ii;
					if (iNofAtom_up[m] != 0)
					{
						outall << atomname[m] << ' ';

					}
				}
				outall << '\n';
				for (m = 0; m < iNofElement; m++)
					if (iNofAtom_up[m] != 0)
						outall << iNofAtom_up[m] << ' ';
				outall << "\n";

				if (iIfCar == 0 || iIfCar == 1)
				{
					outall << "Direct\n";
					for (m = 0; m < iNofAtoms; m++)
						if (atom_initial[m].iIfup == 1)
						{
							outall << atom_initial[m].x << ' ';
							outall << atom_initial[m].y << ' ';
							outall << atom_initial[m].z << '\n';
						}
				}

				else if (iIfCar == 10 || iIfCar == 11)
				{
					outall << "Selective dynamics\n" << "Direct\n";
					for (m = 0; m < iNofAtoms; m++)
						if (atom_initial[m].iIfup == 1)
						{
							outall << atom_initial[m].x << ' ';
							outall << atom_initial[m].y << ' ';
							outall << atom_initial[m].z << ' ';
							outall << atom_initial[m].Sx << ' ';
							outall << atom_initial[m].Sy << ' ';
							outall << atom_initial[m].Sz << '\n';
						}
				}
				outall.close();

				filename = "POSCAR_down";
				outall.open(filename, ios::out);
				outall << "# data file written by LICM-HTC\n";
				outall << constant << " \n";
				outall << ax << ' ' << ay << ' ' << az << " \n";
				outall << bx << ' ' << by << ' ' << bz << " \n";
				outall << cx << ' ' << cy << ' ' << cz << " \n";
				for (m = 0; m < iNofElement; m++)
					if (iNofAtom[m] - iNofAtom_up[m] != 0)
						outall << atomname[m] << ' ';
				outall << '\n';
				for (m = 0; m < iNofElement; m++)
					if (iNofAtom[m] - iNofAtom_up[m] != 0)
						outall << iNofAtom[m] - iNofAtom_up[m] << ' ';
				outall << "\n";

				if (iIfCar == 0 || iIfCar == 1)
				{
					outall << "Direct\n";

					for (m = 0; m < iNofAtoms; m++)
						if (atom_initial[m].iIfup == 0)
						{
							outall << atom_initial[m].x << ' ';
							outall << atom_initial[m].y << ' ';
							outall << atom_initial[m].z << '\n';
						}
				}

				else if (iIfCar == 10 || iIfCar == 11)
				{
					outall << "Selective dynamics\n" << "Direct\n";
					for (m = 0; m < iNofAtoms; m++)
						if (atom_initial[m].iIfup == 0)
						{
							outall << atom_initial[m].x << ' ';
							outall << atom_initial[m].y << ' ';
							outall << atom_initial[m].z << ' ';
							outall << atom_initial[m].Sx << ' ';
							outall << atom_initial[m].Sy << ' ';
							outall << atom_initial[m].Sz << '\n';

						}
				}
				outall.close();

				temp = "mkdir ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up";
				strcpy(command, temp.c_str());
				system(command);
				temp = "mkdir ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down";
				strcpy(command, temp.c_str());
				system(command);

				temp = "mv POSCAR_up ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up/POSCAR";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("rvasp.sh", ios::in);
				inall >> sTemp2;
				while (!inall.eof())
				{
					sTemp1 = sTemp2;
					inall >> sTemp2;

					if (sTemp1 == "#PBS" && sTemp2 == "-N")
					{
						inall >> name;
						break;
					}
				}
				inall.close();

				inall.open("rvasp.sh", ios::in);
				outall.open("rvasp1.sh", ios::out);
				while (!inall.eof())
				{
					getline(inall, line);
					if (strstr(line.c_str(), "#PBS") && strstr(line.c_str(), "-N"))
						outall << "#PBS -N " << name << '_' << l << '_' << mm << '_' << n << "_up" << '\n';
					else
						outall << line << endl;
				}
				inall.close();
				outall.close();


				temp = "cp KPOINTS ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp rvasp1.sh ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up/rvasp.sh";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp INCAR_up ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up/INCAR";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp POTCAR_up ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/up/POTCAR";
				strcpy(command, temp.c_str());
				system(command);


				temp = "mv POSCAR_down ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down/POSCAR";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("rvasp.sh", ios::in);
				inall >> sTemp2;
				while (!inall.eof())
				{
					sTemp1 = sTemp2;
					inall >> sTemp2;

					if (sTemp1 == "#PBS" && sTemp2 == "-N")
					{
						inall >> name;
						break;
					}
				}
				inall.close();

				inall.open("rvasp.sh", ios::in);
				outall.open("rvasp1.sh", ios::out);
				while (!inall.eof())
				{
					getline(inall, line);
					if (strstr(line.c_str(), "#PBS") && strstr(line.c_str(), "-N"))
						outall << "#PBS -N " << name << '_' << l << '_' << mm << '_' << n << "_down" << '\n';
					else
						outall << line << endl;
				}
				inall.close();
				outall.close();


				temp = "cp KPOINTS ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp rvasp1.sh ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down/rvasp.sh";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp INCAR_down ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down/INCAR";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp POTCAR_down ./" + to_string(l) + '_' + to_string(mm) + '_' + to_string(n) + "/down/POTCAR";
				strcpy(command, temp.c_str());
				system(command);

				// cin >>ii;
			}
	return 0;
}
