// environment.cpp
#include "stdafx.h"

environment::environment()
{

}
environment::~environment()
{
	m_map.clear();
}

bool environment::init()
{
	restart();
	m_gem.setFGColor(conYellow);
	m_gem.setChar('$');

	loadFromFile("./game_files/map""");
	return true;
}
void environment::restart()
{
	m_gem.set(39,12);
	m_collisionPoint= 0;
	m_collision = false;
}
bool environment::loadFromFile(const std::string& file)
{
	std::ifstream ifs;
	std::string line;

	ifs.open(file);
	if (ifs)
	{
		// if file is empty, just exit and play game without walls
		if (ifs.eof())
			return false;

		// first two lines do not contain map info
		ifs >> line;
		ifs >> line;

		while(!ifs.eof()) // do while end of file has not been reached
		{
			ifs >> line;  // take one line at a time
			for (int x=0; x<80; x++)	// 80 chars per line
			{
				if (line.substr(x,1) == "x")
					m_map.push_back(true); 
				else
					m_map.push_back(false);
			}
		}
	}
	ifs.close();
	return true;
}

void environment::moveGem()
{
	int gx,gy,collisions,i=0;

	gx = GET_RANDOM_INT(1, (CONSOLE_WIDTH-2));
	gy = GET_RANDOM_INT(1, (CONSOLE_HEIGHT-2));

	if (!m_map.empty())
	{
		do {
			gx = GET_RANDOM_INT(1, (CONSOLE_WIDTH-2));
			gy = GET_RANDOM_INT(1, (CONSOLE_HEIGHT-2));
			collisions = 0;

			for (int y=0;y<25;y++)
			{
				for (int x=0;x<80;x++)
				{
					if (m_map[i] == true)
					{
						if (gx == x && gy == y)
							collisions++;
					}

					i++;
				}
			}
		}while(collisions > 0);
	}

	m_gem.set(gx, gy);
}
bool environment::detectCollision(int sx, int sy)
{
	int i = 0;
	j_consoleCell wall;

	if (!m_map.empty())
	{
		for (int y=0;y<25;y++)
		{
			for (int x=0;x<80;x++)
			{
				if (m_map[i] == true)
				{
					if (x == sx && y == sy) {
						m_collisionPoint = i;
						m_collision = true;
						return true;
					}
				}

				i++;
			}
		}
	}

	return false;
}
bool environment::draw(vector<j_consoleCell>& cells)
{
	int i = 0;
	j_consoleCell wall;
	wall.setChar('#');

	if (!m_map.empty() && !cells.empty())
	{
		for (int y=0;y<25;y++)
		{
			for (int x=0;x<80;x++)
			{
				if (m_map[i] == true)
				{
					cells[i] = wall;
					if(m_collision && m_collisionPoint == i)
					{
						cells[i].setFGColor(conRed);
						m_collision = false;
					}
				}

				i++;
			}
		}
	}
	cells[(m_gem.getY()*80)+m_gem.getX()] = m_gem;

	return true;
}