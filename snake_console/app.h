// app.h - main container class for the application


// game state
enum game_state
{
	game_state_menu,
	game_state_playing,
	game_state_highscores,
	game_state_about,
	game_state_game_over,
};


// app class
class app
{
private:
	// engine manager objects
	j_globalTimer	m_timer;
	j_dataLogger	m_log;
	j_console		m_con;

	bool			m_exit;

	// game manager objects
	snake			m_snake;
	environment		m_env;

	// game variables
	float			m_count;
	char			m_lastKeyPressed;
	bool			m_playing;
	game_state		m_game_state;
	int				m_game_level;			// 0 = quick start, 1 = level 1, etc.
	int				m_score;
	bool			m_draw;
	float			m_drawCount;

	// master draw vector - this vector is constantly updated and the only thing that will be drawn
	vector<j_consoleCell>	m_cells;

	// keep copy of previous cell canvas and only draw the different ones
	vector<j_consoleCell>	m_prevCells;


public:
	app();
	~app();

	bool init();
	bool update();
	bool process();
	void draw();

	//
	// attempt to turn player in a given direction
	void turn(direction dir);

	// update environment and check for collisions
	void checkCollisions();


	bool exit() {return m_exit;}

};