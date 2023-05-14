
#include"../../src/include.hpp"
using namespace std;

void ConsistencyCheck(string ifn_AxisymmetrizedFieldMap, string ofn_root){
  //read axisymmetrized field map which is generated with 3d-OPERA map
  Bs B_target;
  B_target.Read2dFieldMap(ifn_AxisymmetrizedFieldMap);
  cout<<"MFEP number: "<<B_target.MFEPs()<<endl;

  //set solenoid coil at Tsukuba
  cb Coil;
  Coil.SetTsukubaSolenoid();
  
  //calculate target magnetic field by subtract B_coil from B_all
  B_target.subtract(Coil);

  //discritize inner surface of iron yoke as evenly spaced dots
  double pitch = ArrangedPitch_FilamentLoopCoil;//[m]
  int pitch_mm = (int)(pitch*1.e3);
  string FileName_yoke_config = "IronShape_" + to_string(pitch_mm) + "mm.dat";
  string path_to_iron_yoke_config_file="../../data/" + FileName_yoke_config;
  CreateIronYokeGeometry(pitch, FileName_yoke_config);

  //set filament loop coils which reproduce iron yoke
  cb IronYoke;
  IronYoke.read_rz(path_to_iron_yoke_config_file);
  int n_coil_yoke=IronYoke.coil_vec().size();
  cout<<"FLC number: "<<n_coil_yoke<<endl;
  
  //specify scan range of truncated mode number
  int min_mode=60;
  int max_mode=63;

  //prepare TTree 
  auto tree = new TTree("truncated mode scan", "truncated mode scan");
  int i_mode;
  double p2p;
  double max_CurrentDensity;
  tree->Branch("truncated mode number", &i_mode);
  tree->Branch("peak-to-peak of (B_target - B_reproduced)", &p2p);//indicates accuracy
  tree->Branch("max current density", &max_CurrentDensity);//[A/m]

  double threshold_current_density = magnetization_iron;//[A/m]
  //corresponding to saturation current density for iron
  
  for(i_mode=min_mode; i_mode<max_mode; i_mode++){
      puts("----------------------");
      IronYoke.optimize(i_mode, B_target, "Bz");

      vector<double> CurrentDensity_vec;
      int even = 0;
      for(coil coil:IronYoke.coil_vec()){
          even++;
          if(even%2){
              continue;
            }
          CurrentDensity_vec.push_back(coil.I()/pitch);//[A/m]
        }
      max_CurrentDensity = *max_element(CurrentDensity_vec.begin(),
                                      CurrentDensity_vec.end());
      cout<<"max of reproduced current density: ";
      cout<<max_CurrentDensity << "[A/m]" << endl;

      Bs B_error = B_target;
      B_error.subtract(IronYoke);
      double max_error = B_error.max("Bz");
      cout<<"reproduced with the accuracy of "<<max_error*1.e4<<"[Gauss]"<<endl;
      tree -> Fill();
      if(max_CurrentDensity>threshold_current_density){
          break;
        }
      }
  
  auto c = new TCanvas("c", "c");
  DrawMagneticField_TsukubaSolenoid(IronYoke,Coil, c, ifn_AxisymmetrizedFieldMap);
  auto fout = new TFile(ofn_root.c_str(), "recreate");
  c->Write();
  tree -> Write();
  fout->Close();
}

