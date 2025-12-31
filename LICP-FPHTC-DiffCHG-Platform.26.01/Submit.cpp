
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

int CDiffCHG::Submit()
{
	int i, j, k;
	double k1, k2;
	char command[100];
	string temp;
	fstream outall;
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			for (k = 0; k < iNofStep_z; k++)
			{
				outall.open("run.sh", ios::out);
				outall << "#!/bin/bash" << '\n';
				temp = "cd ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/up";
				outall << temp << '\n';
				outall << "qsub rvasp.sh" << '\n';
				outall << "cd ../../" << '\n';
				temp = "cd ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/down";
				outall << temp << '\n';
				outall << "qsub rvasp.sh" << '\n';
				outall << "cd ../../" << '\n';

				outall.close();
				system("chmod 777 run.sh");
				system("./run.sh");

			}
		}
	return 0;
}
