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

int CDiffCHG::Output_DiffCHG_z()
{
	int i, j, k, l, m, n, ii;
	char command[100];
	double zz, fDiffCHG_z, fDiffCHG_z_abs;
	string temp, temp1, temp2, temp3;
	double ftemp;
	double f1, f2, f3;
	int itemp;
	int iNX, iNY, iNZ;
	int i_MinEnergy, j_MinEnergy;
	fstream inall, inall1, inall2, outall, outall1, outall2, outall3;
	fstream outall_DiffCHG_Sun, outall_DeltaDiffCHG_Sun;
	outall1.open("DiffCHG_Sum.dat", ios::out);
	outall_DiffCHG_Sun.open("DiffCHG_Sum_Sun.dat", ios::out);	
	stringstream  inputss, ss;
	//        double fInterface_Site_Min;
	//        cout << "Please input the min interface sites (Direct):" <<'\n';
	//       cin >> fInterface_Site_Min;
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < iNofStep_z; k++)
			{
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
					inall >> ftemp; inall >> ftemp; inall >> ftemp;
				}
				inall >> iNX; inall >> iNY; inall >> iNZ;
				cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
				outall << "zz(A)            DiffCHG(e)" << '\n';
				fDiffCHG_z = 0.0;
				outall2 << "zz(A)            DiffCHG(e)" << '\n';
				fDiffCHG_z_abs = 0.0;
				fDiffCHG_Sum[i][j][k] = 0.0;
				fDiffCHG_Sum_SunJunhui[i][j][k] = 0.0;
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
							//                           if(zz>=fInterface_Site_Min*c && zz<=fInterface_Site_Min*c + z[k])
							{
								//fDiffCHG_z = fDiffCHG_z + fabs(f1);
								//fDiffCHG_Sum[i][j][k] = fDiffCHG_Sum[i][j][k] + fabs(f1);
								fDiffCHG_z = fDiffCHG_z + f1;
								fDiffCHG_z_abs = fDiffCHG_z_abs + fabs(f1);
								fDiffCHG_Sum[i][j][k] = fDiffCHG_Sum[i][j][k] + fabs(f1);
							}
						}
					fDiffCHG_Sum_SunJunhui[i][j][k] = fDiffCHG_Sum_SunJunhui[i][j][k] + fabs(fDiffCHG_z);
					outall << zz << "     " << fDiffCHG_z / double(iNX * iNY * iNZ) << setprecision(12) << '\n';
					outall2 << zz << "     " << fDiffCHG_z_abs / double(iNX * iNY * iNZ) << setprecision(12) << '\n';
				}
				if (k == 0)
				{
					outall1 << '\n';
					outall_DiffCHG_Sun << '\n';
				}
				fDiffCHG_Sum[i][j][k] = fDiffCHG_Sum[i][j][k] / double(iNX * iNY * iNZ);
				fDiffCHG_Sum_SunJunhui[i][j][k] = fDiffCHG_Sum_SunJunhui[i][j][k] / double(iNX * iNY * iNZ);
				outall1 << fDiffCHG_Sum[i][j][k] << setprecision(12) << ' ';
				outall_DiffCHG_Sun << fDiffCHG_Sum_SunJunhui[i][j][k] << setprecision(12) << ' ';
				cout << fDiffCHG_Sum[i][j][k] << '\n';
				if ((k + 1) % 5 == 0)
					outall1 << '\n';
				if ((k + 1) % 5 == 0)
					outall_DiffCHG_Sun << '\n';
				inall.close();
				outall.close();
				outall2.close();
				//cin >> ii;
			}

	outall1.close();
	outall_DiffCHG_Sun.close();

	outall.open("d_DiffCHG_All", ios::out);
	outall << "Interface-Distance(A)  DiffCHG(e) from 00 to ij" << '\n';
	outall_DiffCHG_Sun.open("d_DiffCHG_All_Sun", ios::out);
	outall_DiffCHG_Sun << "Interface-Distance(A)  DiffCHG(e) from 00 to ij" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k];
		outall_DiffCHG_Sun << z[k];
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fDiffCHG_Sum[i][j][k];
				outall_DiffCHG_Sun << ' ' << fDiffCHG_Sum_SunJunhui[i][j][k];
			}
		outall << '\n';
		outall_DiffCHG_Sun << '\n';
	}
	outall.close();
	outall_DiffCHG_Sun.close();

	cout << "Please enter i and j with the minimum energy position to calculate the differential charge density and delta differential charge density: " << '\n';
	cin >> i_MinEnergy >> j_MinEnergy;
	cout << '\n';
	temp = "d_DiffCHG_" + to_string(i_MinEnergy) + '_' + to_string(j_MinEnergy) + "_DeltaEnergy";
	outall.open(temp, ios::out);
	outall << "Interface-Distance(A) DiffCHG_" << i_MinEnergy << '_' << j_MinEnergy << "(e)    DeltaEnergy(eV)" << '\n';
	temp = "d_DiffCHG" + to_string(i_MinEnergy) + '_' + to_string(j_MinEnergy) + "_DeltaEnergy_Sun";
	outall_DiffCHG_Sun.open(temp, ios::out);
	outall_DiffCHG_Sun << "Interface-Distance(A) DiffCHG_Sun" << i_MinEnergy << '_' << j_MinEnergy << "(e)    DeltaEnergy(eV)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k];
		outall_DiffCHG_Sun << z[k];
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fDiffCHG_Sum[i_MinEnergy][j_MinEnergy][k] << ' ' << fEnergy[i][j][k] - fEnergy[i_MinEnergy][j_MinEnergy][k];
				outall_DiffCHG_Sun << ' ' << fDiffCHG_Sum_SunJunhui[i_MinEnergy][j_MinEnergy][k] << ' ' << fEnergy[i][j][k] - fEnergy[i_MinEnergy][j_MinEnergy][k];
			}
		outall << '\n';
		outall_DiffCHG_Sun << '\n';
	}
	outall.close();
	outall_DiffCHG_Sun.close();
	
	outall_DeltaDiffCHG_Sun.open("d_Delta_DiffCHG_Sum_Sun", ios::out);	
	outall_DeltaDiffCHG_Sun << "Interface Distace (A)   DeltaDiffCHG_Sun from 00 to ij (e)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall_DeltaDiffCHG_Sun << z[k] << "   ";
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				fDelta_DiffCHG_Sum_SunJunhui[i][j][k] = 0;
				temp = "DiffCHG_z_" + to_string(i_MinEnergy) + '_' + to_string(j_MinEnergy) + '_' + to_string(k);
				inall1.open(temp, ios::in);
				temp = "DiffCHG_z_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				inall2.open(temp, ios::in);
				getline(inall1, temp);
				getline(inall2, temp);				
				for (n = 0; n < iNZ; n++)
				{
					inall1 >> ftemp; inall1 >> f1;
					inall2 >> ftemp; inall2 >> f2;
					fDelta_DiffCHG_Sum_SunJunhui[i][j][k] = fDelta_DiffCHG_Sum_SunJunhui[i][j][k] + fabs(f2 - f1);
				}
				outall_DeltaDiffCHG_Sun << fDelta_DiffCHG_Sum_SunJunhui[i][j][k] << "   ";
				inall1.close();
				inall2.close();
			}
		outall_DeltaDiffCHG_Sun << '\n';
	}
	outall_DeltaDiffCHG_Sun.close();

	temp = "d_Delta_DiffCHG" + to_string(i_MinEnergy) + '_' + to_string(j_MinEnergy) + "_DeltaEnergy_Sun";
	outall_DeltaDiffCHG_Sun.open(temp, ios::out);
	outall_DeltaDiffCHG_Sun << "Interface-Distance(A) DeltaDiffCHG_Sun" << i_MinEnergy << '_' << j_MinEnergy << "(e)    DeltaEnergy(eV)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall_DeltaDiffCHG_Sun << z[k];
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall_DeltaDiffCHG_Sun << ' ' << fDelta_DiffCHG_Sum_SunJunhui[i][j][k] << ' ' << fEnergy[i][j][k] - fEnergy[i_MinEnergy][j_MinEnergy][k];
			}
		outall_DeltaDiffCHG_Sun << '\n';
	}
	outall_DeltaDiffCHG_Sun.close();

	temp = "mkdir DiffCHGAll_z_abs";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_z_abs* ./DiffCHGAll_z_abs";
	strcpy(command, temp.c_str());
	system(command);

	temp = "mkdir DiffCHGAll_z";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_z* ./DiffCHGAll_z";
	strcpy(command, temp.c_str());
	system(command);
	return 0;
}

