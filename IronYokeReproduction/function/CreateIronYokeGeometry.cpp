
#include"../src/include.hpp"
using namespace std;


void CreateIronYokeGeometry(string ifn_txt, string ofn_dat){
  double pitch = pitch_CircularCurrentLoopsOnIronYoke;
  vector<double> x_edge(2);
  vector<double> y_edge(2);
  ifstream InputFile(ifn_txt.c_str());
  if(InputFile.fail()){
    cout << ifn_txt << " not found" << endl;
  }
  string FirstLine;
  getline(InputFile, FirstLine);
  InputFile >> x_edge[0] >> x_edge[1] >> y_edge[0] >> y_edge[1];


  ofstream f(ofn_dat.c_str());
  f << " r [m]\t z [m]" << endl;
  double x = 0.;
  double y = y_edge[0];

  while(x<x_edge[0])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      x+=pitch;
    }
  x=x_edge[0];

  while(y<y_edge[1])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      y+=pitch;
    }
  y=y_edge[1];

  while(x<x_edge[1])
    {
      f<<fixed<<setprecision(15)<<x<<"\t"<<y<<endl;
      f<<fixed<<setprecision(15)<<x<<"\t"<<-y<<endl;
      x+=pitch;
    }
  x=x_edge[1];

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
