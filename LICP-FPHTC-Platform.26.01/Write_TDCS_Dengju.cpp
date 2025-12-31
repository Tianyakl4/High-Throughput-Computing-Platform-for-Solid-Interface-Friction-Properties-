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

int CInterface::Write_TDCS_Dengju()
{
	int i, j, k, l, m, n;
	fstream outall, outall1;
	string filename, temp;
	stringstream ss;
	double volume;
	volume = fDistance_x * fDistance_y * sin(theta_ab) * c;
	for (k = 0; k < iNofStep_z; k++)
	{
		ss << z[k];
		temp = ss.str();
		ss.str("");
		ss.clear();
		filename = "CHG_TDCS_Dengju" + temp + ".vasp";
		outall1.open(filename, ios::out);
		outall1 << "This file is  TDCS (e in VESTA) from LICP-FPHTC, and take the CHG format." << '\n';
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
			{
				outall1 << ' ' << setprecision(12) << fTDiffCHG_d[i][j][k] * volume / pow(BOHR, 3);
			}
			outall1 << '\n';
		}
		outall1.close();
	}

	char command[100];
	temp = "mkdir TDCS_Dengju";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHG_TDCS_Dengju* ./TDCS_Dengju";
	strcpy(command, temp.c_str());
	system(command);


	return 0;
}
