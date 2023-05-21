
#include"../src/include.hpp"
using namespace std;

void DrawMagneticField_TsukubaSolenoid(coils FLCs_IronYoke, coils Coil, TCanvas* c,
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

  Bs B_reproduce = B_all;
  B_reproduce.clear();
  B_reproduce.add_coil(FLCs_IronYoke);
  auto bz_list_reproduce = (vector<double>)B_reproduce;

  Bs B_error = B_target;
  B_error.subtract(FLCs_IronYoke);
  auto bz_list_error = (vector<double>)B_error;

  double r_in = LowerLimit_scan_r_OPERA;
  double r_out = UpperLimit_scan_r_OPERA;
  double z_out = UpperLimit_scan_z_OPERA;
  int mesh_r = n_scan_RadialDirection_OPERA;
  int mesh_z = n_scan_AxialDirection_OPERA;

  double r_width = (r_out-r_in) / 2.;
  double r_margin = r_width / (double)mesh_r;
  double z_margin = z_out / (double)mesh_z;
  auto h_all = new TH2D("h_all",
                        "B_{all} [Gauss];x [cm];z [cm]",
                        mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                        mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);
  auto h_coil = new TH2D("h_coil",
                         "B_{coil} [Gauss];x [cm];z [cm]",
                         mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                         mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);
  auto h_target = new TH2D("h_target",
                           "B_{target} = B_{yoke} = B_{all} - B_{coil}[Gauss];x [cm];z [cm]",
                           mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                           mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);

  auto h_reproduce = new TH2D("h_reproduce",
                           "B_{reproduce} [Gauss];x [cm];z [cm]",
                           mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                           mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);

  auto h_error = new TH2D("h_error",
                          "B_{error} = B_{target} - B_{reproduce} [Gauss];x [cm];z [cm]",
                          mesh_r, (r_in-r_margin)*100., (r_out+r_margin)*100.,
                          mesh_z, (-z_out-z_margin)*100., (z_out+z_margin)*100.);

  SetStyle_TH2Ds(h_all, h_coil, h_target, h_reproduce, h_error);

  int n_MFEP = B_all.MFEPs();
  for(int i_MFEP=0; i_MFEP<n_MFEP ;i_MFEP++){
    double r = B_all.at(i_MFEP).MFEP().x();
    double z = B_all.at(i_MFEP).MFEP().z();
    h_all -> Fill(r*100., z*100., bz_list_all[i_MFEP]*1.e4);
    h_coil -> Fill(r*100., z*100., bz_list_coil[i_MFEP]*1.e4);
    h_target -> Fill(r*100., z*100., bz_list_target[i_MFEP]*1.e4);
    h_reproduce -> Fill(r*100., z*100., bz_list_reproduce[i_MFEP]*1.e4);
    h_error -> Fill(r*100., z*100., abs(bz_list_error[i_MFEP])*1.e4);
  }

  const char* DrawOption = "colz";
  c->Divide(5, 1);
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
  h_reproduce->Draw(DrawOption);
  c->cd(5);
  SetStyle_TCanvas(c);
  c->SetLogz(1);
  h_error->Draw(DrawOption);
}

