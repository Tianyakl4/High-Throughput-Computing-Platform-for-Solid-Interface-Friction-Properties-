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

int CDiffCHG::Read_file(int jj)
{
	int i, j, k, l, m, n;
	fstream inall, outall;
	stringstream  inputss, ss;
	string temp;
	fstream logout;

	if (jj == 2)
	{
		inall.open("temp.dat", ios::in);
		getline(inall, temp);
		inall >> iNofStep_x;	inall >> iNofStep_y;   inall >> iNofStep_z;
		inall >> a;	inall >> b; inall >> c;   inall >> theta_ab;
		inall >> fStep_x_real; inall >> fStep_y_real;
		inall >> fStep_z_real_down;
		inall >> fStep_z_real_up;

		i_start = 0;
		j_start = 0;
		i_stop = iNofStep_x;
		j_stop = iNofStep_y;

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    Nx:       " << iNofStep_x << '\n';
		logout << "    Ny:       " << iNofStep_y << '\n';
		logout << "    Nz:       " << iNofStep_z << '\n';
		logout << "    fStep_x_real:        " << setprecision(12) << fStep_x_real << " angstrom" << '\n';
		logout << "    fStep_y_real:        " << setprecision(12) << fStep_y_real << " angstrom" << '\n';
		logout << "    fStep_z_real_down:   " << setprecision(12) << fStep_z_real_down << " angstrom" << '\n';
		logout << "    fStep_z_real_up:     " << setprecision(12) << fStep_z_real_up << " angstrom" << '\n';
		logout << '\n';


		cout << '\n';
		cout << "    Nx:       " << iNofStep_x << '\n';
		cout << "    Ny:       " << iNofStep_y << '\n';
		cout << "    Nz:       " << iNofStep_z << '\n';
		cout << "    fStep_x_real:        " << setprecision(12) << fStep_x_real << " angstrom" << '\n';
		cout << "    fStep_y_real:        " << setprecision(12) << fStep_y_real << " angstrom" << '\n';
		cout << "    fStep_z_real_down:   " << setprecision(12) << fStep_z_real_down << " angstrom" << '\n';
		cout << "    fStep_z_real_up:     " << setprecision(12) << fStep_z_real_up << " angstrom" << '\n';
		cout << '\n';

		if (iNofStep_x == 0 || iNofStep_y == 0 || iNofStep_z == 0 || iNofStep_x > STEPX || iNofStep_y > STEPY || iNofStep_z > STEPZ)
		{
			cout << '\n';
			cout << "    The Nx, Ny or Nz contain illegal value. Please make sure 0<Nx<STEPY, 0<Ny<STEPY and 0<Nz<STEPZ.";
			cout << '\n';
			cout << "    ";
			logout << '\n';
			logout << "    The Nx, Ny or Nz contain illegal value. Please make sure 0<Nx<STEPY, 0<Ny<STEPY and 0<Nz<STEPZ.";
			logout << '\n';
			logout << "    ";

			system("pause");
			exit(0);
		}
		n = 0;
		logout << "    Distance_interface:   " << '\n';
		cout << "    Distance_interface:   " << '\n';
		for (k = 0; k < iNofStep_z; k++)
		{
			inall >> z[k];
			n++;
			cout << "      " << setprecision(12) << z[k] << ' ';
			logout << "      " << setprecision(12) << z[k] << ' ';
			if (n % 5 == 0)
			{
				cout << '\n';
				logout << '\n';
			}
		}

		inall.close();
		inall.open("DiffCHG_Sum.dat", ios::in);
		logout << "    DiffCHG_Sum(e):   " << '\n';
		cout << "    DiffCHG_Sum(e):   " << '\n';
		n = 0;
		for (k = 0; k < iNofStep_z; k++)
			for (i = 0; i < iNofStep_x; i++)
				for (j = 0; j < iNofStep_y; j++)				
				{
					inall >> fDiffCHG_Sum[i][j][k];
					n++;
					cout << "      " << setprecision(12) << fDiffCHG_Sum[i][j][k] << ' ';
					logout << "      " << setprecision(12) << fDiffCHG_Sum[i][j][k] << ' ';
					if (n % 5 == 0)
					{
						cout << '\n';
						logout << '\n';
					}
				}
		inall.close();
		inall.open("DiffCHG_Sum_Interface.dat", ios::in);
		logout << "    DiffCHG_Sum_Interface(e):   " << '\n';
		cout << "    DiffCHG_Sum_Interface(e):   " << '\n';
		n = 0;
		for (k = 0; k < iNofStep_z; k++)
			for (i = 0; i < iNofStep_x; i++)
				for (j = 0; j < iNofStep_y; j++)				
				{
					inall >> fDiffCHG_Sum_Interface[i][j][k];
					n++;
					cout << "      " << setprecision(12) << fDiffCHG_Sum_Interface[i][j][k] << ' ';
					logout << "      " << setprecision(12) << fDiffCHG_Sum_Interface[i][j][k] << ' ';
					if (n % 5 == 0)
					{
						cout << '\n';
						logout << '\n';
					}
				}
		inall.close();

		inall.open("temp1.dat", ios::in);
		logout << "    Energy(eV):   " << '\n';
		cout << "    Energy(eV):   " << '\n';
		n = 0;
		for (i = 0; i <= iNofStep_x; i++)
			for (j = 0; j <= iNofStep_y; j++)
				for (k = 0; k < iNofStep_z; k++)			
				{
					inall >> fEnergy[i][j][k];
					n++;
					cout << "      " << setprecision(12) << fEnergy[i][j][k] << ' ';
					logout << "      " << setprecision(12) << fEnergy[i][j][k] << ' ';
					if (n % 5 == 0)
					{
						cout << '\n';
						logout << '\n';
					}
				}
		inall.close();

		logout.close();
	}

	else
	{

		inall.open("temp.dat", ios::in);
		getline(inall, temp);
		inall >> iNofStep_x;	inall >> iNofStep_y;   inall >> iNofStep_z;
		inall >> a;	inall >> b;   inall >> c; inall >> theta_ab;
		inall >> fStep_x_real; inall >> fStep_y_real;
		inall >> fStep_z_real_down;
		inall >> fStep_z_real_up;

		i_start = 0;
		j_start = 0;
		i_stop = iNofStep_x;
		j_stop = iNofStep_y;

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    Nx:       " << iNofStep_x << '\n';
		logout << "    Ny:       " << iNofStep_y << '\n';
		logout << "    Nz:       " << iNofStep_z << '\n';
		logout << "    fStep_x_real:        " << setprecision(12) << fStep_x_real << " angstrom" << '\n';
		logout << "    fStep_y_real:        " << setprecision(12) << fStep_y_real << " angstrom" << '\n';
		logout << "    fStep_z_real_down:   " << setprecision(12) << fStep_z_real_down << " angstrom" << '\n';
		logout << "    fStep_z_real_up:     " << setprecision(12) << fStep_z_real_up << " angstrom" << '\n';
		logout << '\n';


		cout << '\n';
		cout << "    Nx:       " << iNofStep_x << '\n';
		cout << "    Ny:       " << iNofStep_y << '\n';
		cout << "    Nz:       " << iNofStep_z << '\n';
		cout << "    fStep_x_real:        " << setprecision(12) << fStep_x_real << " angstrom" << '\n';
		cout << "    fStep_y_real:        " << setprecision(12) << fStep_y_real << " angstrom" << '\n';
		cout << "    fStep_z_real_down:   " << setprecision(12) << fStep_z_real_down << " angstrom" << '\n';
		cout << "    fStep_z_real_up:     " << setprecision(12) << fStep_z_real_up << " angstrom" << '\n';
		cout << '\n';

		if (iNofStep_x == 0 || iNofStep_y == 0 || iNofStep_z == 0 || iNofStep_x > STEPX || iNofStep_y > STEPY || iNofStep_z > STEPZ)
		{
			cout << '\n';
			cout << "    The Nx, Ny or Nz contain illegal value. Please make sure 0<Nx<STEPY, 0<Ny<STEPY and 0<Nz<STEPZ.";
			cout << '\n';
			cout << "    ";
			logout << '\n';
			logout << "    The Nx, Ny or Nz contain illegal value. Please make sure 0<Nx<STEPY, 0<Ny<STEPY and 0<Nz<STEPZ.";
			logout << '\n';
			logout << "    ";

			system("pause");
			exit(0);
		}

		n = 0;
		logout << "    Distance_interface:   " << '\n';
		cout << "    Distance_interface:   " << '\n';
		for (k = 0; k < iNofStep_z; k++)
		{
			inall >> z[k];
			n++;
			cout << "      " << setprecision(12) << z[k] << ' ';
			logout << "      " << setprecision(12) << z[k] << ' ';
			if (n % 5 == 0)
			{
				cout << '\n';
				logout << '\n';
			}
		}
		inall.close();

		inall.open("temp1.dat", ios::in);
		logout << "    Energy(eV):   " << '\n';
		cout << "    Energy(eV):   " << '\n';
		n = 0;
		for (i = 0; i <= iNofStep_x; i++)
			for (j = 0; j <= iNofStep_y; j++)
				for (k = 0; k < iNofStep_z; k++)
				{
					inall >> fEnergy[i][j][k];
					n++;
					cout << "      " << setprecision(12) << fEnergy[i][j][k] << ' ';
					logout << "      " << setprecision(12) << fEnergy[i][j][k] << ' ';
					if (n % 5 == 0)
					{
						cout << '\n';
						logout << '\n';
					}
				}
		inall.close();
		logout.close();
	}

	return 1;
}
