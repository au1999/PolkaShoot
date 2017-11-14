#include "Physics.h"



Physics::Physics(float ig, float iref)
{
	g = ig;
	ref=iref;
}

void Physics::Physics::initpos(float ix, float iy)
{
	initx = ix;

	inity = iy;
}


Physics::~Physics()
{
}

void Circle::move(float dx, float dy)
{
	float x = this->getPosition().x;
	float y = this->getPosition().y;
	this->setPosition(x + dx, y - dy);

}

void Circle::include(Physics a)
{
	initx = a.initx;
	inity = a.inity-(2 * this->getRadius());
	g = a.g;
	ref = a.ref-(2*this->getRadius());
	cout << "this.ref= " << ref << endl;

}


void Circle::initplace(Physics ig)
{
	
	this->setPosition(ig.initx,ig.inity);

}
void Circle::update()
{
	float px = getPosition().x, py = getPosition().y;
	v.y -= g * 100 / 60;
	move(0, 0.1*v.y);
	py = getPosition().y;
	
	if (py > ref)
	{
		setPosition(getPosition().x,getPosition().y - 1);
		v.y = 0;
		py = ref;
		setPosition(px, ref);
		
		
	}

	if (v.x > 0)
	{
		v.x -= 2;
		if (v.x < 0)
		{
			v.x = 0;
		}
	}
	if (v.x < 0)
	{
		v.x += 2;
		if (v.x > 0)
		{
			v.x = 0;
		}
	}

	if (v.x > 0 && v.y == 0)
	{
		v.x -= 7.5;
		if (v.x < 0)
		{
			v.x = 0;
		}
	}
	if (v.x < 0 && v.y == 0)
	{
		v.x += 7.5;
		if (v.x > 0)
		{
			v.x = 0;
		}
	}
//	cout << "vy " << v.y << "\n";
	
	move(0.1*v.x,0);

}
void Circle::goinit()
{
	this->setPosition(this->initx, this->inity);
}

bool Circle::isCollide(Shape & a)
{
	bool cld=this->getGlobalBounds().intersects(a.getGlobalBounds());
	
	
	return cld;
}

void Circle::Collide(Circle& a)
{
	if (this->p().x + this->getRadius() < a.p().x + a.getRadius())
	{
		this->setPosition(a.p().x - this->getRadius() * 2, this->ref);
	}
	else if (this->p().x + this->getRadius()> a.p().x + a.getRadius())
	{
		this->setPosition(a.p().x + a.getRadius() * 2, this->ref);
	}


	
	if (this->v.x != a.v.x)
	{
		a.v.x = this->v.x*this->m /a.m;
	}
	
//	this->v.x = 0;
	if (abs(this->v.x) < abs(a.v.x)&&this->v.x*a.v.x>=0)
	{
		this->v.x = a.v.x;
	}

	cout << this->v.x << " " << a.v.x << endl;
	

	
	
}

Vector2f Circle::p()
{

	return Vector2f(this->getPosition().x, this->getPosition().y);
}