void DrawMagneticField_TsukubaSolenoid(cb FLCs_IronYoke,cb Coil,TCanvas* c,
                                       string path_to_MFEP_configuration_file){
  Bs B_all;
  B_all.Read2dFieldMap(path_to_MFEP_configuration_file);
  auto bz_list_all = (vector<double>)B_all;

  Bs B_coil= B_all;
  B_coil.clear();
  B_coil.add_coil(Coil);
  auto bz_list_coil = (vector<double>)B_coil;

  Bs B_target = B_all;
  B_target.addBs(B_all, B_coil, 1., -1.);
  auto bz_list_target = (vector<double>)B_target;

  Bs B_error = B_target;
  B_error.subtract(FLCs_IronYoke);
  auto bz_list_error = (vector<double>)B_error;

  //get scan range
  double r_in=1.e10;
  double r_out=-1.e10;
  double z_out=-1.e10;
  for(Bfield b: (vector<Bfield>)B_all){
    TVector3 position = b.MFEP();
    double r = position.x();
    double z = position.z();
    if(r < r_in){
      r_in = r;
    }
    if(r_out < r){
      r_out = r;
    }
    if(z_out < z){
      z_out = z;
    }
  }

  //get scan points
  int mesh_r = n_scan_RadialDirection_OPERA;
  int mesh_z = n_scan_AxialDirection_OPERA;

  double r_width = (r_out-r_in) / 2.;
  double r_margin = r_width / (double)mesh_r;
  double z_margin = z_out / (double)mesh_z;
  auto h_all = new TH2D("h_all",
                        "B_{all} [Gauss];x[cm];z[cm]",
                        mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                        mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);
  auto h_coil = new TH2D("h_coil",
                         "B_{coil} [Gauss];x[cm];z[cm]",
                         mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                         mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);
  auto h_target = new TH2D("h_target",
                           "B_{target} = B_{yoke} = B_{all} - B_{coil}[Gauss];x[cm];z[cm]",
                           mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                           mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);
  auto h_error = new TH2D("h_error",
                          "B_{error} = B_{target} - B_{reproduce} [Gauss];x[cm];z[cm]",
                          mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                          mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);

  SetStyle_TH2Ds(h_all, h_coil, h_target, h_error);

  int n_MFEP = B_all.MFEPs();
  for(int i_MFEP=0; i_MFEP<n_MFEP ;i_MFEP++){
    double r = B_all.at(i_MFEP).MFEP().x();
    double z = B_all.at(i_MFEP).MFEP().z();
    h_all -> Fill(r*100., z*100., bz_list_all[i_MFEP]*1.e4);
    h_coil -> Fill(r*100., z*100., bz_list_coil[i_MFEP]*1.e4);
    h_target -> Fill(r*100., z*100., bz_list_target[i_MFEP]*1.e4);
    h_error -> Fill(r*100., z*100., abs(bz_list_error[i_MFEP])*1.e4);
  }
  
  const char* DrawOption = "colz";
  c->Divide(4, 1);
  c->cd(1);
  SetStyle_TCanvas(c);
  h_all->Draw(DrawOption);
  c->cd(2);
  SetStyle_TCanvas(c);
  h_coil->Draw(DrawOption);
  c->cd(3);
  SetStyle_TCanvas(c);
  h_target->Draw(DrawOption);
  c->cd(4);
  SetStyle_TCanvas(c);
  c->SetLogz(1);
  h_error->Draw(DrawOption);
}

void CreateIronYokeGeometry(double pitch, string ofn_dat)
{
  ofstream f(ofn_dat.c_str());
  double y_edge[2] = {LowerHeight_PoleTip_Tsukuba, InnerHeight_IronYoke_Tsukuba};
  double x_edge[3] = {InnerRadius_PoleTip_Tsukuba,
                      OuterRadius_PoleTip_Tsukuba,
                      InnerRadius_IronYoke_Tsukuba};
  double x = x_edge[0];
  double y = y_edge[0];
  
  while(x<x_edge[1])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      x+=pitch;
    }
  x=x_edge[1];

  while(y<y_edge[1])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      y+=pitch;
    }
  y=y_edge[1];

  while(x<x_edge[2])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      x+=pitch;
    }
  x=x_edge[2];

  while(0. < y)
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      y -= pitch;
    }
  f<<x<<"\t 0."<<endl;

  string destination = " ../../data/";
  mv(ofn_dat, destination);
}

void cb::SetTsukubaSolenoid()
{
  //main coil
  double r_in_main = InnerDiameterOfMainCoil / 2.;
  double r_out_main = OuterDiameterOfMainCoil / 2.;
  double center_r_main = (r_in_main+r_out_main) / 2.;
  double HalfWidth_r_main = (r_out_main - center_r_main) / 2.;
  cb MainCoil;
  MainCoil.SetOnGaussNodes(center_r_main, HalfWidth_r_main,
                           NodeNumberForGaussianQuadrature,
                           0.,FullHeightOfMainCoil/2.,
                           NodeNumberForGaussianQuadrature,
                           CurrentDensityOfMainCoil*1.e4);
  cb::Push_Back(MainCoil);

  //weak focusing coil
  double r_in_weak = InnerDiameterOfWeakFocusingCoil / 2.;
  double r_out_weak = OuterDiameterOfWeakFocusingCoil / 2.;
  double center_r_weak = (r_in_weak+r_out_weak) / 2.;
  double HalfWidth_r_weak = (r_out_weak - center_r_weak) / 2.;
  cb WeakCoil;
  WeakCoil.SetOnGaussNodes(center_r_weak,HalfWidth_r_weak,
                           NodeNumberForGaussianQuadrature,
                           0.,FullHeightOfWeakFocusingCoil/2.,
                           NodeNumberForGaussianQuadrature,
                           CurrentDensityOfWeakFocusingCoil*1.e4);
  cb::Push_Back(WeakCoil);
}


