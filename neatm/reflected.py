# M.Mueller@astro.rug.nl
# 2019/11/06

from astropy import units as u

def reflected( h,g,alpha,r,delta,wavelengths, relativeReflectance=1 ):
    """
    Calculate amount of sunlight reflected by an asteroid.
    Assumes flat reflectance across output wavelengths and a 
    user-provided relative reflectance between output wavelengths and V band.
    The Sun is assumed to be a T=5,800K black body with a 3.6-micron flux of
    5.5464e16 mJy (Gueymard, 2004, Solar Energy 76, 423--453).
    The Vmag of the Sun is assumed to be -26.74.
    alpha, r, delta, and wavelengths must be astropy Quantities,
    calculated flux will be output as (list of) astropy Quantities (in mJy).
    """
    v = vmag( h,g,r,delta,alpha )
    f36 = mjy36( v, relativeReflectance=relativeReflectance )
    flux = scale_reflected( wavelengths, f36 )
    return flux



### Aux functions below


import math
from astropy import units as u

def scale_reflected( wavelengths, flux36 ):
    """
    Scale flux from 3.6 micron, assuming a T=5,800K black-body.
    Aux function in the modeling of sunlight reflected by asteroids.
    """
    try :
        isIterable = True
        for wav in wavelengths :
            pass
    except TypeError :
        isIterable = False
    if isIterable :
        # wavelengths is iterable:
        return [scale_reflected( wav, flux36 ) for wav in wavelengths]  
    # wavelengths is a scalar:
    try :
        f36 = flux36.to_value( u.mJy )
        lambdaMu = wavelengths.to_value( u.micron )
    except AttributeError :
        print( 'Wavelengths and flux36 must be astropy Quantities.')
        print( '(wavelengths may be iterable over Quantities)')
        raise
    except u.UnitConversionError :
        print( 'Wavelenths must have length units, flux36 must be flux density per frequency' )
        raise
    Tsun = 5800  # assumed solar black-body temperature in K
    hck  = 14388 # hc/k in units of micron*Kelvin
    return flux36 * (3.6/lambdaMu)**3 * (math.exp(hck/3.6/Tsun)-1)/(math.exp(hck/lambdaMu/Tsun)-1)
    

def mjy36( V, relativeReflectance=1 ):
    """
    Scale solar spectrum at 3.6 micron to given Vmag, 
    assuming Solar V=-26.74.
    Solar flux at 3.6 micron: 5.5464e16 mJy (Gueymard, 2004).
    """
    return relativeReflectance * 5.5464e16*u.mJy * 10**(-(V+26.74)/2.5)


def HG_W( alpha ):
    """ Aux function used by vmag """
    return math.exp( -90.56*( math.tan(alpha*0.5))**2)

def HG_phi1( alpha ):
    """ Aux function used by vmag """
    return HG_W(alpha)* (1- (.986*math.sin(alpha))/(.119+1.341*math.sin(alpha)-.754*math.sin(alpha)**2) )  +   (1-HG_W(alpha))*math.exp(-3.332 * (math.tan(alpha*0.5))**0.631)

def HG_phi2( alpha ):
    """ Aux function used by vmag """
    return HG_W(alpha)* (1- (.238*math.sin(alpha))/(.119+1.341*math.sin(alpha)-.754*math.sin(alpha)**2) )  +   (1-HG_W(alpha))*math.exp(-1.862 * (math.tan(alpha*0.5))**1.218)


def vmag( H, G, r, delta, alpha ):
    """ 
    Returns V magnitude according to the HG system by
    Bowell et al. (1989).
    R, delta, and alpha must be appropriate astropy Quantities.
    """
    try:
        aRad=alpha.to_value(u.rad)
        rAU =r.to_value(u.AU)
        deltaAU=delta.to_value(u.AU)
    except AttributeError:
        print("R, delta, and alpha must be astropy Quantities")
        raise
    except u.UnitConversionError:
        print("Alpha must be an angle; r and delta must be lengths")
        raise
    return H + 5*math.log10(rAU*deltaAU) - 2.5*math.log10( (1-G)*HG_phi1(aRad)+G*(HG_phi2(aRad)))
