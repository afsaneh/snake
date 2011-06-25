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
	//BOOL WINAPI color;
};

//main.c
struct point makePoint(int, int);
int getKey();
void initializeMatrix(char matrix[][WIDTH]);
void putPoint(char, struct point);
void line(char, struct point, struct point);
void rectangle( char, struct point, int, int);
void pointToString(struct point);	
struct point addX(struct point, int);
struct point addY(struct point, int);
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
void gameover(char []);

char canvas[HEIGHT][WIDTH];

//struct point snakeArray1[HEIGHT*WIDTH];
//struct point snakeArray2[HEIGHT*WIDTH];
