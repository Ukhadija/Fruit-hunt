#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;



int BoardSize =500;



///struct to define player1
struct Player1
{	
	sf::Texture player1texture;
	sf::Sprite player1;
	int x_velocity =60;
	int y_velocity =60;
	int score;
	int x_axis;
	int y_axis;
	int numBlocks;
	public:
	Player1(int BlockSize =0,int num=0 ,int x =0, int y =0, int s =0)
	{
		if (!player1texture.loadFromFile("fox.png" ,sf::IntRect(100, 100,4000,4000)))
		{
			// error...
		}
		
		player1.setTexture(player1texture);
		player1.setScale(0.008f,0.008f);
		score = s;
		x_axis = x;
		y_axis = y;
		player1.setPosition(sf::Vector2f(x_axis,y_axis));
		x_velocity =BlockSize;
		y_velocity =BlockSize;
		numBlocks = num;
	}
	void operator=(const Player1 &p)
	{
		score = p.score;
		player1 = p.player1;
		x_axis = p.x_axis;
		y_axis = p.y_axis;
	}
	void movePlayerLeft()
	{
		if(x_axis > 0)
		{
			x_axis -= x_velocity;
			player1.move(-x_velocity,0.0);
		}
		
	}
	
	void movePlayRight()
	{
		if(x_axis+x_velocity < numBlocks*x_velocity)
		{
			
			x_axis+= x_velocity;
			player1.move(x_velocity,0.0);
		}
		
	}
	void movePlayerUp()
	{
		if(y_axis > 0 )
		{
			y_axis -= y_velocity;
			player1.move(0.0,-y_velocity);
		}
		
		
	}
	void movePlayerDown()
	{
		if(y_axis+ y_velocity < numBlocks*y_velocity)
		{
			y_axis += y_velocity;;
			player1.move(0.0,y_velocity);
		}	
	}
};

struct Player2
{
	sf::Texture player2texture;
	sf::Sprite player2;
	int x_velocity =60;
	int y_velocity =60;
	int score=0;
	int x_axis;
	int y_axis;
	int numBlocks;
	public:
	Player2(int BlockSize =0, int n = 0 ,int x =0, int y =0, int s =0)
	{
		if (!player2texture.loadFromFile("cat.png",sf::IntRect(10, 10,661,571)))
		{
			// error...
		}
		
		player2.setTexture(player2texture);
		player2.setScale(0.05f,0.05f);
		score = s;
		x_axis = x;
		y_axis = y;
		player2.setPosition(sf::Vector2f(x_axis,y_axis));
		x_velocity =BlockSize;
		y_velocity =BlockSize;
		numBlocks = n;
	}
	void operator=(const Player2 &p)
	{
		score = p.score;
		player2 = p.player2;
		x_axis = p.x_axis;
		y_axis = p.y_axis;
	}
	void movePlayerLeft()
	{
		if(x_axis > 0)
		{
			x_axis -= x_velocity;
			
			player2.move(-x_velocity,0.0);
		}
		
	}
	
	void movePlayRight()
	{
		if(x_axis+x_velocity < numBlocks * x_velocity)
		{
			
			x_axis+= x_velocity;
			player2.move(x_velocity,0.0);
		}
		
	}
	void movePlayerUp()
	{
		if(y_axis > 0 )
		{
			y_axis -= y_velocity;
			player2.move(0.0,-y_velocity);
		}
		
		
	}
	void movePlayerDown()
	{
		if(y_axis + y_velocity < numBlocks * y_velocity)
		{
			y_axis += y_velocity;;
			player2.move(0.0,y_velocity);
		}
		
		
	}
};

