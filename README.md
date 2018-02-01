# NEATM
Asteroid thermal emission following the Near-Earth Asteroid Thermal Model (NEATM, Harris 1998, http://dx.doi.org/10.1006/icar.1997.5865)

## Installation:
Run 'make' in this directory.  Move the resulting binary (neatm) to a directory within your $PATH.
'make clean' will remove temporary files (*.o).
Running the binary from the command line should be reasonably self explanatory.

A Python wrapper (neatm.py) is also provided.  All input is provided as scalar float (wavelengths may be iterable).  Values that carry physical units (r, delta, alpha, lambda, output flux) use astropy.units.  The wrapper calls the C++ binary under the hood.

## Disclaimer:
Most of this code was written during the first year of my PhD, ~15 years ago.  There's a number of things I'd do or word differently if I were to redo this from scratch.  On the flip-side, the code has been tested really extensively.  It works.

## Change log:
* 2018/01/31: experimental astropy.units support on 'units' branch
* 2018/01/31: Original release
