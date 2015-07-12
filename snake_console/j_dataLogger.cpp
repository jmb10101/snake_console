/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	j_dataLogger.cpp															          *
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

// data logger class
j_dataLogger*	j_dataLogger::m_singleton = NULL;

j_dataLogger::j_dataLogger()
{
	// create singleton
	if (!m_singleton)
		m_singleton = this;
	else
		assert(false);			// singleton already exists -flag error

	m_console = NULL;
}
j_dataLogger::j_dataLogger(j_console* console)
{
	// create singleton
	if (!m_singleton)
		m_singleton = this;
	else
		assert(false);			// singleton already exists -flag error

	// set console reference
	m_console = console;

}
j_dataLogger::~j_dataLogger()
{
	m_singleton = NULL;
	m_console = NULL;
}

j_dataLogger*	j_dataLogger::getSingleton()
{
	if (m_singleton)
		return m_singleton;
	else
		return NULL;
}

// log to file
bool j_dataLogger::log(const string& note, const string& filename, bool append)
{
	ofstream logfile;
	ios_base::openmode mode = ios::out;

	if (append)
		mode |= ios::app;

	logfile.open(filename, mode);
	logfile << note;
	logfile.close();
	return true;
}

// log to console
bool j_dataLogger::logCon(const string& note)
{
	if (!m_console)
		return false;

	m_console->out(note);
	return true;
}
j_dataLogger& j_dataLogger::operator << (const string& note)
{
	logCon(note);
	return (*this);
}
