
#include"../src/include.hpp"
using namespace std;

int NodeNumberForGaussianQuadrature;
int TruncatedEigenmodeNumber;
double pitch_CircularCurrentLoopsOnIronYoke;

double Radius_PoleTip_Tsukuba;
double InnerRadius_IronYoke_Tsukuba;
double LowerHeight_PoleTip_Tsukuba;
double InnerHeight_IronYoke_Tsukuba;

int n_scan_RadialDirection_OPERA;
int n_scan_AxialDirection_OPERA;
double LowerLimit_scan_r_OPERA;
double UpperLimit_scan_r_OPERA;
double UpperLimit_scan_z_OPERA;

void LoadConfigurationFile(string path_ConfigurationFile){
  ifstream InputFile(path_ConfigurationFile.c_str());
  if(InputFile.fail())
    {
      cout << path_ConfigurationFile << " not found" << endl;
      return;
    }
  
  string VariableName, value;
  vector<string> IPs;//input parameters
  puts("--------------------------------");
  cout << "loading input parameters from " << path_ConfigurationFile << endl;
  cout << endl;
  while(InputFile >> VariableName >> value){
    cout << VariableName << " : " << value << endl;
    IPs.push_back(value);
  }
  puts("-------------------------");

  NodeNumberForGaussianQuadrature = stoi(IPs[0]);
  IPs.erase(IPs.begin());
  TruncatedEigenmodeNumber = stoi(IPs[0]);
  IPs.erase(IPs.begin());
  pitch_CircularCurrentLoopsOnIronYoke = stod(IPs[0]);
  IPs.erase(IPs.begin());  

  Radius_PoleTip_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());   
  InnerRadius_IronYoke_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());
  LowerHeight_PoleTip_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin()); 
  InnerHeight_IronYoke_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());

  n_scan_RadialDirection_OPERA = stoi(IPs[0]);
  IPs.erase(IPs.begin());
  n_scan_AxialDirection_OPERA = stoi(IPs[0]);
  IPs.erase(IPs.begin());                                                  
  LowerLimit_scan_r_OPERA = stod(IPs[0]);
  IPs.erase(IPs.begin());
  UpperLimit_scan_r_OPERA = stod(IPs[0]);
  IPs.erase(IPs.begin());
  UpperLimit_scan_z_OPERA = stod(IPs[0]);
  IPs.erase(IPs.begin());

  if(!(IPs.empty())){                     
    int RemainedElements = IPs.size();  
    cout<<"\033[31m"<< RemainedElements; 
    cout<<" global variable(s) have not read yet.\033[m"<<endl;
    puts("Something is wrong...");
  }
}












