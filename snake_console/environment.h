// environment.h - processes and draws the game environment
class environment
{
private:

	//
	j_consoleCell	m_gem;

	// map layout
	vector<bool>	m_map;
	int				m_collisionPoint;
	bool		    m_collision;


public:
	environment();
	~environment();

	bool init();
	bool loadFromFile(const std::string& file);		// file should specify how fast to increase speed, and how many nodes are gained each time gem is eaten. Under that, the map should be drawn 80*25 where x are walls and - are empty space
	void restart();

	bool draw(vector<j_consoleCell>& cells);
	bool detectCollision(int sx, int sy);
	void moveGem();

	int getGemX () {return m_gem.getX();}
	int getGemY () {return m_gem.getY();}

};
