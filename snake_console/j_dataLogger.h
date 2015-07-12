/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	j_dataLogger.h																		  *
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
 * data logger component															      *
 *																						  *
 * This component makes it possible to record notes at any time to a file. It is          *
 * implemented as a singleton class so that it can be accessible anywhere in the code.	  *
*******************************************************************************************/
class j_dataLogger
{
protected:
	static j_dataLogger*	m_singleton;
	j_console*				m_console;

public:
	j_dataLogger();
	j_dataLogger(j_console* console);
	~j_dataLogger();

	static j_dataLogger*	getSingleton();
	void					init(j_console* console) {m_console = console;}

	// log to a file
	bool log(const string& note, const string& filename = "log.txt", bool append = true);

	// log to console
	bool logCon(const string& note);
	j_dataLogger& operator << (const string& note);
	
};
