
#pragma once

#include"../../../src/include.hpp"
using namespace std;
using namespace Eigen;

class SVD
{
private:
  int _n_MFEP;
  int _n_source;
  int _n_mode;
  vector<double> _SingularValues;
  vector<MatrixXd> _RightUnitary;
  vector<MatrixXd> _LeftUnitary;
public:
  SVD(MatrixXd result_eigen);
  double sigma(int i_mode);
  VectorXd u(int i_MFEP);
  VectorXd v(int i_source);
  int n_mode();
  int n_MFEP();
  int n_source();
};




