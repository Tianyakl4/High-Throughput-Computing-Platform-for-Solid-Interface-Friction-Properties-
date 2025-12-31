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

int CInterface::Output_CHG()
{
	int i, j, k, l, m, n, ii;
	char command[100];
	string temp, temp1, temp2, temp3;
	double ftemp;
	double f1, f2, f3;
	int itemp;
	int iNX, iNY, iNZ;
	fstream inall, inall1, inall2, outall;
	stringstream  inputss, ss;

	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < iNofStep_z; k++)
			{
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/CHGCAR ./CHGCAR_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				strcpy(command, temp.c_str());
				system(command);
			}

	temp = "mkdir CHGAll";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv CHGCAR_* ./CHGAll";
	strcpy(command, temp.c_str());
	system(command);

	return 0;
}

