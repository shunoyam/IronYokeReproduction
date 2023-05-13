

#include"../src/include.hpp"
using namespace std;

void HoleStudy()
{
  ConsistencyCheck("../config/type1.dat",
                   "max_current_type.dat",
                   "decreasing_error_type.dat",
                   "ReproducedMagneticField_type1.root");
  mv("IronYoke_distribution.dat","IronYoke_distribution_type1.dat");
  mv("tmp_mode.dat","mode_type1.dat");

  // ConsistencyCheck("../config/type2.dat",
  //                  "max_current_type.dat",
  //                  "decreasing_error_type.dat",
  //                  "ReproducedMagneticField_type2.root");
  // mv("IronYoke_distribution.dat","IronYoke_distribution_type2.dat");
  // mv("tmp_mode.dat","mode_type2.dat");

  // ConsistencyCheck("../config/type3.dat",
  //                  "max_current_type.dat",
  //                  "decreasing_error_type.dat",
  //                  "ReproducedMagneticField_type3.root");
  // mv("IronYoke_distribution.dat","IronYoke_distribution_type3.dat");
  // mv("tmp_mode.dat","mode_type3.dat");


}

void hole_3mode()
{
  const char* ofn_root="hole_3rd.root";
  double r_in=0.05;
  double r_out=0.18;
  double r_center=(r_out+r_in)/2.;
  double r_width=(r_out-r_in)/2.;
  double height=0.68;
  int mesh_r=14;
  int mesh_z=69;
  Bs B1;
  B1.read("../config/type1.dat");
  Bs B2;
  B2.read("../config/type2.dat");
  Bs B_hole;
  B_hole.read("../config/type2.dat");
  B_hole.addBs(B1,B2,1.,-1.);
  auto h_hole=new TH2D("h_hole",
                       "B-field contribution by hole [Gauss];x[cm];z[cm]",
                       mesh_r,r_in*100.,r_out*100.,
                       mesh_z,-height*100./2.,height*100./2.);
  auto h_3=new TH2D("h_3",
                    "B-field contribution by 3rd mode [Gauss];x[cm];z[cm]",
                    mesh_r,r_in*100.,r_out*100.,
                    mesh_z,-height*100./2.,height*100./2.);
  read_hole(h_hole,B_hole);
  read_3rd_mode(h_3,B_hole);
  auto c=new TCanvas("c","c");
  c->Divide(2,2);
  SetStyle_TCanvas(c);
  c->cd(1);
  h_hole->Draw("colz");
  c->cd(2);
  h_3->Draw("colz");
  auto f=new TFile(ofn_root,"recreate");
  c->Write();
  f->Close();
  delete f;
  delete c;
  delete h_hole;
  delete h_3;
}

static void read_hole(TH2D* h,Bs B_hole)
{
  SetStyle_TH2D(h);
  for(int i=0;i<B_hole.MFEPs();i++)
    {
      double x=B_hole.at(i).MFEP().x();
      double z=B_hole.at(i).MFEP().z();
      double bz=B_hole.at(i).Bz();
      h->Fill(x*1.e2,z*1.e2,bz*1.e4);
    }
  ArrangeRange(h);
}

static void read_3rd_mode(TH2D* h,Bs B)
{
  ifstream ifn("kore.dat");
  if(ifn.fail())
    {
      puts("mode data was not found");
      return;
    }
  double bz;
  string line;
  vector<double> bz_vec;
  for(int row=0;getline(ifn,line);++row)
    {
      istringstream stream(line);
      for(int col=0;stream>>bz;col++)
        {
          bz_vec.push_back(bz);
        }
    }
  if(bz_vec.size()!=B.MFEPs())
    {
      puts("size is different");
      return;
    }
  SetStyle_TH2D(h);
  for(int i=0;i<bz_vec.size();i++)
    {
      h->Fill(B.at(i).MFEP().x()*1.e2,B.at(i).MFEP().z()*1.e2,bz_vec[i]*1.e4);
    }
  ArrangeRange(h);
}



