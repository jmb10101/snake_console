// snake.h - manages the snake

// direction
enum direction
{
	dirUp,
	dirRight,
	dirDown,
	dirLeft
};

// class to define a turn
class turn
{
private:
	direction	m_dir;
	int			m_x;
	int			m_y;

public:
	turn();
	~turn();

	void	setDir(direction dir) {m_dir=dir;}
	void	setX(int x) {m_x=x;}
	void	setY(int y) {m_y=y;}
	void	set(int x, int y, direction dir) {setDir(dir); setX(x); setY(y);}

	direction	getDir() {return m_dir;}
	int			getX() {return m_x;}
	int			getY() {return m_y;}
};

// class to define a node in the snake
class snake_node : public j_consoleCell
{
private:

	//
	direction    m_dir;
	vector<turn> m_turns;	// keeps track of pending turns the node must make

public:
	snake_node();
	~snake_node();

	void setDir(direction dir) {m_dir = dir;}
	direction getDir() {return m_dir;}
	void addTurn(direction dir, int x, int y);
	void move();

};

// snake manager class
class snake
{
private:

	//
	float				m_speed;
	float				m_speedIncrement;
	int					m_nodeIncrement;

	float				m_count;
	vector<snake_node>	m_snake;

	bool				m_draw;
	bool				m_addturns;
	bool				m_detectCollision;

public:
	snake();
	~snake();

	void restart();

	void addNode();
	void turn(direction dir);
	void move();
	void draw(vector<j_consoleCell>& cells);

	
	float getSpeed() {return m_speed;}
	int getX();
	int getY();
	void eat();

	bool detectCollision();

	// logging 
	void log();

};
