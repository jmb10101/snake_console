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
#include "stdafx.h"

// console cell class
j_consoleCell::j_consoleCell ()
{
	m_fgColor = conWhite;
	m_bgColor = conBlack;
	m_character = ' ';
	m_x = 0;
	m_y = 0;
}
j_consoleCell::j_consoleCell (const j_consoleCell& consoleCell)
{
	// use assignment operator to set this instance equal to consoleCell
	(*this) = consoleCell;
}
j_consoleCell::~j_consoleCell ()
{
}
j_consoleCell& j_consoleCell::operator = (const j_consoleCell& consoleCell)
{
	m_fgColor = consoleCell.m_fgColor;
	m_bgColor = consoleCell.m_bgColor;
	m_character = consoleCell.m_character;
	m_x = consoleCell.m_x;
	m_y = consoleCell.m_y;
	
	return (*this);
}
bool j_consoleCell::operator == (const j_consoleCell& consoleCell)
{
	// position and char match, cells are considered equal - color does not matter WE DO NOT DISCRIMINATE
	if (m_x == consoleCell.m_x && m_y == consoleCell.m_y && m_character == consoleCell.m_character)
		return true;
	else
		return false;
}

// console class
j_console*	j_console::m_singleton = NULL;

j_console::j_console ()
{
	m_screen = GetStdHandle (STD_OUTPUT_HANDLE);

	setBGColor (conWhite);
	setFGColor (conBlack);

	moveCursor (0,0);

	// create singleton
	if (!m_singleton)
		m_singleton = this;
	else
		assert(false);			// singleton already exists -flag error

}
j_console::~j_console ()
{
	close ();

	m_singleton = NULL;
}

j_console* j_console::getSingleton()
{
	if (m_singleton)
		return m_singleton;
	else
		return NULL;
}

void j_console::open ()
{
	AllocConsole ();
	m_screen = GetStdHandle (STD_OUTPUT_HANDLE);
}
void j_console::close ()
{
	if (m_screen)
		FreeConsole ();
}

void j_console::moveCursor (int x, int y, j_cursorPositioning positioning)
{
	COORD pos;

	if (positioning == coordAbsolute)
	{
		pos.X = x;
		pos.Y = y;

		m_cursorx = pos.X;
		m_cursory = pos.Y;
	}
	else
	{
		pos.X = x + m_cursorx;
		pos.Y = y + m_cursory;

		m_cursorx = pos.X;
		m_cursory = pos.Y;
	}

	SetConsoleCursorPosition (m_screen, pos);
}

void j_console::setFGColor (j_consoleColors color)
{
	m_jfgColor = color;
	m_fgColor = 0;

	switch (color)
	{
	case conWhite:
		m_fgColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;

	case conRed:
		m_fgColor = FOREGROUND_RED;
		break;

	case conBlue:
		m_fgColor = FOREGROUND_BLUE;
		break;

	case conGreen:
		m_fgColor = FOREGROUND_GREEN;
		break;

	case conYellow:
		m_fgColor = FOREGROUND_RED | FOREGROUND_GREEN;
		break;

	case conPurple:
		m_fgColor = FOREGROUND_RED | FOREGROUND_BLUE;
		break;

	case conCyan:
		m_fgColor = FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;

	}

	// set color
	SetConsoleTextAttribute (m_screen, m_fgColor | m_bgColor);
}
void j_console::setBGColor (j_consoleColors color)
{
	m_jbgColor = color;
	m_bgColor = 0;

	switch (color)
	{
	case conWhite:
		m_bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;

	case conRed:
		m_bgColor = BACKGROUND_RED;
		break;

	case conBlue:
		m_bgColor = BACKGROUND_BLUE;
		break;

	case conGreen:
		m_bgColor = BACKGROUND_GREEN;
		break;

	case conYellow:
		m_bgColor = BACKGROUND_RED | BACKGROUND_GREEN;
		break;

	case conPurple:
		m_bgColor = BACKGROUND_RED | BACKGROUND_BLUE;
		break;

	case conCyan:
		m_bgColor = BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	}

	// set color
	SetConsoleTextAttribute (m_screen, m_fgColor | m_bgColor);
}

void j_console::setTitle (const std::string& title)
{
	SetConsoleTitle (WIDEN (title).c_str ());
}

