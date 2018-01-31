// Convert W/m^2/mu to mJy and backwards


#if !defined(AFX_JANSKY_H__624E8CE4_70D0_47BE_8963_C930E1DB11E0__INCLUDED_)
#define AFX_JANSKY_H__624E8CE4_70D0_47BE_8963_C930E1DB11E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<stdexcept>

namespace jansky
{
	// converts W/m^2/mu (Wm2mu) into mJy - wavelength in mu (lambdaMu)
	inline double SI2mJy (double Wm2mu, double lambdaMu)
	{
		if(Wm2mu<0) throw std::invalid_argument("mJy2SI: You entered a negative flux value!");
		if(lambdaMu<0) throw std::invalid_argument("mJy2SI: You entered a negative wave length!");
		return Wm2mu*lambdaMu*lambdaMu/2.99792458e-15;
	};

	// converts milliJanskies (mJy) to W/m^2/mu - wavelength in mu (lambdaMu)
	inline double mJy2SI (double mJy, double lambdaMu)
	{
		if(mJy<0) throw std::invalid_argument("mJy2SI: You entered a negative flux value!");
		if(lambdaMu<0) throw std::invalid_argument("mJy2SI: You entered a negative wave length!");
		return mJy/(lambdaMu*lambdaMu)*2.99792458e-15;
	};
} // namespace jansky


#endif // !defined(AFX_JANSKY_H__624E8CE4_70D0_47BE_8963_C930E1DB11E0__INCLUDED_)
