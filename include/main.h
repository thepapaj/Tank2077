#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#ifndef KIERUNKI
#define KIERUNKI

#define GO_LEFT 3                // kierunki w ktora strone ma byc obcrocona bitmapka czolgu
#define GO_RIGHT 4
#define GO_UP 2
#define GO_DOWN 1

#endif /* KIERUNKI */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/input.h>
#include <time.h>
#include <pthread.h>

#include "utilities.h"
#include "peripherals.h"

#include "win.h"
#include "tank_up.h"
#include "tank_right.h"
#include "tank_left.h"
#include "tank_down.h"
#include "startgame.h"
#include "background.h"
#include "Enemyclass.h"
#include "bullet.h"
#include "Playerclass.h"

extern struct JoY JoYAct;
extern int gRawKeys[6];

void UpdateIO();
void SystemInit();
void SystemExit();
void DataPrepare();
void ClearScreen();
void DrawObjects();
void PrintDiagnosticInfo();
void rysowanie_ekran(uint32_t* tab, int, int, int, int);
#include "chars.h"
#include "print_text.h"

#define MaxObj 9000
int ActMaxObj;
int dx[MaxObj];
int dy[MaxObj];
int s[MaxObj];
int x[MaxObj];
int y[MaxObj];
int xt[MaxObj];
int yt[MaxObj];

unsigned int GRAPH[640 * 480];


int mode = 0;
int stage = 0;
volatile int flash_ligth=0;
volatile long globalTimer_ms=0;
long startTime_ms;
int frame_count = 0;
pthread_t tID;

int Jxt = 0, Jyt = 0, Jx = 0, Jy = 0, Jz = 0, JRz = 0;


char *fbname;
int FrameBufferFD, inputEventsFD;
struct fb_fix_screeninfo fix_info;
struct fb_var_screeninfo var_info;
void *framebuffer;

#endif /* SRC_MAIN_H_ */
