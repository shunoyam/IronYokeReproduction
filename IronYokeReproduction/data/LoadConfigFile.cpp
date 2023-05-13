
#include"../src/include.hpp"
using namespace std;

double InnerDiameterOfMainCoil;
double OuterDiameterOfMainCoil;
double HeightOfMainCoil;
double CurrentDensityOfMainCoil;

double InnerDiameterOfWeakFocusingCoil;
double OuterDiameterOfWeakFocusingCoil;
double HeightOfWeakFocusingCoil;
double CurrentDensityOfWeakFocusingCoil;

int NodeNumberForGaussianQuadrature;
int TruncatedEigenmodeNumber;
double ArrangedPitch_FilamentLoopCoil;

double InnerRadius_PoleTip_Tsukuba;
double OuterRadius_PoleTip_Tsukuba;
double InnerRadius_IronYoke_Tsukuba;
double LowerHeight_PoleTip_Tsukuba;
double InnerHeight_IronYoke_Tsukuba;

double n_scan_RadialDirection_OPERA;
double n_scan_AxialDirection_OPERA;                                                  

void LoadConfigFile(string path_ConfigurationFile){
  ifstream InputFile(path_ConfigurationFile.c_str());
  if(InputFile.fail())
    {
      cout << path_ConfigurationFile << "not found" << endl;
      return;
    }
  
  string VariableName, value;
  vector<string> IPs;//input parameters
  puts("loading input parameters");
  while(InputFile >> VariableName >> value){
    cout << VariableName << " : " << value << endl;
    IPs.push_back(value);
  }
  puts("-------------------------");
  InnerDiameterOfMainCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  OuterDiameterOfMainCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  HeightOfMainCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  CurrentDensityOfMainCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());

  InnerDiameterOfWeakFocusingCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  OuterDiameterOfWeakFocusingCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  HeightOfWeakFocusingCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());
  CurrentDensityOfWeakFocusingCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());

  NodeNumberForGaussianQuadrature = stoi(IPs[0]);
  IPs.erase(IPs.begin());
  TruncatedEigenmodeNumber = stoi(IPs[0]);
  IPs.erase(IPs.begin());
  ArrangedPitch_FilamentLoopCoil = stod(IPs[0]);
  IPs.erase(IPs.begin());  

  InnerRadius_PoleTip_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin()); 
  OuterRadius_PoleTip_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());   
  InnerRadius_IronYoke_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());
  LowerHeight_PoleTip_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin()); 
  InnerHeight_IronYoke_Tsukuba = stod(IPs[0]);
  IPs.erase(IPs.begin());

  n_scan_RadialDirection_OPERA = stod(IPs[0]);
  IPs.erase(IPs.begin());
  n_scan_AxialDirection_OPERA = stod(IPs[0]);
  IPs.erase(IPs.begin());                                                  

  if(!(IPs.empty())){                     
    int RemainedElements = IPs.size();  
    cout<<"\033[31m"<< RemainedElements; 
    cout<<" global variable(s) have not read yet.\033[m"<<endl;
    puts("Something is wrong...");
  }
}












