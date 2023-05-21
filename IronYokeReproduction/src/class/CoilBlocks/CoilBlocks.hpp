
#pragma once

#include"../../include.hpp"
using namespace std;

class CoilBlocks
{
private:
  vector<coils> _coils_vec;
public:
  CoilBlocks(string path_to_CoilList);
  operator coils();
  TVector3 B(TVector3 MFEP);
  int n_CoilBlock();
  coils GetCoilBlock(int i_CoilBlock);
};

