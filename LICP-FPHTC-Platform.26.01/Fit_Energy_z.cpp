/* This program aims to fit A[i][j] and B[i][j] in the formula of E[i][j]=A[i][j]/z^6+B[i][j]/z^12.*/
/* This program aims to fit a_coe[20][20][RANK] in the multinomial*/
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

using namespace std;

int CInterface::Fit_Energy_z()
{

	int i, j, k, l, m, n, mm, nn;
	fstream logout;
	double fEnergy_temp[40];
	double xielv, xielv1, xielv2, zz, Energy_fit;
	double z_depart;
	int NN = NINJIANGE;
	double Delta_Energy;
	double yita;
	fstream outall1;

	logout.open("log.out", ios::out | ios::app);
	for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
			for (k = 0; k < iNofStep_z - 1; k++)
			{
				k_average[i][j][k] = (fEnergy[i][j][k + 1] - fEnergy[i][j][k]) / (z[k + 1] - z[k]);
			}
	for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
			for (k = 1; k < iNofStep_z - 1; k++)
			{
				k_point[i][j][k] = (k_average[i][j][k - 1] + k_average[i][j][k]) / 2.0;
				yita = fabs((k_average[i][j][k - 1] - (k_average[i][j][k - 1] + k_average[i][j][k]) / 2.0) / (k_average[i][j][k] - k_average[i][j][k - 1]));
				k_point_origin[i][j][k] = (1 - yita) * k_average[i][j][k - 1] + yita * k_average[i][j][k];
			}
	/*
	outall1.open("Fz_point", ios::out);
	outall1 << "    Interface distance z and Fz_point from (0, 0) t0 (5,5)" << '\n';
	for (k = 1; k < iNofStep_z - 1; k++)
	{

		outall1 << ' ' << z[k];
		for (i = 0; i < iNofStep_x + 1; i++)
			for (j = 0; j < iNofStep_y + 1; j++)
			{
				outall1 << ' ' << k_point[i][j][k];				
			}
		outall1 << '\n';
	}
	outall1.close();
	outall1.open("Fz_point_origin", ios::out);
	outall1 << "    Interface distance z and Fz_point from (0, 0) t0 (5,5)" << '\n';
	for (k = 1; k < iNofStep_z - 1; k++)
	{

		outall1 << ' ' << z[k];
		for (i = 0; i < iNofStep_x + 1; i++)
			for (j = 0; j < iNofStep_y + 1; j++)
			{
				outall1 << ' ' << k_point_origin[i][j][k];
			}
		outall1 << '\n';
	}
	outall1.close();
	*/

	for (m = 0; m < iNofStep_x + 1; m++)
		for (n = 0; n < iNofStep_y + 1; n++)
		{
			logout << '\n';
			logout << '(' << m << ',' << n << ')' << '\n';
			cout << '(' << m << ',' << n << ')' << '\n';
			logout << "    z    Energy    Energy_Fit   Delta_Energy" << '\n';
			cout << "    z    Energy    Energy_Fit   Delta_Energy" << '\n';
			Energy_fit = fEnergy[m][n][1];
			for (i = 1; i < iNofStep_z - 2; i++)
			{
				for (j = 0; j < NINJIANGE; j++)
				{
					zz = z[i] + double(j) / double(NINJIANGE) * (z[i + 1] - z[i]);
					z_depart = z[i] + fabs((k_average[m][n][i] - k_point[m][n][i + 1]) / (fabs(k_point[m][n][i + 1] - k_average[m][n][i]) + fabs(k_average[m][n][i] - k_point[m][n][i]))) * (z[i + 1] - z[i]);
					if (zz <= z_depart)
					{
						xielv1 = (zz - z[i]) / (z_depart - z[i]) * k_average[m][n][i] + (z_depart - zz) / (z_depart - z[i]) * k_point[m][n][i];
					}
					else
					{
						xielv1 = (z[i + 1] - zz) / (z[i + 1] - z_depart) * k_average[m][n][i] + (zz - z_depart) / (z[i + 1] - z_depart) * k_point[m][n][i + 1];
					}
					zz = z[i] + double(j + 1) / double(NINJIANGE) * (z[i + 1] - z[i]);
					if (zz <= z_depart)
					{
						xielv2 = (zz - z[i]) / (z_depart - z[i]) * k_average[m][n][i] + (z_depart - zz) / (z_depart - z[i]) * k_point[m][n][i];
					}
					else
					{
						xielv2 = (z[i + 1] - zz) / (z[i + 1] - z_depart) * k_average[m][n][i] + (zz - z_depart) / (z[i + 1] - z_depart) * k_point[m][n][i + 1];
					}
					xielv = (xielv1 + xielv2) / 2;
					Energy_fit = Energy_fit + xielv * (z[i + 1] - z[i]) / NINJIANGE;
				}
				Delta_Energy = fabs(Energy_fit - fEnergy[m][n][i + 1]);
				if (Delta_Energy < 0.0001)
					Delta_Energy = 0;
				logout << z[i + 1] << ' ' << fEnergy[m][n][i + 1] << ' ' << Energy_fit << "      " << Delta_Energy << '\n';
				cout << z[i + 1] << ' ' << fEnergy[m][n][i + 1] << ' ' << Energy_fit << "     " << Delta_Energy << '\n';
			}

		}


	for (i = 0; i < iNofStep_x + 1; i++)
		for (j = 0; j < iNofStep_y + 1; j++)
		{
			for (k = 0; k < iNofStep_z - 1; k++)
			{
				if (k_average[i][j][k] > fFz_Max[i][j])
				{
					fFz_Max[i][j] = k_average[i][j][k];
					z_Max[i][j] = z[k];
				}
				if (k_average[i][j][k] < fFz_Min[i][j])
				{
					fFz_Min[i][j] = k_average[i][j][k];
					z_Min[i][j] = z[k];
				}
			}
			if (fFz_Max[i][j] < fFz_Max_all)
			{
				z_Max_all = z_Max[i][j];
				fFz_Max_all = fFz_Max[i][j];
			}
			if (fFz_Min[i][j] > fFz_Min_all)
			{
				fFz_Min_all = fFz_Min[i][j];
				z_Min_all = z_Min[i][j];
			}


		}
	return 0;
}
