#include <iomanip>
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

int CDiffCHG::Output_DiffCHG_z_Interface()
{
	int i, j, k, l, m, n, ii, iii;
	char command[100];
	double zz, fDiffCHG_z, fDiffCHG_z_abs;
	string temp, temp1, temp2, temp3;
	double ftemp;
	double f1, f2, f3;
	int itemp;
	int iNX, iNY, iNZ;
	fstream inall, inall1, inall2, outall, outall1, outall2, outall3;
	stringstream  inputss, ss;
	double fz, fInterface_Site_Min, fInterface_Site_Max;
	int iNofAtoms;

	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < iNofStep_z; k++)
			{
				fInterface_Site_Max = 1;
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/up/CONTCAR ./CONTCAR";
				strcpy(command, temp.c_str());
				system(command);
				inall.open("CONTCAR", ios::in);
				getline(inall, temp);
				inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				while (inall.get() != 10)
				{
					;
				}

				getline(inall, temp);
                                inputss.str("");
                                inputss.clear();
				inputss << temp;
				iii = 0;
				while (inputss >> atomname[iii])
				{
					iii++;
				}
				iNofElement = iii;			
                                iNofAtoms = 0;	
				for (iii = 0; iii < iNofElement; iii++)
				{
					inall >> iNofAtom[iii];
					iNofAtoms = iNofAtoms + iNofAtom[iii];
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
						for (iii = 0; iii < iNofAtoms; iii++)
						{
							inall >> ftemp; inall >> ftemp; inall >> fz;
							if (fz < fInterface_Site_Max)
								fInterface_Site_Max = fz;
							inall >> temp;
							inall >> temp;
							inall >> temp;
						}
					}
				}
				else if (temp == "Direct" || temp == "direct")
				{
					for (iii = 0; iii < iNofAtoms; iii++)
					{
						inall >> ftemp; inall >> ftemp; inall >> fz;
						if (fz < fInterface_Site_Max)
							fInterface_Site_Max = fz;
					}
				}
				inall.close();

				fInterface_Site_Min = 0;
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/down/CONTCAR ./CONTCAR";
				strcpy(command, temp.c_str());
				system(command);
				inall.open("CONTCAR", ios::in);
				getline(inall, temp);
				inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				while (inall.get() != 10)
				{
					;
				}

				getline(inall, temp);
                                inputss.str("");
                                inputss.clear();
				inputss << temp;
				iii = 0;
				while (inputss >> atomname[iii])
				{
					iii++;
				}
				iNofElement = iii;
                                iNofAtoms = 0;
				for (iii = 0; iii < iNofElement; iii++)
				{
					inall >> iNofAtom[iii];
					iNofAtoms = iNofAtoms + iNofAtom[iii];
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
						for (iii = 0; iii < iNofAtoms; iii++)
						{
							inall >> ftemp; inall >> ftemp; inall >> fz;
							if (fz > fInterface_Site_Min)
								fInterface_Site_Min = fz;
							inall >> temp;
							inall >> temp;
							inall >> temp;
						}
					}
				}
				else if (temp == "Direct" || temp == "direct")
				{
					for (iii = 0; iii < iNofAtoms; iii++)
					{
						inall >> ftemp; inall >> ftemp; inall >> fz;
						if (fz > fInterface_Site_Min)
							fInterface_Site_Min = fz;
					}
				}
				inall.close();

				cout << "fInterface_Site_Min: " << fInterface_Site_Min << '\n';
				cout << "fInterface_Site_Max: " << fInterface_Site_Max << '\n';


				temp = "cp ./DiffCHGAll/DiffCHG_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + " ./CHGCAR";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("CHGCAR", ios::in);
				temp = "DiffCHG_z_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				outall.open(temp, ios::out);
				temp = "DiffCHG_z_abs" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				outall2.open(temp, ios::out);
				getline(inall, temp);
				inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				while (inall.get() != 10)
				{
					;
				}
				getline(inall, temp);
				inputss.str("");
				inputss.clear();
				inputss << temp;
				itemp = 0;
				while (inputss >> temp1)
				{
					itemp++;
				}

				ii = 0;
				for (m = 0; m < itemp; m++)
				{
					inall >> n;
					ii = ii + n;
				}
				inall >> temp;
				for (m = 0; m < ii; m++)
				{
					inall >> ftemp; inall >> ftemp; inall >> fz;
				}
				

				inall >> iNX; inall >> iNY; inall >> iNZ;
				cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
				outall << "zz(A)            DiffCHG(e)" << '\n';
				fDiffCHG_z = 0.0;
				outall2 << "zz(A)            DiffCHG(e)" << '\n';
				fDiffCHG_z_abs = 0.0;
				fDiffCHG_Sum_Interface[i][j][k] = 0.0;
				zz = 0.0;
				for (n = 0; n < iNZ; n++)
				{
					zz = n * c / double(iNZ);
					fDiffCHG_z = 0.0;
					fDiffCHG_z_abs = 0.0;
					for (l = 0; l < iNX; l++)
						for (m = 0; m < iNY; m++)
						{
							inall >> f1;
							if (zz >= fInterface_Site_Min * c && zz <= fInterface_Site_Max * c)
							{
								fDiffCHG_z = fDiffCHG_z + f1;
								fDiffCHG_z_abs = fDiffCHG_z_abs + fabs(f1);
								fDiffCHG_Sum_Interface[i][j][k] = fDiffCHG_Sum_Interface[i][j][k] + fabs(f1);
							}
						}
					outall << zz << "     " << fDiffCHG_z / double(iNX * iNY * iNZ) << setprecision(12) << '\n';
					outall2 << zz << "     " << fDiffCHG_z_abs / double(iNX * iNY * iNZ) << setprecision(12) << '\n';
				}
				fDiffCHG_Sum_Interface[i][j][k] = fDiffCHG_Sum_Interface[i][j][k] / double(iNX * iNY * iNZ);
				cout << fDiffCHG_Sum_Interface[i][j][k] << '\n';
				inall.close();
				outall.close();
				outall2.close();
				//cin >> ii;
			}
	outall1.open("DiffCHG_Sum_Interface.dat", ios::out);
	outall1 << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall1 << fDiffCHG_Sum_Interface[i][j][k] << setprecision(12) << ' ';
			}
		outall1 << '\n';
	}
	outall1.close();

	temp = "mkdir DiffCHGAll_z_abs_Interface";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_z_abs* ./DiffCHGAll_z_abs_Interface";
	strcpy(command, temp.c_str());
	system(command);

	temp = "mkdir DiffCHGAll_z_Interface";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_z* ./DiffCHGAll_z_Interface";
	strcpy(command, temp.c_str());
	system(command);

	/*
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			temp = "DiffCHG_d_" + to_string(i) + '_' + to_string(j);
			outall.open(temp, ios::out);
			outall << "Interface-Distance(A)  DiffCHG(e)" << '\n';
			for (k = 0; k < iNofStep_z; k++)
			{
				outall << z[k] << ' ' << fDiffCHG_Sum_Interface[i][j][k] << '\n';
			}
			outall.close();
		}

	temp = "mkdir DiffCHGAll_d_Interface";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_d* ./DiffCHGAll_d_Interface";
	strcpy(command, temp.c_str());
	system(command);
	*/
	outall.open("d_DiffCHG_Interface", ios::out);
	outall << "Interface-Distance(A)  DiffCHG(e) from 00 to ij" << '\n';	
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k];
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fDiffCHG_Sum_Interface[i][j][k];
			}
		outall << '\n';
	}
	outall.close();
	return 0;
}

