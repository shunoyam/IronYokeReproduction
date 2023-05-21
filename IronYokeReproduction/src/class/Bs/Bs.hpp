#pragma once

#include"../../include.hpp"
using namespace std;

class Bs 
{
private:
  vector<Bfield> _B;
public:
  Bs();
  Bs(string path_to_2dFieldMapFile);
  operator vector<Bfield>();
  int MFEPs();
  Bfield at(int index);
  //return ith Bfield
  void push_back(TVector3 MFEP,TVector3 MagneticField=TVector3(0.,0.,0.), double theta=0.);
  void push_back(TVector3 MFEP, double theta, TVector3 MagneticField);
  double average();
  void subtract(coils coils);
  void addBs(Bs B_added,Bs B_add,double coefficient_added,double coefficient_add);
  void add_coil(coils, double factor=1.);
  void clear();
  Eigen::VectorXd Bs_eigen(string element="Bz");
  void Eigen_Bs(Eigen::VectorXd B_eigen);
  operator vector<double>();
  void Read2dFieldMap(string path_to_MFEP_data);
  void Read3dFieldMap(string path,string unit_pos,string unit_B);
  void DirectionBlinding();
  void out(const char* ofn_dat);
  double max(string element);//element must be "|B|" or "Bz" 
};


