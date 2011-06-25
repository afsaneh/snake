#define WIDTH 80
#define HEIGHT 25
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define SENTINEL makePoint(-1, -1)
#define SNAKELENGTH 12

struct point{
	int x;
	int y;
};

struct snake{
	struct point points[HEIGHT * WIDTH];
	int direction;
	int len;
	int color;
	char shape;
};

//main.c
struct point makePoint(int, int);
int getKey();
void initializeMatrix(char matrix[][WIDTH]);
void putPoint(char, struct point, int color = FOREGROUND_GREEN);
void line(char, struct point, struct point);
void rectangle( char, struct point, int, int);
void pointToString(struct point);	
struct point addX(struct point, int);
struct point addY(struct point, int);
int isClosePoints(struct point, struct point);
//snake.c
void printSnake(struct snake *);
int sentinelIndex(struct snake *);
struct point head(struct snake *);
struct point tail(struct snake *);
int moveSnake(struct snake *, int);
int moveSnakeAI(struct snake *);
void insertHead(struct snake *, struct point);
void insertTail(struct snake *, struct point);
void removeHead(struct snake *);
void removeTail(struct snake *);
void snakeToString(struct snake *);
//void initSnake(struct point[], struct point);
int isFreeSpace(struct point p);
void userGameover(char []);
void pcGameover(char []);

char canvas[HEIGHT][WIDTH];
