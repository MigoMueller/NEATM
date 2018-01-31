# M.Mueller@astro.rug.nl, 2016/09/05
# Wrapper around my NEATM executable.
# Output will be in mJy (default) or W/m^2/micron.
# LambdaMu can be an array or scalar; output will be np.array of floats or a single float.

from __future__ import print_function

def neatm(h,g,alpha,r,delta,lambdaMu,eta,pv, mJy=True):
    import subprocess
    import numpy as np
    from astropy import units as u
    try:
        result=np.empty(len(lambdaMu)) 
        for i,wavelength in enumerate(lambdaMu):
            dummy=neatm(h,g,alpha,r,delta,wavelength,eta,pv,mJy=mJy)
            result[i]=dummy.value
            unit=dummy.unit
        return result*unit
        #return np.array([neatm(h,g,alpha,r,delta,wav,eta,pv,mJy=mJy) for wav in lambdaMu])  ## doesn't work nicely with units...
    except TypeError:
        pass # TypeError will be thrown if lambdaMu is a scalar; ignore and carry on
    try:
        alpha=alpha.to(u.degree).value
        r=r.to(u.AU).value
        delta=delta.to(u.AU).value
        lambdaMu=lambdaMu.to(u.micron).value
    except AttributeError:
        print("alpha, r, delta, and lambdaMu must be astropy quantities")
        raise
    except UnitConversionError:
        print("Alpha must be an angle; r, delta, and lambdaMu must be (wave-)lengths")
        raise
    cmd=['neatm']
    for var in [h,g,alpha,r,delta,lambdaMu,eta,pv]:
        cmd.append(str(var))
    output = subprocess.check_output(cmd)
    output = output.split()
    if mJy:
        return float(output[1])*u.mJy
    else:
        return float(output[0])*u.Watt/u.meter**2/u.micron
