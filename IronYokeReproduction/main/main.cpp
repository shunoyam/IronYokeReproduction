
#ifndef _IN_MAIN
#define _IN_MAIN
#include"../src/include.hpp"

int main(){
  //load global variables
  string path_to_configfile="../../data/ConfigurationFile/configuration.txt";
  LoadConfigFile(path_to_configfile);


  ReproduceIronYoke("../../data/type1.dat",
                    "CurrentDistribution.root",
                    "CurrentDistribution.dat");

  
  return 0;
}

#endif



