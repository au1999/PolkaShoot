#include<SFML/Graphics.hpp>
#include<stdio.h>
#include"Physics.h"
#include<thread>
#include<sstream>
#include<time.h>
#include<string>
#include<conio.h>
#include"SerialClass.h"

#define centerx 600
#define centery 400
using namespace sf;
using namespace std;

char incomingData[256] = "";
int dataLength = 255;
int readResult = 0;
Serial* sp=new Serial("\\\\.\\COM6");

int initx = 200;
int inity = 600;
float angle=0;
float power=0;
int score = 0;
int ballstat = 1;
bool isalive = true;
int boxhp=0;
int bv=5;
int tmp=0;
int best=0;
bool changecmd=false;
bool shootcmd = false;
Circle cira;


void updateSerial();




int main()
{


////Define Window size
	RenderWindow window(VideoMode(2*centerx,2*centery), "Polka Shoot!");
	window.setFramerateLimit(60);
	
	

////Define Physics system
	Physics sys1(10, 750);
	sys1.initpos(0, 750);

////Define circle a
	

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

////DEFINE RAND()////////

	srand(time(NULL));



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

	Text bestever;
	bestever.setString("Best ever:");
	bestever.setFont(normal);
	bestever.setColor(Color(20,180,225,255));
	bestever.setCharacterSize(75);
	midpoint = bestever.getGlobalBounds().width / 2;
	bestever.setOrigin(midpoint, 0);
	bestever.setPosition(a.getPosition().x-300, a.getPosition().y -350);

	Text bscore;
	bscore.setString("Best ever:");
	bscore.setFont(normal);
	bscore.setColor(Color(200, 74, 66, 255));
	bscore.setCharacterSize(90);
	midpoint = bscore.getGlobalBounds().width / 2;
	bscore.setOrigin(midpoint, 0);
	bscore.setPosition(a.getPosition().x - 300, a.getPosition().y - 200);


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
	box.setFillColor(Color(0x505050ff));
	box.setSize(Vector2f(100,100));
	box.setPosition(100,400);

	Text bhp;
	bhp.setString(to_string(boxhp));
	bhp.setFont(normal);
	bhp.setColor(Color(222,222,222,255));
	bhp.setCharacterSize(40);
	bhp.setOrigin(bhp.getLocalBounds().width / 2, bhp.getLocalBounds().height / 2);
	bhp.setPosition(box.getPosition().x+50, box.getPosition().y + 50);

	Text result;
	result.setString("Score: " + to_string(score));
	result.setFont(bold);
	result.setCharacterSize(100);
	
	result.setColor(Color(35, 170, 170, 225));

	
	
////ENDDEF/////////////////////////////////////////

//// RUN UPDATE THREAD///////////////////////////////

	thread(updateSerial).detach();
/////////////////////////////////////////////////////




	
	goto mainpage;



////    MAIN PAGE LOOP      //////////
/////////////
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
		bscore.setString(to_string(best));
		midpoint = bscore.getGlobalBounds().width / 2;
		bscore.setOrigin(midpoint, 0);
		bscore.setPosition(a.getPosition().x - 300, a.getPosition().y - 200);

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
		window.draw(bestever);
		window.draw(bscore);
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
					isalive = true;
					score = 0;
					boxhp = 0;
					tmp = 0;
					bv = 5;
					ballstat = 1;
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
					cira.setRadius(10 * ballstat);
					cira.ref = centery * 2 - (50 + 2 * cira.getRadius());
					cira.setPosition(0, cira.ref);
					goto game;
					break;
				case 2:
					isalive = true;
					score = 0;
					boxhp = 0;
					tmp = 0;
					bv = 5;
					ballstat = 1;
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
					cira.setRadius(10 * ballstat);
					cira.ref = centery * 2 - (50 + 2 * cira.getRadius());
					cira.setPosition(0, cira.ref);
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
	compass.setFillColor(cira.getFillColor());
	while (window.isOpen())
	{
		if (isalive)
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
					cira.v.y += 200;
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
			
				}

				if (Keyboard::isKeyPressed(Keyboard::T))
				{
					angle += 1;
					cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower =" << power << endl;

				}
				if (Keyboard::isKeyPressed(Keyboard::G))
				{
					angle -= 1;
					cout << "angle= " << angle << "deg <> " << angle*0.0174532925 << " rads\nPower =" << power << endl;

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

				
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					sleep(milliseconds(200));
					goto pause;


				}



			}
			if (Keyboard::isKeyPressed(Keyboard::Space) || shootcmd)
			{

				cira.v.x += power*cosf(angle*0.0174532925);
				cira.v.y += power*sinf(angle*0.0174532925);
				cout << cira.v.x << " " << cira.v.y << endl;
				angle = 0;
				power = 0;
				shootcmd = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::K) || changecmd)
			{
				changecmd = false;
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
				cira.setRadius(10 * ballstat);
				cira.ref = centery * 2 - (50 + 2 * cira.getRadius());

			}

			cira.update();

			if (cira.p().x <= 0)
			{
				cira.setPosition(0, cira.getPosition().y);
				cira.v.x *= -1;
			}
			if (cira.p().x + cira.getRadius() * 2 >= 2 * centerx)
			{
				cira.setPosition(2 * centerx - cira.getRadius() * 2, cira.getPosition().y);
				cira.v.x *= -1;
			}
			if (cira.p().y <= 0)
			{
				cira.setPosition(cira.getPosition().x, 0);
				cira.v.y *= -1;
			}

			if (cira.isCollide(box))
			{

				if (cira.p().y > box.getPosition().y)
				{
					cira.setPosition(cira.getPosition().x, box.getPosition().y + box.getLocalBounds().height);
					cira.v.y *= -1;
				}
				else if (cira.p().y <= box.getPosition().y)
				{
					cout << "collide";
					cira.setPosition(cira.p().x, box.getPosition().y - 2 * cira.getRadius());
					cira.v.y *= -1;
				}
				else if (cira.p().x < box.getPosition().x)
				{
					cira.setPosition(box.getPosition().x - 2 * cira.getRadius(), cira.getPosition().y);
					cira.v.x *= -1;
				}
				else if (cira.p().x > box.getPosition().x)
				{
					cira.setPosition(box.getPosition().x + box.getLocalBounds().width, cira.getPosition().y);
					cira.v.x *= -1;
				}
				boxhp -= cira.m;
				score += cira.m;
			}


			compass.setRotation(-angle);
			compass.setSize(Vector2f(20 + power*0.5, 2));
			compass.setPosition(cira.getPosition().x + cira.getRadius(), cira.getPosition().y + cira.getRadius());

			ststat.setString("Power: " + to_string((int)power) + " Angle: " + to_string((int)(angle)) + "   ");
			tscore.setString("Score: " + to_string(score));

			box.setPosition(box.getPosition().x + (bv * 0.1), box.getPosition().y);
			if (box.getPosition().x >= 2 * centerx)
			{
				cout << "out";
				isalive = false;
			}
			if (boxhp == 0)
			{
				box.setPosition(0,rand()%400);
				box.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256, 255));
				boxhp = (rand()%50)+1;
			}
			if (boxhp < 0)
			{
				isalive = false;
			}
			
			bhp.setString(to_string(boxhp));
			bhp.setOrigin(bhp.getLocalBounds().width / 2, bhp.getLocalBounds().height / 2);
			bhp.setPosition(box.getPosition().x + 50, box.getPosition().y + 50);
			
			
			if ( score-tmp >= 100)
			{
				bv += 2;
				tmp = score;
			}


			window.clear();



			window.draw(cira);
			window.draw(compass);
			window.draw(Gnd);
			window.draw(tscore);
			window.draw(ststat);
			window.draw(box);
			window.draw(bhp);


			window.display();

		}
		else
		{
			Event event;
			while (window.pollEvent(event))
			{
				// Close window: exit
				if (event.type == Event::Closed)
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					isalive = true;
					score = 0;
					boxhp = 0;
					ballstat = 1;
					tmp = 0;
					bv = 5;
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
					cira.setRadius(10 * ballstat);
					cira.ref = centery * 2 - (50 + 2 * cira.getRadius());
					cira.setPosition(0, cira.ref);
					sleep(milliseconds(200));
					goto mainpage;


				}
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					isalive = true;
					score = 0;
					boxhp = 0;
					ballstat = 1;
					tmp = 0;
					bv = 5;
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
					cira.setRadius(10 * ballstat);
					cira.ref = centery * 2 - (50 + 2 * cira.getRadius());
					cira.setPosition(0, cira.ref);
					sleep(milliseconds(200));
					goto mainpage;


				}
				
				



			}

			if (score > best)
			{
				best = score;
			}
			
			
			result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);
			result.setPosition(centerx, 250);
			result.setString("Score: " + to_string(score));

			window.clear();
			
			window.draw(result);
			window.display();
		}
	}
