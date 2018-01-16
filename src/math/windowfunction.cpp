/*
	*** Window Function
	*** src/math/windowfunction.cpp
	Copyright T. Youngs 2012-2018

	This file is part of dUQ.

	dUQ is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	dUQ is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with dUQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "math/windowfunction.h"
#include "base/lineparser.h"
#include "base/processpool.h"
#include "base/sysfunc.h"
#include "base/xydata.h"
#include "templates/enumhelpers.h"

// Constructor
WindowFunction::WindowFunction(WindowFunction::FunctionType function, double p1, double p2, double p3, double p4, double p5, double p6)
{
	set(function, p1, p2, p3, p4, p5, p6);

	xMax_ = -1.0;
}

// Assignment operator
void WindowFunction::operator=(const WindowFunction& source)
{
	function_ = source.function_;
	for (int n=0; n<MAXFUNCTIONPARAMS; ++n) parameters_[n] = source.parameters_[n];

	xMax_ = source.xMax_;
}

// Destructor
WindowFunction::~WindowFunction()
{
}

// Window Function keywords
const char* WindowFunctionKeywords[] = { "Unity", "Bartlett", "Hann", "Lanczos", "Nuttall", "Sine", "Lorch0" };

int WindowFunctionNParameters[] = { 0, 0, 0, 0, 0, 0, 0 };

// Return FunctionType from supplied string
WindowFunction::FunctionType WindowFunction::functionType(const char* s)
{
	for (int n=0; n<nFunctionTypes; ++n) if (DUQSys::sameString(s, WindowFunctionKeywords[n])) return (FunctionType) n;
	return WindowFunction::nFunctionTypes;
}

// Return FunctionType name
const char* WindowFunction::functionType(WindowFunction::FunctionType func)
{
	return WindowFunctionKeywords[func];
}

// Return number of parameters needed to define function
int WindowFunction::nFunctionParameters(FunctionType func)
{
	return WindowFunctionNParameters[func];
}

// Return description for FunctionType
const char* WindowFunction::functionDescription(FunctionType func)
{
	switch (func)
	{
		case (WindowFunction::UnityWindow):
			return "Rectangular window (always 1.0)";
			break;
		case (WindowFunction::BartlettWindow):
			return "Bartlett (triangular) window";
			break;
		case (WindowFunction::HannWindow):
			return "von Hann (Hanning) window";
			break;
		case (WindowFunction::LanczosWindow):
			return "Lanczos window";
			break;
		case (WindowFunction::NuttallWindow):
			return "Nuttall window (continuous first derivatives over range)";
			break;
		case (WindowFunction::SineWindow):
			return "Sine Window";
			break;
		case (WindowFunction::Lorch0Window):
			return "Original Lorch function";
			break;
		default:
			break;
	}

	return "NO WINDOW FUNCTION DESCRIPTION AVAILABLE.";
}

/*
 * Function Data
 */

void WindowFunction::set(WindowFunction::FunctionType function, double p1, double p2, double p3, double p4, double p5, double p6)
{
	function_ = function;
	parameters_[0] = p1;
	parameters_[1] = p2;
	parameters_[2] = p3;
	parameters_[3] = p4;
	parameters_[4] = p5;
	parameters_[5] = p6;
}

// Set function data from LineParser source
bool WindowFunction::set(LineParser& parser, int startArg)
{
	// First argument is the form of the function
	WindowFunction::FunctionType funcType = WindowFunction::functionType(parser.argc(startArg));
	if (funcType == WindowFunction::nFunctionTypes)
	{
		Messenger::error("Unrecognised Function type '%s'.\n", parser.argc(startArg));
		return false;
	}

	// Do we have the right number of arguments for the function specified?
	if ((parser.nArgs() - startArg) < WindowFunction::nFunctionParameters(funcType))
	{
		Messenger::error("Too few parameters supplied for Function '%s' (expected %i, found %i).\n", WindowFunction::functionType(funcType), WindowFunction::nFunctionParameters(funcType), parser.nArgs() - startArg);
		return false;
	}

	// Set up function
	function_ = funcType;
	switch (function_)
	{
		case (WindowFunction::UnityWindow):
		case (WindowFunction::BartlettWindow):
		case (WindowFunction::HannWindow):
		case (WindowFunction::LanczosWindow):
		case (WindowFunction::NuttallWindow):
		case (WindowFunction::SineWindow):
		case (WindowFunction::Lorch0Window):
			// No fixed parameters.
			break;
		default:
			Messenger::error("Function form '%s' not accounted for in set(LineParser&,int).\n", WindowFunction::functionType(funcType));
			return false;
	}

	return true;
}

