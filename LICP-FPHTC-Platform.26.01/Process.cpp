#include <stdio.h>
#include <iostream>
#include <fstream>
#include<sstream>
#include<io.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include "CInterface.h"
#include<limits>
using namespace std;


int CInterface::Process()
{
	int i, j, k, l, m, n;
	double fi, fj, fk;
	fstream outall, outall1, logout, d_Fz;
	fstream Fz_d, Fz_Energy_Ad, Fz_Energy_Work, Fz_Energy, Fz_CHG_InterfaceCenter;
	string filename, temp;
	stringstream ss;
	logout.open("log.out", ios::out);
	logout << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    //  Welcome to use LICP-FPHTC-Platform.26.01, which was developed by Prof. Wenhao He   //" << '\n';
	logout << "    //  in Lanzhou Institute of Chemical Physics, Chinese Academy of Sciences.             //" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    //  The Platform aims to automatically execute tribological calculations.              //" << '\n';
	logout << "    //  A file named in.dat should be provided to execute this program.                    //" << '\n';
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
        cout << "    //  Welcome to use LICP-FPHTC-Platform.26.01, which was developed by Prof. Wenhao He   //" << '\n';
        cout << "    //  in Lanzhou Institute of Chemical Physics, Chinese Academy of Sciences.             //" << '\n';
        cout << "    //                                                                                     //" << '\n';
        cout << "    //  The Platform aims to automatically execute tribological calculations.              //" << '\n';
        cout << "    //  A file named in.dat should be provided to execute this program.                    //" << '\n';
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

		logout.open("log.out", ios::out | ios::app);
		for (i = 0; i < iNofElement; i++)
		{
			logout << "    " << atomname[i] << ' ';
			cout << "    " << atomname[i] << ' ';
		}
		cout << '\n';
		logout << '\n';
		for (i = 0; i < iNofElement; i++)
		{
			cout << "    " << iNofAtom[i] << ' ';
			logout << "    " << iNofAtom[i] << ' ';
		}

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
		Operate_file();
		Submit();


		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  Please wait until the VASP calculation finish and use the post processor to        //" << '\n';
		logout << "    //  process the data.                                                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  Please wait until the VASP calculations finish and use the post processor to       //" << '\n';
		cout << "    //  process the data.                                                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
	}



	cout << "    If you want to search Energy from  OUTCAR in VASP,please input 1." << '\n';
	cout << "    If you want to skip searching Energy,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to search Energy from  OUTCAR in VASP." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is searching Energy.                                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is searching Energy.                                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		logout.close();


		Read_file(1);
		Search_Energy();
		Output_CHG();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		cout << "      Energy for i,j,k" << '\n';
		logout << "      Energy for i,j,k" << '\n';


		for (i = 0; i <= iNofStep_x; i++)
			for (j = 0; j <= iNofStep_y; j++)
			{
				for (k = 0; k < iNofStep_z; k++)
				{
					cout << "      " << fEnergy[i][j][k];
					logout << "      " << fEnergy[i][j][k];
					if ((k + 1) % 5 == 0)
					{
						cout << '\n';
						logout << '\n';
					}

				}
				cout << '\n';
				logout << '\n';
			}
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  All Energies have been input fEnergy[i][j][k].                                     //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  All Energies have been input fEnergy[i][j][k].                                     //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
		logout.close();

	}


	cout << "    If you want to output the PES with interface distance,please input 1." << '\n';
	cout << "    If you want to skip outputing the PES with interface distance,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output the PES with interface distance." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing the PES with interface distance.                         //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing the PES with interface distance.                         //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(2);
		Write_PES_Dengju();
		Fit_Energy_z();
		outall.open("d_Friciton", ios::out);
		outall << " The interface distance: angstrom, The delta_potential: eV, The friction force: eV/angstrom, The friction coefficient" << '\n';

		d_Fz.open("d_Fz", ios::out);
		d_Fz << "Interface (A)  Fz (eV/A) (from 00 to ij)" << '\n';
		for (m = 0; m < iNofStep_z; m++)
		{
			logout.open("log.out", ios::out | ios::app);
			logout << '\n';
			cout << '\n';
			cout << "    The interface distance is:                                " << z[m] << " angstrom" << '\n';
			logout << "    The interface distance is:                                " << z[m] << " angstrom" << '\n';
			logout.close();

			Find_Path_z(m);

			logout.open("log.out", ios::out | ios::app);
			f_Fz = fabs(Energy_sandle_Fz - Energy_min_Fz) / Distance_min_sandle;   // eV/A
			f_e_Fz = fabs(f_Fz / Fz);
			logout << "    The corresponding delta_potential is:        " << fabs(Energy_sandle_Fz - Energy_min_Fz) << " eV" << '\n';
			logout << "    The corresponding friction force is:        " << f_Fz << " eV/angstrom" << '\n';
			logout << "    The corresponding friction coefficient is:  " << f_e_Fz << '\n';
			cout << "    The corresponding delta_potential is:        " << fabs(Energy_sandle_Fz - Energy_min_Fz) << " eV" << '\n';
			cout << "    The corresponding friction force is:        " << f_Fz << " eV/angstrom" << '\n';
			cout << "    The corresponding friction coefficient is:  " << f_e_Fz << '\n';
			cout << '\n';
			outall << z[m] << "  " << fabs(Energy_sandle_Fz - Energy_min_Fz) << "  " << f_Fz << "   " << f_e_Fz << '\n';
			logout << "    The Energies(eV):" << '\n';
			cout << "    The Energies(eV):" << '\n';

			for (j = 0; j <= iNofStep_y; j++)			
			{
				for (i = 0; i <= iNofStep_x; i++)
				{
					logout << ' ' << fEnergy_Fz[i][j];
					cout << ' ' << fEnergy_Fz[i][j];
				}
				logout << '\n';
				cout << '\n';
			}
			logout << "    The load(eV/angstrom):" << '\n';
			cout << "    The load(eV/angstrom):" << '\n';
			d_Fz << " " << z[m];
			for (j = 0; j <= iNofStep_y; j++)
			{
				for (i = 0; i <= iNofStep_x; i++)
				{
					logout << ' ' << k_point_origin[i][j][m];
					cout << ' ' << k_point_origin[i][j][m];
				}
				logout << '\n';
				cout << '\n';
			}
			for (i = 0; i <= iNofStep_x; i++)
				for (j = 0; j <= iNofStep_y; j++)
				{
					d_Fz << " " << k_point_origin[i][j][m];
				}
			logout << '\n';
			cout << '\n';
			d_Fz << '\n';
			logout.close();
		}
		outall.close();
		d_Fz.close();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The PES with interface distance have been output.                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The PES with interface distance have been output.                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
	}

	cout << "    If you want to output the CHG and CHG-InterfaceCenter with interface distance,please input 1." << '\n';
	cout << "    If you want to skip outputing the CHG and CHG-InterfaceCenter with interface distance,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output the CHG and CHG-InterfaceCenter with interface distance." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing the CHG and CHG-InterfaceCenter with interface distance. //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing the CHG and CHG-InterfaceCenter with interface distance. //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(2);
		Output_CHG_z();
		Write_CS_Dengju();
		Write_CS_Dengju_Interface_Center();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The CHG and CHG-InterfaceCenter with interface distance have been output.          //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The CHG and CHG-InterfaceCenter with interface distance have been output.          //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
	}


	cout << "    If you want to output the Transverse_DiffCHG,please input 1." << '\n';
	cout << "    If you want to skip outputing the Transverse_DiffCHG,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output the Transverse_DiffCHG." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing the Transverse_DiffCHG.                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing the Transverse_DiffCHG.                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(2);
		Output_Transverse_DiffCHG();
		Write_TDCS_Dengju();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The Transverse_DiffCHG have been output.                                           //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The Transverse_DiffCHG have been output.                                           //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
	}
        /*
	cout << "    If you want to output the Near_Transverse_DiffCHG,please input 1." << '\n';
	cout << "    If you want to skip outputing the Near_Transverse_DiffCHG,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to output the Near_Transverse_DiffCHG." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is outputing the Near_Transverse_DiffCHG.                                  //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is outputing the Near_Transverse_DiffCHG.                                  //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		Read_file(2);
		Output_Near_Transverse_DiffCHG();

		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  The Near_Transverse_DiffCHG have been output.                                           //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The Transverse_DiffCHG have been output.                                           //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
	}

        */




	cout << "    If you want to fit the relationships between Energy and z,please input 1." << '\n';
	cout << "    If you want to skip fitting the relationships between Energy and z,please input 2." << '\n';
	cin >> i;
	if (i == 2)
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    You donot select to fit the relationships between Energy and z." << '\n';
		logout << '\n';
		logout.close();
	}
	else
	{
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    //  This program is fitting the relationships between Energy and z.                    //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();
		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  This program is fitting the relationships between Energy and z.                    //" << '\n';
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
		logout << "    //  The relationships between Energy and z have been fitted.                           //" << '\n';
		logout << "    //                                                                                     //" << '\n';
		logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		logout << '\n';
		logout.close();

		cout << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    //  The relationships between Energy and z have been fitted.                           //" << '\n';
		cout << "    //                                                                                     //" << '\n';
		cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
		cout << '\n';
		//cout << "    Press any key to continue..." << '\n';
		//cout << "    ";
		//cin.ignore(numeric_limits<streamsize>::max(),'\n');
		//system("pause");
	}


	logout.open("log.out", ios::out | ios::app);
	logout << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    //  This program is canculating the energy under special load.                         //" << '\n';
	logout << "    //                                                                                     //" << '\n';
	logout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	logout << '\n';
	logout.close();
	cout << '\n';
	cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	cout << "    //                                                                                     //" << '\n';
	cout << "    //  This program is canculating the energy under special load.                         //" << '\n';
	cout << "    //                                                                                     //" << '\n';
	cout << "    /////////////////////////////////////////////////////////////////////////////////////////" << '\n';
	cout << '\n';


	Fz_d.open("Fz_d", ios::out);
	Fz_d << "Fz (eV/A)  Interface distance (A) (from 00 to ij)" << '\n';
	Fz_Energy_Ad.open("Fz_Energy_Ad", ios::out);
	Fz_Energy_Ad << "Fz (eV/A)  Energy_Ad (eV) (from 00 to ij)" << '\n';
	Fz_Energy_Work.open("Fz_Energy_Work", ios::out);
	Fz_Energy_Work << "Fz (eV/A)  Energy_Work (eV) (from 00 to ij)" << '\n';
	Fz_Energy.open("Fz_Energy", ios::out);
	Fz_Energy << "Fz (eV/A)  Energy_All (eV) (from 00 to ij)" << '\n';
	Fz_CHG_InterfaceCenter.open("Fz_CHG_InterfaceCenter", ios::out);
	Fz_CHG_InterfaceCenter << "Fz (eV/A)  CHG_InterfaceCenter (e) (from 00 to ij) and average" << '\n';
	double fAve_CS_Fz;
	m = 0;
	for (fi = fFz_Max_all; fi > fFz_Min_all; fi = fi - 0.02)
	{
		Fz = fi;
		logout.open("log.out", ios::out | ios::app);
		logout << '\n';
		cout << '\n';
		cout << "    The load is:                                " << Fz << " eV/angstrom" << '\n';
		logout << "    The load is:                                " << Fz << " eV/angstrom" << '\n';
		logout.close();
		if (FzToEnergy(Fz) == 1 && FzToCHG(Fz) == 1)
		{
			Fz_Energy_Ad << ' ' << Fz;
			Fz_Energy_Work << ' ' << Fz;
			Fz_Energy << ' ' << Fz;
			Fz_d << ' ' << Fz;
			Fz_CHG_InterfaceCenter << ' ' << Fz;
			logout.open("log.out", ios::out | ios::app);
			logout << "    The Energies(eV):" << '\n';
			for (j = 0; j <= iNofStep_y; j++)
			{
				for (i = 0; i <= iNofStep_x; i++)
				{
					logout << ' ' << fEnergy_Fz[i][j];
				}

				logout << '\n';
			}
			for (i = 0; i <= iNofStep_x; i++)
				for (j = 0; j <= iNofStep_y; j++)
				{
					Fz_Energy_Ad << ' ' << fEnergy_Fz_Nowork[i][j];
					Fz_Energy_Work << ' ' << -Fz * z_Fz[i][j];
					Fz_Energy << ' ' << fEnergy_Fz[i][j];
					Fz_d << ' ' << z_Fz[i][j];
				}
			Fz_Energy_Ad << '\n';
			Fz_Energy_Work << '\n';
			Fz_Energy << '\n';
			Fz_d << '\n';

			logout << "    The interface_distance(A):  " << '\n';
			for (j = 0; j <= iNofStep_y; j++)
			{
				for (i = 0; i <= iNofStep_x; i++)
				{
					logout << ' ' << z_Fz[i][j];					
				}
				logout << '\n';
			}			
			logout << '\n';
			logout << "    The CHG(e):" << '\n';
			fAve_CS_Fz = 0;
			for (j = 0; j <= iNofStep_y; j++)
			{
				for (i = 0; i <= iNofStep_x; i++)
				{
					logout << ' ' <<fCHG_Fz[i][j];
				}
				logout << '\n';
			}

			for (i = 0; i < iNofStep_x; i++)
				for (j = 0; j < iNofStep_y; j++)
				{
					Fz_CHG_InterfaceCenter << ' ' <<fCHG_Fz[i][j];
					fAve_CS_Fz = fAve_CS_Fz +fCHG_Fz[i][j];
				}
			Fz_CHG_InterfaceCenter  << ' ' << fAve_CS_Fz / double(iNofStep_x * iNofStep_y) << '\n';
			Write_PES_Fz();
			Write_ZS_Fz();
			Write_CS_Fz();
		}
		else
			continue;
	}
	Fz_d.close();
	Fz_Energy_Ad.close();
	Fz_Energy_Work.close();
	Fz_Energy.close();
	Fz_CHG_InterfaceCenter.close();
	cout << '\n';

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
	return 0;
}
