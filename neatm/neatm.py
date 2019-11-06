# M.Mueller@astro.rug.nl, 2016/09/05+
# Wrapper around my NEATM executable.
# Output will be in mJy (default) or W/m^2/micron.
# LambdaMu can be an array (iterable) or a scalar Quantity;
# output will be a list of Quantitites or a single Quantity, resp.

from __future__ import print_function

def neatm(h,g,alpha,r,delta,lambdaMu,eta,pv, mJy=True):
    import subprocess
    import numpy as np
    from astropy import units as u
    try:
        return [neatm(h,g,alpha,r,delta,wav,eta,pv,mJy=mJy) for wav in lambdaMu]  
    except TypeError:
        pass # TypeError will be thrown if lambdaMu is a scalar; ignore and carry on
    try:
        alpha=alpha.to_value(u.degree)
        r=r.to_value(u.AU)
        delta=delta.to_value(u.AU)
        lambdaMu=lambdaMu.to_value(u.micron)
    except AttributeError:
        print("alpha, r, delta, and lambdaMu must be astropy quantities")
        raise
    except u.UnitConversionError:
        print("Alpha must be an angle; r, delta, and lambdaMu must be (wave-)lengths")
        raise
    cmd=['neatm']
    for var in [h,g,alpha,r,delta,lambdaMu,eta,pv]:
        cmd.append(str(var))
    process=subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, cerr = process.communicate()
    output = output.split()
    if mJy:
        return float(output[1])*u.mJy
    else:
        return float(output[0])*u.Watt/u.meter**2/u.micron
