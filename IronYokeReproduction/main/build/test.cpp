
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<vector>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<numeric>
#include<string.h>
#include<boost/version.hpp>
using namespace std;

void test(){
  auto h= new TH2D("h", "title; x; y", 100, -1, 1, 100, -1, 1);
  auto r = new TRandom2();
  for(int i=0;i<1e4; i++){
    double x = r->Gaus(0., .1);
    double y = r->Gaus(0., .1);
    h->Fill(x, y);
  }
  auto c=new TCanvas("c", "c");
  c->Draw();
  h -> Draw("colz");
  auto f= new TFile("test.root", "recreate");
  c ->Write();
  f -> Close();
}
