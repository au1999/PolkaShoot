#pragma once
#include<SFML\Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;

class Physics
{
public:
	Physics(float ig, float ref);
	~Physics();
	float initx;
	float inity;
	float g;
	float ref;
	void initpos(float ix, float iy);






};

struct pos
{
	float x;
	float y;
	float *ax=&x;
	float *ay=&y;
	Vector2f p(float(*ax),float( *ay));
};

struct veloc
{
	float x;
	float y;
	
	float *ax = &x;
	float *ay = &y;
	float dx = *ax / abs(*ax);
	float mx = *ax / dx;
	float dy = *ay / abs(*ay);
	float my = *ay / dy;
	float theta=atan2f(float(*ay), float(*ax));

};

struct accel
{
	float x;
	float y;
	float *ax = &x;
	float *ay = &y;
	float dx = *ax / abs(*ax);
	float mx = *ax / dx;
	float dy = *ay / abs(*ay);
	float my = *ay / dy;
	float theta = atan2f(float(*ay), float(*ax));

};

class Circle : public CircleShape
{
public:
	float initx;
	float inity;
	float g;
	float ref;
	float m;
	veloc v;
	accel a;
	


	void initplace(Physics ig);
	void move(float dx, float dy);
	void include(Physics a);
	void update();
	void goinit();
	bool isCollide(Shape& a);
	void Collide(Circle& a);
	Vector2f p();
};



