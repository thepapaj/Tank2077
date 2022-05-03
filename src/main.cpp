#include "main.h"

using namespace std;

Playerclass player_tank;
Bullet bullet_player;
Bullet *ptr_bullet_player = &bullet_player;

Enemyclass enemy_tank1(300,10,GO_RIGHT,2);
Enemyclass *ptr_enemy_tank1 = &enemy_tank1;
Bullet bullet_enemy1;
Bullet *ptr_bullet_enemy1 = &bullet_enemy1;

Enemyclass enemy_tank2(300,10,GO_DOWN,2);
Enemyclass *ptr_enemy_tank2 = &enemy_tank2;
Bullet bullet_enemy2;
Bullet *ptr_bullet_enemy2 = &bullet_enemy2;

Enemyclass enemy_tank3(300,10,GO_DOWN,2);
Enemyclass *ptr_enemy_tank3 = &enemy_tank3;
Bullet bullet_enemy3;
Bullet *ptr_bullet_enemy3 = &bullet_enemy3;

char buffer [4];

void reset();
//int time_enemy;
//int reset1=1;
int i=1;					// zmienna pomocznica do sterowania funkcjonalnosciami ( menu, gra itd )
char punkty; 		 		// liczba punktow  nie powinien byc int ? chyba ze punkty mialy byc wyswietlane jako czczionka


void print_picture(unsigned long* obraz,int x,int y,int szerokosc,int wysokosc);
void print_background(unsigned long* obraz,int x,int y,int szerokosc,int wysokosc);

int main(int argc, char *argv[]) {
	SystemInit();
	DataPrepare();

	// MOZNA BY BYL TO ZROBIC W CIELE KLASY .cpp np Playerclass::Playercass {
	//player_tank.posX = 100;   // polozenie pocztokowe gracza x
	//player_tank.posY = 100; 	// polozenie poczotkowe gracza y
	//player_tank.direct = GO_RIGHT; 		// poczotokowe skierowanie czolgu - kierunki zdefiniowane w klasie.cpp
	//

	while (1) {
		UpdateIO();
		PrintDiagnosticInfo();
		ClearScreen();

		// ERAN STARTOWY - wchodzenie do gry i wychodzenie z GAME OVER
		if (gRawKeys[0]==KEY_ESC)
			i=1;
		//
		if (gRawKeys[0]==KEY_ENTER)
			i=2;



		if(i==1){
			print_picture((unsigned long*)startgame,0,0,WIDTH_startgame,HEIGHT_startgame);
			reset();
		}
		if(i==2){
			print_background((unsigned long*) background,0,0,WIDTH_background,HEIGHT_background); // sprawdzic ta funkcje bo chyba mozna to lepiej i argumentow nie przyjumuje albo zastopiac ta wyzej z odpowiednimi parametrami

			player_tank.move();    // ustawia czolga w odpowiednim kierunku i go przemieszcza
			//if (player_tank.speed_X != 0 && player_tank.speed_Y != 0)
			player_tank.moveTank();



			player_tank.print_tank(GRAPH);    // rusyje ustawionego czolga po pixelach przesunietych o odczytane z .move
			player_tank.fire(ptr_bullet_player);
			bullet_player.move_bullet();
			bullet_player.print_bullet(GRAPH);

			bullet_player.hit(ptr_enemy_tank1, &player_tank);
			enemy_tank1.move();
			enemy_tank1.kolizja(player_tank.posX, player_tank.posY);
			enemy_tank1.print_tank(GRAPH);
			enemy_tank1.fire(ptr_bullet_enemy1);
			bullet_enemy1.move_bullet();
			bullet_enemy1.print_bullet(GRAPH);

			bullet_player.hit(ptr_enemy_tank2, &player_tank);
			enemy_tank2.move();
			enemy_tank2.kolizja(player_tank.posX, player_tank.posY);
			enemy_tank2.print_tank(GRAPH);
			enemy_tank2.fire(ptr_bullet_enemy2);
			bullet_enemy2.move_bullet();
			bullet_enemy2.print_bullet(GRAPH);

			bullet_player.hit(ptr_enemy_tank3, &player_tank);
			enemy_tank3.move();
			enemy_tank3.kolizja(player_tank.posX, player_tank.posY);
			enemy_tank3.print_tank(GRAPH);
			enemy_tank3.fire(ptr_bullet_enemy3);
			bullet_enemy3.move_bullet();
			bullet_enemy3.print_bullet(GRAPH);

			bullet_enemy1.hit_player (ptr_enemy_tank1, &player_tank);
			bullet_enemy2.hit_player (ptr_enemy_tank2, &player_tank);
			bullet_enemy3.hit_player (ptr_enemy_tank3, &player_tank);

			sprintf(buffer,"%2d",player_tank.points);
			PrintText(buffer,2,600,10);

			if(enemy_tank1.wykrycie_kolizji==1 || enemy_tank2.wykrycie_kolizji==1 || enemy_tank3.wykrycie_kolizji==1)
			{
				enemy_tank1.print_gameover(GRAPH);
				player_tank.points = 0;
			}


			if (enemy_tank1.life == 0 && enemy_tank2.life == 0 && enemy_tank3.life == 0)
				print_picture((unsigned long*)win,150,150,WIDTH_win,HEIGHT_win);

		}
	}

	usleep(10000);
}


//-----------------------------------------------------------------------------------------------------------------------------//

void print_background(unsigned long* obraz,int x,int y,int szerokosc,int wysokosc){
	for (int dx=0;dx<szerokosc;dx++){
		for(int dy=0;dy<wysokosc;dy++){
			GRAPH[dx+(dy)*640]=obraz[x+dx+(y+dy)*640];}
	}
}

