#ifndef ENEMYCLASS_H_
#define ENEMYCLASS_H_

#ifndef KIERUNKI
#define KIERUNKI

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

#endif /* KIERUNKI */

#include <iostream>
#include "peripherals.h"
#include "tank_enemy_left.h"
#include "tank_enemy_right.h"
#include "tank_enemy_down.h"
#include "tank_enemy_up.h"
#include "game_over.h"
#include "bullet.h"

class Bullet;

class Enemyclass {
public:
	int posX;
	int posY;
	int life;
	int predkosc;
	int direct;
	int wykrycie_kolizji;

	Enemyclass(int x, int y, int z, int c);

	void print_tank(unsigned int* GRAPH);                     // printe czolg
	void print_tank_right(unsigned int* GRAPH);					// poprawic to by byla jedna funkcja
	void print_gameover(unsigned int* GRAPH);				//
	void move();
	void move_right();
	void kolizja(int xplayer, int yplayer);
	void fire(Bullet *);

};

#endif /* ENEMYCLASS_H_ */
