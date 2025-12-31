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
#define NX 84
#define NY 84
#define NZ 640
using namespace std;
int CInterface::Output_Near_Transverse_DiffCHG()
{
	int i, j, k, l, m, n, ii, iii, jjj, kkk;
	int i_MinEnergy, j_MinEnergy;
	char command[100];
	string temp, temp1, temp2, temp3;
	double ftemp;
	float fCHGCAR_initial[NX][NY][NZ], fCHGCAR_temp[NX][NY][NZ], fCHGCAR_finial[NX][NY][NZ];
	double f1, f2, f3;
	int itemp;
	int iNX, iNY, iNZ;
	double a_move_direct_distance, b_move_direct_distance, c_move_direct_site, c_move_direct_Maxsite;
	double fTDiffCHG_z_abs, fTDiffCHG_abs;
	fstream inall, inall1, inall2, outall, outall1, outall2, outall_TDiffCHG_d;
	stringstream  inputss, ss;
	for (l = 0; l < NX; l++)
		for (m = 0; m < NY; m++)
			for (n = 0; n < NZ; n++)
			{
				fCHGCAR_initial[l][m][n] = 0;
				fCHGCAR_temp[l][m][n] = 0;
				fCHGCAR_finial[l][m][n] = 0;
			}

	int iNofAtoms, iNofPoint;
	double fz;
	double fInterface_Site_Min, fInterface_Site_Max;
	double volume;
	cout << '\n' << "    " << "The in.dat will be required here!" << '\n';
	int iNofLayer = 0;
	int iIfCompress = 0;
	double FSITEOFFACE[100];//jiemian weizhi dayu cizhi de yuanzi bei yidong, Direct zuobiao de zhi
	double fSiteofFace_Move;

	inall1.open("in.dat", ios::in);
	inall1 >> iNofLayer;
	inall1 >> iIfCompress;
	for (i = 0; i < iNofLayer - 1; i++)
		inall1 >> FSITEOFFACE[i];
	inall1 >> fSiteofFace_Move;
	inall1.close();

	cout << "    " << "The POSCAR will be required here!" << '\n';
	int iOrder_Max, iOrder_Min;
	fInterface_Site_Max = 1;
	fInterface_Site_Min = 0;
	inall.open("POSCAR", ios::in);
	getline(inall, temp);
	inall >> ftemp;
	inall >> ftemp; inall >> ftemp; inall >> ftemp;
	inall >> ftemp; inall >> ftemp; inall >> ftemp;
	inall >> ftemp; inall >> ftemp; inall >> ftemp;
	while (inall.get() != 10)
	{
		;
	}

	getline(inall, temp);
	inputss.str("");
	inputss.clear();
	inputss << temp;
	iii = 0;
	while (inputss >> atomname[iii])
	{
		iii++;
	}
	iNofElement = iii;
	iNofAtoms = 0;
	for (iii = 0; iii < iNofElement; iii++)
	{
		inall >> iNofAtom[iii];
		iNofAtoms = iNofAtoms + iNofAtom[iii];
	}

	while (inall.get() != 10)
	{
		;
	}
	getline(inall, temp);
	inputss.str("");
	inputss.clear();
	inputss << temp;
	inputss >> temp;
	fInterface_Site_Max = 1;
	fInterface_Site_Min = 0;
	if (temp == "Selective" || temp == "selective")
	{
		getline(inall, temp);  //Selective dynamics or not
		inputss.str("");
		inputss.clear();
		inputss << temp;
		inputss >> temp;
		if (temp == "Direct" || temp == "direct")
		{
			for (iii = 0; iii < iNofAtoms; iii++)
			{
				inall >> ftemp;	inall >> ftemp;	inall >> fz; inall >> temp;	inall >> temp; inall >> temp;
				if (fz < fInterface_Site_Max && fz > fSiteofFace_Move)
				{
					fInterface_Site_Max = fz;
					iOrder_Max = iii + 1;
				}
				if (fz > fInterface_Site_Min && fz < fSiteofFace_Move)
				{
					fInterface_Site_Min = fz;
					iOrder_Min = iii + 1;
				}

			}
		}
	}
	else if (temp == "Direct" || temp == "direct")
	{
		for (iii = 0; iii < iNofAtoms; iii++)
		{
			inall >> ftemp; inall >> ftemp; inall >> fz;
			if (fz < fInterface_Site_Max && fz > fSiteofFace_Move)
			{
				fInterface_Site_Max = fz;
				iOrder_Max = iii + 1;
			}
			if (fz > fInterface_Site_Min && fz < fSiteofFace_Move)
			{
				fInterface_Site_Min = fz;
				iOrder_Min = iii + 1;
			}
		}
	}
	inall.close();
	cout << "iOrder_Min:  " << iOrder_Min << '\n';
	cout << "iOrder_Max:  " << iOrder_Max << '\n';

	/*
	cout << "Please enter i and j with the minimum energy position to calculate the lateral differential charge density: " << '\n';
	cin >> i_MinEnergy >> j_MinEnergy;
	cout << '\n';
	*/
	cout << "Please enter the maximum allowed z-position for movement c_move_direct_Maxsite: " << '\n';
	cin >> c_move_direct_Maxsite;
	cout << '\n';

	outall.open("d_Near_TDiffCHG_DeltaEnergy", ios::out);
	outall << "Interface-Distance(A)  ";
	for (i = 0; i < iNofStep_x; i++)
		for (j = 0; j < iNofStep_y; j++)
		{
			if (i + 1 >= iNofStep_x && j + 1 >= iNofStep_y)
				continue;
			if (i + 1 >= iNofStep_x && j + 1 < iNofStep_y)
			{
				outall << i << j << "-" << i << j + 1 << " ";
				outall << i << j << "-" << i << j + 1 << " ";
			}
			if (i + 1 < iNofStep_x && j + 1 >= iNofStep_y)
			{
				outall << i << j << "-" << i + 1 << j << " ";
				outall << i << j << "-" << i + 1 << j << " ";
			}
			if (i + 1 < iNofStep_x && j + 1 < iNofStep_y)
			{
				outall << i << j << "-" << i << j + 1 << " ";
				outall << i << j << "-" << i << j + 1 << " ";
				outall << i << j << "-" << i + 1 << j << " ";
				outall << i << j << "-" << i + 1 << j << " ";
			}
		}
	outall << '\n';

	for (k = 0; k < iNofStep_z; k++)
	{
		outall << z[k] << ' ';
		for (i = 0; i < iNofStep_x; i++)
			for (j = 0; j < iNofStep_y; j++)
			{
				fTDiffCHG_d[i][j][k] = 0;
				fTDiffCHG_Interface_d[i][j][k] = 0.0;
				fTDiffCHG_Interface_Relative_d[i][j][k] = 0.0;
				cout << "(i, j, k):  " << i << ", " << j << ", " << k << '\n';
				temp = "cp ./" + to_string(i) + '_' + to_string(j) + '_' + to_string(k) + "/CONTCAR ./CONTCAR";
				strcpy(command, temp.c_str());
				system(command);
				inall.open("CONTCAR", ios::in);
				getline(inall, temp);
				inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				inall >> ftemp; inall >> ftemp; inall >> ftemp;
				while (inall.get() != 10)
				{
					;
				}
				getline(inall, temp);
				inputss.str("");
				inputss.clear();
				inputss << temp;
				iii = 0;
				while (inputss >> atomname[iii])
				{
					iii++;
				}
				iNofElement = iii;
				iNofAtoms = 0;
				for (iii = 0; iii < iNofElement; iii++)
				{
					inall >> iNofAtom[iii];
					iNofAtoms = iNofAtoms + iNofAtom[iii];
				}
				while (inall.get() != 10)
				{
					;
				}
				getline(inall, temp);  //Selective dynamics or not
				inputss.str("");
				inputss.clear();
				inputss << temp;
				inputss >> temp;
				if (temp == "Selective" || temp == "selective")
				{
					getline(inall, temp);  //Selective dynamics or not
					inputss.str("");
					inputss.clear();
					inputss << temp;
					inputss >> temp;
					if (temp == "Direct" || temp == "direct")

					{
						for (iii = 0; iii < iNofAtoms; iii++)
						{
							inall >> ftemp; inall >> ftemp; inall >> fz;
							inall >> temp; inall >> temp; inall >> temp;
							if (iii == iOrder_Max - 1)
								fInterface_Site_Max = fz;
							if (iii == iOrder_Min - 1)
								fInterface_Site_Min = fz;
						}
					}
				}
				else if (temp == "Direct" || temp == "direct")
				{
					for (iii = 0; iii < iNofAtoms; iii++)
					{
						inall >> ftemp; inall >> ftemp; inall >> fz;
						if (iii == iOrder_Max - 1)
							fInterface_Site_Max = fz;
						if (iii == iOrder_Min - 1)
							fInterface_Site_Min = fz;
					}
				}
				inall.close();
				cout << "fInterface_Site_Min: " << fInterface_Site_Min << '\n';
				cout << "fInterface_Site_Max: " << fInterface_Site_Max << '\n';

				temp = "cp ./" + to_string(i) + "_" + to_string(j) + "_" + to_string(k) + "/CHGCAR ./CHGCAR_initial";
				strcpy(command, temp.c_str());
				system(command);
				if (i + 1 >= iNofStep_x && j + 1 >= iNofStep_y)
					continue;
				if (i + 1 >= iNofStep_x && j + 1 < iNofStep_y)
				{
					temp = "cp ./" + to_string(i) + "_" + to_string(j + 1) + "_" + to_string(k) + "/CHGCAR ./CHGCAR_finial";
					strcpy(command, temp.c_str());
					system(command);
					inall.open("CHGCAR_initial", ios::in);
					inall1.open("CHGCAR_finial", ios::in);
					getline(inall, temp);
					inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;

					while (inall.get() != 10)
					{
						;
					}

					getline(inall, temp);

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
						ii = ii + n;
					}
					inall >> temp;

					for (m = 0; m < ii; m++)
					{
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					}
					inall >> iNX; inall >> iNY; inall >> iNZ;
					cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';

					if (NX < iNX || NY < iNY || NZ < iNZ)
					{
						cout << "NX <= iNX || NY <= iNY || NZ <= iNZ, please increase NX, NY, and NZ in the source program!\n";
						cin >> ftemp;
					}

					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								inall >> fCHGCAR_initial[l][m][n];
							}

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
					cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								inall1 >> fCHGCAR_finial[l][m][n];
							}
					inall.close();
					inall1.close();

					a_move_direct_distance = double(0) / double(iNofStep_x);
					b_move_direct_distance = double(1) / double(iNofStep_y);
					c_move_direct_site = (fInterface_Site_Max + fInterface_Site_Min) / 2.0;

					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								if (n < iNZ * c_move_direct_site || n > iNZ * c_move_direct_Maxsite)
								{
									fCHGCAR_temp[l][m][n] = fCHGCAR_initial[l][m][n];
								}
								else
								{
									iii = l - round(iNX * a_move_direct_distance);
									jjj = m - round(iNY * b_move_direct_distance);
									kkk = n;
									if (iii < 0)
										iii = iii + iNX;
									else if (iii >= iNX)
										iii = iii - iNX;
									if (jjj < 0)
										jjj = jjj + iNY;
									else if (jjj >= iNY)
										jjj = jjj - iNY;
									fCHGCAR_temp[l][m][n] = fCHGCAR_initial[iii][jjj][kkk];
								}
								//cout << fCHGCAR_temp[l][m][n] << '\n';
							}
					fTDiffCHG_abs = 0;
					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								ftemp = fCHGCAR_finial[l][m][n] - fCHGCAR_temp[l][m][n];
								fTDiffCHG_abs = fTDiffCHG_abs + fabs(ftemp);
							}
					fTDiffCHG_abs = fTDiffCHG_abs / double(iNX * iNY * iNZ);
					outall << "  " << fTDiffCHG_abs << "  " << fEnergy[i][j + 1][k] - fEnergy[i][j][k];
				}
				if (i + 1 < iNofStep_x && j + 1 >= iNofStep_y)
				{
					temp = "cp ./" + to_string(i + 1) + "_" + to_string(j) + "_" + to_string(k) + "/CHGCAR ./CHGCAR_finial";
					strcpy(command, temp.c_str());
					system(command);
					inall.open("CHGCAR_initial", ios::in);
					inall1.open("CHGCAR_finial", ios::in);
					getline(inall, temp);
					inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					inall >> ftemp;  inall >> ftemp;  inall >> ftemp;

					while (inall.get() != 10)
					{
						;
					}

					getline(inall, temp);

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
						ii = ii + n;
					}
					inall >> temp;

					for (m = 0; m < ii; m++)
					{
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
					}
					inall >> iNX; inall >> iNY; inall >> iNZ;
					cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';

					if (NX < iNX || NY < iNY || NZ < iNZ)
					{
						cout << "NX <= iNX || NY <= iNY || NZ <= iNZ, please increase NX, NY, and NZ in the source program!\n";
						cin >> ftemp;
					}

					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								inall >> fCHGCAR_initial[l][m][n];
							}

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
					cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								inall1 >> fCHGCAR_finial[l][m][n];
							}
					inall.close();
					inall1.close();

					a_move_direct_distance = double(1) / double(iNofStep_x);
					b_move_direct_distance = double(0) / double(iNofStep_y);
					c_move_direct_site = (fInterface_Site_Max + fInterface_Site_Min) / 2.0;

					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								if (n < iNZ * c_move_direct_site || n > iNZ * c_move_direct_Maxsite)
								{
									fCHGCAR_temp[l][m][n] = fCHGCAR_initial[l][m][n];
								}
								else
								{
									iii = l - round(iNX * a_move_direct_distance);
									jjj = m - round(iNY * b_move_direct_distance);
									kkk = n;
									if (iii < 0)
										iii = iii + iNX;
									else if (iii >= iNX)
										iii = iii - iNX;
									if (jjj < 0)
										jjj = jjj + iNY;
									else if (jjj >= iNY)
										jjj = jjj - iNY;
									fCHGCAR_temp[l][m][n] = fCHGCAR_initial[iii][jjj][kkk];
								}
								//cout << fCHGCAR_temp[l][m][n] << '\n';
							}
					fTDiffCHG_abs = 0;
					for (n = 0; n < iNZ; n++)
						for (m = 0; m < iNY; m++)
							for (l = 0; l < iNX; l++)
							{
								ftemp = fCHGCAR_finial[l][m][n] - fCHGCAR_temp[l][m][n];
								fTDiffCHG_abs = fTDiffCHG_abs + fabs(ftemp);
							}
					fTDiffCHG_abs = fTDiffCHG_abs / double(iNX * iNY * iNZ);
					outall << "  " << fTDiffCHG_abs << "  " << fEnergy[i + 1][j][k] - fEnergy[i][j][k];
				}
				if (i + 1 < iNofStep_x && j + 1 < iNofStep_y)
				{
					{
						temp = "cp ./" + to_string(i) + "_" + to_string(j + 1) + "_" + to_string(k) + "/CHGCAR ./CHGCAR_finial";
						strcpy(command, temp.c_str());
						system(command);
						inall.open("CHGCAR_initial", ios::in);
						inall1.open("CHGCAR_finial", ios::in);
						getline(inall, temp);
						inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;

						while (inall.get() != 10)
						{
							;
						}

						getline(inall, temp);

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
							ii = ii + n;
						}
						inall >> temp;

						for (m = 0; m < ii; m++)
						{
							inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						}
						inall >> iNX; inall >> iNY; inall >> iNZ;
						cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';

						if (NX < iNX || NY < iNY || NZ < iNZ)
						{
							cout << "NX <= iNX || NY <= iNY || NZ <= iNZ, please increase NX, NY, and NZ in the source program!\n";
							cin >> ftemp;
						}

						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									inall >> fCHGCAR_initial[l][m][n];
								}

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
						cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									inall1 >> fCHGCAR_finial[l][m][n];
								}
						inall.close();
						inall1.close();

						a_move_direct_distance = double(0) / double(iNofStep_x);
						b_move_direct_distance = double(1) / double(iNofStep_y);
						c_move_direct_site = (fInterface_Site_Max + fInterface_Site_Min) / 2.0;

						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									if (n < iNZ * c_move_direct_site || n > iNZ * c_move_direct_Maxsite)
									{
										fCHGCAR_temp[l][m][n] = fCHGCAR_initial[l][m][n];
									}
									else
									{
										iii = l - round(iNX * a_move_direct_distance);
										jjj = m - round(iNY * b_move_direct_distance);
										kkk = n;
										if (iii < 0)
											iii = iii + iNX;
										else if (iii >= iNX)
											iii = iii - iNX;
										if (jjj < 0)
											jjj = jjj + iNY;
										else if (jjj >= iNY)
											jjj = jjj - iNY;
										fCHGCAR_temp[l][m][n] = fCHGCAR_initial[iii][jjj][kkk];
									}
									//cout << fCHGCAR_temp[l][m][n] << '\n';
								}
						fTDiffCHG_abs = 0;
						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									ftemp = fCHGCAR_finial[l][m][n] - fCHGCAR_temp[l][m][n];
									fTDiffCHG_abs = fTDiffCHG_abs + fabs(ftemp);
								}
						fTDiffCHG_abs = fTDiffCHG_abs / double(iNX * iNY * iNZ);
						outall << "  " << fTDiffCHG_abs << "  " << fEnergy[i][j + 1][k] - fEnergy[i][j][k];
					}


					{
						temp = "cp ./" + to_string(i + 1) + "_" + to_string(j) + "_" + to_string(k) + "/CHGCAR ./CHGCAR_finial";
						strcpy(command, temp.c_str());
						system(command);
						inall.open("CHGCAR_initial", ios::in);
						inall1.open("CHGCAR_finial", ios::in);
						getline(inall, temp);
						inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						inall >> ftemp;  inall >> ftemp;  inall >> ftemp;

						while (inall.get() != 10)
						{
							;
						}

						getline(inall, temp);

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
							ii = ii + n;
						}
						inall >> temp;

						for (m = 0; m < ii; m++)
						{
							inall >> ftemp;  inall >> ftemp;  inall >> ftemp;
						}
						inall >> iNX; inall >> iNY; inall >> iNZ;
						cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';

						if (NX < iNX || NY < iNY || NZ < iNZ)
						{
							cout << "NX <= iNX || NY <= iNY || NZ <= iNZ, please increase NX, NY, and NZ in the source program!\n";
							cin >> ftemp;
						}

						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									inall >> fCHGCAR_initial[l][m][n];
								}

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
						cout << iNX << ' ' << iNY << ' ' << iNZ << '\n';
						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									inall1 >> fCHGCAR_finial[l][m][n];
								}
						inall.close();
						inall1.close();

						a_move_direct_distance = double(1) / double(iNofStep_x);
						b_move_direct_distance = double(0) / double(iNofStep_y);
						c_move_direct_site = (fInterface_Site_Max + fInterface_Site_Min) / 2.0;

						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									if (n < iNZ * c_move_direct_site || n > iNZ * c_move_direct_Maxsite)
									{
										fCHGCAR_temp[l][m][n] = fCHGCAR_initial[l][m][n];
									}
									else
									{
										iii = l - round(iNX * a_move_direct_distance);
										jjj = m - round(iNY * b_move_direct_distance);
										kkk = n;
										if (iii < 0)
											iii = iii + iNX;
										else if (iii >= iNX)
											iii = iii - iNX;
										if (jjj < 0)
											jjj = jjj + iNY;
										else if (jjj >= iNY)
											jjj = jjj - iNY;
										fCHGCAR_temp[l][m][n] = fCHGCAR_initial[iii][jjj][kkk];
									}
									//cout << fCHGCAR_temp[l][m][n] << '\n';
								}
						fTDiffCHG_abs = 0;
						for (n = 0; n < iNZ; n++)
							for (m = 0; m < iNY; m++)
								for (l = 0; l < iNX; l++)
								{
									ftemp = fCHGCAR_finial[l][m][n] - fCHGCAR_temp[l][m][n];
									fTDiffCHG_abs = fTDiffCHG_abs + fabs(ftemp);
								}
						fTDiffCHG_abs = fTDiffCHG_abs / double(iNX * iNY * iNZ);
						outall << "  " << fTDiffCHG_abs << "  " << fEnergy[i + 1][j][k] - fEnergy[i][j][k];
					}
				}

			}
		outall << '\n';
	}
	outall.close();
}

