#include "Playerclass.h"

Playerclass::Playerclass(){
	posX=100;
	posY=100;
	inert=0.9;
	points=0;
	speed_X=0;
	speed_Y=0;
	direct=GO_DOWN;
}

void Playerclass::setSpeed_X(float wartosc) {
		speed_X = (wartosc*(1-inert) + speed_X*inert);
		std::cout << speed_X <<"Predkosc wynosi " << speed_X<<std::endl;
	}
void Playerclass::setSpeed_Y(float wartosc) {
		speed_Y = (wartosc*(1-inert) + speed_Y*inert);
		std::cout << speed_Y <<"Predkosc wynosi " << speed_Y<<std::endl;
	}

void Playerclass::moveTank (){
	short motion_X = speed_X;
	short motion_Y = speed_Y;
	//posX
	if (motion_X<0)
	{
		if(posX>-(motion_X))
			posX+=motion_X;
	}
	if (motion_X>0)
	{
		if(posX<(640-(70+motion_X)))
			posX+=motion_X;
	}

	if (motion_Y<0)
	{
		if(posY>-(motion_Y))
			posY+=motion_Y;
	}
	if (motion_Y>0)
	{
		if(posY<(480-(70+motion_Y)))
			posY+=motion_Y;
	}
}

void Playerclass::move() {
	if(getKey()==KEY_RIGHT){
		setSpeed_X(15);
		direct = GO_RIGHT;
		//posX=posX+speed;
	}
	if(getKey()==KEY_LEFT){   // KEY_LEFT = 105 z biblioteki od linuxa/ input
		setSpeed_X(-15);
		direct =GO_LEFT;
		//posX=posX-4;
	}
	if(getKey()==KEY_UP){
		setSpeed_Y(-15);
		direct = GO_UP;
		//posY = posY-3;

	}
	if(getKey()==KEY_DOWN){
		setSpeed_Y(15);
		direct = GO_DOWN;
		//posY = posY+3;
	}
	else {
		this->setSpeed_X(0);
		this->setSpeed_Y(0);
	}

}

void Playerclass::fire(Bullet *bullet)
{
	if (getKey() == KEY_F)
	{
		bullet->get_pos(posX,posY);
		bullet->get_direct(direct);
		bullet->make_alive();
		//bullet->move_bullet(direct);
	}
}

void Playerclass::print_tank(unsigned int* GRAPH) // to mozna zaoptymilizowac i nie powtarzac tych funkcji
{
	if(direct==2){
		for (int dx=0;dx<70;dx++){
			for(int dy=0;dy<70;dy++){
				if ((tank_up[dx+dy*70])!=0xffffff){
					GRAPH[posX+dx+(posY+dy)*640]=tank_up[dx+dy*70];}
			}
		}
	}
	else if (direct==4){
		for (int dx=0;dx<70;dx++){
			for(int dy=0;dy<70;dy++){
				if ((tank_right[dx+dy*70])!=0xffffff){
					GRAPH[posX+dx+(posY+dy)*640]=tank_right[dx+dy*70];}
			}
		}
	}
	else if (direct==3){
		for (int dx=0;dx<70;dx++){
			for(int dy=0;dy<70;dy++){
				if ((tank_left[dx+dy*70])!=0xffffff){
					GRAPH[posX+dx+(posY+dy)*640]=tank_left[dx+dy*70];}
			}
		}
	}
	else if (direct==1){
		for (int dx=0;dx<70;dx++){
			for(int dy=0;dy<70;dy++){
				if ((tank_down[dx+dy*70])!=0xffffff){
					GRAPH[posX+dx+(posY+dy)*640]=tank_down[dx+dy*70];}
			}
		}
	}
}
