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
	return -1;
	
}

struct point head(struct point s[]){
	return s[0];
}

struct point tail(struct point s[]){
	return s[sentinelIndex(s) - 1];
}


int moveSnake(struct point s[], int direction, int currentDirection){
	//let's not lose if the current direction is left and you press right
	//printf("move: %d", currentDirection);
	if (direction == UP && currentDirection == DOWN)
		direction = DOWN;
	if (direction == DOWN && currentDirection == UP)
		direction = UP;
	if (direction == RIGHT && currentDirection == LEFT)
		direction = LEFT;
	if (direction == LEFT && currentDirection == RIGHT)
		direction = RIGHT;

	if (direction == UP){
		//if (currentDirection == DOWN)
		//	return 1;
		insertTail(s, (addY(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == DOWN){
		//if (currentDirection == UP)
		//	return 1;
		insertTail(s, (addY(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == RIGHT){
		//if (currentDirection == LEFT)
		//	return 1;
		insertTail(s, (addX(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == LEFT){
		//if (currentDirection == RIGHT)
		//	return 1;
		insertTail(s, (addX(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}

	putPoint(' ', head(s));
	removeHead(s);
	putPoint('0', tail(s));

	return 1;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int moveSnakeAI(struct point s[], int *direction){
	struct point pointUp = addY(tail(s), -1);
	struct point pointDown = addY(tail(s), 1);
	struct point pointRight = addX(tail(s), 1);
	struct point pointLeft = addX(tail(s), -1);
	int currentDirection = *direction;
	int makeUnexpectedTurn = 0;

	if (rand() % 10 == 0)
		makeUnexpectedTurn = 1;

	putPoint(' ', head(s));

	if (*direction == UP){
		if (isFreeSpace(pointUp)){
			if (makeUnexpectedTurn && isFreeSpace(pointRight)){
				*direction = RIGHT;
				return moveSnake(s, RIGHT, currentDirection);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointLeft)){
				*direction = LEFT;
				return moveSnake(s, LEFT, currentDirection);
			}

			return moveSnake(s, UP, currentDirection);
			}
		else{
			if(isFreeSpace(pointRight)){
				*direction = RIGHT;
				return moveSnake(s, RIGHT, currentDirection);
			}
			else{
				*direction = LEFT;
				return moveSnake(s, LEFT, currentDirection);
			}
		}
	}
	else if (*direction == DOWN){
		if (isFreeSpace(pointDown)){
			if (makeUnexpectedTurn && isFreeSpace(pointRight)){
				*direction = RIGHT;
				return moveSnake(s, RIGHT, currentDirection);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointLeft)){
				*direction = LEFT;
				return moveSnake(s, LEFT, currentDirection);
			}
			return moveSnake(s, DOWN, currentDirection);
		
			}else{
			if(isFreeSpace(pointRight)){
				*direction = RIGHT;
				return moveSnake(s, RIGHT, currentDirection);
			}
			else{
				*direction = LEFT;
				return moveSnake(s, LEFT, currentDirection);
			}
		}
	}
	else if (*direction == RIGHT){
		if (isFreeSpace(pointRight)){
			if (makeUnexpectedTurn && isFreeSpace(pointUp)){
				*direction = UP;
				return moveSnake(s, UP, currentDirection);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointDown)){
				*direction = DOWN;
				return moveSnake(s, DOWN, currentDirection);
			}
			
			return moveSnake(s, RIGHT, currentDirection);
		
			}else{
			if(isFreeSpace(pointUp)){
				*direction = UP;
				return moveSnake(s, UP, currentDirection);
			}
			else{
				*direction = DOWN;
				return moveSnake(s, DOWN, currentDirection);
			}
		}
	}
	else if (*direction == LEFT){
		if (isFreeSpace(pointLeft)){
			if (makeUnexpectedTurn && isFreeSpace(pointUp)){
				*direction = UP;
				return moveSnake(s, UP, currentDirection);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointDown)){
				*direction = DOWN;
				return moveSnake(s, DOWN, currentDirection);
			}
	

		return moveSnake(s, LEFT, currentDirection);
		
		}
		else{
			if(isFreeSpace(pointUp)){
				*direction = UP;
				return moveSnake(s, UP, currentDirection);
			}
			else{
				*direction = DOWN;
				return moveSnake(s, DOWN, currentDirection);
			}
		}
	}
	return 0;
}


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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
	if (canvas[p.y][p.x] != '0' && canvas[p.y][p.x] != '\'' )
		return 1;
	return 0;		
}
