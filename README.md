# NEATM
Asteroid thermal emission following the Near-Earth Asteroid Thermal Model (NEATM, Harris 1998, http://dx.doi.org/10.1006/icar.1997.5865)

## Installation:
Run 'make' in this directory.  Move the resulting binary (neatm) to a directory within your $PATH.
'make clean' will remove temporary files (*.o).
Running the binary from the command line should be reasonably self explanatory.

A Python wrapper (neatm.py) is also provided.  All input is provided as scalar float (wavelengths may be iterable) in customary units: r and delta in AU, alpha in degree, wavelengths in micron.  It will call the C++ binary under the hood.

## Disclaimer:
Most of this code was written during the first year of my PhD, ~15 years ago.  It may not be the most elegant or numerical efficient code ever, but it sure has been tested extensively.  Think of it as a Soyuz...

## Change log:
2018/01/31: experimental astropy.units support on 'units' branch
2018/01/31: Original release
