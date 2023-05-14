
#pragma once

#include"../src/include.hpp"
using namespace std;

extern double InnerDiameterOfMainCoil;
extern double OuterDiameterOfMainCoil;
extern double FullHeightOfMainCoil;
extern double CurrentDensityOfMainCoil;

extern double InnerDiameterOfWeakFocusingCoil;
extern double OuterDiameterOfWeakFocusingCoil;
extern double FullHeightOfWeakFocusingCoil;
extern double CurrentDensityOfWeakFocusingCoil;

extern int NodeNumberForGaussianQuadrature;
extern int TruncatedEigenmodeNumber;
extern double ArrangedPitch_FilamentLoopCoil;

extern double InnerRadius_PoleTip_Tsukuba;
extern double OuterRadius_PoleTip_Tsukuba;
extern double InnerRadius_IronYoke_Tsukuba;
extern double LowerHeight_PoleTip_Tsukuba;
extern double InnerHeight_IronYoke_Tsukuba;

extern double n_scan_RadialDirection_OPERA;
extern double n_scan_AxialDirection_OPERA;

void LoadConfigFile(string path_InputConfigFile);

