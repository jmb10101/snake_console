/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	j_timer.cpp																	          *
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

// timer class
j_timer::j_timer()
{
	m_iLastQuery.QuadPart = 0;

	// get Hardware clock frequency and current count
	QueryPerformanceFrequency (&m_iFrequency);
	update ();
}
j_timer::~j_timer()
{
}

void j_timer::update ()
{
	LARGE_INTEGER	kTempTimer;
	time_t			iTempTimeDate;

	// get current timer information and calculate difference
	QueryPerformanceCounter (&kTempTimer);
	m_iDelta.QuadPart = kTempTimer.QuadPart - m_iLastQuery.QuadPart;

	// Save current timer information
	m_iLastQuery.QuadPart = kTempTimer.QuadPart;

	// get current time and date
	time (&iTempTimeDate);
	localtime_s (&m_pkTime, &iTempTimeDate);
}

float j_timer::getDelta ()
{
	// convert to float and calculate delta in seconds
	return (float) (m_iDelta.QuadPart) / (float) (m_iFrequency.QuadPart);
}

unsigned int j_timer::getSeconds()
{
	return m_pkTime.tm_sec;
}
unsigned int j_timer::getMinutes()
{
	return m_pkTime.tm_min;
}
unsigned int j_timer::getHours()
{
	// adjust to normal time
	int hr = m_pkTime.tm_hour;
	if (hr > 12)
		hr -= 12;
	return hr;
}
unsigned int j_timer::getDay()
{
	return m_pkTime.tm_mday;
}
unsigned int j_timer::getMonth()
{
	return m_pkTime.tm_mon + 1;		// + 1 because month starts at Jan = 0
}
unsigned int j_timer::getYear()
{
	return m_pkTime.tm_year + 1900;	// + 1900 (unknown difference)
}


// j_globalTimer class **************************************************
j_globalTimer*	j_globalTimer::m_singleton = NULL;

j_globalTimer::j_globalTimer ()
{
	m_iLastQuery.QuadPart = 0;

	// get Hardware clock frequency and current count
	QueryPerformanceFrequency (&m_iFrequency);
	update ();

	// create singleton
	if (!m_singleton)
		m_singleton = this;
	else
		assert(false);			// singleton already exists -flag error
}
j_globalTimer::~j_globalTimer ()
{
	m_singleton = NULL;
}

j_globalTimer* j_globalTimer::getSingleton ()
{
	if (m_singleton)	
		return m_singleton;
	else
		return NULL;
}
