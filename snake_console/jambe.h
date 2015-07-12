/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	jambe.h																		          *
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

/******************************************************************************************
 * general component																	  *
 *																						  *
 * This component includes many standard header files and declares general, useful        *
 * functions and classes. It also includes other jambe components depending on            *
 * declaration of preprocessor directives.									              *
*******************************************************************************************/
#pragma once

// Windows Header File
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

// Standard Header Files 
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdio.h>

// C RunTime Header Files
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

// use namespace std
using namespace std;

// NOTE: 
// jambe specific header files are included at the end of this file. 
// different files will be included depending on if which preprocessor directives are defined	

// Useful macros
#define _SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }    
#define _SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }

// Pre-defined parameters
#define USE_DEFAULT	0x0FFFFFAA						// Use as parameter to set a default value
#define DONT_CHANGE 0x0FFFFFAB						// Use as parameter to keep a field at same value


// General/Miscellaneous Classes and Global Functions
class j_2DPoint
{
protected:
	float	m_x;
	float   m_y;

public:
	j_2DPoint () {m_x=0; m_y=0;}
	j_2DPoint (float x, float y) {m_x=x; m_y=y;}
	j_2DPoint (const j_2DPoint& point) {m_x=point.m_x; m_y=point.m_y;}
	~j_2DPoint () {}

	j_2DPoint& operator = (const j_2DPoint& point) {m_x=point.m_x; m_y=point.m_y; return *this;}
	bool operator == (const j_2DPoint& point) {if (m_x==point.m_x && m_y==point.m_y) {return true;}else{return false;}}

	void set (float x, float y) {m_x=x; m_y=y;}
	void setX (float x) {m_x=x;}
	void setY (float y) {m_y=y;}
	void move (float x, float y) {m_x += x; m_y += y;}
	void moveX (float x) {m_x += x;}
	void moveY (float y) {m_y += y;}

	float x () {return m_x;}
	float y () {return m_y;}

};

const std::wstring WIDEN(const std::string& str);   // Convert std::string into std::wstring (Used for certain Win32 functions in Unicode setting)

template <class NUM>
std::string NUM_TO_STRING (NUM kNum)			    // Converts any numeric value into a std::string type
{
	// convert the number into a string
	std::stringstream	out;
	out << kNum;
	return out.str ();
}	

void    RANDOMIZE_SEED ();  // randomizes seed
int		GET_RANDOM_INT (int low, int high);    // Returns a random number between low and high, inclusive
float	GET_RANDOM_FLOAT (float low, float high); // Returns random decimal between low and high, inclusive
double  GET_RANDOM_DOUBLE (double low, double high); // same
float	GET_ANGLE_XY (float x1, float y1, float x2, float y2); // Returns the angle formed by 2 points and horizontal line through lower point (0->2PI)
float   GET_DISTANCE_XY (float x1, float y1, float x2, float y2); // Returns the distance between two points
void	ROTATE_POINT (float& x, float& y, float centerX, float centerY, float radians); // Rotates a point around a center point by an angle measure  
bool    DOES_POINT_INTERSECT_RECT (float x, float y, RECT rct);  // Returns true if (x,y) lies inside rectangle rct


// Include Jambe header files based on defined preprocessor directives
// console-only headers
#ifdef J_CONSOLE_APP

#include "j_console.h"
#include "j_dataLogger.h"
#include "j_timer.h"


#endif

// extend jambe engine to include directX and windows (win32) functionality
#ifdef J_WIN32_APP

#include "j_console.h"
#include "j_dataLogger.h"
#include "j_timer.h"
//#include "j_windows.h"
//#include "j_d3dGraphics.h"
//#include "j_physics.h"
//#include "j_audio.h"
//#include "j_d3dInput.h"

#endif




