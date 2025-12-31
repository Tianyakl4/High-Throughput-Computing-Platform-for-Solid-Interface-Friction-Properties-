#include <stdio.h>
#include <iostream>
#include<stdlib.h>
#include "CInterface.h"
using namespace std;

CInterface::CInterface()

{
	int i, j, k, l;
	iNofElement = 0;
	constant = a = b = c = theta_ab = 0.0;
	fArea_Interface = 0.0;
	ax = ay = az = bx = by = bz = cx = cy = cz = 0.0;

	iNofStep_x = iNofStep_y = 0;
	iNofStep_z = 0;
	iNofStep_z_Down = iNofStep_z_Up = 0;

	fStep_x_real = fStep_y_real = 0.0;
	fStep_z_real_down = fStep_z_real_up = 0;

	x_sandle_Fz = y_sandle_Fz = x_min_Fz = y_min_Fz = 0;
	Energy_min_Fz = 0.0;
	Energy_sandle_Fz = 10000000.0;
	Distance_min_sandle = 0.0;

	iNofGroup = 0;
	fFz_Min_all = -1000000.0;
	fFz_Max_all = 100000000.0;
	z_Max_all = 10.0;
	z_Min_all = 0.0;

	f_Fz = f_e_Fz = 0.0;

	z_initial = 0.0;

	i_start = j_start = i_stop = j_stop = 0;

	for (i = 0; i < 10; i++)
	{
		iNofAtom[i] = 0;
		atomname[i] = ' ';
	}
	for (i = 0; i < STEPX; i++)
		for (j = 0; j < STEPY; j++)
			for (k = 0; k < STEPZ; k++)
			{
				fEnergy[i][j][k] = 0.0;
				fFz[i][j][k] = 0.0;
				fCHG_Interface[i][j][k] = 0.0;
				fCHG_Interface_Center[i][j][k] = 0.0;
				fTDiffCHG_d[i][j][k] = 0.0;
				fTDiffCHG_Interface_d[i][j][k] = 0.0;
				fTDiffCHG_Interface_Relative_d[i][j][k] = 0.0;
				fTDiffCHG_zDirection[i][j][k] = 0.0;
				k_point[i][j][k] = k_point_origin[i][j][k] = k_average[i][j][k] = 0.0;
			}
	for (i = 0; i < STEPX; i++)
		for (j = 0; j < STEPY; j++)
		{
			fEnergy_Fz[i][j] = 0.0;
			fEnergy_Fz_Nowork[i][j] = 0.0;
			fCHG_Fz[i][j] = 0.0;
			z_Fz[i][j] = 0.0;
			A[i][j] = B[i][j] = 0.0;
			fFz_Max[i][j] = -1000000;
			fFz_Min[i][j] = 1000000;
			z_Max[i][j] = z_Min[i][j] = 0.0;
		}

	for (i = 0; i < STEPX; i++)
		for (j = 0; j < STEPY; j++)
			for (k = 0; k < RANK; k++)
			{
				a_coe[i][j][k] = 0.0;
			}
	for (k = 0; k < STEPZ; k++)
	{
		z[k] = 0.0;
	}
	for (i = 0; i < 8; i++)
	{
		iNinGroup[i] = 0;
	}
        fDistance_x = fDistance_y = fDistance_z = 0.0;
}
