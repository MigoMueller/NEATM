# M.Mueller@astro.rug.nl
# 2019/11/06

from astropy import units as u
import numpy as np

def reflected( h,g,alpha,r,delta,wavelengths, relativeReflectance=1 ):
    """
    Calculate amount of sunlight reflected by an asteroid.
    Assumes flat reflectance across output wavelengths and a 
    user-provided relative reflectance between output wavelengths and V band.
    The Sun is assumed to be a T=5,800K black body with a 3.6-micron flux of
    5.5464e16 mJy (Gueymard, 2004, Solar Energy 76, 423--453).
    The Vmag of the Sun is assumed to be -26.74.
    alpha, r, delta, and wavelengths must be astropy Quantities,
    calculated flux will be output as astropy Quantity (in mJy).
    Wavelengths can be a scalar or an iterable; in the latter case, 
    output is a list of mJy Quantities.
    """
    v = vmag( h,g,r,delta,alpha )
    f36 = mjy36( v, relativeReflectance=relativeReflectance )
    flux = scale_reflected( wavelengths, f36 )
    return flux


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
    return H + 5*np.log10(rAU*deltaAU) - 2.5*np.log10( (1-G)*HG_phi1(aRad)+G*(HG_phi2(aRad)))



### Aux functions below

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
    try :
        if isIterable :
            lambdaMu = np.array([wav.to_value(u.micron) for wav in wavelengths])
        else :
            lambdaMu = wavelengths.to_value( u.micron )
        f36 = flux36.to_value( u.mJy )
    except AttributeError :
        print( 'Wavelengths and flux36 must be astropy Quantities.')
        print( '(wavelengths may be iterable over Quantities)')
        raise
    except u.UnitConversionError :
        print( 'Wavelenths must have length units, flux36 must be flux density per frequency' )
        raise
    Tsun = 5800  # assumed solar black-body temperature in K
    hck  = 14388 # hc/k in units of micron*Kelvin
    numerator = 0.9918830742423241 # = np.exp(hck/3.6/Tsun)-1
    return flux36 * (3.6/lambdaMu)**3 * (numerator)/(np.exp(hck/lambdaMu/Tsun)-1)
    

def mjy36( V, relativeReflectance=1 ):
    """
    Scale solar spectrum at 3.6 micron to given Vmag, 
    assuming Solar V=-26.74.
    Solar flux at 3.6 micron: 5.5464e16 mJy (Gueymard, 2004).
    """
    return relativeReflectance * 5.5464e16*u.mJy * 10**(-(V+26.74)/2.5)


def HG_W( alpha ):
    """ Aux function used by vmag """
    return np.exp( -90.56*( np.tan(alpha*0.5))**2)

def HG_phi1( alpha ):
    """ Aux function used by vmag """
    return HG_W(alpha)* (1- (.986*np.sin(alpha))/(.119+1.341*np.sin(alpha)-.754*np.sin(alpha)**2) )  +   (1-HG_W(alpha))*np.exp(-3.332 * (np.tan(alpha*0.5))**0.631)

def HG_phi2( alpha ):
    """ Aux function used by vmag """
    return HG_W(alpha)* (1- (.238*np.sin(alpha))/(.119+1.341*np.sin(alpha)-.754*np.sin(alpha)**2) )  +   (1-HG_W(alpha))*np.exp(-1.862 * (np.tan(alpha*0.5))**1.218)


