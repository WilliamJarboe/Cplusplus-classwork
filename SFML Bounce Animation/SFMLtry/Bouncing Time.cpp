/*
* Course: CMPS 2143 - OOP
*
* Purpose: Creates a Clock Class to handle the counter
* moving, and bouncing off of the edges
*
* @author Evan Jackson
* @version 1.0 11/14/2018
* @github https://github.com/ejackson007/2143-OOP-Jackson
*/

//I had used the current time while debugging it,
//and Visual Studios gives a warning, so I had to 
//put in an ignore of the warning
#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include "Group.h"
#include <ctime>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

const int WINDOWWIDTH = 500;
const int WINDOWHEIGHT = 500;

using namespace std;

class Counter{
private:
	sf::Clock clock;
	sf::Time start;
	sf::Time end;
	sf::Time elapsed;
	int xPosition, yPosition;
	
public:
	/**
	* Creates Counter
	* @param ()
	* @return n/a
	*/
	Counter()
	{
		start = sf::seconds(0);
		end = sf::seconds(0);
	}

	/**
	* Creates Counter
	* @param (int s, int e)
	* @return n/a
	*/
	Counter(int s, int e)
	{
		start = sf::seconds(s);
		end = sf::seconds(e);
	}

	/**
	* gets the elapsed time
	* @param ()
	* @return round(elapsed)
	*/
	int getElapsed()
	{
		elapsed = clock.getElapsedTime();
		 //used round function to get rid of decimals
		return round(elapsed.asSeconds());
	}

	/**
	* return the start time
	* @param ()
	* @return start of clock
	*/
	int getStart()
	{
		return start.asSeconds();
	}
	
	/**
	* set start time 
	* @param (int x)
	* @return void
	*/
	void setStart(int x)
	{
		start = sf::seconds(x);
	}

	/**
	* returns the end time
	* @param ()
	* @return end of clock
	*/
	int getEnd()
	{
		return end.asSeconds();
	}

	/**
	* set end time
	* @param (int x)
	* @return void
	*/
	void setEnd(int x)
	{
		end = sf::seconds(x);
	}


};

class Clock : public sf::Text{
private:
	sf::Font font;
	int xTranslation, yTranslation;
	Counter c;
	bool up;

public:
	Clock()
	{
		if (!font.loadFromFile("imagine_font.otf")) {
			std::cout << "error loading font...\n";
		}
		else {
			setFont(font);
		}
		setString("Time to get a watch");
		setCharacterSize(15);
		setFillColor(sf::Color::Cyan);
		setPosition(200, 200);

		xTranslation = .05;
		yTranslation = .05;
		up = true;
	}

	void setTime(int x, int y)
	{
		c.setStart(x);
		c.setEnd(y);
		if (x > y)
			up = false;
		else if (x == y)
			setString("CANNOT ENTER SAME NUMBERS");

		if (up)
			setString("Incrementing Clock: " + to_string(x));
		else
			setString("Decrementing Clock: " + to_string(x));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);

	}

	void updateText()
	{
		move(xTranslation, yTranslation);

		if (getPosition().x  + (getLocalBounds().width / 2) >= WINDOWWIDTH || getPosition().x - (getLocalBounds().width / 2) <= 0)
			xTranslation *= -1;

		if (getPosition().y + (getLocalBounds().height / 2) >= WINDOWHEIGHT || getPosition().y - (getLocalBounds().height / 2) <= 0)
			yTranslation *= -1;

		if (up)
			setString("" + to_string(c.getStart() + c.getElapsed()));


		else if (!up)
			setString("" + to_string(c.getStart() - c.getElapsed()));
	}

		/**
	* Checks if the program should close
	* @param ()
	* @return n/a
	*/
	bool checkClose()
	{
		if ((c.getStart() + c.getElapsed()) == c.getEnd() + 1)
			return true;
		else if ((c.getStart() - c.getElapsed()) == c.getEnd() - 1)
			return true;
		else
			return false;
	}

		/**
	* Sets color using color object
	* @param ()
	* @return n/a
	*/
	void settextColor(sf::Color c)
	{
		setColor(c);
	}

		/**
	* sets color using rgb values
	* @param ()
	* @return n/a
	*/
	void settextColor(int x, int y, int z)
	{
		setColor(sf::Color(x, y, z));
	}

	/*sf::Text getText()
	{
		return text;
	}*/
};

/*Bounding box is a class that displays a
**rectangle behind the clock.
*/
class BoundingBox : public sf::RectangleShape {
private:
	int width;
	int height;
	int xTranslation, yTranslation;
public:
	
	BoundingBox()
	{

	}

	BoundingBox(int x, int y)
	{
		
		width = 45;
		height = 45;

		setSize(sf::Vector2f(width, height));
		setOrigin(width / 2, height / 2);
		setFillColor(sf::Color::Black);
		setOutlineColor(sf::Color::Cyan);
		setOutlineThickness(20);
		setPosition(x,y);
		xTranslation = .05;
		yTranslation = .05;
	}

	
	void updateBox()
	{
		move(xTranslation, yTranslation);
		if (getPosition().x + (width / 2) >= WINDOWWIDTH || getPosition().x - (width / 2) <= 0)
			xTranslation *= -1;

		if (getPosition().y + (height / 2) >= WINDOWHEIGHT || getPosition().y - (height / 2) <= 0)
			yTranslation *= -1;
	}


	void setboxColor(sf::Color c)
	{
		setFillColor(c);
	}

	
	void setboxColor(int x, int y, int z)
	{
		setFillColor(sf::Color(x, y, z));
	}
	
	
	void setOboxColor(sf::Color c)
	{
		setOutlineColor(c);
	}

	
	void setOboxColor(int x, int y, int z)
	{
		setOutlineColor(sf::Color(x, y, z));
	}

};




class ClockClass : public Group {
private:
	int x;
	int y;
	int h;
	int w;
	int xVel;
	int yVel;

public:
	Clock clock;
	BoundingBox box;
	ClockClass() {
		push_back(box);
		push_back(clock);
	}

	ClockClass(int x, int y, int start, int end, int xvel, int yvel) {
		clock.setTime(start, end);
		push_back(box);
		push_back(clock);
	}

	void update() {
		x += xVel;
		y += yVel;
		clock.setPosition(x,y);
	}

};


int main()
{
	ClockClass G = ClockClass(70,70,0,100,0.04,0.04);
	//I have to read in Start and End first to get the correct size for the bounding box
	int start, end;
	
	G.clock.setTime(0, 99999);

	//Passes in clock so that I know how large to build it
	//could overload class to use other drawables as well
	


	sf::RenderWindow window(sf::VideoMode(WINDOWHEIGHT, WINDOWWIDTH), "SFML works!");

	 while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
        window.clear();


		G.update();


        window.draw(G);
		//window.draw(D);
        window.display();

		//D.updateDraw();
		//Must push and update so that Draw will have new values
		
		//clock.updateTime();
		G.box.updateBox();
		G.clock.updateText();
		//Check if they are equal and can close
		if (G.clock.checkClose())
			window.close();

    }

	//system("pause");
	return 0; 
}