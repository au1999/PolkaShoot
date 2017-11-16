#include<SFML/Graphics.hpp>
#include<stdio.h>
#include"Physics.h"
#include<thread>
#include<sstream>

#define centerx 600
#define centery 400
using namespace sf;
using namespace std;

int initx = 200;
int inity = 600;
float angle=0;
float power=0;
int score = 0;
int ballstat = 1;



void snd()
{
	int s1[] = {7,6,5,3,5,0,6,5,3,1,3,0,5,3,1,-1,1,0};
	int ds1[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,4};
	int i = 0;
	while (1)
	{
		if (s1[i % 17] != 0)
		{
			_beep(powf(1.059463,s1[i%17]-1)*523,ds1[i%17]*1000);
		}
		else
		{
			_beep(0, ds1[i % 17] * 1000);
		}
		i++;
	}
	
}






int main()
{

////Define Window size
	RenderWindow window(VideoMode(2*centerx,2*centery), "Polka Shoot!");
	window.setFramerateLimit(60);
	
	

////Define Physics system
	Physics sys1(10, 750);
	sys1.initpos(0, 750);

////Define circle a
	Circle cira;

	cira.setRadius(10);
	cira.include(sys1);
	cira.goinit();
	cira.v.x = 0;
	cira.setPosition(0, 600);
	cira.m = 1;
	cira.setFillColor(Color(0x73d7d7ff));

////Define compass
	RectangleShape compass;
	compass.setSize(Vector2f(20, 2));
	compass.setOrigin(10, 1);
	compass.setPosition(cira.getPosition());



////call timer
	Clock c;
	Time t = c.getElapsedTime();
	Int32 tmis = t.asMilliseconds();
	float tm = tmis / 1000;




////get font
	Font normal;
	Font bold;
	Font selected;
	if(!normal.loadFromFile("CaviarDreams.ttf"))
	{
		cout << "'nornal' Font Error";
	}
	if (!bold.loadFromFile("CaviarDreams_Bold.ttf"))
	{
		cout << "'bold' Font Error";
	}
	if (!selected.loadFromFile("CaviarDreams_BoldItalic.ttf"))
	{
		cout << "'selected' Font Error";
	}

////get color
	Color cbold(255,255,255,255);
	Color cnormal(128, 128, 128, 255);
	Color cselected(255, 128, 128, 255);

////define and init pause page's text
	Text paused;
	Text cont;
	Text mainmenu;
	Text exit;
	Text reset;
	float midpoint=0;
	int selectedstate = 0;

	paused.setString("Paused");
	paused.setFont(bold);
	paused.setCharacterSize(125);
	paused.setFillColor(cbold);
	midpoint = paused.getGlobalBounds().width / 2;
	paused.setOrigin(midpoint,0);
	paused.setPosition(centerx,100);

	cont.setString("Continue");
	cont.setFont(normal);
	cont.setColor(cnormal);
	cont.setCharacterSize(75);
	midpoint = cont.getGlobalBounds().width / 2;
	cont.setOrigin(midpoint, 0);
	cont.setPosition(centerx, 255);

	reset.setString("Reset");
	reset.setFont(normal);
	reset.setColor(cnormal);
	reset.setCharacterSize(75);
	midpoint = reset.getGlobalBounds().width / 2;
	reset.setOrigin(midpoint, 0);
	reset.setPosition(centerx, 355);
	
	mainmenu.setString("Main Menu");
	mainmenu.setFont(normal);
	mainmenu.setColor(cnormal);
	mainmenu.setCharacterSize(75);
	midpoint = mainmenu.getGlobalBounds().width / 2;
	mainmenu.setOrigin(midpoint, 0);
	mainmenu.setPosition(centerx, 455);

	exit.setString("Exit");
	exit.setFont(normal);
	exit.setColor(cnormal);
	exit.setCharacterSize(75);
	midpoint = exit.getGlobalBounds().width / 2;
	exit.setOrigin(midpoint, 0);
	exit.setPosition(centerx, 555);

////ENDDEF/////////////////////////////////////////


////mainpage DEFINE ///////////////////////////////

	RectangleShape a;
	a.setSize(Vector2f(600, 400));
	a.setFillColor(Color(255, 255, 255, 150));
	a.setOrigin(600,400);
	a.setPosition(2*centerx-50,2*centery-50);

	Circle cirm;
	cirm.setRadius(10);
	cirm.include(sys1);
	cirm.goinit();
	cirm.v.x = 20;
	cirm.setPosition(0, 600);
	cirm.setOrigin(cirm.getRadius(), cirm.getRadius());
	cirm.m = 1;
	cirm.setFillColor(Color(255, 255, 255, 50));

	Text polka;
	polka.setString("Polka Shoot!");
	polka.setFont(normal);
	polka.setColor(Color(0X76E0E0FF));
	polka.setCharacterSize(200);
	midpoint = polka.getGlobalBounds().width / 2;
	polka.setOrigin(midpoint, 0);
	polka.setPosition(centerx-10, 50);

	Text play;
	play.setString("Play");
	play.setFont(normal);
	play.setColor(cnormal);
	play.setCharacterSize(75);
	midpoint = play.getGlobalBounds().width / 2;
	play.setOrigin(midpoint, 0);
	play.setPosition(centerx/2, 355);

	Text how;
	how.setString("How to play");
	how.setFont(normal);
	how.setColor(cnormal);
	how.setCharacterSize(75);
	midpoint = how.getGlobalBounds().width / 2;
	how.setOrigin(midpoint, 0);
	how.setPosition(centerx / 2, 485);


////ENDDEF/////////////////////////////////////////

/*
use both Slider to adjust shooting power and angle
use adjustment knob to adjust gravity
use button to change the ball
use 't' and 'g' to adjust angle
use 'h' and 'j' to adjust power

press 'ESC' or 'Space' to return to main page


*/


////    DEFINE HOW TO PAGE      ///////////////////////

	Text howto2;
	howto2.setString("use both Slider to adjust shooting power and angle \nuse adjustment knob to adjust gravity \nuse button to change the ball \n\nor\n\nuse 't' and 'g' to adjust angle \nuse 'h' and 'j' to adjust power\n\npress 'ESC' or 'Space' to return to main page");
	howto2.setFont(normal);
	howto2.setColor(cnormal);
	howto2.setCharacterSize(35);
	howto2.setPosition(70, 350);

	Text howto;
	howto.setString("Developer: Chinatip Lawansuk [60010235]");
	howto.setFont(normal);
	howto.setColor(cbold);
	howto.setCharacterSize(55);
	howto.setPosition(70, 70);

	Text howto3;
	howto3.setString("This project is a part of Programming Fundamental\n01076002 Department of Computer Engineering,\nFaculty of Engineering KMITL");
	howto3.setFont(normal);
	howto3.setColor(cbold);
	howto3.setCharacterSize(40);
	howto3.setPosition(70, 150);


////ENDDEF/////////////////////////////////////////

////    DEFINE GAME PAGE //////////////////////////
	RectangleShape Gnd;
	Gnd.setFillColor(Color(0x505050ff));
	Gnd.setSize(Vector2f(centerx * 2, 50));
	Gnd.setPosition(0, centery * 2 - 50);

	Text ststat;
	ststat.setString("Power: "+to_string((int)power)+" Angle: "+ to_string((int)(angle)) + "     ");
	ststat.setFont(normal);
	ststat.setColor(cbold);
	ststat.setCharacterSize(40);
	midpoint = ststat.getGlobalBounds().width;
	ststat.setOrigin(midpoint, 0);
	ststat.setPosition(2*centerx-50, 2*centery-45);
	
	Text tscore;
	tscore.setString("Score: "+to_string(score));
	tscore.setFont(normal);
	tscore.setColor(cbold);
	tscore.setCharacterSize(40);
	tscore.setPosition(50, 2 * centery - 45);

	RectangleShape box;
	Gnd.setFillColor(Color(0x505050ff));
	Gnd.setSize(Vector2f(100,100));
	Gnd.setPosition(0,70);

	

////ENDDEF/////////////////////////////////////////




	goto mainpage;



////    MAIN PAGE LOOP      ///////////////////////
mainpage:
	int i = 0;
	bool flip=0;
	
	sleep(milliseconds(200));
	selectedstate = 0;
	exit.setPosition(centerx/2, 605);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				sleep(milliseconds(200));
				switch (selectedstate)
				{
				default:
					break;
				case 0:
					goto game;
					break;
				case 1:
					goto how;
					break;
				case 2:
					window.close();
					break;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				
				selectedstate += 1;
				selectedstate %= 3;
				cout << selectedstate;
				sleep(milliseconds(200));
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				selectedstate -= 1;
				selectedstate += 3;
				selectedstate %= 3;
				sleep(milliseconds(200));
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				
			}
		}
		if (!flip)
		{
			i++;
			if (i == 200)
			{
				flip = !flip;
			}
		}
		else
		{
			i--;
			if (i == 20)
			{
				flip = !flip;
			}
		}
		
		i %= 256;
		a.setFillColor(Color(255, 255, 255, 200));
		cirm.setFillColor(Color((85 + i) % 256, (170+i)%256, (170- i) % 256, 150));
		cirm.update();
		
		if (cirm.getPosition().y >= 2*centery-100)
		{
			cirm.v.y += 250;
			
		}
		if (cirm.p().x <=0)
		{
			cirm.v.x = -cirm.v.x;
			
		}
		if (cirm.p().x >= 2*centerx)
		{
			cirm.setPosition(2 * centerx-20, cirm.p().y);
			
			cirm.v.x = -cirm.v.x;
		}		
		if (cirm.v.x >= 0)
		{
			cirm.v.x += 50;
		}
		else
		{
			cirm.v.x -= 50;
		}
		cirm.v.x /= 1.5;
		cirm.setRadius(10 + i/5);

		switch (selectedstate)
		{
		default:
			break;
		case 0:
			play.setColor(cselected);
			how.setColor(cnormal);
			exit.setColor(cnormal);
			break;
		case 1:
			play.setColor(cnormal);
			how.setColor(cselected);
			exit.setColor(cnormal);
			break;
		case 2:
			play.setColor(cnormal);
			how.setColor(cnormal);
			exit.setColor(cselected);
			break;
		}
		
		window.clear();

		window.draw(a);
		window.draw(cirm);
		window.draw(polka);
		window.draw(play);
		window.draw(how);
		window.draw(exit);

		window.display();
	}
	