void j_console::clearScreen (j_consoleColors color)
{
	// record current bg color so it can be restored
	j_consoleColors bg_cur = m_jbgColor;

	COORD start;
	DWORD written; 

	start.X = 0; start.Y = 0;

	setBGColor (color);

	FillConsoleOutputAttribute (m_screen, m_fgColor | m_bgColor, CONSOLE_WIDTH * CONSOLE_HEIGHT, start, &written);
	FillConsoleOutputCharacter (m_screen, ' ', CONSOLE_WIDTH * CONSOLE_HEIGHT, start, &written);
	moveCursor (0, 0);

	// restore original bg color
	setBGColor(bg_cur);
}

void j_console::drawTextBox (const std::string& caption, const std::string& message, int x, int y, int width, int height, j_consoleColors border, 
		j_consoleColors fill, j_consoleColors captionTextColor, j_consoleColors textColor, j_messageBox messageBoxType, const std::string& closingMessage)
{
	int messagePosition = 0;
	int linesWritten = 0;

	// Draw Box
	for (int i = 0; i < height; ++i)
	{
		for (int ii = 0; ii < width; ++ii)
		{
			if (i == 0 || i == (height-1) || ii == 0 || ii == (width-1))
				setBGColor (border);
			else
				setBGColor (fill);

			moveCursor (ii+x, i+y);
			out (" ");
		}
	}

	// Display Caption
	moveCursor (x,y);
	setBGColor (border);
	setFGColor (captionTextColor);
	out (caption);


	// Display main message
	if (height <= 3)
	{
		moveCursor (x+1, y+1);
		out (message);
	}
	else
	{
		moveCursor (x+(width-2)/2, y+1);
	
		setBGColor (fill);
		setFGColor (textColor);

		while (message.size () >= messagePosition)
		{
			moveCursor (x + 1, y + 1 + linesWritten);
			out (message.substr (messagePosition, (width-2)));
			messagePosition += width-2;
			linesWritten++;
		}
		
		
	}

	//  Display closing message
	if (messageBoxType == mboxEnter)
	{
		moveCursor (x, y+height-1);
		setBGColor (border);
		setFGColor (captionTextColor);
		out ("Press Enter");
	}
	else if (messageBoxType == mboxYesNo)
	{
		moveCursor (x, y+height-1);
		setBGColor (border);
		setFGColor (captionTextColor);
		out ("Yes(y)  No(n)");
	}
	else if (messageBoxType = mboxOther)
	{
		moveCursor (x, y+height-1);
		setBGColor (border);
		setFGColor (captionTextColor);
		out (closingMessage);
	}

	moveCursor (0, 0);
}

// Console Output
void j_console::out (const std::string& outputString)
{
	if (m_screen)
		std::cout << outputString;
}
j_console& j_console::operator << (const std::string& outputString)
{
	out (outputString);
	return (*this);
}
void j_console::drawCell (j_consoleCell& consoleCell)
{
	setBGColor(consoleCell.getBGColor());
	setFGColor(consoleCell.getFGColor());
	moveCursor(consoleCell.getX(), consoleCell.getY());

	cout << consoleCell.getChar();
}

// Console Input
void j_console::in (std::string& inputString)
{
	if (m_screen)
		std::getline(std::cin, inputString);

	// command to close console
	if (inputString == "exit -now")
		close();
}
j_console& j_console::operator >> (std::string& inputString)
{
	in (inputString);
	return (*this);
}
void j_console::in (char& inputChar)
{
	if (_kbhit())
		inputChar = _getch();
}
j_console& j_console::operator >> (char& inputChar)
{
	in(inputChar);
	return (*this);
}

// Extra
void j_console::drawRainbowSplash (float& count)
{
	j_consoleColors iColor;
	iColor = conRed;
	setFGColor (conWhite);

	if (count > 0.1)
	{
			count = 0;
			moveCursor (0,0);

		for (int i = 0; i < 25; ++i)
		{
			for (int ii = 0; ii < 80; ++ii)
			{
				if (ii == 0)
				{
					if (i == 0)
						iColor = conRed;
				}
				else
				{
					switch (iColor)
					{
					case conRed:
						iColor = conYellow;
						break;
					case conYellow:
						iColor = conGreen;
						break;
					case conGreen:
						iColor = conBlue;
						break;
					case conBlue:
						iColor = conCyan;
						break;
					case conCyan:
						iColor = conPurple;
						break;
					case conPurple:
						iColor = conRed;
						break;
					}

				}

				setBGColor (iColor);
				moveCursor (ii, i);
				if (GET_RANDOM_INT (0,50) == 1)
					out ("*");
				else
					out (" ");
			}
		}
	}
}