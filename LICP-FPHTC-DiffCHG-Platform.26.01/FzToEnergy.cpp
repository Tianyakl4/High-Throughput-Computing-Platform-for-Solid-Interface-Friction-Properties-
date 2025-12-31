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
#include "CDiffCHG.h"

using namespace std;

int CDiffCHG::FzToEnergy(double Fz)
{

	int i, j, k, l, m, n, ii;
	double z1, zz;
	double xielv, xielv1, xielv2, Energy_fit;
	double z_depart;
	int ifbeyond;
	if (Fz > fFz_Max_all || Fz < fFz_Min_all)
		ifbeyond = 1;
	else
	{
		for (i = 0; i < iNofStep_x + 1; i++)
		{
			for (j = 0; j < iNofStep_y + 1; j++)
			{
				fEnergy_Fz[i][j] = 0.0;
				z_Fz[i][j] = 0.0;
			}
		}

		for (i = 0; i < iNofStep_x + 1; i++)   //Fz_z zhi shiyong dandiao dizenghansh
			for (j = 0; j < iNofStep_y + 1; j++)
			{

				for (k = 1; k < iNofStep_z - 2; k++)
				{
					if ((Fz >= k_point[i][j][k] && Fz <= k_point[i][j][k + 1]) || (Fz <= k_point[i][j][k] && Fz >= k_point[i][j][k + 1]))
					{
						break;
					}
					else
						;
				}
				z1 = 0.0;
				if (k >= iNofStep_z - 2)
				{
					cout << " Fz=" << Fz << " error for FzToEnergy. Can't find Fz!" << '\n';
					ifbeyond = 1;
					break;
				}
				else
				{
					z1 = Fz * (z[k + 1] - z[k]) + z[k] * k_point_origin[i][j][k + 1] - z[k + 1] * k_point_origin[i][j][k];
					z1 = z1 / (k_point_origin[i][j][k + 1] - k_point_origin[i][j][k]);
				}

				z_Fz[i][j] = z1;

				Energy_fit = fEnergy[i][j][k];
				for (m = 0; m < NINJIANGE; m++)
				{
					zz = z[k] + double(m) / double(NINJIANGE) * (z[k + 1] - z[k]);
					if (zz >= z1 - double(i) / double(NINJIANGE))
						break;
					else
					{
						if (k_point[i][j][k + 1] - k_point[i][j][k] > -0.000001 && k_point[i][j][k + 1] - k_point[i][j][k] < 0.000001)
							z_depart = z[k];
						else
							z_depart = z[k] + fabs((k_average[i][j][k] - k_point[i][j][k + 1]) / (k_point[i][j][k + 1] - k_point[i][j][k])) * (z[k + 1] - z[k]);
						if ((z_depart - z[k] > -0.000001 && z_depart - z[k] < 0.000001) || (z_depart - z[k + 1] > -0.000001 && z_depart - z[k + 1] < 0.000001))
							xielv = (zz - z[k]) / (z[k + 1] - z[k]) * k_point[i][j][k + 1] + (z[k + 1] - zz) / (z[k + 1] - z[k]) * k_point[i][j][k];
						else
						{
							if (zz <= z_depart)
							{
								xielv1 = (zz - z[k]) / (z_depart - z[k]) * k_average[i][j][k] + (z_depart - zz) / (z_depart - z[k]) * k_point[i][j][k];
							}
							else
							{
								xielv1 = (z[k + 1] - zz) / (z[k + 1] - z_depart) * k_average[i][j][k] + (zz - z_depart) / (z[k + 1] - z_depart) * k_point[i][j][k + 1];
							}
							zz = z[k] + double(m + 1) / double(NINJIANGE) * (z[k + 1] - z[k]);
							if (zz <= z_depart)
							{
								xielv2 = (zz - z[k]) / (z_depart - z[k]) * k_average[i][j][k] + (z_depart - zz) / (z_depart - z[k]) * k_point[i][j][k];
							}
							else
							{
								xielv2 = (z[k + 1] - zz) / (z[k + 1] - z_depart) * k_average[i][j][k] + (zz - z_depart) / (z[k + 1] - z_depart) * k_point[i][j][k + 1];
							}
							xielv = (xielv1 + xielv2) / 2;
						}

						Energy_fit = Energy_fit + xielv * (z[k + 1] - z[k]) / NINJIANGE;
					}
				}
				fEnergy_Fz_Nowork[i][j] = Energy_fit;
				fEnergy_Fz[i][j] = fEnergy_Fz_Nowork[i][j] - Fz * z_Fz[i][j];
			}

	}
	if (ifbeyond == 1)
		return 0;
	else
		return 1;
}
