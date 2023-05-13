


#include"../../include.hpp"

using namespace std;

cb::cb()
{
  
}

cb::cb(vector<coil> coils)
{
  cb::set(coils);
}

void cb::set(vector<coil> coils)
{
  this->_coils=coils;
}

void cb::WriteDownSides(double r_in,double r_out,
                        double z_lower,double z_upper)
{
  this->_center_r=(r_out+r_in)/2.;
  this->_center_z=(z_upper+z_lower)/2.;  
  this->_r_in=r_in;
  this->_r_out=r_out;
  this->_z_upper=z_upper;
  this->_z_lower=z_lower;
}

void cb::SetOnMesh(double r_in,double r_out,double height,int mesh_r,int mesh_z,
                   double TotalCurrent,double center_z)
{
  if(mesh_r<1 or mesh_z<1 )
    {
      cout<<"Number of meshes is invalid."<<endl;
      cout<<"number of radial meshes:"<<mesh_r<<endl;
      cout<<"number of axial meshes:"<<mesh_z<<endl;
      return;
    }
  if(height<0.)
    {
      cout<<"error!"<<endl;
      cout<<"height of coil needs to be positive"<<endl;
      return;
    }
  double IndividualCurrent=TotalCurrent/(mesh_r*mesh_z);
  coil coil_tmp;
  double r,z;
  double div_r=(r_out-r_in)/mesh_r;
  double div_z=height/mesh_z;
  double z_low=center_z-height/2.;
  for(int mesh_r_i=0;mesh_r_i<mesh_r;mesh_r_i++)
    {
      r=r_in+div_r*(mesh_r_i+0.5);
      for(int mesh_z_i=0;mesh_z_i<mesh_z;mesh_z_i++)
        {
          z=z_low+div_z*(mesh_z_i+0.5);
          coil_tmp.set(IndividualCurrent,r,z);
          cb::push_back(coil_tmp);
        }      
    }
}

void cb::push_back(coil coil)
{
  this->_coils.push_back(coil);
}

void cb::Push_Back(cb coils)
{
  vector<coil> coils_vec=coils.coil_vec();
  int n_coil=coils_vec.size();
  for(int i_coil=0;i_coil<n_coil;i_coil++)
    {
      this->push_back(coils_vec[i_coil]);
    }
}

coil cb::at(int index)
{
  coil coil_index=this->_coils[index];
  return coil_index;
}

vector<coil> cb::coil_vec()
{
  return this->_coils;
}

TVector3 cb::B(TVector3 MFEP)
{
  TVector3 _B;
  for(coil flc:this->_coils)
    {
      _B+=flc.b(MFEP);
    }
  return _B;
}

double cb::Bz(TVector3 MFEP)
{
  double _Bz=cb::B(MFEP).z();
  return _Bz;
}

double cb::Flux(TVector3 MFEP)
{
  vector<coil> coils=this->_coils;
  double _flux_coil=0.;
  for(int i_coil=0;i_coil<coils.size();i_coil++)
    {
      _flux_coil+=coils[i_coil].flux(MFEP);
    }
  return _flux_coil;
}

double cb::MMF()
{
  double magnetomotiveforce=0.;
  double current;
  vector<coil> coils=this->_coils;
  for(int i_flc=0;i_flc<coils.size();i_flc++)
    {
      current=coils[i_flc].I();
      magnetomotiveforce+=abs(current);
    }
  return magnetomotiveforce;
}

void cb::read(string path_to_magnet_data)
{
  vector<coil> CoilBlock;
  ifstream InputFile(path_to_magnet_data.c_str());
  if(InputFile.fail()){
    cout << path_to_magnet_data << "not found" << endl;
  }
  int number;
  double radius,height,current;
  coil coil_temp;
  while(InputFile >> number >> radius >> height >> current){
          coil_temp.set(current,radius,height);
          CoilBlock.push_back(coil_temp);    
  }
  this->_coils = CoilBlock;
}

void cb::read_rz(string path_to_magnet_data)
{
  vector<coil> CoilBlock;
  ifstream InputFile(path_to_magnet_data.c_str());
  double radius,height,current=0.;
  coil coil_temp;
  while(InputFile >> radius >> height){
    coil_temp.set(current,radius,height);
    CoilBlock.push_back(coil_temp);
  }
  this->_coils=CoilBlock;
}

double cb::z_lower()
{
  return this->_z_lower;
}

double cb::TotalCurrent()
{
  double current=0.;
  for(coil coil: _coils)
    {
      current+=coil.I();
    }
  return current;
}


void cb::SetOnGaussNodes(double center_r,double width_r,int nodes_r,
                         double center_z,double width_z,int nodes_z,double CurrentDensity){
  int nodes = nodes_r * nodes_z;
  double TotalCurrent=CurrentDensity*2.*width_r*2.*width_z;
  double current,r,z,weight_r,weight_z,node_r,node_z;
  Legendre leg_r(nodes_r);
  Legendre leg_z(nodes_z);
  vector<double> weights_r_vec=leg_r.GetWeights();
  vector<double> weights_z_vec=leg_z.GetWeights();
  vector<double> nodes_r_vec=leg_r.GetNodes();
  vector<double> nodes_z_vec=leg_z.GetNodes();
  for(int i_node_r=0;i_node_r<nodes_r;i_node_r++)
    {
      for(int i_node_z=0;i_node_z<nodes_z;i_node_z++)
        {
          weight_r=weights_r_vec[i_node_r];
          weight_z=weights_z_vec[i_node_z];
          node_r=nodes_r_vec[i_node_r];
          node_z=nodes_z_vec[i_node_z];
          current=TotalCurrent*weight_r*weight_z/4.;
          r = center_r + node_r*width_r;
          z=center_z+node_z*width_z;
          coil flc(current,r,z);
          cb::push_back(flc);
        }
    }
}

void cb::optimize(int n_mode, vector<Bfield> B_TG, string element){
  int n_MFEP = B_TG.size();
  int n_coil = this->_coils.size();
  if(n_MFEP<n_mode or n_coil<n_mode){
    string text = "Truncated eigenmode number must be larger";
    text += " than both MFEP number and FLC number.";
    cout << "\033[31m error \033[m :" << text << endl;
    cout<< "Check if their values are as expected. " << endl;
    cout << "Truncated eigenmode number: " << n_mode << endl;
    cout << "MFEP number: " << n_MFEP << endl;
    cout << "FLC(filament loop coil) number: " << n_coil << endl;
    return;
    }
  vector<vector<double>> _A_vec(n_MFEP);
  TVector3 temp_A;
  for(int i_MFEP=0;i_MFEP<n_MFEP;i_MFEP++)
    {
      for(int i_coil=0;i_coil<n_coil;i_coil++)
        {
          temp_A=this->_coils[i_coil].ResponseElement(B_TG[i_MFEP].MFEP());
          _A_vec[i_MFEP].push_back(temp_A.z());
        }
    }
  //
  vector<double> I_vec = solution_inverse_TSVD(_A_vec, B_TG, n_mode, element);
  //
  for(int i_coil=0; i_coil<n_coil; i_coil++){
    this->_coils[i_coil].setI(I_vec[i_coil]);
    }
}

void cb::out(string OutputFileName_dat){
  ofstream OutputFile(OutputFileName_dat.c_str());
  OutputFile << "# radial position[m]\t axial position[m]\t current[A]" << endl;
  for(coil _coil: this->_coils){
    OutputFile << _coil.r() << "\t" << _coil.z() << "\t" << _coil.I() << endl;
  }
}



