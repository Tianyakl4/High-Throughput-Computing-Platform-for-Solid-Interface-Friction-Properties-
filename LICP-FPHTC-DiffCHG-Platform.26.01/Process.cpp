#include <stdio.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include<io.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "CDiffCHG.h"
#include<limits>
using namespace std;


int CDiffCHG::Process()
{
int i, j, k, l, m, n;
	double fi;
	fstream outall, outall1, logout, outFz_DiffCHG, outFz_DiffCHG_Interface;
	string filename, temp;
	stringstream ss;
	logout.open("log.out", ios::out);
	logout << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
        logout << "    //                                                                                     //" << '\n';
        logout << "    //  Welcome to use LICP-FPHTC-DiffCHG.26.01, which was developed by Prof. Wenhao He    //" << '\n';
        logout << "    //  in Lanzhou Institute of Chemical Physics, Chinese Academy of Sciences.             //" << '\n';
        logout << "    //                                                                                     //" << '\n';
        logout << "    //  The Platform aims to automatically calculate the different CHG, which must be      //" << '\n';
        logout << "    //  executed in a folder where LICP-FPHTC.26.01 has been executed.                     //" << '\n';
        logout << "    //                                                                                     //" << '\n';
        logout << "    //  When using this platform, please cite the following references:                    //" << '\n';
        logout << "    //  1.Wenhao He, et al., High throughput computing method based on the first principle //" << '\n';
        logout << "    //    for the solid interface tribological properties, Tribology 42, 493(2022).        //" << '\n';
        logout << "    //  2.Yu Cao, et al., Potential negative friction coefficient predicted by             //" << '\n';
        logout << "    //    first-principles calculations: A possible consequence of inaccurate computational//" << '\n';
        logout << "    //    models, Phys. Rev. B 111, 054109 (2025).                                         //" << '\n';
        logout << "    //                                                                                     //" << '\n';
        logout << "    //  Please contact us (hewh@licp.ac.cn) if you have any questions.                     //" << '\n';
        logout << "    //                                                                                     //" << '\n';
        logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
        logout << '\n';
	logout.close();

	cout << '\n';
	cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    //  Welcome to use LICP-FPHTC-DiffCHG.26.01, which was developed by Prof. Wenhao He    //" << '\n';
        cout << "    //  in Lanzhou Institute of Chemical Physics, Chinese Academy of Sciences.             //" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    //  The Platform aims to automatically calculate the different CHG, which must be      //" << '\n';
        cout << "    //  executed in a folder where LICP-FPHTC.26.01 has been executed.                     //" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    //  When using this platform, please cite the following references:                    //" << '\n';
        cout << "    //  1.Wenhao He, et al., High throughput computing method based on the first principle //" << '\n';
        cout << "    //    for the solid interface tribological properties, Tribology 42, 493(2022).        //" << '\n';
        cout << "    //  2.Yu Cao, et al., Potential negative friction coefficient predicted by             //" << '\n';
        cout << "    //    first-principles calculations: A possible consequence of inaccurate computational//" << '\n';
        cout << "    //    models, Phys. Rev. B 111, 054109 (2025).                                         //" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    //  Please contact us (hewh@licp.ac.cn) if you have any questions.                     //" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
        cout << '\n';
	cout << "    Press any key to continue..." << '\n';
	cout << "    ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//system("pause");

	cout << "    If you want to create POSCAR files,please input 1." << '\n';
	cout << "    If you want to skip creating POSCAR files,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to create POSCAR files." << '\n';
		logout << '\n';
		logout.close();
	}

	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is creating POSCAR files.                                             //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is creating POSCAR files.                                             //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';

		CrePOS();

		logout << '\n' << '\n' << '\n';
		logout << "    The informations to creat POSCARs." << '\n';
		logout << "    iNofStep_x:  " << iNofStep_x << '\n'; //ceshi
		logout << "    iNofStep_y:  " << iNofStep_y << '\n'; //ceshi
		logout << "    iNofStep_z:  " << iNofStep_z << '\n'; //ceshi
		logout << "    fStep_x_real:" << fStep_x_real << '\n'; //ceshi
		logout << "    fStep_y_real:" << fStep_y_real << '\n'; //ceshi
		logout << "    fStep_z_real_down:" << fStep_z_real_down << '\n'; //ceshi
		logout << "    fStep_z_real_up:" << fStep_z_real_up << '\n'; //ceshi
		logout << "    The number of the created POSCAR files:" << iNofStep_x * iNofStep_y * iNofStep_z << '\n';

		cout << '\n' << '\n' << '\n';
		cout << "    The informations to creat POSCARs." << '\n';
		cout << "    iNofStep_x:  " << iNofStep_x << '\n'; //ceshi
		cout << "    iNofStep_y:  " << iNofStep_y << '\n'; //ceshi
		cout << "    iNofStep_z:  " << iNofStep_z << '\n'; //ceshi
		cout << "    fStep_x_real:" << fStep_x_real << '\n'; //ceshi
		cout << "    fStep_y_real:" << fStep_y_real << '\n'; //ceshi
		cout << "    fStep_z_real_down:" << fStep_z_real_down << '\n'; //ceshi
		cout << "    fStep_z_real_up:" << fStep_z_real_up << '\n'; //ceshi
		cout << "    The number of the created POSCAR files:" << iNofStep_x * iNofStep_y * iNofStep_z << '\n';

		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  Creating POSCARs has been done.                                                    //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  Creating POSCARs has been done.                                                    //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
	}
	logout.close();

	cout << "    If you want to call VASP,please input 1." << '\n';
	cout << "    If you want to skip calling VASP,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to call VASP." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is calling VASP to calculate the total energy of systems.             //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is calling VASP to calculate the total energy of systems.             //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(1);
		Submit();


		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  Please wait until the VASP calculation is finished and use the post processor to   //" << '\n';
		logout << "    //  process the data.                                                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  Please wait until the VASP calculation is finished and use the post processor to   //" << '\n';
		cout << "    //  process the data.                                                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
	}


	//*
	cout << "    If you want to output DiffCHG,please input 1." << '\n';
	cout << "    If you want to skip outputing DiffCHG,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output DiffCHG." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing DiffCHG.                                                 //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing DiffCHG.                                                 //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		logout.close();


		Read_file(1);
		Output_DiffCHG();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  All DiffCHG have been output.                                                      //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  All DiffCHG have been output.                                                     //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
		logout.close();

	}

	cout << "    If you want to output DiffCHG_z,please input 1." << '\n';
	cout << "    If you want to skip outputing DiffCHG_z,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output DiffCHG_z." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing DiffCHG_z.                                               //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing DiffCHG_z.                                               //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		logout.close();


		Read_file(1);
		//Output_DiffCHG_z_Interface();
		Output_DiffCHG_z();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  All DiffCHG_z have been output.                                                    //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  All DiffCHG_z have been output.                                                    //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//                //cout << "    ";
		//                                //cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//                                                //system("pause");
		logout.close();
	}

	//*
	cout << "    If you want to output the DCS with interface distance,please input 1." << '\n';
	cout << "    If you want to skip outputing the DCS with interface distance,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output the DCS with interface distance." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing the DCS with interface distance.                         //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing the DCS with interface distance.                         //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(2);
		Write_DCS_Dengju();
		//Write_DCS_Dengju_Interface();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The DCS with interface distance have been output.                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The DCS with interface distance have been output.                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
	}

	/*
	cout << "    If you want to calculate the DiffCHG with Fz,please input 1." << '\n';
	cout << "    If you want to skip calculating the DiffCHG with Fz,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to calculate the DiffCHG with Fz." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is calculating the DiffCHG with Fz.                                   //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is calculating the DiffCHG with Fz.                                   //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';

		Read_file(2);
		Fit_Energy_z();


		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    全部数据拟合完毕!" << '\n';
		logout << "    The minimum load and corresponding distance_interface (Compressive strain):  " << fFz_Min_all << " eV/angstrom, " << z_Min_all << " angstrom," << '\n';
		logout << "    The maximal load and corresponding distance_interface (Tensile strain):      " << fFz_Max_all << " eV/angstrom, " << z_Max_all << " angstrom," << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    全部数据拟合完毕!" << '\n';
		cout << "    The minimum load and corresponding distance_interface (Compressive strain):  " << fFz_Min_all << " eV/angstrom, " << z_Min_all << " angstrom," << '\n';
		cout << "    The maximal load and corresponding distance_interface (Tensile strain):      " << fFz_Max_all << " eV/angstrom, " << z_Max_all << " angstrom," << '\n';
		cout << '\n';

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The relationships between the DiffCHG and Fz have been fitted.                     //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The relationships between the DiffCHG and Fz have been fitted.                     //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
	}


	outFz_DiffCHG.open("Fz_DiffCHG", ios::out | ios::app);
	outFz_DiffCHG << "Fz(eV/angstrom)  ";
	for (i = 0; i < iNofStep_x; i++)
	{
		for (j = 0; j < iNofStep_y; j++)
			outFz_DiffCHG << '(' << i << ',' << j << ")  ";
	}
	outFz_DiffCHG << '\n';
	outFz_DiffCHG.close();

	outFz_DiffCHG_Interface.open("Fz_DiffCHG_Interface", ios::out | ios::app);
	outFz_DiffCHG_Interface << "Fz(eV/angstrom)  ";
	for (i = 0; i < iNofStep_x; i++)
	{
		for (j = 0; j < iNofStep_y; j++)
			outFz_DiffCHG_Interface << '(' << i << ',' << j << ")  ";
	}
	outFz_DiffCHG_Interface << '\n';
	outFz_DiffCHG_Interface.close();

	
	for (fi = fFz_Max_all; fi > fFz_Min_all; fi = fi - 0.02)
	{
		Fz = fi;
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		cout << '\n';
		cout << "    The load is:                                " << Fz << " eV/angstrom" << '\n';
		logout << "    The load is:                                " << Fz << " eV/angstrom" << '\n';
		logout.close();

		if (FzToEnergy(Fz) == 1 && FzToDiffCHG(Fz) == 1 && FzToDiffCHG_Interface(Fz) == 1)
		{
			logout.open("log.out", ios::out | ios::app);
			logout << "    The DiffCHG(e):" << '\n';
			outFz_DiffCHG.open("Fz_DiffCHG", ios::out | ios::app);
			outFz_DiffCHG << Fz << "   ";
			outFz_DiffCHG_Interface.open("Fz_DiffCHG_Interface", ios::out | ios::app);
			outFz_DiffCHG_Interface << Fz << "   ";
			for (i = 0; i < iNofStep_x; i++)
			{
				for (j = 0; j < iNofStep_y; j++)
				{
					logout << ' ' << fDiffCHG_Fz[i][j];
					outFz_DiffCHG << ' ' << fDiffCHG_Fz[i][j];
					outFz_DiffCHG_Interface << ' ' << fDiffCHG_Fz_Interface[i][j];
				}
				logout << '\n';

			}
			outFz_DiffCHG << '\n';
			outFz_DiffCHG.close();
			outFz_DiffCHG_Interface << '\n';
			outFz_DiffCHG_Interface.close();

			logout << "    The interface_distance(A):  " << '\n';
			for (i = 0; i <= iNofStep_x; i++)
			{
				for (j = 0; j <= iNofStep_y; j++)
					logout << ' ' << z_Fz[i][j];
				logout << '\n';
			}
			logout << '\n';
			logout.close();
			Write_DCS_Fz();
			Write_DCS_Fz_Interface();
			m++;
		}
		else
			continue;
	}
        //*/

	logout.open("log.out", ios::out | ios::app);
	logout << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    //  The program has been done. Thank you for using this program!                       //" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	logout << '\n';
	logout.close();

	cout << '\n';
	cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	cout << "    //                                                                                     //" << '\n';
	cout << "    //  The program has been done. Thank you for using this program!                       //" << '\n';
	cout << "    //                                                                                     //" << '\n';
	cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	cout << '\n';
	//cout << "    Press any key to continue..." << '\n';
	//cout << "    ";
	//cin.ignore(numeric_limits<streamsize>::max(),'\n');
	//system("pause");
	return 0;
}
