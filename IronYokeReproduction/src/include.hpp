
#pragma once

#include<TFile.h>
#include<TVector3.h>
#include<TTree.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TH2.h>
#include<TF1.h>
#include<TStyle.h>
#include<TPaveStats.h>
#include<TMultiGraph.h>
#include<TPaletteAxis.h>
#include<TRandom2.h>
#include<Math/Vector3D.h>
#include<TFrame.h>
#include<TArrow.h>

#include<bits/stdc++.h>
//Clang compiler may not be able to use this. 
//In that case, include appropriate STLs.

#include<Eigen/SVD>
#include<Eigen/Core>
#include"constants.hpp"

#include"../data/LoadConfigFile.hpp"

#include"../function/UsefulFunctions.hpp"
#include"../function/cpp17.hpp"

#include"class/coil/coil.hpp"
#include"class/Bfield/Bfield.hpp"
#include"class/svd/svd.hpp"
#include"class/info_SVD/info_SVD.hpp"
#include"../function/solution_inverse_TSVD.hpp"
#include"class/Legendre/Legendre.hpp"
#include"class/cb/cb.hpp"
#include"class/Bs/Bs.hpp"


#include"../function/ConsistencyCheck.hpp"
#include"../function/ReproduceIronYoke.hpp"











