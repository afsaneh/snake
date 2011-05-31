#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
 
void printSnake(struct point s[]){
	//for printing a snake array
	int i = 0;
	while(s[i].x != -1) //while the array is not (-1, -1) ==> end of 
		putPoint('0', s[i++]);	
}

int sentinelIndex(struct point s[]){
	int i;

	for(i = 0; i < (HEIGHT*WIDTH); i++)
		if(s[i].x == -1 && s[i].y == -1)
			return i;
	
}

struct point head(struct point s[]){
	return s[0];
}

struct point tail(struct point s[]){
	return s[sentinelIndex(s) - 1];
}

int moveSnake(struct point s[], int direction){
	
	putPoint(' ', head(s));

	if (direction == UP){
		insertTail(s, (addY(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
		removeHead(s);
		putPoint('0', tail(s));
	}
	else if (direction == DOWN){
		insertTail(s, (addY(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
		removeHead(s);
		putPoint('0', tail(s));
	}
	else if (direction == RIGHT){
		insertTail(s, (addX(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
		removeHead(s);
		putPoint('0', tail(s));
	}
	else if (direction == LEFT){
		insertTail(s, (addX(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
		removeHead(s);
		putPoint('0', tail(s));
	}
	return 1;
}

void insertHead(struct point s[], struct point m){
	//
	int i;

	for(i = sentinelIndex(s) ; i > 0; i--)
		s[i+1] = s[i];
	s[0] = m;
}

void insertTail(struct point s[], struct point m){
	//

	s[sentinelIndex(s)+ 1] = sentinel;
	s[sentinelIndex(s)] = m;
}

void removeHead(struct point s[]){
		
	int i;

	for(i = 0; i < sentinelIndex(s); i++)
		s[i] = s[i+1];
}

void removeTail(struct point s[]){
	s[sentinelIndex(s) - 1] = sentinel;
}

void snakeToString(struct point s[]){
	int i;

	for(i = 0; s[i].x != -1 ; i++)
		pointToString(s[i]);
}

/*void initSnake(struct point s[], struct point head){
	int i;

	for(i = 0; i < 5; i++){
		s[i] = head;
		head.x++;
	}
	s[i] = sentinel;
}*/

int isFreeSpace(struct point p){
	if (canvas[p.y][p.x] == ' ')
		return 1;
	return 0;		
}
