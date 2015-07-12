/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	jambe.cpp																	          *
 *																						  *
 *																						  *
 *	This file is part of The Jambe C++ Engine.	                                          *
 *  The Jambe C++ Engine is a versitile and lightweight wrapper for windows-based         *
 *  console and DirectX applications. It is primarily intended to provide all the         *
 *  functionality needed to make console and basic 2D games. The engine is intended       *
 *  to be versitile in the sense that users can pick and choose which components to       *
 *  use. However, some components may have dependencies on others in some cases. For      *
 *  more information, see the documentation. If you do not have the documentation,        *
 *  or have a question about Jambe, email me at jmb10101@gmail.com                        *
 *																						  *
 *	The Jambe C++ Engine is free software: you can redistribute it and/or modify	      *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version. Giving credit to me is not necessary, but         *
 *  it is appreciated. If you have any questions, comments, etc email me at               *
 *  jmb10101@gmail.com.                                                                   *
 *																						  *
 *	The Jambe C++ is distributed in the hope that it will be useful,		              *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Jambe C++ Engine.  If not, see <http://www.gnu.org/licenses/>.         *
 ******************************************************************************************/
#include "stdafx.h"

// Helper Functions
const std::wstring WIDEN(const std::string& str)
{
	std::wstring wstr (str.size (), L'');
	std::copy(str.begin(), str.end(), wstr.begin());

	const std::wstring _wstr (wstr);

	return _wstr;
}

void RANDOMIZE_SEED () 
{	
	srand ((unsigned int) (time (NULL)));
}

int GET_RANDOM_INT (int low, int high)
{
	int r=0;
	int range=0;

	if (low < high)
	{
		range = (high - low) + 1;
		r = low + (rand() % range); 
	}
	else
	{
		if (high == low)
			r = high;
		else
			r = 0;
	}
	
	return r;
}
float	GET_RANDOM_FLOAT (float low, float high)
{
	float r=0.0f;
	float range=0.0f;
	float deci=0.0f;

	if (low < high)
	{
		range = high - low;
		deci = (float)(rand ()) / (float)(RAND_MAX);
		r = low + (deci*range);
	}
	else
	{
		r = low;
	}

	return r;	
}
double	GET_RANDOM_DOUBLE (double low, double high)
{
	double r=0.0;
	double range=0.0;
	double deci=0.0;

	if (low <= high)
	{
		range = high - low;
		deci = (double)(rand ()) / (double)(RAND_MAX);
		r = low + (deci*range);
	}
	else
	{
		r = 0;
	}

	return r;	
}
float	GET_ANGLE_XY (float x1, float y1, float x2, float y2)
{
	float angle = 0.0f;
	float X = 0.0f; float Y = 0.0f;
	X = abs(x1 - x2);
	Y = abs(y1 - y2);
	angle = atan (Y/X);

	// calculate screen angle by locating quadrant
	if (x1 < x2 && y1 < y2)			// quad 2
		angle = (float)(M_PI) - angle;
	else if (x1 < x2 && y1 >= y2)	// quad 3
		angle = (float)(M_PI) + angle;
	else if (x1 >= x2 && y1 > y2)	// quad 4
		angle = (2*(float)(M_PI)) - angle;
	
	// convert to screen (directx) angles
	angle = (2*(float)(M_PI) - angle);

	return angle;
}

float   GET_DISTANCE_XY (float x1, float y1, float x2, float y2)
{
	// return distance
	return sqrt (pow(x1-x2,2)+pow(y1-y2,2));
}

void	ROTATE_POINT (float& x, float& y, float centerX, float centerY, float radians)
{
	// find radius
	float radius = GET_DISTANCE_XY (x, centerX, y, centerY);

	// find current angle orientation and determine final angle orientation
	float angle = GET_ANGLE_XY (x, centerX, y, centerY);
	angle += radians;

	// update new position
	x = (cos (angle) * radius) + centerX;
	y = (sin (angle) * radius) + centerY;
}
bool    DOES_POINT_INTERSECT_RECT (float x, float y, RECT rct)
{
	if (x >= rct.left && x <= rct.right && y >= rct.top && y <= rct.bottom)
		return true;
	else
		return false;
}