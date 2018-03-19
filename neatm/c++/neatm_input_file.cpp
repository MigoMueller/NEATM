#include "neatm_input_file.h"
#include<sstream>
#include "jansky.h"
#include <cmath>
using namespace std;


void NEATM_input_file::readin(const char* const filename)
{
	ifstream parameterfile (filename);
	if(!parameterfile){
		stringstream dummy;
		dummy<<"Couldn't open "<<filename<<" for reading!";
		throw logic_error(dummy.str());
	} 

	skip_comments(parameterfile); parameterfile>>H;
	skip_comments(parameterfile); parameterfile>>G;
	skip_comments(parameterfile); parameterfile>>alpha;
	skip_comments(parameterfile); parameterfile>>r;
	skip_comments(parameterfile); parameterfile>>delta;
	skip_comments(parameterfile); parameterfile>>n_points;

	lambdaMu.resize(n_points);
	fluxSI.resize(n_points);
	sigmaSI.resize(n_points);
	sigmaSquaredSI.resize(n_points);

	for (unsigned int i=0; i<n_points; i++)
	{
		skip_comments(parameterfile); parameterfile>>lambdaMu[i];
		skip_comments(parameterfile); parameterfile>>fluxSI[i];
		skip_comments(parameterfile); parameterfile>>sigmaSI[i];
		sigmaSquaredSI[i] = pow(sigmaSI[i],2);
	}
};	


void NEATM_input_file::skip_comments(ifstream& in)
{
	char dummystr[2256];	

	// 10=CR, 32=blank 9=TAB -- to ignore lines starting like'   #' and such as well as blank lines
	while((in.peek()==10) || (in.peek()==' ') || (in.peek()==9))
		in.ignore();

	// ignore comments
	while((in.peek()=='#') || (in.peek()=='/')||(in.peek()=='%')) 
	{
		char dummy;
		in>>dummy;
		if (dummy == '#' && in.peek() == '#') 
			// two subsequent #'s are *not* a comment (2005 Dec 12 update)
		{
			in.ignore(); // remove 2nd '#' from stream
			return;
		};
		in.getline(dummystr, 2255);
		while((in.peek()==10) || (in.peek()==' ')|| (in.peek()==9))
			in.ignore();
	}
	return;
} // skip_comments(in)



NEATM_input_file_MJy::NEATM_input_file_MJy(const char* const filename)
	: NEATM_input_file (filename)
{
	for (unsigned int i=0; i<n_points; i++)
	{
		fluxSI[i] = jansky::mJy2SI(fluxSI[i], lambdaMu[i]);
		sigmaSI[i] = jansky::mJy2SI(sigmaSI[i], lambdaMu[i]);
		sigmaSquaredSI[i] = pow(sigmaSI[i],2);
	};
};

