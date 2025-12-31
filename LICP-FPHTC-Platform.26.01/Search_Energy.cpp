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

int CInterface::Search_Energy()
{
	int i, j, k, m, n;
	char command[100];
	string temp, temp1, temp2, temp3;
	fstream inall, outall;
	double k1, k2;
	k1 = iNofStep_y * 1.0 / (iNofStep_x * 1.0);
	k2 = -1.0 * k1; double distance_temp1, distance_temp2;

	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			for (k = 0; k < iNofStep_z; k++)
			{
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/OUTCAR ./";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("OUTCAR", ios::in);
				m = 0;
				while (!inall.eof())
				{
					inall >> temp1;
					if (temp1 == "energy(sigma->0)")
					{
						m++;
						inall >> temp2;
						inall >> fEnergy[i][j][k];

					}

				}
				inall.close();
				/*
				inall.open("OUTCAR", ios::in);
				n = 0;
				while (!inall.eof())
				{
						inall >> temp1;
						if (temp1 == "energy(sigma->0)")
						{
								n++;
								inall >> temp2;
								if(n == m-1)
								  inall >> fEnergy[i][j][k];
						}

				}
				inall.close();
				*/
				if (i == 0)
					fEnergy[iNofStep_x][j][k] = fEnergy[i][j][k];
				if (j == 0)
					fEnergy[i][iNofStep_y][k] = fEnergy[i][j][k];
				fEnergy[iNofStep_x][iNofStep_y][k] = fEnergy[0][0][k];
			}
		}

	outall.open("temp1.dat", ios::out);
	outall << '\n';
	for (i = 0; i <= iNofStep_x; i++)
		for (j = 0; j <= iNofStep_y; j++)
		{
			for (k = 0; k < iNofStep_z; k++)
			{
				outall << " " << setprecision(12) << fEnergy[i][j][k];
				if ((k + 1) % 5 == 0)
					outall << '\n';
			}
			outall << '\n';
		}
	outall.close();

	/*
	outall.open("Dengju.dat", ios::out);
	outall << '\n';
	for (k = 0; k <= iNofStep_z; k++)
	{
		for (j = 0; j <= iNofStep_y; j++)
		{
			for (i = 0; i <= iNofStep_x; i++)
			{
				outall << "  " << fEnergy[i][j][k];
				if ((k + 1) % iNofStep_y == 0)
					;
			}
			outall << '\n';
		}
		outall << '\n';
		outall << '\n';
	}
	outall.close();
	*/

	outall.open("d_Energy", ios::out);
	outall << "Interface-Distance(A)  Energy(eV) from 00 to ij" << '\n';
	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				outall << ' ' << fEnergy[i][j][k] << setprecision(12);
			}
		outall << '\n';
	}
	outall.close();

	return 0;
}

