/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	j_timer.h																		      *
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
 * timer component																	      *
 *																						  *
 * This component makes it possible to keep track of time during program execution, 	  *
 * and allows the time and date to be retrieved. There is a normal timer class as well    *
 * as a singleton class derived from the normal one.									  *
*******************************************************************************************/
class j_timer
{
protected:
	LARGE_INTEGER		m_iFrequency;
	LARGE_INTEGER		m_iLastQuery;
	LARGE_INTEGER		m_iDelta;

	tm					m_pkTime;

public:
	j_timer ();
	~j_timer ();

	// update time variables
	void update ();

	// Return timer information
	float			getDelta ();
	unsigned int	getSeconds ();
	unsigned int	getMinutes ();
	unsigned int    getHours ();
	unsigned int	getDay ();
	unsigned int	getMonth ();
	unsigned int	getYear ();


};

// use j_globalTimer for a master singleton timer to be accessible from everywhere in the application
class j_globalTimer : public j_timer
{
protected:

	static j_globalTimer*	m_singleton;

public:
	j_globalTimer ();
	~j_globalTimer ();

	static j_globalTimer* getSingleton ();
};