////    END MAIN PAGE        ///////////////////////




////    PAUSE PAGE LOOP      ///////////////////////

pause:
	selectedstate = 0;
	exit.setPosition(centerx, 555);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				switch (selectedstate)
				{
				default:
					break;
				case 0:
					goto game;
					break;
				case 1:
					break;
				case 2:
					goto mainpage;
					break;
				case 3:
					window.close();
					break;
				}
				
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				
				selectedstate += 1;
				selectedstate %= 4;
				sleep(milliseconds(200));
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				
				selectedstate -= 1;
				selectedstate += 4;
				selectedstate %= 4;
				sleep(milliseconds(200));
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				sleep(milliseconds(200));
				goto game;
				
			}
			

		}

		switch (selectedstate)
		{
		default:
			break;
		case 0:
			cont.setColor(cselected);
			reset.setColor(cnormal);
			mainmenu.setColor(cnormal);
			exit.setColor(cnormal);
			break;
		case 1:
			cont.setColor(cnormal);
			reset.setColor(cselected);
			mainmenu.setColor(cnormal);
			exit.setColor(cnormal);
			break;
		case 2:
			cont.setColor(cnormal);
			reset.setColor(cnormal);
			mainmenu.setColor(cselected);
			exit.setColor(cnormal);
			break;
		case 3:
			cont.setColor(cnormal);
			reset.setColor(cnormal);
			mainmenu.setColor(cnormal);
			exit.setColor(cselected);
			break;
		}

		window.clear();
		window.draw(paused);
		window.draw(cont);
		window.draw(reset);
		window.draw(mainmenu);
		window.draw(exit);

		window.display();
	}

