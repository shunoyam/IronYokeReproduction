
#ifndef _IN_MAIN
#define _IN_MAIN
#include"../src/include.hpp"

int main(){
  //load global variables
  string path_to_configfile = "../../data/configuration.txt";
  LoadConfigFile(path_to_configfile);


  string path_to_OPERA3Dmap = "../../data/toSVD_876_684_noLHoles_SUS.table";
  //  string path_to_OPERA3Dmap = "../../data/toSVD_876_684.table";
  string OutputFileName_root = "MagneticDistributions.root";
  string OutputFileName_dat = "CurrentDistribution.dat";
  ReproduceIronYoke(path_to_OPERA3Dmap, OutputFileName_root, OutputFileName_dat);

  
  return 0;
}

#endif