void print_picture(unsigned long* obraz,int x,int y,int szerokosc,int wysokosc){ //a bo jest inny bo wycina biale do okola obrazka
	for (int dx=0;dx<szerokosc;dx++){
		for(int dy=0;dy<wysokosc;dy++){
			if ((obraz[dx+dy*szerokosc])!=0x000000){
				GRAPH[x+dx+(y+dy)*640]=obraz[dx+dy*szerokosc];
			}
		}
	}
}

void rysowanie_ekran(uint32_t* tab, int posX, int posY, int length, int height)
{
	int dy=0;
	int dx=0;
	for(dy=0;dy<height;dy++)
	{
		for(dx=0;dx<length;dx++)
		{
			if (tab[dy * length + dx] != 0xFFFFFF)
			{
				GRAPH[posX+dx+(posY+dy)*640]=tab[dx+dy*length];
			}
		}
	}
}




//-----------------------------------------------------------------------------------------------------------------------------------//

void* TimerThread(void* arguments){
	struct timespec destTime;
	clock_gettime(CLOCK_MONOTONIC,&destTime);
	while(1)
	{
		destTime.tv_nsec+=1000000;
		if(destTime.tv_nsec>=1E9)
		{
			destTime.tv_nsec-=1E9;
			destTime.tv_sec++;
		}
		globalTimer_ms++;
		if(!(globalTimer_ms%1000)) flash_ligth=0xFF;
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &destTime, NULL);
	}
	return NULL;
}

void SystemInit() {
	FrameBufferFD = open("/dev/fb0", O_RDWR);
	ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info);
	framebuffer = mmap(NULL, fix_info.line_length * 480, PROT_READ | PROT_WRITE,MAP_SHARED, FrameBufferFD, 0);
	inputEventsFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	startTime_ms=tTime.tv_sec*1000+tTime.tv_usec/1000;
}

void PrintDiagnosticInfo(){
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	long TimeDiff=(tTime.tv_sec*1000+tTime.tv_usec/1000)-startTime_ms;
	long actTime=globalTimer_ms;
	if((frame_count%20)==0) printf("%i:: %li:%li=>%li KEYS: %i, %i, %i, %i, %x\n",frame_count,actTime,TimeDiff,actTime-TimeDiff,getKey(), Jx, Jy,JRz,JoYAct.ButtonStates);
}

void UpdateIO() {

	struct input_event ev;
	while (read(inputEventsFD, &ev, sizeof ev) > 0) {
		if (ev.type == EV_KEY) {
			switch (ev.value) {
			case 1:
				gRawKeys[0] = ev.code;
				break;
			case 0:
				gRawKeys[0] = 0;
				break;
			default:
				break;
			}

			switch (ev.code) {
			case KEY_KP4: JoYAct.AxisX =-127*(ev.value&1); break;
			case KEY_KP6: JoYAct.AxisX =127*(ev.value&1); break;
			case KEY_KP8: JoYAct.AxisY =-127*(ev.value&1); break;
			case KEY_KP2: JoYAct.AxisY =127*(ev.value&1); break;
			case KEY_RIGHT:
				if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_2;
				if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_2;
				break;
			case KEY_LEFT:
				if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_4;
				if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_4;
				break;
			case KEY_UP:
				if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_1;
				if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_1;
				break;
			case KEY_DOWN:
				if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_3;
				if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_3;
				break;
			default:
				break;
			}

		}

	}

}

void ClearScreen() {

	unsigned int bckgmask =getKey()>>2;

	int stage_max= -JRz/20;
	if (stage_max < 1)		stage_max = 1;
	if (stage_max > 9)		stage_max = 9;

	if (JoYAct.ButtonStates & BUTTON_SELECT)
		stage_max = 24;

	stage++;
	for (int a = stage % stage_max; a < (640 * 480); a += stage_max) {
		((u_int32_t*) framebuffer)[fix_info.line_length / 4 * (a / 640)
								   + a % 640] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1) | bckgmask;
	}
}
void DataPrepare() {
	for (unsigned char a = 0; a < sizeof(struct JoY); a++)
		((char*) &JoYAct)[a] = 0;
	ActMaxObj = MaxObj;

	for (int a = 0; a < MaxObj; a++) {
		do {
			s[a] = randr(0x1f) + 1;
			xt[a] = x[a] = randr(619 * 16 - s[a]);
			yt[a] = y[a] = randr(479 * 16 - s[a]);
			int spd = randr(15) + 7;
			dx[a] = (x[a] - 320 * 16) * spd;
			dy[a] = (y[a] - 240 * 16) * spd;

			while (abs(dx[a]) > (9) || abs(dy[a]) > (9)) {
				dx[a] /= 3;
				dy[a] /= 3;
			}
		} while ((abs(dy[a]) + abs(dx[a])) <= 4);
	}
}


void reset()
{

	player_tank.posX=300;
	player_tank.posY=200;

	enemy_tank1.posX=550;;
	enemy_tank1.posY=rand()%350;
	enemy_tank1.predkosc=rand()%3+1;
	enemy_tank1.wykrycie_kolizji=0;
	enemy_tank1.life = 1;

	enemy_tank2.posX=rand()%100;
	enemy_tank2.posY=0;
	enemy_tank2.predkosc=rand()%4 +1;
	enemy_tank2.wykrycie_kolizji=0;
	enemy_tank2.life = 1;

	enemy_tank3.posX=rand()%500+1;;
	enemy_tank3.posY=rand()%150;
	enemy_tank3.predkosc=rand()%5+1;
	enemy_tank3.wykrycie_kolizji=0;
	enemy_tank3.life = 1;

}
