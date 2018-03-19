// Calculates the flux in watts/m^2/mu at 
// wavelength lambda (in mu)
// according to the NEATM. 

// Nomenclature follows Delbo/Harris 2002.

// Requires integral.cc, integral.h as well as constants.h to be in the same directory.

double neatm(double lambda, double pv, double eta, double H, double G, double alpha, double r, double Delta, double emissivity=.9);
// emissivity=.9 by default, but CAN be changed

double SI2mJy(double SI,    // in W/m^2/mu
			  double lambda // in mu
			  );
// Output in mJy

double mJy2SI(double mJy,   // in mJy (!)
			  double lambda // in mu
			  );
// Output in W/m^2/mu
