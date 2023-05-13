

#include"../../../src/include.hpp"
using namespace std;
using namespace Eigen;


SVD::SVD(MatrixXd ResponseMatrix)
{
  int n_MFEP=ResponseMatrix.rows();
  int n_source=ResponseMatrix.cols();
  int n_mode=min(n_MFEP,n_source);
  if(n_MFEP<n_source)
    {
      n_mode=n_MFEP;
    }
  if(n_MFEP<n_mode || n_source<n_mode)
    {
      cout<< "\033[31m";
      cout<<"error"<<endl;
      cout<<"Truncated number must be size of response matrix"<<endl;
      cout<<"truncated number:"<<n_mode<<endl;
      cout<<"number of MFEPs:"<<n_MFEP<<endl;
      cout<<"number of coils(or iron shims):"<<n_source<<endl;
      cout<<"\033[m"<<endl;
      return;
    }
  JacobiSVD<MatrixXd> result_eigen(ResponseMatrix,
                                   ComputeFullU |ComputeFullV);
  MatrixXd V=result_eigen.matrixV(); 
  MatrixXd U=result_eigen.matrixU(); 
  VectorXd u(n_source);
  VectorXd v(n_MFEP);
  VectorXd u0(n_source);
  VectorXd v0(n_MFEP);
  for(int i_mode=0;i_mode<n_mode;i_mode++) 
    {  
      u=U.col(i_mode);
      v=V.col(i_mode);
      double SingularValue=result_eigen.singularValues()[i_mode];
      this->_LeftUnitary.push_back(u);
      this->_RightUnitary.push_back(v);
      this->_SingularValues.push_back(SingularValue);
    }
  this->_n_MFEP=n_MFEP;
  this->_n_source=n_source;
  this->_n_mode=n_mode;
}

double SVD::sigma(int i_mode)
{
  if(i_mode>=this->_n_mode)
    {
      cout<<"argument "<<i_mode<<" is invalid."<<endl;
      return nan("");
    }
  double SingularValue=this->_SingularValues[i_mode];
  return SingularValue;
}

VectorXd SVD::u(int i_source)
{
  if(i_source>=this->_n_source)
    {
      cout<<"argument "<<i_source<<" is invalid."<<endl;
      auto zero=VectorXd::Zero(0);
      return zero;
    }
  auto LeftVector=this->_LeftUnitary[i_source];
  return LeftVector;
}

VectorXd SVD::v(int i_MFEP)
{
  if(i_MFEP>=this->_n_MFEP)
    {
      cout<<"argument "<<i_MFEP<<" is invalid."<<endl;
      auto zero=VectorXd::Zero(0);
      return zero;
    }
  auto RightVector=this->_RightUnitary[i_MFEP];
  return RightVector;
}

int SVD::n_mode()
{
  return this->_n_mode;
}

int SVD::n_MFEP()
{
  return this->_n_MFEP;
}

int SVD::n_source()
{
  return this->_n_source;
}

