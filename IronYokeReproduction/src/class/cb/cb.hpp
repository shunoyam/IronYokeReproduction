
#pragma once

#include"../../include.hpp"
using namespace std;

class cb//coil block
{
private:
  vector<coil> _coils;
  double _center_r;
  double _center_z;
  double _r_in;
  double _r_out;
  double _z_upper;
  double _z_lower;
public:
  cb();
  cb(vector<coil> coils);
  void set(vector<coil> coils);
  void WriteDownSides(double r_in,double r_out,double z_lower,double z_upper);
  void SetOnMesh(double r_in,double r_out,double height,int mesh_r,int mesh_z,
                 double TotalCurrent=0.,double center_z=0.);
  void push_back(coil coil);
  void Push_Back(cb coilblocks);
  coil at(int index);
  vector<coil> coil_vec();
  TVector3 B(TVector3 MagneticFieldEvaluaionPoint);
  double Bz(TVector3 MFEP);
  double Flux(TVector3 MFEP);
  //scalar magnetic potential for drawing equal magnetic field lines.
  double MMF();// magnetomotive force of the coils.
  //i.e. absolutely sum of the coil currents
  void read(string path_to_magnet_data="../config/M20210727-Abe.DAT");
  void read_rz(string path_to_magnet_data);
  double z_lower();
  void SetOnGaussNodes(double center_r,double width_r,int nodes_r,
                       double center_z,double width_z,int nodes_z,double CurrentDensity);
  //width is "half width"!!
  double TotalCurrent();
  void SetTsukubaSolenoid();//defined at various/  
  void optimize(int n_mode, vector<Bfield> B_target, string element);
  void out(string OutputFileName_dat);
};

