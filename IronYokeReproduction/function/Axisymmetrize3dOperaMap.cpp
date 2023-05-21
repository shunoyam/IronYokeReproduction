

//This is based on a macro by Iinuma-san, readMiniSol.C
#include"../src/include.hpp"
using namespace std;

void Axisymmetrize3dOperaMap(string ifn_table, string ofn_dat){
  double r_in_scan = LowerLimit_scan_r_OPERA * 1.e2; //[cm]
  double r_out_scan = UpperLimit_scan_r_OPERA * 1.e2; //[cm]
  double z_out_scan = UpperLimit_scan_z_OPERA * 1.e2; //[cm]
  int n_scan_r = n_scan_RadialDirection_OPERA;
  int n_scan_z = n_scan_AxialDirection_OPERA;

  double r_div = (r_out_scan-r_in_scan) / (n_scan_r-1.);
  double z_div = 2. * z_out_scan / (n_scan_z-1.);

  double BR[n_scan_r][n_scan_z]={};
  double BZ[n_scan_r][n_scan_z]={};
  double mapR[n_scan_r], mapZ[n_scan_z];
  int nn[n_scan_r][n_scan_z]={};
  for(int i=0; i<n_scan_r; ++i){
    mapR[i] = r_in_scan + r_div*(double)i;
  }
  for(int i=0; i<n_scan_z; ++i){
    mapZ[i] = -z_out_scan + z_div*(double)i;
  }
  
  ifstream InputFile(ifn_table.c_str());
  string line;
  int n_header = 8;// .table file by OPERA begins from 8 rows of header
  for(int i_header=0; i_header<n_header; ++i_header){
    getline(InputFile, line);
  }

  double x, y, z; // [cm]
  double bx, by, bz;// [Gauss]
  double tolerance = 1.e-5;//[cm]
  while(InputFile >> x >> y >> z >> bx >> by >> bz){
    
    //This process comes from difference of coordinate system.
    x *= -1.;
    bx *= -1.;
    swap(y, z);
    swap(by, bz);
    
    double R = hypot(x, y);
    double theta = atan2(y, x);
    if(y<=0){
      theta = TMath::TwoPi() - theta;
    }
    theta *= 180. / TMath::Pi();//[rad] -> [deg]
    for(int i_scan_r=0;i_scan_r<n_scan_r;++i_scan_r){
      for(int i_scan_z=0;i_scan_z<n_scan_z;++i_scan_z){
        if(abs(R-mapR[i_scan_r]) < tolerance){
          if(abs(z-mapZ[i_scan_z]) < tolerance){
            BR[i_scan_r][i_scan_z] += (bx*x+by*y) / R;
            BZ[i_scan_r][i_scan_z] += bz;
            nn[i_scan_r][i_scan_z]++;
          }
        }
      }
    }
  }
    
  //divide by n_vane to calculate average over rotational direction 
  for(int i_scan_r=0; i_scan_r<n_scan_r; ++i_scan_r){
      for(int i_scan_z=0;i_scan_z<n_scan_z;++i_scan_z){
          BR[i_scan_r][i_scan_z] /= (double)nn[i_scan_r][i_scan_z];
          BZ[i_scan_r][i_scan_z] /= (double)nn[i_scan_r][i_scan_z];
        }
    }

  //write to file
  ofstream OutputFile(ofn_dat.c_str());
  for(int i=0;i<n_scan_z;++i){
      for(int j=0;j<n_scan_r;j++){
          OutputFile << mapR[j] << "\t" << mapZ[i] << "\t";
          OutputFile << BZ[j][i] << "\t" << BR[j][i] << endl;
        }
    }

  //move to IronYokeReproduction/data/
  string destination = " ../../data/";
  mv(ofn_dat, destination);
}


