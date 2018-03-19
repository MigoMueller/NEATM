#include<cmath>
#include"integral.h"
#include"constants.h"

const double PI=3.141;
// must not be TOO good a value (cut-off!)

const double relative_precision=.001;
const int inner_points=10;
// should be fine enough

double PHI, lambdaT0, phase_angle; // crude possibility to mask them from inner integrand


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  pure integrand without prefactors including angular factors
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
inline double Planck(double phi,double theta){
  double cphi=cos(phi);
  double ctheta=cos(theta);
  return (cphi*cphi*ctheta/(exp(hck/(lambdaT0*sqrt(sqrt(cos(theta+phase_angle)*cphi))))-1.));
}

double inner_integrand(double theta){
  return (Planck(PHI,theta));
} /* inner_integrand */

double inner_integral(double phi){
  double estimate;
  PHI=phi;
  double result=integral(inner_integrand,-PI/2,PI/2-phase_angle,relative_precision,inner_points,&estimate);
  // if (estimate >> result)...
  
  return (result);
} /* inner_integral */


// !!!!!!!!!!!!!!!!!!!!!
// !       neatm       !
// !!!!!!!!!!!!!!!!!!!!!

double neatm(double lambda, double pv, double eta, double H, double G, double alpha, double r, double Delta, double emissivity=.9){

  double estimate;
  double flux;

  phase_angle=degrees*alpha;// "global", in radiants

  double D=1329*exp(-H*log(10.)/5.)/sqrt(pv); // 10^{-H/5}
  lambdaT0=lambda*sqrt(sqrt((1.-q(G)*pv)*solar_over_stefan_boltzmann/(r*r*eta*emissivity)));

  flux=integral(inner_integral,0,PI/2,relative_precision,inner_points,&estimate); // not normalized, yet

  double dummy=D/(AU*Delta*lambda*lambda);
  // will be squared, gives parts of lambda^5

  flux*=dummy*dummy/lambda*emissivity*hc2;

  return(flux);

} /* neatm */


double SI2mJy(double SI, double lambda)
{
	return SI/(2.99792458e-15/lambda/lambda);
};

double mJy2SI(double mJy, double lambda)
{
	return mJy*2.99792458e-15/lambda/lambda;
};
