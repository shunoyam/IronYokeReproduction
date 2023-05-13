#pragma once

#include"../../include.hpp"
using namespace std;

class Bs 
{
private:
  vector<Bfield> _B;
  double _min_Bz;
  double _max_Bz;
  double _min_Br;
  double _max_Br;
  double _min_Bx;
  double _max_Bx;
public:
  Bs();
  Bs(string path_to_2dFieldMapFile);
  operator vector<Bfield>();
  int MFEPs();
  double min(char component);
  double max(char component);
  Bfield at(int index);
  //return ith Bfield
  void push_back(TVector3 MFEP,TVector3 MagneticField=TVector3(0.,0.,0.),
                 double theta=0.);
  void push_back(TVector3 MFEP,int channel,double theta=0.,
                 TVector3 MagneticField=TVector3(0.,0.,0.));
  void setUniform(double Bz_target);
  void setonDSS(double diameter_DSS,int n_theta_MFEP,int n_phi_MFEP,
                double Bz_target=0.);
  double average();
  void subtract(cb coils);
  void addBs(Bs B_added,Bs B_add,double coefficient_added,double coefficient_add);
  void peak2peakSubstitution();
  void add_coil(cb coils,double factor=1.);
  void add_coil(vector<cb> CBs,double factor=1.);
  
  void clear();
  Eigen::VectorXd Bs_eigen(string element="Bz");
  void Eigen_Bs(Eigen::VectorXd B_eigen);
  operator vector<double>();
  void Read2dFieldMap(string path_to_MFEP_data);
  void Read3dFieldMap(string path,string unit_pos,string unit_B);
  void DirectionBlinding();
  void ChangeB(int i_mfep,TVector3 NewB);
  void out(const char* ofn_dat);
  void reverse();
};


