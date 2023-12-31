#include <iostream>
#include <SFML/Graphics.hpp>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <fstream>
#include <X11/Xlib.h>
#include "queue.h"
#include "fruits.h"
#include "board.h"
#include "players.h"
using namespace std;
using namespace sf;

int n=15;
int screenSize = 500;
int BlockSize;
int slepTime = 1;

struct Argument
{
	Queue<char> *MessageQueue;
	Player1 *P1;
	Player2 *P2;
	RenderWindow * window;
	Apple* a;
	int Atotal;
	Banana* b;
	int Btotal =0;
	Leaf* l;
	int Ltotal =0;
	
	Argument(Queue<char>* mQ = NULL, Player1* P1q = NULL, Player2* P2q =NULL,RenderWindow* w=NULL, Apple* A=NULL, Banana* B=NULL, Leaf* L=NULL,int app=0, int bana =0 , int lef = 0)
	{
	
		MessageQueue = mQ;
		P1 =P1q;
		P2 = P2q;
		window = w;
		a = A;
		b= B;
		l = L;
		Atotal = app;
		Btotal = bana;
		Ltotal = lef;
	}
};


/////////collision functions

char collision(Player1 *p1 = NULL,Apple * a=NULL,int Atotal=0, Banana * b=NULL,int Btotal=0, Leaf* l=NULL,int Ltotal=0 )
{
//check for any collsion
	//sif()
	for(int i=0;i<Atotal;i++)
	{
		if(p1->x_axis+BlockSize > a[i].apple_x and 
		p1->y_axis+BlockSize > a[i].apple_y and 
		p1->x_axis < (a[i].apple_x+BlockSize) and 
		p1->y_axis < (a[i].apple_y+BlockSize))
		{
			a[i].apple.setPosition(5000,5000);
			a[i].apple_x = 5000;
			a[i].apple_y = 5000;
			return 'a';
		}
		
	}
	for(int i=0;i<Btotal;i++)
	{
		if(p1->x_axis+BlockSize >b[i].banana_x and 
		p1->y_axis+BlockSize > b[i].banana_y and 
		p1->x_axis < (b[i].banana_x+BlockSize) and 
		p1->y_axis < (b[i].banana_y+BlockSize))
		{
			b[i].banana.setPosition(5000,5000);
			b[i].banana_x = 5000;
			b[i].banana_y = 5000;
			return 'b';
		}
		
	}
	for(int i=0;i<Ltotal;i++)
	{
		if(p1->x_axis+BlockSize >l[i].leaf_x and 
		p1->y_axis+BlockSize > l[i].leaf_y and 
		p1->x_axis < (l[i].leaf_x+BlockSize) and 
		p1->y_axis < (l[i].leaf_y+BlockSize))
		{
			l[i].leaf_x = 5000;
			l[i].leaf_y = 5000;
			l[i].leaf.setPosition(5000,5000);
			return 'l';
		}
		
	}
	return '=';
	
}

//function overloading for player 2 collision

char collision(Player2 *p2 = NULL,Apple * a=NULL,int Atotal=0, Banana * b=NULL,int Btotal=0, Leaf* l=NULL,int Ltotal=0 )
{
//check for any collsion
	//sif()
	sf::Vector2f scale = p2->player2.getScale();
	for(int i=0;i<Atotal;i++)
	{
		if(p2->x_axis+BlockSize >a[i].apple_x and 
		p2->y_axis+BlockSize > a[i].apple_y and 
		p2->x_axis < (a[i].apple_x+BlockSize) and 
		p2->y_axis < (a[i].apple_y+BlockSize))
		{
			a[i].apple_x = 5000;
			a[i].apple_y = 5000;
			a[i].apple.setPosition(5000,5000);
			return 'a';
		}
		
	}
	for(int i=0;i<Btotal;i++)
	{
		if(p2->x_axis+BlockSize >b[i].banana_x and 
		p2->y_axis+BlockSize > b[i].banana_y and 
		p2->x_axis < (b[i].banana_x+BlockSize) and 
		p2->y_axis < (b[i].banana_y+BlockSize))
		{
			b[i].banana.setPosition(5000,5000);
			b[i].banana_x = 5000;
			b[i].banana_y = 5000;
			return 'b';
		}
		
	}
	for(int i=0;i<Ltotal;i++)
	{
		if(p2->x_axis+BlockSize >l[i].leaf_x and 
		p2->y_axis+BlockSize > l[i].leaf_y and 
		p2->x_axis < (l[i].leaf_x+BlockSize) and 
		p2->y_axis < (l[i].leaf_y+BlockSize))
		{
			l[i].leaf.setPosition(5000,5000);
			l[i].leaf_x = 5000;
			l[i].leaf_y = 5000;
			return 'l';
		}
		
	}
	return '=';
	
}

