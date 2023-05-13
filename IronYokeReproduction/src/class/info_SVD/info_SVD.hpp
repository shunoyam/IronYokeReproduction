
#pragma once

#include"../../include.hpp"
using namespace std;
using namespace Eigen;

class SVD;
class Bs;

class info_SVD
{
private:
  VectorXd _source_vec;
  vector<double> _ModeStrength_vec;
  vector<double> _SingularValue_vec;
  int _n_mode;
public:
  info_SVD(SVD result_SVD, vector<Bfield> B_TG,const char* ofn_intermediate,
           int n_mode=TruncatedEigenmodeNumber, string element="Bz");
  VectorXd info_svd_eigen();
  void out(string ofn_dat);








  
};
















  


