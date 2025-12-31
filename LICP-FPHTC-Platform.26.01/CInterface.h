#include <string.h>
using namespace std;
#define  FSTEP 0.001   //ce shi shifou chonghe yidong juli danwei A
#define  DIFF 0.01  //pandu shifou chonghe
#define  RANK 13 //Energy_z jie=RANK-1
#define  NINGROUP 8 //Number in group during fitting.
#define  NINJIANGE 10000 //Number of inserted points in a jiange.
#define  STEPX 15
#define  STEPY 15
#define  STEPZ 100
class CInterface
{
public:
	int Process();
	CInterface();

private:
	int iNofElement, iNofAtom[10];
	string atomname[10];
	double constant, a, b, c, theta_ab, fArea_Interface; //constant shi POSCAR zhong de dierhang shuju. a,b,c shi POSCAR zhong sange zhou de changdu,chen le constant.
        double fDistance_x, fDistance_y, fDistance_z;
	double ax, ay, az, bx, by, bz, cx, cy, cz;//POSCAR zhong zuobiaozhou de 9 ge fenliang,meiyou chen constant.

	int iNofStep_x, iNofStep_y;
	int iNofStep_z;  //only for test*********************
	int iNofStep_z_Down, iNofStep_z_Up;
	double Fz;       //only for test*********************
	double fStep_x_real, fStep_y_real, fStep_z_real_down, fStep_z_real_up;

	double fEnergy[STEPX][STEPY][STEPZ], fCHG_Interface[STEPX][STEPY][STEPZ], fCHG_Interface_Center[STEPX][STEPY][STEPZ];//x,y,z weizhi chu de energy.
	double fTDiffCHG_d[STEPX][STEPY][STEPZ], fTDiffCHG_Interface_d[STEPX][STEPY][STEPZ], fTDiffCHG_Interface_Relative_d[STEPX][STEPY][STEPZ];
	double fTDiffCHG_zDirection[STEPX][STEPY][STEPZ];
	double fFz[STEPX][STEPY][STEPZ];//x,y,z weizhi chu de zaihe,fEnergy[STEPX][STEPY][STEPX]de daoshu.
	double fFz_Max[STEPX][STEPY], fFz_Min[STEPX][STEPY], z_Max[STEPX][STEPY], z_Min[STEPX][STEPY];
	double fFz_Max_all, fFz_Min_all, z_Max_all, z_Min_all;//jisuan fanweinei zuida he zuixiao de zaihe
	double fEnergy_Fz[STEPX][STEPY], fEnergy_Fz_Nowork[STEPX][STEPY], fCHG_Fz[STEPX][STEPY];//zaihe fz, x,y,z weizhi chu de energy.
	double z_Fz[STEPX][STEPY];
	int x_sandle_Fz, y_sandle_Fz, x_min_Fz, y_min_Fz;//zaihe fz, zuixiaode he andian energy cuiying de shuzuxuhao.
	double Energy_sandle_Fz, Energy_min_Fz;
	double Distance_min_sandle;

	double f_Fz;//   eV/A
	double f_e_Fz;

	int    iNofGroup;
	int    iNinGroup[8];
	double A[STEPX][STEPY], B[STEPX][STEPY]; //E=A/x^6+B/x^12
	double a_coe[STEPX][STEPY][RANK]; //duoxiangshi nihe xishu
	double k_point[STEPX][STEPY][STEPZ], k_average[STEPX][STEPY][STEPZ], k_point_origin[STEPX][STEPY][STEPZ];
	double z[STEPZ]; //danwei A
	double z_initial; //jiemianjian yuanshi juli.

	int i_start, j_start, i_stop, j_stop;

	int CrePOS();
	int Fit_Energy_z();//duiyu meiyige z nihe energy he z de guanxi, xie A he B.^M
	int FzToEnergy(double);//genju zaihe qiu duiying de energy,xie fEnergy_Fz[STEPY][STEPY].^M
	int Find_Path_UnderFz(double);//du fEnergy_fz[STEPY][STEPY],xuzhao nengliang zuidi path.^M
	int Find_Path_z(int);
	int Read_file(int);
	int Operate_file();
	int Submit();
	int Search_Energy();
	int Write_PES_Fz();
	int Write_PES_Dengju();
	int Output_CHG();
	int Output_CHG_z();
	int Output_Transverse_DiffCHG();
	int Output_Near_Transverse_DiffCHG();
	int FzToCHG(double);
	int Write_CS_Dengju();
	int Write_CS_Dengju_Interface_Center();
	int Write_TDCS_Dengju();
	int Write_CS_Fz();
	int Write_ZS_Fz();

};
