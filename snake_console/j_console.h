/****************************************************************************************** 
 *	Jambe C++ Engine																	  *	
 *	j_console.h																		      *
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
 * console component																      *
 *																						  *
 * This component makes input/ouput to the console easy. String insertions by position    *
 * and foreground/background color support are some of its functions.				      *
*******************************************************************************************/

// console dimensions
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

// Colors
enum j_consoleColors
{
	conBlack,
	conWhite,
	conRed,
	conGreen,
	conBlue,
	conYellow,
	conPurple,
	conCyan
};

// Common ASCII Key Values
// Note: ASCII Key Values can be calculated by enclosing the character in single quotes, like 'a'
enum keyValues 
{
	keyEnter	= 13,
	keyUp		= 72,
	keyLeft		= 75,
	keyRight	= 77,
	keyDown		= 80
};

// Cursor Positioning
enum j_cursorPositioning
{
	coordAbsolute,
	coordRelative
};

// Console GUI message box types
enum j_messageBox
{
	mboxOther,
	mboxEnter,
	mboxYesNo
};

// Console cell class **************************************************
// ->This class contains everything necessary to define a particular 
//   console cell. It can be useful in some implementations where a
//   collection of this class is used to keep track of each cell, or
//   alternatively, as a way to contain the properties of a cell and draw
//   them with j_console::drawCell().
class j_consoleCell
{
protected:
	j_consoleColors  m_fgColor;
	j_consoleColors  m_bgColor;
	char			 m_character;
	int				 m_x;
	int				 m_y;

public:
	j_consoleCell ();
	j_consoleCell (const j_consoleCell& consoleCell);
	~j_consoleCell ();

	// assignment /comparison operators
	j_consoleCell& operator = (const j_consoleCell& consoleCell);
	bool operator == (const j_consoleCell& consoleCell);

	// accessor methods
	j_consoleColors getFGColor () {return m_fgColor;}
	j_consoleColors getBGColor () {return m_bgColor;}
	char getChar () {return m_character;}
	int getX () {return m_x;}
	int getY () {return m_y;}

	// mutator methods
	void setFGColor (j_consoleColors color) {m_fgColor = color;}
	void setBGColor (j_consoleColors color) {m_bgColor = color;}
	void setChar (char character) {m_character = character;}
	void setX (int x) {m_x = x;}
	void setY (int y) {m_y = y;}
	void set (int x, int y) {m_x = x; m_y = y;}
	void moveX (int x) {m_x += x;}
	void moveY (int y) {m_y += y;}
	void move (int x, int y) {m_x += x; m_y += y;}
};


// Console class **************************************************
class j_console
{
private:
	HANDLE m_screen;
	HANDLE m_keyboard;

	// use two seperate color identifiers, one for windows use and one for j_console use
	WORD m_bgColor;
	WORD m_fgColor;
	j_consoleColors m_jbgColor;
	j_consoleColors m_jfgColor;

	int m_cursorx;
	int m_cursory;

	// singleton
	static j_console*	m_singleton;


public:
	j_console ();
	~j_console ();

	static j_console*	getSingleton();

	// Must create console before use in Win32 (non-console) applications
	void open ();
	void close ();

	void moveCursor (int x, int y, j_cursorPositioning positioning = coordAbsolute);

	int getCursorX() {return m_cursorx;}
	int getCursorY() {return m_cursory;}

	j_consoleColors getFGColor (void) {return m_jfgColor;}
	j_consoleColors getBGColor (void) {return m_jbgColor;}

	void setFGColor (j_consoleColors color);
	void setBGColor (j_consoleColors color);

	void setTitle (const std::string& title);
	void clearScreen (j_consoleColors color = conBlack);

	// Console Output
	void out (const std::string& outputString);
	j_console& operator << (const std::string& outputString);
	void drawCell (j_consoleCell& consoleCell);

	// Console Input
	void in (std::string& inputString);						// uses getline() to retrieve a string after enter has been pressed
	j_console& operator >> (std::string& inputString);

	void in (char& inputChar);								// uses _getch() to retrieve a key value as soon as it has been pressed
	j_console& operator >> (char& inputChar);

	// Console GUI
	void drawTextBox (const std::string& caption, const std::string& message, int x = 1, int y = 1, int width = 78, int height = 23, j_consoleColors border = conWhite, 
		j_consoleColors fill = conBlack, j_consoleColors captionTextColor = conBlack, j_consoleColors textColor = conWhite, j_messageBox messageBoxType = mboxOther, 
		const std::string& closingMessage = "");

	// Extra
	void drawRainbowSplash (float& count);


};