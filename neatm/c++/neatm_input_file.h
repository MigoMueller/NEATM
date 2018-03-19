#include<vector>
#include<string>
#include<fstream>
#pragma once

class NEATM_input_file
{
public:
	NEATM_input_file(const char* const filename)
		{readin(filename);};
	//NEATM_input_file(const string& filename)
	//	{readin filename.c_str())};
	virtual ~NEATM_input_file(void){};
	const std::vector<double>& get_lambda() const throw()
		{return lambdaMu;};
	const std::vector<double>& get_fluxes() const throw()
		{return fluxSI;};
	const std::vector<double>& get_sigma() const throw()
		{return sigmaSI;};
	const std::vector<double>& get_sigmaSquared() const throw()
		{return sigmaSquaredSI;};
	double getH() const throw()
		{return H;}
	double getG() const throw()
		{return G;}
	double getR() const throw()
		{return r;}
	double getDelta() const throw()
		{return delta;}
	double getAlpha() const throw()
		{return alpha;};
	
	// evil hack: replaces flux values with vector provided (and vice versa!)
	// use at your own risk!
	void swap_fluxes(std::vector<double>& rhs)
		{this->fluxSI.swap(rhs);};

protected:
	void readin(const char* const filename);
	void skip_comments(std::ifstream& in);
	double H,G,r,delta,alpha;
	unsigned int n_points;
	std::vector<double> lambdaMu, fluxSI, sigmaSI, sigmaSquaredSI;
private: // prohibitive declarations, only
	NEATM_input_file(void);
	NEATM_input_file(const NEATM_input_file&);
	NEATM_input_file& operator=(const NEATM_input_file&);
}; // class NEATM_input_file


class NEATM_input_file_MJy : public NEATM_input_file
{
public:
	NEATM_input_file_MJy(const char* const filename);
};
