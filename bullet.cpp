#ifndef KIERUNKI
#define KIERUNKI

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

#endif /* KIERUNKI */

#include "bullet.h"

Bullet::Bullet ()
{
	posX = 0;
	posY = 0;
	life = 0;
	direct = 0;
}

void Bullet::get_pos(int tank_X, int tank_Y)
{
	if (!life)
	{
		posX = tank_X;
		posY = tank_Y;
	}
}

void Bullet::make_alive()
{
	life = 1;
}

void Bullet::get_direct(int a)
{
	if (!life)
		direct = a;
}

void Bullet::hit(Enemyclass *tank_enemy, Playerclass *tank_player)
{
	if ((life == 1) && (posX>tank_enemy->posX && posX<tank_enemy->posX+70) && (posY>tank_enemy->posY && posY<tank_enemy->posY+70) && (tank_enemy->life > 0))
	{
		life = 0;
		tank_enemy->life--;
		tank_player->points++;
	}
}

void Bullet::hit_player (Enemyclass *tank_enemy, Playerclass *tank_player)
{
	if ((life == 1) && (posX>tank_player->posX && posX<tank_player->posX+70) && (posY>tank_player->posY && posY<tank_player->posY+70))
	{
		life = 0;
		tank_enemy->wykrycie_kolizji = 1;
	}
}


void Bullet::move_bullet()
{
	if (life)
	{
		if (direct == GO_UP)
		{
			if(posY>=-31)
				posY-=5;
			else
			{
				posY=-32;
				life = 0;
			}
		}
		else if (direct == GO_DOWN)
		{
			if(posY<=438)
				posY+=5;
			else
			{
				posY=439;
				life = 0;
			}
		}
		else if (direct == GO_LEFT)
		{
			if(posX>=-31)
				posX-=5;
			else
			{
				posX=-32;
				life = 0;
			}
		}
		else if (direct == GO_RIGHT)
		{
			if(posX<=600)
				posX+=5;
			else
			{
				posX=601;
				life = 0;
			}
		}
	}
}

void Bullet::print_bullet(unsigned int* GRAPH)
{
	if (life)
	{
		int dx, dy;
		for (dx=32;dx<37;dx++)
		{
			for(dy=32;dy<37;dy++)
			{
				GRAPH[posX+dx+(posY+dy)*640]=0xFF0000;
			}
		}
	}
}
