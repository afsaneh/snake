#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "snake.h"

#define UPARROW1 1002
#define LEFTARROW1 1001
#define RIGHTARROW1 1003
#define DOWNARROW1 1004
/*#define UPARROW2 'w'
#define LEFTARROW2 'a'
#define RIGHTARROW2 'd'
#define DOWNARROW2 's'*/
#define QUIT 'q'

#define SNAKESPEED 150

struct point makePoint(int x, int y){
	struct point p = {x, y};
	return p;
}

int main(){
	struct snake snake1, snake2;

	snake1.len = SNAKELENGTH;
	snake1.color = FOREGROUND_RED | FOREGROUND_INTENSITY;
	snake1.shape = '0';

	snake2.len = SNAKELENGTH;
	snake2.color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	snake2.shape = 'x';

	int c;
	int i, j;
	int count = 0;
	int dir1 = RIGHT;
	int speed = SNAKESPEED;
	int rx, ry, dirx, diry;
	int retSnake1, retSnake2;

	SetConsoleTitle("Snakes");
	initializeMatrix(canvas);

	for (i = 0; i < snake1.len; i++)
		snake1.points[i] = makePoint(i,5);
	snake1.points[i] = SENTINEL;
	printSnake(&snake1);

	for(j = 0; j < snake2.len ; j++)
		snake2.points[j] = makePoint(j,10);
	snake2.points[j] = SENTINEL;
	snake2.direction = RIGHT;
	printSnake(&snake2);
	
	srand(time(NULL));
	
	while((c = getKey()) != QUIT){
			snake1.direction = dir1;
			switch (c){
				case UPARROW1: dir1 = UP; break;
				case LEFTARROW1: dir1 = LEFT; break;
				case RIGHTARROW1: dir1 = RIGHT; break;
				case DOWNARROW1: dir1 = DOWN; break;
				default: break;
			}
			while( !_kbhit()){
				count++;
				if (rand() % 200 == 0){
					rx = rand() % (WIDTH - 8) + 4;
					ry = rand() % (HEIGHT - 8) + 4;
					dirx = rand() % 3 - 1;
					diry = rand() % 3 - 1;
					line('*', makePoint(rx, ry), makePoint(rx + dirx*4 , ry + diry*4));
				}
				Sleep(speed);
				if (count % 50 == 0 && speed > 50){
					count = 0;
					speed *= 0.99;
				}
				retSnake1 = moveSnake(&snake1, dir1);
				retSnake2 = moveSnakeAI(&snake2);
			
				if (retSnake1 ==0 && retSnake2 == 0)
					printf("GAME OVER! BUT NOBODY WON!");
				if (retSnake1 == 0 ){
					userGameover("Computer won!");
					return 0;
				}
				else if (retSnake2 == 0){
					pcGameover("You won!");
					return 0;
				}
		}
	}
}

int getKey(void){
	//get a key and return its ASCII number	

	int c = _getch();

	if(c == 224){
    	c = _getch();
		if (c == 75)
			c = LEFTARROW1;
		else if (c == 72)
			c = UPARROW1;
		else if (c == 77)
			c = RIGHTARROW1;
		else if (c == 80)
			c = DOWNARROW1;
	}
	return c;
}

void initializeMatrix(char matrix[][WIDTH]){
	//get a matrix and set its elements to ' '

	int i, j;	
	
	for(i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH; j++)
			matrix[i][j] = ' ';
}
	
void putPoint(char character , struct point p, int color){
	//put the character in (x,y) position in canvas & set cursor in (x,y) position in console 
	HANDLE hOut;
    COORD Position;


	canvas[p.y][p.x] = character;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = p.x;
    Position.Y = p.y;
    SetConsoleCursorPosition(hOut, Position);
	SetConsoleTextAttribute(hOut,color);
    putchar(character);
}

