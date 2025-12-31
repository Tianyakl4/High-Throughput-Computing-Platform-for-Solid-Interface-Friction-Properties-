#include <iomanip>
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

int CInterface::Output_CHG_z()
{
	int i, j, k, l, m, n, ii, iii;
	int i_MinEnergy, j_MinEnergy;
	int iNofAtoms;
	int iNofPoint;
	char command[100];
	double zz, fCHG_z;
	string temp, temp1, temp2, temp3;
	double ftemp;
	double f1, f2, f3;
	double fz;
	int itemp;
	int iNX, iNY, iNZ;
	fstream inall, inall1, inall2, inall_CHGCAR_z, outall, outall1, outall2;
	stringstream  inputss, ss;
	double fInterface_Site_Min, fInterface_Site_Max;
	double volume;
	//cout << "Please input the min interface sites (Direct):" << '\n';
	//cin >> fInterface_Site_Min;

	cout << '\n' << "    " << "The in.dat will be required here!" << '\n';
	int iNofLayer = 0;
	int iIfCompress = 0;
	double FSITEOFFACE[100];//jiemian weizhi dayu cizhi de yuanzi bei yidong, Direct zuobiao de zhi
	double fSiteofFace_Move;
	inall1.open("in.dat", ios::in);
	inall1 >> iNofLayer;
	inall1 >> iIfCompress;
	for (i = 0; i < iNofLayer - 1; i++)
		inall1 >> FSITEOFFACE[i];
	inall1 >> fSiteofFace_Move;
	inall1.close();

	cout << "    " << "The POSCAR will be required here!" << '\n';
	int iOrder_Max, iOrder_Min;
	fInterface_Site_Max = 1;
	fInterface_Site_Min = 0;
	inall.open("POSCAR", ios::in);
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
	getline(inall, temp);
	inputss.str("");
	inputss.clear();
	inputss << temp;
	inputss >> temp;
	fInterface_Site_Max = 1;
	fInterface_Site_Min = 0;
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
				inall >> ftemp;	inall >> ftemp;	inall >> fz; inall >> temp;	inall >> temp; inall >> temp;				
				if (fz < fInterface_Site_Max && fz > fSiteofFace_Move)
				{
					fInterface_Site_Max = fz;
					iOrder_Max = iii + 1;					
				}
				if (fz > fInterface_Site_Min && fz < fSiteofFace_Move)
				{
					fInterface_Site_Min = fz;
					iOrder_Min = iii + 1;
				}
				
			}
		}
	}
	else if (temp == "Direct" || temp == "direct")
	{
		for (iii = 0; iii < iNofAtoms; iii++)
		{
			inall >> ftemp; inall >> ftemp; inall >> fz;
			if (fz < fInterface_Site_Max && fz > fSiteofFace_Move)
			{
				fInterface_Site_Max = fz;
				iOrder_Max = iii + 1;
			}
			if (fz > fInterface_Site_Min && fz < fSiteofFace_Move)
			{
				fInterface_Site_Min = fz;
				iOrder_Min = iii + 1;
			}
		}
	}
	inall.close();
	cout << "iOrder_Min:  " << iOrder_Min << '\n';
	cout << "iOrder_Max:  " << iOrder_Max << '\n';



	outall1.open("CHG_Interface.dat", ios::out);
	outall2.open("CHG_Interface_Center.dat", ios::out);
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < iNofStep_z; k++)
			{
				cout << "(i, j, k):  " << i << ", " << j << ", " << k << '\n';
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/CONTCAR ./CONTCAR";
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
							inall >> temp; inall >> temp; inall >> temp;
							if (iii == iOrder_Max - 1)
								fInterface_Site_Max = fz;
							if (iii == iOrder_Min - 1)
								fInterface_Site_Min = fz;
						}
					}
				}
				else if (temp == "Direct" || temp == "direct")
				{
					for (iii = 0; iii < iNofAtoms; iii++)
					{
						inall >> ftemp; inall >> ftemp; inall >> fz;
						if (iii == iOrder_Max - 1)
							fInterface_Site_Max = fz;
						if (iii == iOrder_Min - 1)
							fInterface_Site_Min = fz;
					}
				}
				inall.close();
				cout << "fInterface_Site_Min: " << fInterface_Site_Min << '\n';
				cout << "fInterface_Site_Max: " << fInterface_Site_Max << '\n';


				temp = "cp ./CHGAll/CHGCAR_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + " ./CHGCAR";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("CHGCAR", ios::in);
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

				temp = "CHGCAR_z_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				outall.open(temp, ios::out);
				outall << "zz(A)            CHG(e)" << '\n';
				fCHG_z = 0.0;
				fCHG_Interface[i][j][k] = 0.0;
				fCHG_Interface_Center[i][j][k] = 0.0;
				zz = 0.0;
				iNofPoint = 0;
				for (n = 0; n < iNZ; n++)
				{
					zz = n * c / double(iNZ);
					fCHG_z = 0.0;

					for (l = 0; l < iNX; l++)
						for (m = 0; m < iNY; m++)
						{
							inall >> f1;
							fCHG_z = fCHG_z + f1;
							if (zz >= fInterface_Site_Min * c && zz <= fInterface_Site_Max * c)
							{
								iNofPoint++;
								fCHG_Interface[i][j][k] = fCHG_Interface[i][j][k] + f1;
							}
						}
					outall << zz << "     " << fCHG_z / double(iNX * iNY * iNZ) << setprecision(12) << '\n';
				}
				outall.close();

				temp = "CHGCAR_z_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				inall_CHGCAR_z.open(temp, ios::in);

				inall_CHGCAR_z >> temp >> temp;
				fCHG_Interface_Center[i][j][k] = 1000000000000;
				for (n = 0; n < iNZ; n++)
				{
					zz = n * c / double(iNZ);
					inall_CHGCAR_z >> ftemp;
					inall_CHGCAR_z >> fCHG_z;
					if (zz > fInterface_Site_Min * c && zz < fInterface_Site_Max * c && fCHG_z < fCHG_Interface_Center[i][j][k])
					{
						cout << "zz: " << zz << '\n';
						fCHG_Interface_Center[i][j][k] = fCHG_z;
					}
				}
				cout << "CHG_Interface_Center (e): " << fCHG_Interface_Center[i][j][k] << '\n';
				inall_CHGCAR_z.close();

				if (k == 0)
				{
					outall1 << '\n';
					outall2 << '\n';
				}
				fCHG_Interface[i][j][k] = fCHG_Interface[i][j][k] / double(iNX * iNY * iNZ);
				//volume = a * b * sin(theta_ab) * z[k];
				//fCHG_Interface[i][j][k] = fCHG_Interface[i][j][k] / volume;
				outall1 << fCHG_Interface[i][j][k] << setprecision(12) << ' ';
				outall2 << fCHG_Interface_Center[i][j][k] << setprecision(12) << ' ';
				//cout << "CHG_Sum (e): " << fCHG_Interface[i][j][k] << '\n';
				/*
				if ((k + 1) % 5 == 0)
				{
					outall1 << '\n';
					outall2 << '\n';
				}
				*/
				inall.close();
			}

	outall1.close();
	outall2.close();

	/*
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			temp = "CHGCAR_d_" + to_string(i) + '_' + to_string(j);
			outall.open(temp, ios::out);
			outall << "Interface-Distance(A)  CHG(e)" << '\n';
			for (k = 0; k < iNofStep_z; k++)
			{
				outall << z[k] << ' ' << fCHG_Interface[i][j][k] << setprecision(12) << '\n';
			}
			outall.close();
		}
		temp = "mkdir CHGAll_d";
	    strcpy(command, temp.c_str());
	    system(command);
	    temp = "mv CHGCAR_d* ./CHGAll_d";
	    strcpy(command, temp.c_str());
	    system(command);
    */

	outall.open("d_CHGCAR_Interface", ios::out);
	outall << "Interface-Distance(A)  CHG(e)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';	
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fCHG_Interface[i][j][k] << setprecision(12);
			}
		outall << '\n';
	}
	outall.close();
	
	/*
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			temp = "CHGCAR_d_Interface_Center" + to_string(i) + '_' + to_string(j);
			outall.open(temp, ios::out);
			outall << "Interface-Distance(A)  CHG(e)" << '\n';
			for (k = 0; k < iNofStep_z; k++)
			{
				outall << z[k] << ' ' << fCHG_Interface_Center[i][j][k] << setprecision(12) << '\n';
			}
			outall.close();
		}
    temp = "mkdir CHGAll_d_Interface_Center";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHGCAR_d_* ./CHGAll_d_Interface_Center";
	strcpy(command, temp.c_str());
	system(command);
	*/

	outall.open("d_CHGCAR_Interface_Center", ios::out);
	outall << "Interface-Distance(A)  CHG(e)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fCHG_Interface_Center[i][j][k] << setprecision(12);
			}
		outall << '\n';
	}
	outall.close();

	cout << "Please enter i and j with the minimum energy position to calculate the DeltaCHGCAR_Interface_Center: " << '\n';
	cin >> i_MinEnergy >> j_MinEnergy;
	cout << '\n';
	outall.open("d_DeltaCHGCAR_Interface_Center_DeltaEnergy", ios::out);
	outall << "Interface-Distance(A) DeltaCHGCAR_Interface_Center(e) DeltaEnergy(eV)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fCHG_Interface_Center[i][j][k] - fCHG_Interface_Center[i_MinEnergy][j_MinEnergy][k] << ' ' << fEnergy[i][j][k] - fEnergy[i_MinEnergy][j_MinEnergy][k];
			}
		outall << '\n';
	}
	outall.close();

	outall.open("d_TDiffCHG_zDirection_DeltaEnergy", ios::out);
	outall << "Interface-Distance(A) TDiffCHG_zDirection(e) DeltaEnergy(eV)" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				fTDiffCHG_zDirection[i][j][k] = 0;
				temp = "CHGCAR_z_" + to_string(i_MinEnergy) + '_' + to_string(j_MinEnergy) + '_' + to_string(k);
				inall1.open(temp, ios::in);
				temp = "CHGCAR_z_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				inall2.open(temp, ios::in);
				getline(inall1, temp);
				getline(inall2, temp);
				for (n = 0; n < iNZ; n++)
				{
					inall1 >> ftemp; inall1 >> f1;
					inall2 >> ftemp; inall2 >> f2;
					fTDiffCHG_zDirection[i][j][k] = fTDiffCHG_zDirection[i][j][k] + fabs(f2 - f1);
				}	
				inall1.close();
				inall2.close();
				outall << ' ' << fTDiffCHG_zDirection[i][j][k] << ' ' << fEnergy[i][j][k] - fEnergy[i_MinEnergy][j_MinEnergy][k];
			}
		outall << '\n';
	}
	outall.close();


	temp = "mkdir CHGAll_z";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHGCAR_z* ./CHGAll_z";
	strcpy(command, temp.c_str());
	system(command);
	return 0;
}

