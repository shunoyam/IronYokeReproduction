
#include"../../include.hpp"

using namespace std;

CoilBlocks::CoilBlocks(string path_to_CoilList){
  ifstream InputFile(path_to_CoilList.c_str());
  if(InputFile.fail()){
    cout << path_to_CoilList << " not found" << endl;
    return;
  }
  string name;
  double r_out, r_in, z_center, HalfHeight; //[m]
  double CurrentDensity;//[A/m^2]
  cout << "loading coil data from " << path_to_CoilList << endl;
  cout << endl;
  string FirstLine;
  getline(InputFile, FirstLine);
  while(InputFile >> name >> r_out >> r_in >> z_center >> HalfHeight >> CurrentDensity){
    cout << "coil \"" << name << "\" was added. "<< endl;
    cout << "outer radius: " << r_out << endl;
    cout << "inner radius: " << r_in << endl;
    cout << "axial center: " << z_center << endl;
    cout << "half height: " << HalfHeight << endl;
    cout << "current density: " << CurrentDensity << endl;
    cout << "------------------------------" << endl;
    coils _coils;
    _coils.SetName(name);
    double r_center = (r_out+r_in) / 2.;
    double r_width = (r_out-r_in) / 2.;    
    _coils.SetOnGaussNodes(r_center, r_width, NodeNumberForGaussianQuadrature,
                           z_center, HalfHeight, NodeNumberForGaussianQuadrature,
                           CurrentDensity);
    this->_coils_vec.push_back(_coils);
  }
}

TVector3 CoilBlocks::B(TVector3 MFEP){
  TVector3 _B(0., 0., 0.);
  for(coils c: this->_coils_vec){
    TVector3 b = c.B(MFEP);
    _B += b;
  }
  return _B;
}

int CoilBlocks::n_CoilBlock(){
  return this->_coils_vec.size();
}

coils CoilBlocks::GetCoilBlock(int i_CoilBlock){
  if(i_CoilBlock<0 or CoilBlocks::n_CoilBlock()<=i_CoilBlock){
    cout << i_CoilBlock << " th coil not exists" << endl;
  }
  return this->_coils_vec[i_CoilBlock];
}

CoilBlocks::operator coils(){
  coils coils_cat;
  for(coils coils: this->_coils_vec){
    coils_cat.Push_Back(coils);
  }
  cout << coils_cat.coil_vec().size() << " should be 800" << endl;
  return coils_cat;
}











