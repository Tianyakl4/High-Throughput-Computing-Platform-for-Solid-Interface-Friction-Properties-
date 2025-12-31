#!/bin/bash
g++ CInterface.cpp main.cpp Process.cpp CrePOS.cpp Operate_file.cpp Submit.cpp Read_file.cpp Search_Energy.cpp Fit_Energy_z.cpp FzToEnergy.cpp  Find_Path_UnderFz.cpp Find_Path_z.cpp Write_PES_Fz.cpp Write_PES_Dengju.cpp Output_CHG.cpp Output_CHG_z.cpp Write_CS_Dengju.cpp Write_CS_Dengju_Interface_Center.cpp Write_CS_Fz.cpp Write_ZS_Fz.cpp  FzToCHG.cpp  Output_Transverse_DiffCHG.cpp   Write_TDCS_Dengju.cpp Output_Near_Transverse_DiffCHG.cpp  -std=c++11 -o LICP-FPHTC-Platform.26.01

