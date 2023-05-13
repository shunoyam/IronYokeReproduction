

#include"../../../src/include.hpp"
using namespace std;

Legendre::Legendre(int _degree,int _TrialNumber,double _epsilon)
{
  if(_degree<1)
    {
      cout<<"legendre polynomials of degree "<<_degree<<" is invalid"<<endl;
      return;
    }
  this->degree=_degree;
  this->TrialNumber=_TrialNumber;
  this->epsilon=_epsilon;
  Legendre::SearchNodesAndWeights();  
}

int Legendre::ArgumentCheck(int i)
{
    if(this->degree<=i)
    {
      cout<<i<<"th node is invalid for Legendre polynomials of degree ";
      cout<<this->degree<<endl;
      return 1;
    }
    return 0;
}

double Legendre::node(int i_th)
{
  if(Legendre::ArgumentCheck(i_th))
    {
      return nan("");
    }
  return this->nodes[i_th];
}

double Legendre::weight(int i_th)
{
  if(Legendre::ArgumentCheck(i_th))
    {
      return nan("");
    }
  return this->weights[i_th];
}

vector<double> Legendre::GetNodes()
{
  return this->nodes;
}

vector<double> Legendre::GetWeights()
{
  return this->weights;
}


double Legendre::dif_legendre(double x)
{
  int n=this->degree;
  if(x==1 || x==-1)
    {
      x+=1.e-10;
    }
  double _dif_legendre=n*(legendre_lib(n-1,x)-x*legendre_lib(n,x))/(1-x*x);
  return _dif_legendre;  
}

double Legendre::ZeroPoint(double InitialValue)
{
  int n=this->degree;
  double NextValue;
  for(int i_trial=0;i_trial<this->TrialNumber;i_trial++)
    {
      NextValue=InitialValue-legendre_lib(n,InitialValue)/Legendre::dif_legendre(InitialValue);
      double progress=abs(NextValue-InitialValue);
      if(progress<this->epsilon)
        {
          break;
        }
      InitialValue=NextValue;
      if(i_trial==this->TrialNumber)
        {
          cout<<"Zero point not found in "<<this->TrialNumber<<" trials."<<endl;
        }
    }
  return NextValue;
}

double Legendre::CalcWeight(double x)
{
  double _weight=2.*(1.-(x*x))/pow(this->degree *legendre_lib(this->degree-1,x),2);
  return _weight;
}

void Legendre::SearchNodesAndWeights()
{
  int n=this->degree;
  for(int i_th=0;i_th<n;i_th++)
    {
      double InitialValue=cos(TMath::Pi()*(i_th+0.75)/(n+0.5));
      double _node=ZeroPoint(InitialValue);
      if(abs(_node)<1.e-10)
        {
          _node=0.;
        }
      double _weight=Legendre::CalcWeight(_node);
      this->nodes.push_back(_node);
      this->weights.push_back(_weight);
    }
}