//we need args for collision and a queue for players and a window obj
void * player1Thread(void * arg)
	{
		Argument* argument = (Argument*) arg;
		RenderWindow * window = argument->window;
		Player1 * ptrP1;//ptr to pass to queue
		Queue<char>* MQueue = argument->MessageQueue;
		char mms;
		// the rendering loop
		while (window->isOpen())
		{
			if(!window->isOpen())
			{
				break;
			}
			//////////////////key detection for player 1
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					// right key is pressed: move our character
					MQueue->enqueue('R');
					//P1.movePlayRight();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// left key is pressed: move our character
					MQueue->enqueue('L');
					//P1.movePlayerLeft();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// up key is pressed: move our character
					MQueue->enqueue('U');
					//P1.movePlayerUp();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					// down key is pressed: move our character
					MQueue->enqueue('D');
					//P1.movePlayerDown();
				}
			///collision func call
			
		   	mms = collision(argument->P1,argument->a,argument->Atotal,argument->b, argument->Btotal, argument->l, argument->Ltotal);
			if(mms == 'a' || mms == 'b' || mms == 'l')
				{
					MQueue->enqueue(mms);
				}
			
			/////
			//window->clear();
		    // draw...
		    
		    // end the current frame
		    //window->display();
		    sleep(slepTime);
		}
		cout<<"out"<<endl;
		pthread_exit (NULL) ;
	}
///for player 2

void * player2Thread(void * arg)
	{
		cout<<"entering thread for player 2";
		Argument* argument = (Argument*) arg;
		RenderWindow * window = argument->window;
		Player2 * ptrP2;//ptr to pass to queue
		Queue<char>* MQueue = argument->MessageQueue;
		char mms;
		// the rendering loop
		while (window->isOpen())
		{
			if(!window->isOpen())
			{
				break;
			}
			//////////////////key detection for player 1
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					// right key is pressed: move our character
					MQueue->enqueue('R');
					//P1.movePlayRight();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					// left key is pressed: move our character
					MQueue->enqueue('L');
					//P1.movePlayerLeft();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					// up key is pressed: move our character
					MQueue->enqueue('U');
					//P1.movePlayerUp();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					// down key is pressed: move our character
					MQueue->enqueue('D');
					//P1.movePlayerDown();
				}
			///collision func call
			
		   	mms = collision(argument->P2,argument->a,argument->Atotal,argument->b, argument->Btotal, argument->l, argument->Ltotal);
			if(mms == 'a' || mms == 'b' || mms == 'l')
				{
					MQueue->enqueue(mms);
				}
			
			/////
			//window->clear();
		    // draw...
		    
		    // end the current frame
		    window->display();
		    sleep(slepTime);
		}
		cout<<"out"<<endl;
		pthread_exit (NULL) ;
	}

