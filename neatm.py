# M.Mueller@astro.rug.nl, 2016/09/05
# Wrapper around my NEATM executable.
# Output will be in mJy (default) or W/m^2/micron.
# LambdaMu can be an array or scalar; output will be np.array of floats or a single float.

def neatm(h,g,alpha,r,delta,lambdaMu,eta,pv, mJy=True):
    import subprocess
    import numpy as np
    try:
        result=np.empty(len(lambdaMu)) 
        for i,wavelength in enumerate(lambdaMu):
            result[i]=neatm(h,g,alpha,r,delta,wavelength,eta,pv,mJy=mJy)
        return result
    except TypeError:
        pass # TypeError will be thrown if lambdaMu is a scalar; ignore and carry on
    cmd=['neatm']
    for var in [h,g,alpha,r,delta,lambdaMu,eta,pv]:
        cmd.append(str(var))
    output = subprocess.check_output(cmd)
    output = output.split()
    if mJy:
        return float(output[1])
    else:
        return float(output[0])   
