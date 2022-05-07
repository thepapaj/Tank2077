#ifndef BULLET_H_
#define BULLET_H_

#ifndef KIERUNKI
#define KIERUNKI

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

#endif /* KIERUNKI */

#include <iostream>
#include <linux/input.h>
#include "peripherals.h"
#include "tank_up.h"
#include "tank_right.h"
#include "tank_left.h"
#include "tank_down.h"
#include "Enemyclass.h"
#include "Playerclass.h"

class Enemyclass;
class Playerclass;

class Bullet{
	int posX;
	int posY;
	unsigned short life;
	int direct;
public:
	Bullet();
	void print_bullet(unsigned int* GRAPH);
	void move_bullet();
	void get_pos(int, int);
	void make_alive();
	void get_direct(int);
	//void hit(int, int,unsigned int* GRAPH);
	void hit(Enemyclass *, Playerclass *);
	void hit_player (Enemyclass *, Playerclass *);

};



#endif /* BULLET_H_ */
