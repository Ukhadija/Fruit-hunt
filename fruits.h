#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

struct Apple
{

	sf::Texture Appletexture;
	sf::Sprite apple;
	int apple_x;
	int apple_y;
	bool status;
	Apple(int x=0, int y=0)
	{
		
		if (!Appletexture.loadFromFile("applw.png"))
		{
			// error...
		}
		
		apple.setTexture(Appletexture);
		apple.setScale(0.02f,0.02f);
		status = true;
		apple_x = 0;
		apple_y = 0;
		apple.move(apple_x, apple_y);
	}
	
	void moveApple (int x, int y)
    	{
    		
    		apple.move(x,y);
    	}
	
};

struct Banana
{
	sf::Texture Bananatexture;
	sf::Sprite banana;
	int banana_x;
	int banana_y;
	bool status;
	Banana(int x=0, int y=0)
	{
		status = true;
		if (!Bananatexture.loadFromFile("banana.png"))
		{
			// error...
		}
		banana.setTexture(Bananatexture);
		banana.setScale(0.03f,0.03f);
		banana_x = x;
		banana_y = y;
		banana.move(banana_x, banana_y);	
    }
    void moveBanana (int x, int y)
    	{
    		
    		banana.move(x,y);
    	}
    
    
};


struct Orange
{
	CircleShape orange;
	int orange_x;
	int orange_y;
	bool status;
	Orange(int x=0, int y=0)
	{
		status = true;
		orange.setFillColor(Color::Blue);
		orange.setRadius(10);
		orange_x = x;
		orange_y = y;
		orange.move(orange_x, orange_y);	
    	}
    	void moveOrange (int x, int y)
    	{
    		
    		orange.move(x,y);
    		return;
    	}
    
    
};

struct Leaf
{
	sf::Texture leaftexture;
	sf::Sprite leaf;
	int leaf_x;
	int leaf_y;
	bool status;
	Leaf(int x=0, int y=0)
	{
		status = true;
		if (!leaftexture.loadFromFile("leaf.png"))
		{
			// error...
		}
		
		leaf.setTexture(leaftexture);
		leaf.setScale(0.04f,0.04f);
		leaf_x = x;
		leaf_y = y;
		leaf.move(leaf_x, leaf_y);	
    }
    void moveLeaf (int x, int y)
    	{
    		
    		leaf.move(x,y);
    	}
    
    
};

