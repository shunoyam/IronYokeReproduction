
#pragma once

#include"../src/include.hpp"
using namespace std;

extern int NodeNumberForGaussianQuadrature;
extern int TruncatedEigenmodeNumber;
extern double  pitch_CircularCurrentLoopsOnIronYoke;

extern double Radius_PoleTip_Tsukuba;
extern double InnerRadius_IronYoke_Tsukuba;
extern double LowerHeight_PoleTip_Tsukuba;
extern double InnerHeight_IronYoke_Tsukuba;

extern int n_scan_RadialDirection_OPERA;
extern int n_scan_AxialDirection_OPERA;
extern double LowerLimit_scan_r_OPERA;
extern double UpperLimit_scan_r_OPERA;
extern double UpperLimit_scan_z_OPERA;

void LoadConfigurationFile(string path_InputConfigFile);

