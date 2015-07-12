// app.cpp
#include "stdafx.h"

app::app()
{
	m_exit = false;
	m_count = 0;
	m_lastKeyPressed = 0;
	m_playing = true;
	m_score = 0;
	m_draw = true;
	m_drawCount = 0;
	m_game_state = game_state_menu;
	m_game_level = 0;

	j_consoleCell cell;
	for (int x=0; x<2000; x++)
		m_cells.push_back(cell);

	m_prevCells = m_cells;

}
app::~app()
{
}

bool app::init()
{
	RANDOMIZE_SEED();
	m_log.init(&m_con);
	m_con.setTitle("Snake");

	m_env.init();

	// clear log file
	m_log.log("","C:/tmp/snake.txt", false);


	return true;
}

bool app::update()
{
	m_timer.update();

	m_con >> m_lastKeyPressed;
	m_count += m_timer.getDelta();
	return true;
}

bool app::process()
{
	// if playing, show game, otherwise show message box asking player to play.
	if (!m_playing)
	{
		m_con.drawTextBox("GAME OVER", "                                                               Score: " + NUM_TO_STRING(m_score) + "                                                                                   Try Again?", 
			15, 1, 48, 10, conWhite, conBlack, conRed, conWhite, mboxYesNo);
		char a = 0;

		//save score if it is highest score
		//


		do{
			a = _getch();
		}while(a != 'y' && a != 'n');
		if (a == 'y')
		{
			m_playing = true;
			m_snake.restart();
			m_env.restart();
			m_score = 0;
			m_con.clearScreen();
			m_cells.clear();
			m_lastKeyPressed = 0;
			m_count = 0;

			j_consoleCell cell;
			for (int x=0; x<2000; x++)
				m_cells.push_back(cell);

			m_prevCells = m_cells;

			return true;
		}
		else
		{
			m_exit = true;
			return false;
		}	
	}

	// check for input and try to change snake movement to that direction with move()
	switch (m_lastKeyPressed)
	{
	case keyUp:
		turn(dirUp);
		break;
	case keyRight:
		turn(dirRight);
		break;
	case keyDown:
		turn(dirDown);
		break;
	case keyLeft:
		turn(dirLeft);
		break;
	case 'q':
		m_exit = true;
		break;
	}

	// move snake
	m_snake.move();
	checkCollisions();

	// draw snake and environment
	draw();

	// reset cursor position to 0,0
	m_con.moveCursor(0,0);


	return true;
}

void app::draw()
{
	if (m_drawCount > (1/(m_snake.getSpeed())))
	{

		m_prevCells = m_cells;

		// clear buffer, then fill cell buffer
		j_consoleCell cell;
		for (int x=0; x<2000; x++)
			m_cells[x] = cell;

		m_snake.draw(m_cells);
		m_env.draw(m_cells);

		// draw anything that has changed since last time to the screen
		int i = 0;
		for (int y=0;y<25;y++)
		{
			for (int x=0;x<80;x++)
			{
				m_cells[i].set(x,y);
				if (!(m_cells[i] == m_prevCells[i]))
				{
					m_con.drawCell(m_cells[i]);
				}


				i++;
			}
		}
		m_drawCount = 0;
	}

	// increment count
	m_drawCount += m_timer.getDelta();
}

// turn snake in a given direction
void app::turn(direction dir)
{
	// turn snake if needed
	m_snake.turn(dir);
}

// update environment and check for collisions
void app::checkCollisions()
{
	// check snake collisions with gems
	if (m_snake.getX() == m_env.getGemX() && m_snake.getY() == m_env.getGemY())
	{
		m_snake.eat();
		m_env.moveGem();
		m_score += 5;
	}

	// check snake collisions with itself
	if (m_snake.detectCollision())
	{
		m_playing = false;
		return;
	}

	// check snake collisions with walls
	if (m_env.detectCollision(m_snake.getX(), m_snake.getY()))
	{
		m_playing = false;
		return;
	}
}