int main()
{
	int windowSize = 500;
	XInitThreads();
	RenderWindow window(VideoMode(windowSize,windowSize), "fruit hunt!");
    RenderWindow * win =&window;
	pthread_t t1,t2;
	pthread_attr_t attr1,attr2;
	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1,PTHREAD_CREATE_DETACHED);
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr2,PTHREAD_CREATE_DETACHED);
	/*
		0- empty 
		1-apple (red circle) 2pts
		2-banana (yellow rectangle) 4pts
		3-orange (orange circle)  
		4-leaf (greeen triangle)  6pts
	*/
	int appleScore = 2, bananaScore = 4,leafScore =6, noApple=0, noBanana=0, noOrange=0,noLeaf =0;
	
	//load fonts and text object /usr/share/fonts/X11/Type1/c0632bt_.pfb
	sf::Font font;
	if (!font.loadFromFile("cour.ttf"))
	{
	    // error...
	}
	sf::Text winText;

	// select the font
	winText.setFont(font); // font is a sf::Font

	// set the string to display

	// set the character size
	winText.setCharacterSize(24); // in pixels, not points!

	// set the color
	winText.setFillColor(sf::Color::Yellow);
	
	
	srand(time(0));
	/* n=5;
	int ** board = new int *[n];
	for(int i=0;i<n;i++)
		board[i] = new int[n];
	*/
	int ** board = generateBoard(n);
    BlockSize = screenSize/n;
    cout<<n<<" "<<BlockSize<<endl;
   
	for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				board[i][j] = rand()%5;
				if( board[i][j] == 1)
					{
						
						noApple++;
					}
				else if( board[i][j] == 2)
					{
						noBanana++;
					}
				else if( board[i][j] == 3)
					{
						noOrange++;
					}
				else if( board[i][j] == 4)
					{
						noLeaf++;
					}
			}
		}
		
	Apple * apple_ = new Apple [noApple];
	Banana * banana_ = new Banana [noBanana];
	Orange * orange_ = new Orange [noOrange];
	Leaf * leaf_ = new Leaf [noLeaf];
	int Acounter=0, Bcounter=0, Ocounter=0, Lcounter=0;
	for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
			//check for each apple and update apple position
				if(board[i][j] == 1)
				{
					apple_[Acounter].apple_x =i *BlockSize;
					apple_[Acounter].apple_y =j *BlockSize;
					apple_[Acounter].apple.setPosition (apple_[Acounter].apple_x, apple_[Acounter].apple_y);
					Acounter++;
				}
				else if(board[i][j] == 2)
				{
					banana_[Bcounter].banana_x = i *BlockSize;
					banana_[Bcounter].banana_y = j *BlockSize;
					banana_[Bcounter].banana.setPosition(banana_[Bcounter].banana_x, banana_[Bcounter].banana_y);
					Bcounter++;
				}
				else if(board[i][j] == 3)
				{
					orange_[Ocounter].orange_x = i *BlockSize;
					orange_[Ocounter].orange_y = j *BlockSize;
					orange_[Ocounter].orange.setPosition (orange_[Ocounter].orange_x, orange_[Ocounter].orange_y);
					Ocounter++;
				}
				else if(board[i][j] == 4)
				{
					leaf_[Lcounter].leaf_x = i *BlockSize;
					leaf_[Lcounter].leaf_y = j *BlockSize;
					leaf_[Lcounter].leaf.setPosition (leaf_[Lcounter].leaf_x, leaf_[Lcounter].leaf_y);
					Lcounter++;
				}
			}
			
		}
	//player object
	Player1 P1(BlockSize,n);	//creating player in thread
	Player2 P2(BlockSize,n);
	Player1 * Pptr = &P1;
	Player2 * Pptr2 = &P2;
	//queue for char 1
	Queue<char> q;
	Queue<char>* messageQ = &q; //q which is to be passed to argument struct
	//queue for char 2
	Queue<char> q2;
	Queue<char>* messageQ2 = &q2; //q which is to be passed to argument struct
	char message;
	char message2;
	//argument struct for player1 thread
	
	//create thread for player 1 
	
	window.setActive(false);
	Argument argument(messageQ,Pptr, NULL, &window,apple_,banana_,leaf_,noApple,noBanana,noLeaf);
	Argument *arg = &argument;
	pthread_create(&t1,&attr1,player1Thread,(void *)arg);// thr
	
	window.setActive(false);
	Argument argument2(messageQ2,NULL, Pptr2, &window,apple_,banana_,leaf_,noApple,noBanana,noLeaf);
	Argument *arg2 = &argument2;
	pthread_create(&t2,&attr2,player2Thread,(void *)arg2);// thr
	RectangleShape bb;
	
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed)
            {
                
			}
        
			
        }
        //dequeue messages for player1
      
      	 while(!messageQ->isEmpty() || !messageQ2->isEmpty())
		{
			if(!messageQ->isEmpty())
			{
				
				if(!messageQ->isEmpty())
				{
					message=messageQ->Front();
				}
				messageQ->dequeue();
				//conditions for movements of player 1
				if (message == 'R')
					{
						// right key is pressed: move our character
						P1.movePlayRight();
					}
				if (message == 'L')
					{
						// right key is pressed: move our character
						P1.movePlayerLeft();
					}
				if (message == 'U')
					{
						// right key is pressed: move our character
						P1.movePlayerUp();
					}
				if (message == 'D')
					{
						// right key is pressed: move our character
						P1.movePlayerDown();
					}
				if(message == 'a')
					{
						P1.score += appleScore;
						Acounter--;
					}
				if(message == 'b')
					{
						P1.score += bananaScore;
						Bcounter--;
					}
				if(message == 'l')
					{
						P1.score += leafScore;
						Lcounter--;
					}
			}
			if(!messageQ2->isEmpty())
			{
				if(!messageQ2->isEmpty())
				{
					message2=messageQ2->Front();
				}
				messageQ2->dequeue();
				//conditions for movements of player 1
				if (message2 == 'R')
					{
						// right key is pressed: move our character
						P2.movePlayRight();
					}
				if (message2 == 'L')
					{
						// right key is pressed: move our character
						P2.movePlayerLeft();
					}
				if (message2 == 'U')
					{
						// right key is pressed: move our character
						P2.movePlayerUp();
					}
				if (message2 == 'D')
					{
						// right key is pressed: move our character
						P2.movePlayerDown();
					}
				if(message2 == 'a')
					{
					
						P2.score += appleScore;
						Acounter--;
					}
				if(message2 == 'b')
					{
						P2.score += bananaScore;
						Bcounter--;
					}
				if(message2 == 'l')
					{
						P2.score += leafScore;
						Lcounter--;
					}
			}
			
		}
        cout<<"player1: "<<P1.score<<'\t'<<"player2:"<<P2.score<<endl;
		//collision(Pptr,apple_,noApple,banana_,noBanana,leaf_,noLeaf);
		//collision(Pptr2,apple_,noApple,banana_,noBanana,leaf_,noLeaf);
	//check if apples bananas and leafs have all ben picked up
	
	if(Acounter <= 0 && Bcounter <= 0 && Lcounter <=0)
	{
		string winMess;
		//cout<<"end ga,e"<<endl;
		if(P1.score> P2.score)
		{
			winMess = "PLAYER 1 WINS \n";
		}
		else
		{
			winMess = "PLAYER 2 WINS \n";
		}
		winMess += "Player1 : " + to_string(P1.score);
		winMess += "\n Player2 : " + to_string(P2.score);
		window.clear();
		winText.setString(winMess);
		window.draw(winText);
		sleep(4);
		//window.close();
	}
        window.clear();
        //draw board
        for(int k=0;k<n;k++)
        {
        	 for(int i=0;i<n;i++)
		    {		    
		    	if(k%2==0 && i%2 == 0)
		    	{
		    		bb = DrawSq(i*BlockSize,k*BlockSize,BlockSize);
		    		window.draw(bb);
		    	}
		    	else if (k%2!=0 && i%2 != 0)
		    	{
		    		bb = DrawSq(i*BlockSize,k*BlockSize,BlockSize);
		    		window.draw(bb);
		    	}
		    }
        }
       //draw fruits
        
        for (int i=0;i< noApple ;i++)
        {
        	window.draw(apple_[i].apple);
        }
         for (int i=0;i< noBanana ;i++)
        {
        	window.draw(banana_[i].banana);
        }
         for (int i=0;i< noLeaf ;i++)
        {
        	window.draw(leaf_[i].leaf);
        }
        //draw players
        window.draw(P2.player2);
        window.draw(P1.player1);
        window.display();
        sleep(slepTime);
    }
	cout<<"player1: "<<P1.score<<'\t'<<"player2:"<<P2.score<<endl;
	
    return 0;
}
