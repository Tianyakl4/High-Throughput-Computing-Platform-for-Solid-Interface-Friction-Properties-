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
#define BOHR 0.5291772108

using namespace std;

int CDiffCHG::Write_DCS_Dengju_Interface()
{
	int i, j, k, l, m, n;
	fstream outall, outall1;
	string filename, temp;
	stringstream ss;
	double volume;
	
	volume = a * b * sin(theta_ab) * c;
	for (k = 0; k < iNofStep_z; k++)
	{
		ss << z[k];
		temp = ss.str();
		ss.str("");
		ss.clear();
		filename = "CHG_DCS_Dengju" + temp + "_Interface.vasp";
		outall1.open(filename, ios::out);
		outall1 << "This file is  DCS (e in VESTA) from LICP-FPHTC, and take the CHG format." << '\n';
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
			{
				outall1 << ' ' << setprecision(12) << fDiffCHG_Sum_Interface[i][j][k] * volume / pow(BOHR, 3);				
			}
			outall1 << '\n';
		}
		outall1.close();
	}

	char command[100];
	temp = "mkdir DCS_Dengju_Interface";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHG_DCS_Dengju* ./DCS_Dengju_Interface";
	strcpy(command, temp.c_str());
	system(command);


	return 0;
}