////    END GAME PAGE LOOP      ///////////////////////

}


void updateSerial()
{
	while (sp->IsConnected())
	{
		readResult = sp->ReadData(incomingData, dataLength);
		incomingData[readResult] = 0;


		//				printf("%s", incomingData);

		for (int i = 0; i < 244; i++)
		{
			if (incomingData[i] == '\n'&&incomingData[i + 11] == '\r')
			{
				cout << i << ". ";
				for (int k = 1; k <= 10; k++)
				{
					cout << incomingData[i + k];

				}

				if (incomingData[i + 2] == '1')
				{
					shootcmd = true;
					cout << "shoot";
					
				}
				else
				{
					shootcmd = false;
				}

				if (incomingData[i + 3] == '1')
				{
					changecmd = true;
					
					
				}
				else
				{
					changecmd = false;
				}
				angle = (incomingData[i + 4] * 100 + incomingData[i + 5] * 10 + incomingData[i + 6]) - 53328 + 48000;
				power = (incomingData[i + 7] * 1000 + incomingData[i + 8] * 100 + incomingData[i + 9] * 10 + incomingData[i + 10]) - 53328;


				cout << endl;
				cout << angle;
				i += 245;
			}
			sleep(milliseconds(10));

		}

		//sleep(milliseconds(1000));

	}

}
