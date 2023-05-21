

#include"../src/include.hpp"
using namespace std;
using namespace ROOT::Math;

double elliptic_integral_1(double k);

double elliptic_integral_2(double k);

double Average(vector<double> elements);
// for uniformity calculation 

double P2P(vector<double> elements);
// for uniformity calculation 

double StdDev(vector<double> elements);

void OutputElapsedTime(clock_t start,const char* ofn);

void rm(const char* filename);

void dl(int length=1);

vector<double> eigen_vec(Eigen::VectorXd vector);

XYZVector TVector3_XYZVector(TVector3 vector);

TVector3 XYZVector_TVector3(XYZVector vector);

void SetStyle_TH2D(TH2D* hist,double factor_xz=1.);

void SetStyle_TH2Ds(TH2D* h1=0,TH2D* h2=0,TH2D* h3=0,TH2D* h4=0,TH2D* h5=0,TH2D* h6=0);

void SetStyle_TCanvas(TCanvas* canvas);

void mv(string fn_old,string fn_new);

double ellint_3_lib(double m,double alpha,double phase);

double elslint_1_lib(double m,double phase);