// Return function type
WindowFunction::FunctionType WindowFunction::function() const
{
	return function_;
}

// Return short summary of function parameters
CharString WindowFunction::parameterSummary() const
{
	switch (function_)
	{
		case (WindowFunction::UnityWindow):
		case (WindowFunction::BartlettWindow):
		case (WindowFunction::HannWindow):
		case (WindowFunction::LanczosWindow):
		case (WindowFunction::NuttallWindow):
		case (WindowFunction::SineWindow):
			return "No Parameters";
			break;
		case (WindowFunction::Lorch0Window):
			return CharString("Delta0=%f", parameters_[0]);
			break;
		default:
			Messenger::warn("WindowFunction::value(x) - Function id %i not accounted for.\n", function_);
			break;
	}

	return "NULL";
}

// Set-up function for specified data
bool WindowFunction::setUp(const XYData& data)
{
	// Store maximum x value of data
	xMax_ = data.xLast();

	switch (function_)
	{
		case (WindowFunction::UnityWindow):
		case (WindowFunction::BartlettWindow):
		case (WindowFunction::HannWindow):
		case (WindowFunction::LanczosWindow):
		case (WindowFunction::NuttallWindow):
		case (WindowFunction::SineWindow):
			break;
		case (WindowFunction::Lorch0Window):
			// Set Delta0 from the high x limit of the data
			parameters_[0] = PI /  data.xLast();
			break;
		default:
			Messenger::warn("WindowFunction::value(x) - Function id %i not accounted for.\n", function_);
			break;
	}

	return true;
}

// Return value of function given parameters x (current abscissa value) and omega (target abscissa value)
double WindowFunction::y(double x, double omega) const
{
	// Determine current fractional x value (from our stored xMax_)
	double chi = x / xMax_;

#ifdef CHECKS
	if ((chi < 0.0) || (chi > 1.0)) Messenger::warn("Position for window function is out of range (%f).\n", chi);
#endif

	switch (function_)
	{
		case (WindowFunction::UnityWindow):
			return 1.0;
			break;
		case (WindowFunction::BartlettWindow):
			return (1.0 - fabs( (chi-0.5)/0.5 ));
			break;
		case (WindowFunction::HannWindow):
			return 0.5*(1.0-cos(2*PI*chi));
			break;
		case (WindowFunction::LanczosWindow):
			return sin(PI*(2*chi-1.0))/(PI*(2*chi-1.0));
			break;
		case (WindowFunction::NuttallWindow):
			return (0.355768 - 0.487396*cos(2.0*PI*chi) + 0.144232*cos(4.0*PI*chi) - 0.012604*cos(6.0*PI*chi));
			break;
		case (WindowFunction::SineWindow):
			return 1.0 - sin(PI*0.5*chi);
			break;
		case (WindowFunction::Lorch0Window):
			/*
			 * Original Lorch function
			 * 
			 * Parameters:  0 = delta0	( = PI/xmax )
			 * 
			 * 	  sin(x * delta0)
			 * f(x) = ---------------
			 * 	    x * delta0
			 */
			return sin(chi*parameters_[0]) / (chi*parameters_[0]);
			break;
		default:
			Messenger::warn("WindowFunction::value() - Function id %i not accounted for.\n", function_);
			break;
	}

	return 0.0;
}

/*
 * GenericItemBase Implementations
 */

// Return class name
const char* WindowFunction::itemClassName()
{
	return "WindowFunction";
}

// Write data through specified LineParser
bool WindowFunction::write(LineParser& parser)
{
	CharString line("%s", functionType(function_));
	for (int n=0; n<nFunctionParameters(function_); ++n) line.strcatf(" %16.9e", parameters_[n]);
	return parser.writeLine(line.get());
}

// Read data through specified LineParser
bool WindowFunction::read(LineParser& parser)
{
	if (parser.getArgsDelim(LineParser::Defaults) != LineParser::Success) return false;
	function_ = functionType(parser.argc(0));
	for (int n=0; n<nFunctionParameters(function_); ++n) parameters_[n] = parser.argd(n+1);
	return true;
}

/*
 * Parallel Comms
 */

// Broadcast data from Master to all Slaves
bool WindowFunction::broadcast(ProcessPool& procPool, int root)
{
#ifdef PARALLEL
	if (!procPool.broadcast(EnumCast<WindowFunction::FunctionType>(function_), root)) return false;
	if (!procPool.broadcast(parameters_, MAXFUNCTIONPARAMS, root)) return false;
#endif
	return true;
}