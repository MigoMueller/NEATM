// some natural constants in SI-units

const double h=6.6260755e-34;  // Js
const double c=2.99792458e8;   // m/s
const double k=1.380658e-23;   // J/K
const double solar=1367;       // W/m^2 // Thuillier et al. (2004)
const double sigma=5.67e-8;    // W/m^2/K^4
const double AU=149597870.691; // AU->km
const double degrees=3.14159265358979/180.;  //degrees->rad

// derived constants in practical units

const double solar_over_stefan_boltzmann=solar/sigma; // in K^4
const double hck=1e6*h*c/k;    // mu*K
const double hc2=1e24*h*c*c;   // in W/(m^2 mu)*(mu)^5
// note: will be divided by lambda^5 (in mu)


// Asteroid-specific

//const double G=.15; // slope parameter
// make G a variable
double q(double G){ return (.29+.684*G);}// phase integral
