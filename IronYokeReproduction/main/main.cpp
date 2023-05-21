
#ifndef _IN_MAIN
#define _IN_MAIN
#include"../src/include.hpp"

int main(){
  
  string path_to_ConfigurationFile = "../../data/configuration.txt";
  string path_to_IronYokeParameter = "../../data/parameter_TsukubaIronYoke.txt";
  string path_to_CoilInformation = "../../data/CoilList.txt";
  string ifn_3dOPERAMap = "../../data/toSVD_876_684.table";
  string ofn_root = "MagneticFieldDistributions.root";
  string ofn_dat = "information_CircularCurrentLoops.dat";

  ReproduceIronYoke(path_to_ConfigurationFile, path_to_IronYokeParameter,
                    path_to_CoilInformation,
                    ifn_3dOPERAMap, ofn_root, ofn_dat);


  


  return 0;
}

#endif



