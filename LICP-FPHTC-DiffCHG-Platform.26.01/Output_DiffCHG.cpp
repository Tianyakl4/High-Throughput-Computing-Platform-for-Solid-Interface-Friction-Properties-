#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include<io.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "CDiffCHG.h"
using namespace std;

int CDiffCHG::Output_DiffCHG()
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
        cout << iNofStep_x << " "<< iNofStep_y << " "<< iNofStep_z << "\n";
	int iii, jjj, kkk;
        int ifStart = 1;
        cout << "Please input i, j, k. \n";
        cin >> iii  >> jjj >>kkk; 

         for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			for (k = 0; k < iNofStep_z; k++)
			{       
                                if(ifStart == 1)
                                {
                                    i = iii; j = jjj; k = kkk; ifStart = 0;
                                } 
                                cout << i << " "<< j << " "<< k << "\n";
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/CHGCAR ./CHGCAR";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/up/CHGCAR ./CHGCAR_up";
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/down/CHGCAR ./CHGCAR_down";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("CHGCAR", ios::in);
				inall1.open("CHGCAR_up", ios::in);
				inall2.open("CHGCAR_down", ios::in);
				temp = "DiffCHG_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				outall.open(temp, ios::out);

				outall << temp << '\n';
				getline(inall, temp);
				inall >> ftemp;
				outall << ftemp << '\n';
				inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << '\n';

				inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << '\n';

				inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << '\n';

				while (inall.get() != 10)
				{
					;
				}

				getline(inall, temp);
				outall << temp << '\n';

				inputss.str("");
				inputss.clear();
				inputss << temp;

				itemp = 0;
				while (inputss >> temp1)
				{
					itemp++;
				}

				ii = 0;
				for (m = 0; m < itemp; m++)
				{
					inall >> n;
					outall << n << ' ';
					ii = ii + n;
				}
				outall << '\n';

				inall >> temp;
				outall << temp << '\n';

				for (m = 0; m < ii; m++)
				{
					inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << ' '; inall >> ftemp; outall << ftemp << '\n';
				}
				outall << '\n';
				inall >> iNX; inall >> iNY; inall >> iNZ;
				outall << iNX << ' ' << iNY << ' ' << iNZ << '\n';
			//	cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';

				getline(inall1, temp);
				inall1 >> ftemp;
				inall1 >> ftemp; inall1 >> ftemp; inall1 >> ftemp;
				inall1 >> ftemp; inall1 >> ftemp; inall1 >> ftemp;
				inall1 >> ftemp; inall1 >> ftemp; inall1 >> ftemp;
				while (inall1.get() != 10)
				{
					;
				}

				getline(inall1, temp);

				inputss.str("");
				inputss.clear();
				inputss << temp;

				itemp = 0;
				while (inputss >> temp1)
				{
					itemp++;
				}

				ii = 0;
				for (m = 0; m < itemp; m++)
				{
					inall1 >> n;
					ii = ii + n;
				}
				inall1 >> temp;

				for (m = 0; m < ii; m++)
				{
					inall1 >> ftemp; inall1 >> ftemp; inall1 >> ftemp;
				}
				inall1 >> iNX; inall1 >> iNY; inall1 >> iNZ;
			//	cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';


				getline(inall2, temp);
				inall2 >> ftemp;
				inall2 >> ftemp; inall2 >> ftemp; inall2 >> ftemp;
				inall2 >> ftemp; inall2 >> ftemp; inall2 >> ftemp;
				inall2 >> ftemp; inall2 >> ftemp; inall2 >> ftemp;
				while (inall2.get() != 10)
				{
					;
				}

				getline(inall2, temp);

				inputss.str("");
				inputss.clear();
				inputss << temp;

				itemp = 0;
				while (inputss >> temp1)
				{
					itemp++;
				}

				ii = 0;
				for (m = 0; m < itemp; m++)
				{
					inall2 >> n;
					ii = ii + n;
				}
				inall2 >> temp;

				for (n = 0; n < ii; n++)
				{
					inall2 >> ftemp; inall2 >> ftemp; inall2 >> ftemp;
				}
				inall2 >> iNX; inall2 >> iNY; inall2 >> iNZ;
				// cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
				for (l = 0; l < iNX; l++)
					for (m = 0; m < iNY; m++)
						for (n = 0; n < iNZ; n++)
						{
							inall >> f1; inall1 >> f2; inall2 >> f3;
							ftemp = f1 - f2 - f3;
							outall << ftemp << setprecision(12) << ' ';
							if (((l * iNY + m) * iNZ + n + 1) % 5 == 0)
								outall << '\n';
						}

				inall.close();
				inall1.close();
				inall2.close();
				outall.close();
				//cin >> ii;
			}

	temp = "mkdir DiffCHGAll";
	strcpy(command, temp.c_str());
	system(command);
	temp = "mv DiffCHG_* ./DiffCHGAll";
	strcpy(command, temp.c_str());
	system(command);

	return 0;
}