////    END PAUSE PAGE LOOP      ///////////////////////



////    HOW TO PAGE LOOP      ///////////////////////

how:
	howto2.setColor(Color(0xFDFD97FF));
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				
				goto mainpage;

			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				sleep(milliseconds(200));
				goto mainpage;

			}


		}

		

		window.clear();
		window.draw(howto);
		window.draw(howto2);
		window.draw(howto3);


		window.display();
	}

////    END HOW TO PAGE LOOP      ///////////////////////


////    GAME PAGE LOOP      ///////////////////////
game:
	compass.setFillColor(Color(0x73d7d7ff));
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				cira.v.x -= 25;
				if (cira.v.x < -150)
				{
					cira.v.x = -150;
				}
				cout << "a\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				cira.v.y -= 50;
				if (cira.v.y < -50)
				{
					cira.v.y = -50;
				}
				cout << "s\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				cira.v.y +=200;
				if (cira.v.y > 200)
				{
					cira.v.y = 200;
				}
				cout << "w\n";
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				cira.v.x += 25;
				if (cira.v.x > 150)
				{
					cira.v.x = 150;
				}
				cout << "d\n";
			}
			

			if (Keyboard::isKeyPressed(Keyboard::L))
			{
				
				
				cira.v.x = 0;
				cira.setPosition(0, 600);

			}
			if (Keyboard::isKeyPressed(Keyboard::N))
			{
				Circle a;
				a.setRadius(20);
				a.include(sys1);
				a.goinit();
				a.v.x = 0;
				a.m = 2;
//				va.push_back(a);
//				va[va.size()-1].setPosition(100, 100);
//				cout << va.size();
//				sleep(milliseconds(200));
				
			}

			if (Keyboard::isKeyPressed(Keyboard::T))
			{
				angle += 1;
				cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower =" << power << endl;

			}
			if (Keyboard::isKeyPressed(Keyboard::G))
			{
				angle -= 1;
				cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower ="<<power<<endl;

			}

			if (Keyboard::isKeyPressed(Keyboard::J))
			{
				power += 10;
				cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower =" << power << endl;
				

			}
			if (Keyboard::isKeyPressed(Keyboard::H))
			{
				power -= 10;
				cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower =" << power << endl;

			}

			if(Keyboard::isKeyPressed(Keyboard::Space))
			{
				
				cira.v.x += power*cosf(angle*0.0174532925);
				cira.v.y += power*sinf(angle*0.0174532925);
				cout << cira.v.x << " " << cira.v.y << endl;
				angle = 0;
				power = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::K))
			{
				sleep(milliseconds(100));
				ballstat = ballstat % 3;
				ballstat += 1; 
				switch (ballstat)
				{
				default:
					break;
				case 1:
					cira.m = 1;
					cira.setFillColor(Color(0x73d7d7ff));
					compass.setFillColor(Color(0x73d7d7ff));
					break;
				case 2:
					cira.m = 5;
					cira.setFillColor(Color(0xFDFD97FF));
					compass.setFillColor(Color(0xFDFD97FF));
					break;
					
				case 3:
					cira.m = 10;
					cira.setFillColor(Color(0xfa8072ff));
					compass.setFillColor(Color(0xfa8072ff));
					break;
				}
				cira.setRadius(10*ballstat);
				cira.ref = centery * 2 - (50 + 2 * cira.getRadius());
				
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				sleep(milliseconds(200));
				goto pause;
				

			}



		}

		
		

		cira.update();
		if (cira.p().x <= 0)
		{
			cira.setPosition(0, cira.getPosition().y);
			cira.v.x *= -1;
		}
		if (cira.p().x +cira.getRadius()*2>= 2*centerx)
		{
			cira.setPosition(2 * centerx- cira.getRadius() * 2, cira.getPosition().y);
			cira.v.x *= -1;
		}
		if (cira.p().y <= 0)
		{
			cira.setPosition(cira.getPosition().x,0);
			cira.v.y *= -1;
		}
		compass.setRotation(-angle);
		compass.setSize(Vector2f(20+power*0.5,2));
		compass.setPosition(cira.getPosition().x+cira.getRadius(), cira.getPosition().y + cira.getRadius());
		
		ststat.setString("Power: " + to_string((int)power) + " Angle: " + to_string((int)(angle)) + "   ");
		tscore.setString("Score: " + to_string(score));

		window.clear();


		
		window.draw(cira);
		window.draw(compass);
		window.draw(Gnd);
		window.draw(tscore);
		window.draw(ststat);
		window.draw(box);


		window.display();
	}
////    END GAME PAGE LOOP      ///////////////////////

}

