// Provide a NEATM flux value for a given wavelength
// Michael.Mueller@as.arizona.edu
// 2008 May 29

#include<iostream>
#include<fstream>
#include<cmath> 
#include<cstdlib>
#include "neatm_input_file.h"
#include<sstream>
#include"neatm.h" // taken over without any changes
using namespace std;


int main(int nargs, char *args[])
{
  double H, G, emissivity, alpha, r, delta, eta, pv;
  double lambda;
  vector<double> input_flux, input_sigma; 
  string inname, outname;
  emissivity = 0.9; //BAUSTELLE: make that variable, somehow!
	
  switch (nargs)
    {
    case 5:
      { // make objects in and input temporary
	ifstream in(args[1]);
	if (!in)
	  {
	    cerr<<"Couldn't open "<<args[1]<<" for reading!"<<endl;
	    return -1;
	  };
	NEATM_input_file input(args[1]);
	H = input.getH();
	G = input.getG();
	alpha = input.getAlpha();
	delta = input.getDelta();
	r     = input.getR();
      }
      lambda  = atof(args[2]);
      eta     = atof(args[3]);
      pv      = atof(args[4]);
      break;

    case 9:
      H = atof(args[1]);
      G = atof(args[2]);
      alpha = atof(args[3]);
      r     = atof(args[4]);
      delta = atof(args[5]);
      lambda  = atof(args[6]);
      eta     = atof(args[7]);
      pv      = atof(args[8]);
      break;	
  
    default:
      cerr<<"Wrong number of command line arguments!\n"
	  <<"Please provide four or eight arguments:\n"
	  <<"Four arguments:\n"
	  <<"1. NEATM parameter file name\n"
	  <<"2. lambda (micron)\n"
	  <<"3. eta\n"
	  <<"4. pV\n"
	  <<"Eight arguments:\n"
	  <<"1. H\n"
	  <<"2. G\n"
	  <<"3. alpha (deg)\n"
	  <<"4. r (AU)\n"
	  <<"5. delta (AU)\n"
	  <<"6. lambda (micron)\n"
	  <<"7. eta\n"
	  <<"8. pV"
	  <<endl;
      return -1;
    }; // switch (nargs)

  double flux=neatm(lambda, pv, eta, H, G, alpha, r, delta, emissivity);
  cerr<<"NEATM flux for stated parms:\n"
      <<"parm file "<<args[1]<<", lambda "<<lambda
      <<", eta "<<eta<<", pV "<<pv<<'\n'
      <<"First line: W/m^2/micron; second line: mJy"<<endl;
  cout<<flux<<'\n'<<SI2mJy(flux, lambda)<<endl;
  return 0;
}
