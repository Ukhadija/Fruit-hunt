#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;


RectangleShape DrawSq(int i, int j, int blckSize)
{
	sf::RectangleShape rectangle(sf::Vector2f(blckSize, blckSize));
	rectangle.setFillColor(sf::Color(222, 166,84));
	rectangle.setPosition(i,j);
	return rectangle;
}

int** generateBoard(int &size)
{
	//generate random number between 10 to 99
	srand(time(0));
	double Rnum = rand()%(99-10+1);
	//multiply with last digit of roll number
	//0427
	Rnum *= 7;
	//divide roll num with generated numbnre
	double number, rollNumber =427;
	number = rollNumber / static_cast<double>(Rnum);
	//take mod with 25 , if less than 10 and add 15
	int n = number;
	n = n%25;

	if(n < 10)
	{
		n+=15;
	}
	//create n*n matrix
	int ** board = new int* [n];
	for(int i=0;i<n;i++)
	{
		board[i] =  new int[n];
	}
	size =n;
	return board;
}


