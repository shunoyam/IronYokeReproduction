

#include"../src/include.hpp"
using namespace std;
using namespace ROOT::Math;

double elliptic_integral_1(double k)
{

  double kk=1.-k;
  double logkk=log(kk);
  double integral=0.,k1,k2;
  for(int i=0;i<11;i++)
    {
      k1=coefficient_elliptical_c[i]*pow(kk,i);
      integral+=k1;
      k2=logkk*coefficient_elliptical_d[i]*pow(kk,i);
      integral-=k2;
    }
  return integral;
}

double elliptic_integral_2(double k)
{
  double kk=1.-k;
  double logkk=log(kk);
  double integral=1.,e1,e2;
  for(int i=0;i<10;i++)
    {
      e1=coefficient_elliptical_a[i]*pow(kk,i+1);
      integral+=e1;
      e2=logkk*coefficient_elliptical_b[i]*pow(kk,i+1);
      integral-=e2;
    }
  return integral;
}

double Average(vector<double> elements)
{
  double ave=accumulate(elements.begin(),elements.end(),(double)0);
  int n_element=elements.size();
  ave/=n_element;
  return ave;
}

double P2P(vector<double> elements)
{
  double min=*min_element(elements.begin(), elements.end());
  double max=*max_element(elements.begin(), elements.end());
  double p2p=max-min;
  return p2p;
}

double StdDev(vector<double> elements)
{
  double variance;
  double element;
  double average=Average(elements);
  vector<double> variance_vec;
  double i_variance;
  int n_element=elements.size();
  for(int i_element=0;i_element<n_element;i_element++)
    {
      element=elements[i_element];
      i_variance=pow(element-average,2);
      variance_vec.push_back(i_variance);
    }
  variance=Average(variance_vec);
  double sd=sqrt(variance);
  return sd;
}

vector<double> eigen_vec(VectorXd vector_eigen)
{
  vector<double> vector_vec;
  double element;
  for(int i=0;i<vector_eigen.rows();i++)
    {
      element=vector_eigen(i);
      vector_vec.push_back(element);
    }
  return vector_vec;
}

void OutputElapsedTime(clock_t start,const char* ofn)
{
  double unit_minute=60.;
  double unit_hour=unit_minute*60.;
  double unit_day=unit_hour*24.;
  clock_t end=clock();
  double duration=(double)(end-start)/CLOCKS_PER_SEC;
  int day=trunc(duration/unit_day);
  int hour=trunc((duration-day*unit_day)/unit_hour);
  int minute=trunc((duration-day*unit_day-hour*unit_hour)/unit_minute);
  int second=trunc(duration-day*unit_day-hour*unit_hour-minute*unit_minute);
  ofstream file_out;
  file_out.open(ofn,ios_base::app);
  file_out<<day<<"[d] "<<hour<<"[h] "<<minute<<"[m] "<<second<<"[s] have passed."<<endl;
}

void rm(const char* filename)
{
  string rm="rm ";
  string command=rm+filename;
  int result=system(command.c_str());
}

void dl(int length)
{
  for(int i_length=0;i_length<length;i_length++)
    {
      cout<<"-----------------";
    }
  cout<<endl;
}

XYZVector TVector3_XYZVector(TVector3 vector)
{
  XYZVector vector_XYZ(vector.x(),vector.y(),vector.z());
  return vector_XYZ;
}

TVector3 XYZVector_TVector3(XYZVector vector)
{
  TVector3 vector_TVector3(vector.x(),vector.y(),vector.z());
  return vector_TVector3;
}

void SetStyle_TH2D(TH2D* hist,double factor_xz)
{
  if(hist)
    {
      int fontid=42;
      gStyle->SetPalette(55);
      gStyle->SetStatFont(fontid);
      gStyle->SetLabelFont(fontid,"XYZ");
      gStyle->SetLabelFont(fontid,"");
      gStyle->SetTitleFont(fontid,"XYZ");
      gStyle->SetTitleFont(fontid,"");
      gStyle->SetTextFont(fontid);
      gStyle->SetLegendFont(fontid);  
      double size_font=.07;
      double title_offset_x=.55;
      int option_stat=0;
      auto st=(TPaveStats*)hist->FindObject("stats");
      hist->GetXaxis()->SetLabelSize(size_font*factor_xz);
      hist->GetXaxis()->SetTitleSize(size_font*factor_xz);
      hist->GetXaxis()->SetTitleOffset(title_offset_x);
      hist->GetXaxis()->SetLabelOffset(-.02);
      hist->GetXaxis()->CenterTitle();
      hist->GetYaxis()->SetLabelSize(size_font);
      hist->GetYaxis()->SetTitleSize(size_font);
      hist->GetYaxis()->SetTitleOffset(.8);
      hist->GetYaxis()->CenterTitle();
      hist->GetZaxis()->SetLabelSize(size_font/1.2);
      hist->SetStats(option_stat);
      hist->SetLineWidth(2);
      //      hist->SetTitleFontSize(3.2);//.8
    }
}

void SetStyle_TH2Ds(TH2D* h1,TH2D* h2,TH2D* h3,TH2D* h4,TH2D* h5,TH2D* h6)
{
  SetStyle_TH2D(h1);
  SetStyle_TH2D(h2);
  SetStyle_TH2D(h3);
  SetStyle_TH2D(h4);
  SetStyle_TH2D(h5);
  SetStyle_TH2D(h6);
}

void SetStyle_TCanvas(TCanvas* canvas)
{
  gPad->SetLeftMargin(.13);
  gPad->SetRightMargin(.13);
  gPad->SetTopMargin(0.1);
  gPad->SetBottomMargin(0.1);
  gPad->Update();
}

void mv(string fn_old, string fn_new)
{
  string fn_old_str=fn_old;
  string fn_new_str=fn_new;
  string ShellCommand="mv "+fn_old_str+" "+fn_new;
  int AbnormalTermination=system(ShellCommand.c_str());
  if(AbnormalTermination)
    {
      cout<<fn_old<<" was not found"<<endl;
    }
}
