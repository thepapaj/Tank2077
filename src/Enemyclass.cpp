#ifndef KIERUNKI
#define KIERUNKI

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

#endif /* KIERUNKI */

#include "Enemyclass.h"

Enemyclass::Enemyclass(int x, int y, int z, int c) {

	posX=x;       // pozycje poczatkujece x y czolgu
	posY=y;		// moze to wstawid do .move ?  // jak zrobic zeby bylo pare czolgow w losowych miejscach
	life = 1;
	predkosc=c;
	wykrycie_kolizji=1;
	direct = z;
}

void Enemyclass::print_gameover(unsigned int* GRAPH)
{
	if (life > 0)
	{
		for (int dx=0;dx<640;dx++)
		{
			for(int dy=0;dy<480;dy++)
			{
				GRAPH[dx+(dy)*640]=game_over[dx+dy*640];
			}
		}
	}
}

void Enemyclass::fire(Bullet *bullet)
{
	if (life)
	{
		bullet->get_pos(posX,posY);
		bullet->get_direct(direct);
		bullet->make_alive();
	}
}

void Enemyclass::print_tank(unsigned int* GRAPH){
	if(life > 0)
	{
		if (direct == GO_LEFT)
		{
			for (int dx=0;dx<75;dx++)
			{
				for(int dy=0;dy<75;dy++)
				{
					if ((tank_enemy_left[dx+dy*75])!=0xffffff)
						GRAPH[posX+dx+(posY+dy)*640]=tank_enemy_left[dx+dy*75];
				}
			}
		}
		if (direct == GO_RIGHT)
		{
			for (int dx=0;dx<75;dx++)
			{
				for(int dy=0;dy<75;dy++)
				{
					if ((tank_enemy_right[dx+dy*75])!=0xffffff)
						GRAPH[posX+dx+(posY+dy)*640]=tank_enemy_right[dx+dy*75];
				}
			}
		}
		if (direct == GO_DOWN)
		{
			for (int dx=0;dx<75;dx++)
			{
				for(int dy=0;dy<75;dy++)
				{
					if ((tank_enemy_down[dx+dy*75])!=0xffffff)
						GRAPH[posX+dx+(posY+dy)*640]=tank_enemy_down[dx+dy*75];
				}
			}
		}
		if (direct == GO_UP)
		{
			for (int dx=0;dx<75;dx++)
			{
				for(int dy=0;dy<75;dy++)
				{
					if ((tank_enemy_up[dx+dy*75])!=0xffffff)
						GRAPH[posX+dx+(posY+dy)*640]=tank_enemy_up[dx+dy*75];
				}
			}
		}

	}
}

void Enemyclass::move()
{
	if (life > 0)
	{
		if (direct == GO_LEFT)
		{
			posX = posX - predkosc;
			if(posX<0)
				posX=640;
		}
		if (direct == GO_RIGHT)
		{
			posX = posX + predkosc;
			if(posX>640)
				posX = 0;

		}
		if (direct == GO_DOWN)
		{
			posY = posY + predkosc;
			if (posY > 400)
				posY=0;
		}
		if (direct == GO_UP)
		{
			posY = posY - predkosc;
			if (posY < 1)
				posY=400;
		}
	}
}

void Enemyclass::kolizja(int xplayer, int yplayer)
{
	if (life > 0)
	{
		if ((xplayer-75<posX&&xplayer+75>posX)&&(yplayer-75<posY&&yplayer+75>posY))
			wykrycie_kolizji=1;
	}
}


