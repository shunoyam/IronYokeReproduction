
#include"../include.hpp"

using namespace std;
using namespace ROOT::Math;
using namespace Eigen;

vector<double> solution_inverse_TSVD(vector<vector<double>> ResponseMatrix,
                                     vector<Bfield> _B_TG,int n_mode, string element)
{
  auto B_TG = (vector<Bfield>)_B_TG;
  int n_MFEP_check=B_TG.size();
  int n_MFEP=ResponseMatrix.size();
  int n_source=ResponseMatrix[0].size();
  if(n_MFEP!=n_MFEP_check)
    {
      cout<<"Error!!"<<endl;
      puts("Element counts are not consistent with matrix A and vector B.");
    }

  MatrixXd ResponseMatrix_eigen(n_MFEP,n_source);
  for(int i_MFEP=0;i_MFEP<n_MFEP;i_MFEP++)
    {
      for(int i_source=0;i_source<n_source;i_source++)
        {
          ResponseMatrix_eigen(i_MFEP,i_source)=ResponseMatrix[i_MFEP][i_source];
        }
    }
  SVD SVDresult(ResponseMatrix_eigen);
  MatrixXd I_mode(n_source,n_mode);
  //
  info_SVD solution(SVDresult, _B_TG, "mode.dat", n_mode, "Bz");
  auto I_eigen = (VectorXd)solution.info_svd_eigen();
  //
  vector<double> I_vec;
  for(int i_source=0;i_source<n_source;i_source++)
    {
     double I = I_eigen(i_source);
      I_vec.push_back(I);
    }
  return I_vec;
}



