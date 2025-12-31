
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

int CInterface::Submit()
{
	int i, j, k;
	double k1, k2;
	char command[100];
	string temp;
	fstream outall;
	k1 = iNofStep_y * 1.0 / (iNofStep_x * 1.0);
	k2 = -1.0 * k1;
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
			//if(j<k1*i+0.1 && j<k2*i+iNofStep_y+0.1)
		{
			for (k = 0; k < iNofStep_z; k++)
			{
				outall.open("run.sh", ios::out);
				outall << "#!/bin/bash" << '\n';
				temp = "cd ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k);
				outall << temp << '\n';
				outall << "qsub rvasp.sh" << '\n';
				outall << "cd ../" << '\n';
				outall.close();
				system("chmod 777 run.sh");
				system("./run.sh");

				// cout <<temp<<'\n';
				//cin>>k;
			}
		}
	return 0;
}
