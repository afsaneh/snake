#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
 
void printSnake(struct snake *s){
	//for printing a snake array
	int i = 0;
	while(s -> points[i].x != -1) //while the array is not (-1, -1)
		putPoint(s -> shape, s -> points[i++], s -> color);
}

int sentinelIndex(struct snake *s){
	int i;

	for(i = 0; i < (s -> len) + 1; i++)
		if(s -> points[i].x == -1 && s -> points[i].y == -1)
			return i;
	return -1;
}

struct point head(struct snake *s){
	return s -> points[0];
}

struct point tail(struct snake *s){
	return s -> points[(s -> len) - 1];
}


int moveSnake(struct snake *s, int direction){
	
	if (direction == UP && s -> direction == DOWN)
		direction = DOWN;
	if (direction == DOWN && s -> direction == UP)
		direction = UP;
	if (direction == RIGHT && s -> direction == LEFT)
		direction = LEFT;
	if (direction == LEFT && s -> direction == RIGHT){
		direction = RIGHT;
	}

	if (direction == UP){
		insertTail(s, (addY(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == DOWN){
		insertTail(s, (addY(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == RIGHT){
		insertTail(s, (addX(tail(s), 1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == LEFT){
		insertTail(s, (addX(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	putPoint(' ', head(s),s -> color);
	removeHead(s);
	putPoint(s -> shape, tail(s), s -> color);

	return 1;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int moveSnakeAI(struct snake *s){
	struct point pointUp = addY(tail(s), -1);
	struct point pointDown = addY(tail(s), 1);
	struct point pointRight = addX(tail(s), 1);
	struct point pointLeft = addX(tail(s), -1);
	int makeUnexpectedTurn = 0;
	int firstDir = 0, secondDir = 0;

	if (rand() % 10 == 0)
		makeUnexpectedTurn = 1;

	putPoint(' ', head(s));

	if (s -> direction == UP){
		if (isFreeSpace(pointUp)){
			if (makeUnexpectedTurn){
				firstDir = RIGHT;
				secondDir = LEFT;
			}
			if (rand() % 2 == 0){
					firstDir = LEFT;
					secondDir = RIGHT;
			}
			if (firstDir == RIGHT && isFreeSpace(pointRight) ||
					firstDir == LEFT && isFreeSpace(pointLeft)){
					s -> direction = firstDir;
					return moveSnake(s, firstDir);
			}
			if ((secondDir == LEFT && isFreeSpace(pointLeft)) || 
					(secondDir == RIGHT && isFreeSpace(pointDown))){
					s -> direction = secondDir;
					return moveSnake(s, secondDir);
			}
			return moveSnake(s, UP);
		}
		else{
			if(isFreeSpace(pointRight)){
				s -> direction = RIGHT;
				return moveSnake(s, RIGHT);
			}
			else{
				s -> direction = LEFT;
				return moveSnake(s, LEFT);
			}		
		}
	}

	else if (s -> direction == DOWN){
		if (isFreeSpace(pointDown)){
			if (makeUnexpectedTurn){
				firstDir = RIGHT;
				secondDir = LEFT;
			}
			if (rand() % 2 == 0){
					firstDir = LEFT;
					secondDir = RIGHT;
			}
			if (firstDir == RIGHT && isFreeSpace(pointRight) ||
					firstDir == LEFT && isFreeSpace(pointLeft)){
					s -> direction = firstDir;
					return moveSnake(s, firstDir);
			}
			if ((secondDir == LEFT && isFreeSpace(pointLeft)) || 
					(secondDir == RIGHT && isFreeSpace(pointDown))){
					s -> direction = secondDir;
					return moveSnake(s, secondDir);
			}
			return moveSnake(s, DOWN);
		}
		else{
				if(isFreeSpace(pointRight)){
					s -> direction = RIGHT;
					return moveSnake(s, RIGHT);
			}
				else{
						s -> direction = LEFT;
						return moveSnake(s, LEFT);
					}
			}
	}
	else if (s -> direction == RIGHT){
		if (isFreeSpace(pointRight)){
			if (makeUnexpectedTurn){
				firstDir = UP;
				secondDir = DOWN;
				if (rand() % 2 == 0){
					firstDir = DOWN;
					secondDir = UP;
				}
		
				if ((firstDir == UP && isFreeSpace(pointUp)) || 
					(firstDir == DOWN && isFreeSpace(pointDown))){
					s -> direction = firstDir;
					return moveSnake(s, firstDir);
				}
				if ((secondDir == DOWN && isFreeSpace(pointDown)) || 
					(secondDir == UP && isFreeSpace(pointUp))){
					s -> direction = secondDir;
					return moveSnake(s, secondDir);
				}	
			}
			return moveSnake(s, RIGHT);
		
		}else{
				if(isFreeSpace(pointUp)){
					s -> direction = UP;
					return moveSnake(s, UP);
				}
				else{
						s -> direction = DOWN;
						return moveSnake(s, DOWN);
					}
			}
	}
	else if (s -> direction == LEFT){
		if (isFreeSpace(pointLeft)){
			if (makeUnexpectedTurn){
				firstDir = UP;
				secondDir = DOWN;
				if (rand() % 2 == 0){
					firstDir = DOWN;
					secondDir = UP;
				}
		
				if ((firstDir == UP && isFreeSpace(pointUp)) || 
					(firstDir == DOWN && isFreeSpace(pointDown))){
					s -> direction = firstDir;
					return moveSnake(s, firstDir);
				}
				if ((secondDir == DOWN && isFreeSpace(pointDown)) || 
					(secondDir == UP && isFreeSpace(pointUp))){
					s -> direction = secondDir;
					return moveSnake(s, secondDir);
				}	
			
			}
			return moveSnake(s, LEFT);
		
		}
		else{
			if(isFreeSpace(pointUp)){
				s -> direction = UP;
				return moveSnake(s, UP);
			}
			else{
					s -> direction = DOWN;
					return moveSnake(s, DOWN);
				}
		}
	}
	return 0;
}


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void insertHead(struct snake *s, struct point m){
	//
	int i;

	for(i = s -> len ; i > 0; i--)
		s -> points[i+1] = s -> points[i];
	s -> points[0] = m;
}

void insertTail(struct snake *s, struct point m){

	s -> points[(s -> len) + 1] = SENTINEL;
	s -> points[s -> len] = m;
	s -> len += 1;
}

void removeHead(struct snake *s){
		
	int i;

	for(i = 0; i < s -> len; i++)
		s -> points[i] = s -> points[i+1];
	s -> len -= 1;
}

void removeTail(struct snake *s){
	s -> points[(s -> len) - 1] = SENTINEL;
}

void snakeToString(struct snake *s){
	int i;

	for(i = 0; s -> points[i].x != -1 ; i++)
		pointToString(s -> points[i]);
}

/*void initSnake(struct point s[], struct point head){
	int i;

	for(i = 0; i < 5; i++){
		s[i] = head;
		head.x++;
	}
	s[i] = SENTINEL;
}*/

int isFreeSpace(struct point p){
	if (canvas[p.y][p.x] == ' ')
		return 1;
	return 0;
}
