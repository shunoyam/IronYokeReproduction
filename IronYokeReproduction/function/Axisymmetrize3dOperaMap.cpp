
//This is based on a macro by Iinuma-san, readMiniSol.C
#include"../src/include.hpp"
using namespace std;

void Axisymmetrize3dOperaMap(string ifn_table, string ofn_dat){
  int n_scan_r = n_scan_RadialDirection_OPERA;
  int n_scan_z = n_scan_AxialDirection_OPERA;
  const char* ofn_ripple="ripple_r10z34_type3.dat";
  FILE *ofile,*infile;

  /////////////read abe Spartial//////
  double posR[3],R,theta;
  double readx0,ready0,readz0,readBx0,readBy0,readBz0;
  double readx,ready,readz,readBx,readBy,readBz;

  TPolyMarker3D *refpoint[12];
  for(int kk=0;kk<12;++kk)
    {
      refpoint[kk]=new TPolyMarker3D(2048*8);
    }

  TH1D *h_theta, *h_r,*h_z;
  h_theta=new TH1D("h_theta","",37,0,360);
  h_r=new TH1D("h_r","",21,0,20);
  h_z=new TH1D("h_z","",71,-35,35);
  TH2D *h_BR,*h_BZ;
  h_BZ=new TH2D("h_BZ","",n_scan_r,0,n_scan_r,n_scan_z,0,n_scan_z);
  h_BR=new TH2D("h_BR","",n_scan_r,0,n_scan_r,n_scan_z,0,n_scan_z);

  double BR[n_scan_r][n_scan_z]={};
  double BZ[n_scan_r][n_scan_z]={};
  vector<vector<vector<double>>> Bz_vec(n_scan_r, vector<vector<double>>(n_scan_z, vector<double>(0)));
  vector<vector<vector<double>>> Br_vec(n_scan_r, vector<vector<double>>(n_scan_z, vector<double>(0)));
  double mapR[n_scan_r],mapZ[n_scan_z];
  int nn[n_scan_r][n_scan_z]={};
  ofstream ripple_r10z34(ofn_ripple);
  ofstream ripple_r10z_34("ripple_r10z_34.dat");
  ofstream ripple_r10z0("ripple_r10z0.dat");
  for(int i=0;i<n_scan_r;++i)mapR[i]=3+1*i;
  for(int i=0;i<n_scan_z;++i)mapZ[i]=-34+1*i;
  char fname[256*2];
  int num=1;
  for(int ii=0;ii<num;++ii)
    {
      if(ii==0)sprintf(fname,ifn_table.c_str());
      infile=fopen(fname,"r");
      //      printf("now is %s\n",fname);
      char lineread[256];
      for(int i=0;i<8;++i)
        {
          fgets(lineread,1024,infile);
          //          printf("%s",lineread);
        }
      int i=0;
      while( fscanf(infile,"   %lf       %lf       %lf       %lf      %lf       %lf    \n",
                    &readx0,&ready0,&readz0,&readBx0,&readBy0,&readBz0)==6)
        {	  
          readx=readx0*-1;
          ready=readz0;
          readz=ready0;
          readBx=readBx0*-1;
          readBy=readBz0;
          readBz=readBy0;
          refpoint[ii]->SetPoint(i,readx,ready,readz);
          R=hypot(readx,ready);
          theta=acos(readx/(double)R);
          if(abs(R-10.)<1.e-10)
            {
              theta=atan2(ready,readx);
              if(readz==34.)
                {
                  ripple_r10z34<<theta<<"\t"<<readBz<<endl;
                }
              if(readz==-34.)
                {
                  ripple_r10z_34<<theta<<"\t"<<readBz<<endl;
                }
              if(readz==0.)
                {
                  ripple_r10z0<<theta<<"\t"<<readBz<<endl;
                }
            }
          theta=acos(readx/(double)R);
          if(ready<=0)theta=TMath::TwoPi()-theta;
          theta=theta*180/TMath::Pi();
          h_r->Fill(R);
          h_theta->Fill(theta);
          h_z->Fill(readz);
          for(int k=0;k<n_scan_r;++k){
            for(int l=0;l<n_scan_z;++l){
              if(pow(R-mapR[k],2)<0.01){
                if(pow(readz-mapZ[l],2)<0.01){
                  BR[k][l]+=(readBx*readx+readBy*ready)/(double)R;
                  BZ[k][l]+=readBz; 
                  nn[k][l]++;
                  Bz_vec[k][l].push_back(readBz);
                  Br_vec[k][l].push_back((readBx*readx+readBy*ready)/(double)R);
                }
              }
            }
          }
          i++;
        }
      // cout<<"i is: "<<i<<endl;
      // cout<<Bz_vec[2][3].size()<<endl;
      //    printf("ii=%d i=%d\n",ii,i);
      fclose(infile);
    }

  for(int i=0;i<n_scan_r;++i)
    {
      for(int j=0;j<n_scan_z;++j)
        {
          double min_Bz=*min_element(Bz_vec[i][j].begin(),Bz_vec[i][j].end());
          double max_Bz=*max_element(Bz_vec[i][j].begin(),Bz_vec[i][j].end());
          double min_Br=*min_element(Br_vec[i][j].begin(),Br_vec[i][j].end());
          double max_Br=*max_element(Br_vec[i][j].begin(),Br_vec[i][j].end());
          double p2p_Bz=(max_Bz-min_Bz);
          BR[i][j]=BR[i][j]/(double)nn[i][j];
          BZ[i][j]=BZ[i][j]/(double)nn[i][j];
          //      printf("nn[%d][%d]=%d BR=%lf BZ=%lf\n",i,j,nn[i][j],BR[i][j],BZ[i][j]);
          h_BR->SetBinContent(i+1,j+1,BR[i][j]);
          h_BZ->SetBinContent(i+1,j+1,BZ[i][j]);
        }
    }

  //write to file
  ofstream OutputFile(ofn_dat.c_str());
  for(int i=0;i<n_scan_z;++i)
    {
      for(int j=0;j<n_scan_r;j++)
        {
          OutputFile << mapR[j] << "\t" << mapZ[i] << "\t";
          OutputFile << BZ[j][i] << "\t" << BR[j][i] << endl;
        }
    }
  // ///////Graph
  // gROOT->SetStyle("Plain");
  // gROOT->ForceStyle();
  // gStyle->SetOptStat(0);
  // gStyle->SetCanvasBorderMode(0);
  // gStyle->SetPadColor(0);
  // gStyle->SetTitleFillColor(0);
  // gStyle->SetStatColor(0);

  // gStyle->SetCanvasBorderMode(0);//remove yellow line
  // gStyle->SetCanvasColor(0);
  // gStyle->SetFrameLineColor(1);
  // gStyle->SetPadColor(0);
  // gStyle->SetTitleFillColor(0);
  // gStyle->SetStatColor(0);
  // //gStyle->SetPalette(52);
  // gStyle->SetPalette(1);

  // TCanvas *c1 = new TCanvas("c1","check",200,100,500,500);
  // c1->SetLeftMargin(0.13);
  // c1->SetRightMargin(0.05);
  // c1->SetBottomMargin(0.10);
  // TH3F *framec1;
  // framec1 = new TH3F("framec1","",1, -45, 45,1, -45, 45, 10,-45,45);
  // framec1->GetXaxis()->SetLabelSize(0.03);
  // framec1->GetXaxis()->SetTitleSize(0.03);
  // framec1->GetYaxis()->SetLabelSize(0.03);
  // framec1->GetYaxis()->SetTitleSize(0.03);
  // framec1->GetZaxis()->SetLabelSize(0.03);
  // framec1->GetZaxis()->SetTitleSize(0.03);
  // framec1->GetXaxis()->SetTitle("x [cm]");
  // framec1->GetYaxis()->SetTitle("y [cm]");
  // framec1->GetZaxis()->SetTitle("z [cm]");
  // framec1->GetXaxis()->SetTitleOffset(1.5);
  // framec1->GetYaxis()->SetTitleOffset(1.5);
  // framec1->GetZaxis()->SetTitleOffset(1.6);
  // framec1->SetStats(0);
  // framec1->Draw();

  // refpoint[0]->SetMarkerStyle(9);
  // refpoint[0]->SetMarkerColor(1);
  // refpoint[0]->Draw("same");

  // TCanvas *c = new TCanvas("check","check",200,100,500,500);
  // c->SetLeftMargin(0.18);
  // c->SetRightMargin(0.23);
  // h_BZ->SetMaximum(90);
  // h_BZ->SetMinimum(20);
  // h_BZ->Draw("colz");

  // c->SetGrid();

  // TCanvas *c0 = new TCanvas("c0","check",200,100,500,500);
  // c0->SetLeftMargin(0.08);
  // c0->SetRightMargin(0.23);
  // TH1F* frame0 = new TH1F("frame0"," ",10, 0, TMath::TwoPi());
  // frame0->SetTitle("");
  // frame0->GetXaxis()->SetLabelSize(0.04);
  // frame0->GetXaxis()->SetTitleSize(0.05);
  // frame0->GetYaxis()->SetLabelSize(0.04);
  // frame0->GetYaxis()->SetTitleSize(0.05);
  // frame0->GetXaxis()->SetTitle("degree");
  // frame0->GetYaxis()->SetTitle("");
  // frame0->GetYaxis()->SetTitleOffset(1.2);
  // frame0->SetStats(0);
  // frame0->Draw();
  // h_theta->Draw("");

  // c0->SetGrid();
  
}


