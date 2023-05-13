
#ifndef _IN_LEGENDRE
#define _IN_LEGENDRE

#include"../../../src/include.hpp"
using namespace std;

class Legendre
{
private:
  int degree;
  vector<double> nodes;
  vector<double> weights;
  int TrialNumber;
  double epsilon;
public:
  Legendre(int _degree,int _TrialNumber=50,double epsilon=1.e-15);
  int ArgumentCheck(int i);
  double node(int i_th);
  double weight(int i_th);
  vector<double> GetNodes();
  vector<double> GetWeights();
  double dif_legendre(double x);
  double ZeroPoint(double InitialValue);
  double CalcWeight(double x);
  void SearchNodesAndWeights();
};


#endif
