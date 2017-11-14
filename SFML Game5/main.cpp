#include<SFML/Graphics.hpp>
#include<stdio.h>
#include"Physics.h"
#include<thread>

#define centerx 600
#define centery 400
using namespace sf;
using namespace std;

int initx = 200;
int inity = 600;
float angle=0;
float power=0;
Int64 freq;

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
void genFreq()
{
	srand(time(NULL));
	while (1)
	{
		freq=(rand()+freq)%750;
		freq += 200;
		sleep(milliseconds(100));
		

		
	}
}



int main()
{
	//Define Window size
	RenderWindow window(VideoMode(2*centerx,2*centery), "Polka Shoot!");
	window.setFramerateLimit(60);
	
	thread (genFreq).detach();

	//Define Physics system
	Physics sys1(10, 800);
	sys1.initpos(0, 800);

	//Define circle a
	Circle cira;

	cira.setRadius(10);
	cira.include(sys1);
	cira.goinit();
	cira.v.x = 0;
	cira.setPosition(0, 600);
	cira.m = 1;

	//Define compass
	RectangleShape compass;
	compass.setSize(Vector2f(20, 2));
	compass.setOrigin(10, 1);
	compass.setPosition(cira.getPosition());



	//call timer
	Clock c;
	Time t = c.getElapsedTime();
	Int32 tmis = t.asMilliseconds();
	float tm = tmis / 1000;




	//get font
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

	//get color
	Color cbold(255,255,255,255);
	Color cnormal(128, 128, 128, 255);
	Color cselected(255, 128, 128, 255);

	//define and init pause page's text
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




	RectangleShape a;
	a.setSize(Vector2f(200, 200));
	a.setOrigin(100, 100);
	a.setPosition(500, 500);
	
	goto mainpage;

mainpage:
	cout << "into main\n";
	sleep(milliseconds(200));
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
				goto game;
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				a.setPosition(a.getPosition().x, a.getPosition().y+ 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				a.setPosition(a.getPosition().x, a.getPosition().y - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				
			}


		}

		window.clear();
		window.draw(a);



		window.display();
	}
	



pause:
	selectedstate = 0;
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




game:
	
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
				thread (snd).detach();
				
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				sleep(milliseconds(200));
				goto pause;
				

			}



		}

		
		

		cira.update();
		compass.setRotation(-angle);
		compass.setSize(Vector2f(20+power*0.5,2));
		compass.setPosition(cira.getPosition().x+cira.getRadius(), cira.getPosition().y + cira.getRadius());
		

		window.clear();


		
		window.draw(cira);
		window.draw(compass);
		


		window.display();
	}

}