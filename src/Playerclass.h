#ifndef PLAYERCLASS_H_
#define PLAYERCLASS_H_

#include <iostream>
#include <linux/input.h>
#include "peripherals.h"
#include "tank_up.h"
#include "tank_right.h"
#include "tank_left.h"
#include "tank_down.h"
#include "bullet.h"

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

class Bullet;

class Playerclass {
public:
	int posX;										// polozenia poczotkowe gracza x
	int posY;										// polozenie poczotkowe gracza y
	int direct;                                // kierunek w któr¹ strone obrócony jest czolg
	int points;
	float speed_X;
	float speed_Y;
	float inert;

	Playerclass();

	void moveTank ();
	void move();
	void print_tank(unsigned int* GRAPH);          //rysuje czolg gracza
	void setSpeed_X(float wartosc);
	void setSpeed_Y(float wartosc);
	void fire(Bullet *);

};


#endif /* PLAYERCLASS_H_ */
