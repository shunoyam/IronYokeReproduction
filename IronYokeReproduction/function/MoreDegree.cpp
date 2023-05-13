

#include"../../src/include.hpp"
using namespace std;

void gauss_mesh()
{
  TVector3 ClosestPoint(.18,0.,0.);
  const char* ofn_dat="PrecisionBattle.dat";
  ofstream of(ofn_dat);
  of<<"#factor   Bz by gaussian quadrature   Bz by mesh dividing"<<endl;
  of<<fixed<<setprecision(15);
  int n_point=100;
  double diameter_in=.46;
  double diameter_out=.4808;
  double height=.54;
  double r_in=diameter_in/2.;
  double r_out=diameter_out/2.;
  double center_r=(r_in+r_out)/2.;
  double width_r=r_out-center_r; //half width
  double width_z=height/2.;
  double CurrentDensity=88.7986069450757e4;//A/m2

  for(int i=0;i<n_point;i++)
    {
      cout<<i<<"point now"<<endl;
      int factor=i+5;
      cb coil_gauss;
      int node_r=round(factor/30)+1;
      int node_z=factor;
      coil_gauss.SetOnGaussNodes(center_r,width_r,node_r,
                                 0.,width_z,node_z,CurrentDensity);
      cb coil_mesh;
      int mesh_r=factor;
      int mesh_z=30*factor;
      coil_mesh.SetOnMesh(r_in,r_out,height,
                          mesh_r,mesh_z,height*2.*width_r*CurrentDensity);
      double bz_gauss=coil_gauss.Bz(ClosestPoint);
      double bz_mesh=coil_mesh.Bz(ClosestPoint);
      of<<i<<"\t"<<bz_gauss<<"\t"<<bz_mesh<<endl;
    }

}


