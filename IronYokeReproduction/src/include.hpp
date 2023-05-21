
#pragma once

#include<TFile.h>
#include<TVector3.h>
#include<TTree.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TF1.h>
#include<TH2.h>
#include<TH3.h>
#include<TStyle.h>
#include<TPaveStats.h>
#include<TMultiGraph.h>
#include<TPaletteAxis.h>
#include<TRandom2.h>
#include<Math/Vector3D.h>
#include<TFrame.h>
#include<TArrow.h>
#include<TPolyMarker3D.h>
#include<TROOT.h>


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<vector>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<numeric>
#include<string.h>

#include<Eigen/SVD>
#include<Eigen/Core>
#include"constants.hpp"

#include"../function/LoadConfigurationFile.hpp"

#include"../function/UsefulFunctions.hpp"
#include"../function/cpp17.hpp"

#include"class/coil/coil.hpp"
#include"class/Bfield/Bfield.hpp"
#include"class/svd/svd.hpp"
#include"class/info_SVD/info_SVD.hpp"
#include"../function/solution_inverse_TSVD.hpp"
#include"class/Legendre/Legendre.hpp"
#include"class/coils/coils.hpp"
#include"class/CoilBlocks/CoilBlocks.hpp"
#include"class/Bs/Bs.hpp"

#include"../function/Axisymmetrize3dOperaMap.hpp"
#include"../function/CreateIronYokeGeometry.hpp"
#include"../function/DrawMagneticField_TsukubaSolenoid.hpp"
#include"../function/ReproduceIronYoke.hpp"