void line(char character, struct point p1, struct point p2){
	//get two points and draw a line between them
	
	double m, b;
	int x, y;
	int temp;
	int i;
	
	if (p2.x == p1.x){
		if ( p1.y > p2.y){
			//set y2 greater than x1
			temp = round(p1.y);
			p1.y = round(p2.y);
			p2.y = temp;
		}
		for(i = p1.y; i <= p2.y; i++)
			//printf("%d, %d\n ", x1, i);
			putPoint(character, makePoint(p1.x, i));
		return;
	}	
	m = (double)(p2.y - p1.y) / (p2.x - p1.x);
	b = p1.y - m*p1.x;
	if (m < 1 && m > -1){
		if ( p1.x > p2.x){
			//set x2 greater than x1
			temp = p1.x;
			p1.x = p2.x;
			p2.x = temp;
		}
		for(i = p1.x; i <= p2.x; i++){
			y = round(m *(i)+ b);
			//printf("%d, %d\n ", i, y);
			putPoint(character, makePoint(i, y));
		}
	}
	else {
		if ( p1.y > p2.y){
			//set y2 greater than x1
			temp = p1.y;
			p1.y = p2.y;
			p2.y = temp;
		}
		for(i = p1.y; i <= p2.y; i++){
			x = round((i - b)/ m);
			//printf("i= ,%d ,m= ,%f,b= ,%f,x= ,%d\n ", i,m, b, x );
			putPoint(character, makePoint(x, i));
		}
	}
}

void rectangle(char character, struct point p1, int width, int height){
	//get upper point, width and height and draw a rectangle with character
	struct point p2 = {p1.x + width - 1, p1.y}; // "-1" because starting point is (0,0)
	struct point p3 = {p1.x, p1.y + height - 1}; 
	struct point p4 = {p1.x + width - 1, p1.y + height - 1}; 
	
	line(character, p1, p2);
	line(character, p2, p4);
	line(character, p4, p3);
	line(character, p3, p1);
}

void pointToString(struct point p){
	//print a point like (x,y)
	printf("(%d,%d)", p.x, p.y);
}

struct point addX(struct point p, int amount){
	//get a point and + or - amount from p.x
	
	p.x = (p.x + amount) % WIDTH;
	if(p.x < 0)
		p.x = p.x + WIDTH;
	return p;
}

struct point addY(struct point p, int amount){
	//get a point and + or - amount from p.y
	
	p.y = (p.y + amount) % HEIGHT;
	if(p.y < 0)
		p.y = p.y + HEIGHT;
	return p;
}

void userGameover(char m[]){

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	int size, x;
	char string[50];
	Sleep(1000);
	system("cls");

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	sprintf(string, "%s", m);
	printf("\n\n\n\n\t\t\t\t%s", string);
  
	SetConsoleTextAttribute(h,FOREGROUND_RED |
							 FOREGROUND_GREEN | 
							FOREGROUND_INTENSITY);
	printf("\a");
	char sentgo[]="\n\n"
              "\n\n\n\n\n\n"
              "\t\t\t  Ok! Seems you've become sooks!\n"
              "\n\n"
              "\t\t\t  Concentrate more on the game!\n"
              "\n\n"
              "\t\t\t  Ha Ha\n"
              "\n\n"
              "\t\t\t  .....\n"
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t"
              "\n\t\t\t  G  A  M  E    O  V  E  R!\n";
                         
	size=strlen(sentgo);
	for(x=0;x<size;x++){   
		Sleep(40); 
		printf("%c",sentgo[x]);
	}
	Sleep(4000);
	exit(0);
}

void pcGameover(char m[]){

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	int size, x;
	char string[50];
	Sleep(1000);
	system("cls");

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	sprintf(string, "%s", m);
	printf("\n\n\n\n\t\t\t\t%s", string);
  
	SetConsoleTextAttribute(h,FOREGROUND_RED |
							 FOREGROUND_GREEN | 
							FOREGROUND_INTENSITY);
	printf("\a");
	char sentgo[]="\n\n"
              "\n\n\n\n\n\n"
              "\t\t\t  Good job!\n"
              "\n\n"
              "\t\t\t  Seems PC has become sooks!\n"
              "\n\n"
              "\t\t\t  Ha Ha\n"
              "\n\n"
              "\t\t\t  .....\n"
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t  ."
              "\n\n\t\t\t"
              "\n\t\t\t  G  A  M  E    O  V  E  R!\n";
                         
	size=strlen(sentgo);
	for(x=0;x<size;x++){   
		Sleep(40); 
		printf("%c",sentgo[x]);
	}
	Sleep(4000);
	exit(0);
}
