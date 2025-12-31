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

int CInterface::Operate_file()
{
	int i, j, k;
	char command[100];
	double k1, k2;
	string temp;
	string sTemp1 = "1111";
	string sTemp2 = "1111";
	string line, name;
	fstream inall, outall;
	k1 = iNofStep_y * 1.0 / (iNofStep_x * 1.0);
	k2 = -1.0 * k1;
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			// if(j<k1*i+0.1&&j<k2*i+iNofStep_y+0.1)
		{
			for (k = 0; k < iNofStep_z; k++)
			{
				temp = "mkdir " + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				strcpy(command, temp.c_str());
				system(command);

				temp = "mv POSCAR_" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "  ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/POSCAR";
				strcpy(command, temp.c_str());
				system(command);

				inall.open("rvasp.sh", ios::in);
				inall >> sTemp2;
				while (!inall.eof())
				{
					sTemp1 = sTemp2;
					inall >> sTemp2;

					if (sTemp1 == "#PBS" && sTemp2 == "-N")
					{
						inall >> name;
						break;
					}
				}
				inall.close();

				inall.open("rvasp.sh", ios::in);
				outall.open("rvasp1.sh", ios::out);
				while (!inall.eof())
				{
					getline(inall, line);
					if (strstr(line.c_str(), "#PBS") && strstr(line.c_str(), "-N"))
						outall << "#PBS -N " << name << '_' << i << '_' << j << '_' << k << '\n';
					else
						outall << line << endl;
				}


				inall.close();
				outall.close();


				temp = "cp INCAR KPOINTS POTCAR ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				strcpy(command, temp.c_str());
				system(command);

				temp = "cp rvasp1.sh ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/rvasp.sh";
				strcpy(command, temp.c_str());
				system(command);


				// cout <<temp<<'\n';
				//cin>>k;
			}

		}

	//system("rm POSCAR_*");

	return 0;
}
