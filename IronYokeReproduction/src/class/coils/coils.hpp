
#pragma once

#include"../../include.hpp"
using namespace std;

class coils
{
private:
  vector<coil> _coil_vec;
  double _center_r;
  double _center_z;
  double _r_in;
  double _r_out;
  double _z_upper;
  double _z_lower;
  string _name;
public:
  coils();
  coils(vector<coil> coil_vec);
  void set(vector<coil> coil_vec);
  void WriteDownSides(double r_in,double r_out,double z_lower,double z_upper);
  void SetOnMesh(double r_in,double r_out,double height,int mesh_r,int mesh_z,
                 double TotalCurrent=0.,double center_z=0.);
  void push_back(coil coil);
  void Push_Back(coils coilblocks);
  coil at(int index);
  vector<coil> coil_vec();
  TVector3 B(TVector3 MagneticFieldEvaluaionPoint);
  double Bz(TVector3 MFEP);
  void read(string path_to_magnet_data="../config/M20210727-Abe.DAT");
  void read_rz(string path_to_magnet_data);
  double z_lower();
  void SetName(string name);
  void SetOnGaussNodes(double center_r,double HalfWidth_r,int nodes_r,
                       double center_z,double HalfWidth_z,int nodes_z,
                       double CurrentDensity);
  double TotalCurrent();
  void optimize(int n_mode, vector<Bfield> B_target, string element);
  void out(string OutputFileName_dat);
};

