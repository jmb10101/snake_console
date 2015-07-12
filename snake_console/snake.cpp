// snake.cpp
#include "stdafx.h"

// turn class
turn::turn()
{
}
turn::~turn()
{
}

// snake node class
snake_node::snake_node()
{
	m_dir = dirRight;
	m_character = 'o';
	m_fgColor = conGreen;
	m_x = 5;
	m_y = 12;
}
snake_node::~snake_node()
{
}
void snake_node::addTurn(direction dir, int x, int y)
{
	turn t;
	t.set(x,y,dir);
	m_turns.push_back(t);


}
void snake_node::move()
{
	// check pending turns to see if direction needs to change
	if (!m_turns.empty())
	{
		if (m_turns.front().getX() == m_x && m_turns.front().getY() == m_y)
		{
			// change direction
			m_dir = m_turns.front().getDir();

			// remove front element of turns
			m_turns.erase(m_turns.begin());
		}
	}

	// move node
	switch (m_dir)
	{
	case dirUp:
		m_y -= 1;
		break;
	case dirRight:
		m_x += 1;
		break;
	case dirDown:
		m_y += 1;
		break;
	case dirLeft:
		m_x -= 1;
		break;
	}

	// check if node is out of bounds, then adjust its position
	if (m_x < 0)
		m_x = (CONSOLE_WIDTH - 1);

	if (m_x > (CONSOLE_WIDTH - 1))
		m_x = 0;

	if (m_y < 0)
		m_y = (CONSOLE_HEIGHT - 1);

	if (m_y > (CONSOLE_HEIGHT - 1))
		m_y = 0;
}


// snake class ********************************************************
snake::snake()
{
	restart();
}
snake::~snake()
{
}

void snake::restart()
{
	m_snake.clear();
	m_speed = 5;
	m_speedIncrement = 0.3;
	m_nodeIncrement = 3;
	
	// load file information
	std::ifstream ifs;
	ifs.open("./game_files/map");
	if (ifs)
	{
		// if file is empty, keep default values for incrementation
		if (!ifs.eof())
		{
			// first two lines contain increment infor (speed/num nodes)
			ifs >> m_speedIncrement;
			ifs >> m_nodeIncrement;
		}
	}
	else
	{
		std::cerr << "Could not open the file!" << std::endl;
	}
	ifs.close();

	// create a snake 
	for (int x=0; x<3; x++)
	{
		addNode();
	}

	m_draw = true;
	m_addturns = false;
	m_detectCollision = true;
}

void snake::addNode()
{
	if (!m_snake.empty())
	{
		// first copy the last node and set it to the previous position of that node
		snake_node new_node;
		new_node = m_snake.back();
		new_node.setChar('o');

		switch (m_snake.back().getDir())
		{
		case dirUp:
			new_node.moveY(1);
			break;
		case dirRight:
			new_node.moveX(-1);
			break;
		case dirDown:
			new_node.moveY(-1);
			break;
		case dirLeft:
			new_node.moveX(1);
			break;
		}

		// append the node to the end of snake
		m_snake.push_back(new_node);
	}
	else
	{
		//snake is empty - create head node
		m_snake.push_back(snake_node());
		m_snake.front().setChar(1);
	}
}

void snake::turn(direction dir)
{
	if (m_addturns)
	{
		// check if this is a real turn 
		// (does the head node turn?) If no, exit
		if (m_snake.front().getDir() == dir)
			return;

		// (is the turn in the opposite direction the head node is moving?) If yes, exit
		if (m_snake.front().getDir() == dirUp && dir == dirDown)
			return;
		else if (m_snake.front().getDir() == dirDown && dir == dirUp)
			return;
		else if (m_snake.front().getDir() == dirLeft && dir == dirRight)
			return;
		else if (m_snake.front().getDir() == dirRight && dir == dirLeft)
			return;

		// for each node, add the turn to the collection of "pending turns"
		for (int x=0; x<m_snake.size(); x++)
		{
			m_snake[x].addTurn(dir, m_snake.front().getX(), m_snake.front().getY());
		}

		// reset addturns to limit the addition of turns to that of the speed. 
		// this eliminates the problem of exessive input being interpretted as real turns
		m_addturns = false;
	}

}

void snake::move()
{
	// move each node at m_speed
	if (m_count >= (1/m_speed))
	{
		for (int x=0; x<m_snake.size(); x++)
		{
			m_snake[x].move();
		}

		// reset count
		m_count = 0;
		m_draw = true;
		m_addturns = true;
		m_detectCollision = true;
	}

	// increment count
	m_count += j_globalTimer::getSingleton()->getDelta();
}

void snake::draw(vector<j_consoleCell>& cells)
{
	// for each node, convert the node into a j_consoleCell and draw the cell
	j_consoleCell cell;
	for (int x=0; x<m_snake.size(); x++)
	{
		cell = static_cast<j_consoleCell> (m_snake[x]);
		cells[(m_snake[x].getY()*80)+m_snake[x].getX()] = cell;
	}

}

int snake::getX()
{
	if (!m_snake.empty())
	{
		return m_snake.front().getX();
	}
	return 0;
}
int snake::getY()
{
	if (!m_snake.empty())
	{
		return m_snake.front().getY();
	}
	return 0;
}
void snake::eat()
{
	m_speed += m_speedIncrement;

	for(int x=0;x<m_nodeIncrement;x++)
	{
		addNode();
	}
}

bool snake::detectCollision()
{
	if (m_detectCollision)
	{
		for (int x=0; x<m_snake.size()-1; x++)
		{
			if (m_snake[0].getX() == m_snake[x+1].getX() && m_snake[0].getY() == m_snake[x+1].getY())
			{
				// MAKE COLLISION POINT A RED X --> m_snake[x]
				m_snake[x+1].setFGColor(conRed);
				m_snake[x+1].setChar('X');
				return true;
			}
		}
		m_detectCollision = false;
	}
	return false;
}


void snake::log()
{
	/* log stuff
	string strlog;
	for (int x=0; x<m_snake.size(); x++)
	{
		strlog = strlog + "node " + NUM_TO_STRING(x) + " x: " + NUM_TO_STRING(m_snake[x].getX()) + "\n";
		strlog = strlog + "node " + NUM_TO_STRING(x) + " y: " + NUM_TO_STRING(m_snake[x].getY()) + "\n";
	}
	strlog = strlog + "--------------------------------------------\n";
	j_dataLogger::getSingleton()->log(strlog, "C:/tmp/snake.txt");
	*/
	
}