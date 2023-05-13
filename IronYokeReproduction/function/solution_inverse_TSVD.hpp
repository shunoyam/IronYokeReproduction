
#pragma once

#include"../include.hpp"
using namespace std;
using namespace ROOT::Math;
using namespace Eigen;

vector<double> solution_inverse_TSVD(vector<vector<double>> ResponseMatrix,
                                     vector<Bfield> B_target,
                                     int n_mode, string element="Bz");




