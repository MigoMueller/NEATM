#include<iostream>
#include<cmath>
using namespace std;

double EPS;
int POINTS; // visible for all functions contained here

double rekursiv(double (*f)(double x), const double &a, const double &fa, const double &b, const double &fb, const double &alt, const double &h, const double &limit){
  //&a: call per reference
  // a is NOT copied, space (and time) is saved (not too much...)

  double mitte=(a+b)/2.;
  double fmitte=f(mitte);
  double links=h*(fa+fmitte);
  double rechts=h*(fmitte+fb);
  double ratio=fabs(1-(alt/(links+rechts)));

  if (ratio<EPS) // accuracy goal reached
    {
      //cerr<<"accuracy goal reached at a="<<a<<"."<<endl;
      return(links+rechts);}
  else {
    if (fabs(links+rechts-alt)<limit) // contribution marginal
      {
	//cerr<<"marginal contribution encountered at a= "<<a<<"."<<endl;
	return(links+rechts);
      }
    else{ // go ahead by splitting interval
//       cerr<<a<<"  "<<fa<<"  "<<endl;
//       cerr<<mitte<<"  "<<fmitte<<"  "<<endl;
//       cerr<<b<<"  "<<fb<<"  "<<endl;
//       cerr<<"alt= "<<alt<<endl;
//       cerr<<"neu= "<<links<<"+"<<rechts<<"="<<links+rechts<<endl;
//       cerr<<"ratio= "<<ratio<<endl<<endl;
    
      return(rekursiv(f,a,fa,mitte,fmitte,links,h/2.,limit/2.)
	     + rekursiv(f,mitte,fmitte,b,fb,rechts,h/2.,limit/2.));
    }
  }
  cerr<<"Houston, we have a problem!!!"<<endl;
  // never get here, anyway
} /* rekursiv */


// **************************************************
// *           new function ahead!                  *
// **************************************************

double integral(double (*integrand)(double x), const double a, const double b, const double eps, const int points, double *crude){
  EPS=eps; 
  POINTS=points; // visible to rekursiv

  double h=(b-a)/(POINTS+1); // step width for crude
  double *y;
  y=new double [points+2]; // POINTS inner ones + 2@boundary
  for(int i=0;i<=(POINTS+1);i++)
    y[i]=integrand(a+h*i);

  double *F;
	F=new double [POINTS+1]; // partial integrals
  *crude=0; // sum thereof
  {
	  for(int i=0;i<=POINTS;i++) {
		F[i]=(y[i]+y[i+1])*h/2.;
		*crude+=F[i];
	  }
  }

  double errorlimit=fabs(*crude*EPS/3.);
  // half a order of magnitude "Knautschzone"

  double result=0;
  {
	  for (int i=0; i<=POINTS;i++){
		  result+= rekursiv(integrand,a+i*h,y[i],a+(i+1)*h,y[i+1],F[i],h/4., errorlimit/(POINTS+1));
	  }
  }
  //plot: each trapez-estimate is put into the recursive routine
  //together with the corresponding interval; the results are summed up.

	delete [] y;
	delete [] F;
	return result;

} /* integral */
