#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"
 
void printSnake(struct snake *s){
	//for printing a snake array
	int i = 0;
	while(s -> points[i].x != -1) //while the array is not (-1, -1) ==> end of 
		putPoint('0', s -> points[i++]);
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
	//let's not lose if the current direction is left and you press right
	
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
		//printf("\nSnake after press right: ");
		//snakeToString(s);
		//printf("\nfirst\n");
		//pointToString(tail(s));
		//printf("\naddx tail: ");
		//pointToString(addX(tail(s), 1));
		insertTail(s, (addX(tail(s), 1)));
		//printf("\nsnake after insert:");
		//snakeToString(s);
		//printf("\ntail\n");
		//pointToString(tail(s));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	else if (direction == LEFT){
		insertTail(s, (addX(tail(s), -1)));
		if (!isFreeSpace(tail(s)))
			return 0;
	}
	putPoint(' ', head(s));
	removeHead(s);
	//pointToString(tail(&s));
	putPoint('0', tail(s));

	return 1;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int moveSnakeAI(struct snake *sp){
	struct point pointUp = addY(tail(sp), -1);
	struct point pointDown = addY(tail(sp), 1);
	struct point pointRight = addX(tail(sp), 1);
	struct point pointLeft = addX(tail(sp), -1);
	int makeUnexpectedTurn = 0;

	if (rand() % 10 == 0)
		makeUnexpectedTurn = 1;

	putPoint(' ', head(sp));

	if (sp -> direction == UP){
		if (isFreeSpace(pointUp)){
			if (makeUnexpectedTurn && isFreeSpace(pointRight)){
				sp -> direction = RIGHT;
				return moveSnake(sp, RIGHT);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointLeft)){
				sp -> direction = LEFT;
				return moveSnake(sp, LEFT);
			}

			return moveSnake(sp, UP);
			}
		else{
			if(isFreeSpace(pointRight)){
				sp -> direction = RIGHT;
				return moveSnake(sp, RIGHT);
			}
			else{
				sp -> direction = LEFT;
				return moveSnake(sp, LEFT);
			}
		}
	}
	else if (sp -> direction == DOWN){
		if (isFreeSpace(pointDown)){
			if (makeUnexpectedTurn && isFreeSpace(pointRight)){
				sp -> direction = RIGHT;
				return moveSnake(sp, RIGHT);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointLeft)){
				sp -> direction = LEFT;
				return moveSnake(sp, LEFT);
			}
			return moveSnake(sp, DOWN);
		
			}else{
			if(isFreeSpace(pointRight)){
				sp -> direction = RIGHT;
				return moveSnake(sp, RIGHT);
			}
			else{
				sp -> direction = LEFT;
				return moveSnake(sp, LEFT);
			}
		}
	}
	else if (sp -> direction == RIGHT){
		if (isFreeSpace(pointRight)){
			if (makeUnexpectedTurn && isFreeSpace(pointUp)){
				sp -> direction = UP;
				return moveSnake(sp, UP);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointDown)){
				sp -> direction = DOWN;
				return moveSnake(sp, DOWN);
			}
			
			return moveSnake(sp, RIGHT);
		
			}else{
			if(isFreeSpace(pointUp)){
				sp -> direction = UP;
				return moveSnake(sp, UP);
			}
			else{
				sp -> direction = DOWN;
				return moveSnake(sp, DOWN);
			}
		}
	}
	else if (sp -> direction == LEFT){
		if (isFreeSpace(pointLeft)){
			if (makeUnexpectedTurn && isFreeSpace(pointUp)){
				sp -> direction = UP;
				return moveSnake(sp, UP);
			}
			if (makeUnexpectedTurn && isFreeSpace(pointDown)){
				sp -> direction = DOWN;
				return moveSnake(sp, DOWN);
			}
	

		return moveSnake(sp, LEFT);
		
		}
		else{
			if(isFreeSpace(pointUp)){
				sp -> direction = UP;
				return moveSnake(sp, UP);
			}
			else{
				sp -> direction = DOWN;
				return moveSnake(sp, DOWN);
			}
		}
	}
	return 0;
}


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void insertHead(struct snake *s, struct point m){
	//
	int i;

	for(i = sentinelIndex(s) ; i > 0; i--)
		s -> points[i+1] = s -> points[i];
	s -> points[0] = m;
}

void insertTail(struct snake *s, struct point m){
	//

	//s.points[sentinelIndex(s) + 1] = SENTINEL;
	//s.points[sentinelIndex(s)] = m;
	//printf("\n snake in inserttail: ");
	//snakeToString(s);
	s -> points[(s -> len) + 1] = SENTINEL;
	s -> points[(s -> len)] = m;
	s -> len += 1;
	//printf("\n snake after inserttail: ");
	//snakeToString(s);
}

void removeHead(struct snake *s){
		
	int i;

	for(i = 0; i < sentinelIndex(s); i++)
		s -> points[i] = s -> points[i+1];
	s -> len -= 1;
}

void removeTail(struct snake *s){
	s -> points[sentinelIndex(s) - 1] = SENTINEL;
}

void snakeToString(struct snake *s){
	int i;

	for(i = 0; s -> points[i].x != -1 ; i++)
	//for(i = 0; i < (s -> len) ; i++)
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
	//printf("\nFree Space: ");
	//pointToString(p);
	if (canvas[p.y][p.x] == ' ' )
		return 1;
	return 0;		
}
