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

int CDiffCHG::FzToDiffCHG_Interface(double Fz)
{

	int i, j, k, l, m, n, ii;
	double z1, zz;
	double xielv, xielv1, xielv2, DiffCHG_fit;
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
				fDiffCHG_Fz_Interface[i][j] = 0.0;
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

				for (ii = 0; ii < iNofStep_z; ii++)
					if (z_Fz[i][j] > z[ii])
						k = ii;
				DiffCHG_fit = fDiffCHG_Sum_Interface[i][j][k];
				xielv = (fDiffCHG_Sum_Interface[i][j][k + 1] - fDiffCHG_Sum_Interface[i][j][k]) / (z[k + 1] - z[k]);
				DiffCHG_fit = DiffCHG_fit + xielv * (z_Fz[i][j] - z[k]);
				fDiffCHG_Fz_Interface[i][j] = DiffCHG_fit;
			}

	}
	if (ifbeyond == 1)
		return 0;
	else
		return 1;
}
