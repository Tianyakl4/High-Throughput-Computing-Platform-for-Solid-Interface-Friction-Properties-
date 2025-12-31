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
#define BOHR 0.5291772108

using namespace std;

int CInterface::Write_PES_Fz()
{
	int i, j, k, l, m, n;
	fstream outall1;
	string filename, temp;
	stringstream ss;
	double volume;

	volume = fDistance_x * fDistance_y * sin(theta_ab) * c;

	ss << Fz;
	temp = ss.str();
	ss.str("");
	ss.clear();
	filename = "CHG_Energy_Fz" + temp + ".vasp";
	outall1.open(filename, ios::out);
	outall1 << "This file is  PES (eV in VESTA) from LICP-FPHTC-Flatform, and take the CHG format." << '\n';
	outall1 << "1.0" << '\n';
	outall1 << fDistance_x;   outall1 << "  0  0" << '\n';
	outall1 << fDistance_y * cos(theta_ab) << " " << fDistance_y * sin(theta_ab) << " 0" << '\n';
	outall1 << "0  0  "; outall1 << c << '\n';
	outall1 << "He" << '\n';
	outall1 << "1 " << '\n';
	outall1 << "Direct " << '\n';
	outall1 << "0  0  0 " << '\n';
	outall1 << '\n';
	outall1 << iNofStep_x << "  " << iNofStep_y << "  " << "1 " << '\n';
	for (j = 0; j < iNofStep_y; j++)
	{
		for (i = 0; i < iNofStep_x; i++)
			outall1 << ' ' << setprecision(12) << fEnergy_Fz[i][j] * volume / pow(BOHR, 3);
		outall1 << '\n';
	}
	outall1.close();

	filename = "CHG_Energy_Fz_Nowork" + temp + ".vasp";
	outall1.open(filename, ios::out);
	outall1 << "This file is  PES (eV in VESTA) from LICP-FPHTC-Flatform, and take the CHG format." << '\n';
	outall1 << "1.0" << '\n';
	outall1 << a;   outall1 << "  0  0" << '\n';
	outall1 << b * cos(theta_ab) << " " << b * sin(theta_ab) << " 0" << '\n';
	outall1 << "0  0  "; outall1 << c << '\n';
	outall1 << "He" << '\n';
	outall1 << "1 " << '\n';
	outall1 << "Direct " << '\n';
	outall1 << "0  0  0 " << '\n';
	outall1 << '\n';
	outall1 << iNofStep_x << "  " << iNofStep_y << "  " << "1 " << '\n';
	for (j = 0; j < iNofStep_y; j++)
	{
		for (i = 0; i < iNofStep_x; i++)
			outall1 << ' ' << setprecision(12) << fEnergy_Fz_Nowork[i][j] * volume / pow(BOHR, 3);
		outall1 << '\n';
	}
	outall1.close();

	char command[100];
	temp = "mkdir PES_Fz";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHG_Energy_Fz* ./PES_Fz";
	strcpy(command, temp.c_str());
	system(command);

	/*
	   filename = "Energy_Fz" + temp;
	   outall1.open(filename, ios::out);
	   for (i = 0; i <= iNofStep_x; i++)
			{
				for (j = 0; j <=iNofStep_y; j++)
					outall1 << ' '<< setprecision(12) << fEnergy_Fz[i][j];
				outall1 << '\n';
			}
		outall1.close();

		filename = "CHG_z_Fz" + temp + ".vasp";
		outall1.open(filename, ios::out);
		outall1<<"This file is  z (A in VESTA) from LICP-FPHTC-Flatform, and take the CHG format."<<'\n';
		outall1<<"1.0"<<'\n';
		outall1<<a;   outall1<<"  0  0"<<'\n';
		outall1<<b*cos(theta_ab);outall1<<b*sin(theta_ab);  outall1<<"0  "<<'\n';
		outall1<<"0  0  ";outall1<<c<<'\n';
		outall1<<"He"<<'\n';
		outall1<<"1 "<<'\n';
		outall1<<"Direct "<<'\n';
		outall1<<"0  0  0 "<<'\n';
		outall1<<iNofStep_x<<"  "<<iNofStep_y<<"  "<<"1 "<<'\n';
		for (i = 0; i < iNofStep_x; i++)
			{
				for (j = 0; j < iNofStep_y; j++)
					outall1 << ' ' << setprecision(12)<< z_Fz[i][j]*volume/pow(BOHR,3);
				outall1 << '\n';
			}
		outall1.close();

		filename = "z_Fz" + temp;
		outall1.open(filename, ios::out);
		for (i = 0; i <= iNofStep_x; i++)
			{
				for (j = 0; j <= iNofStep_y; j++)
					outall1 << ' '<< setprecision(12) << z_Fz[i][j];
				outall1 << '\n';
			}
		outall1.close();
	//*/

}
