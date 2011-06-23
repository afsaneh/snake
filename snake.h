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
	char color[20];
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
void printSnake(struct snake *s);
int sentinelIndex(struct snake *s);
struct point head(struct snake *s);
struct point tail(struct snake *s);
int moveSnake(struct snake *s, int direction);
int moveSnakeAI(struct snake *s);
void insertHead(struct snake *s, struct point m);
void insertTail(struct snake *s, struct point m);
void removeHead(struct snake *s);
void removeTail(struct snake *s);
void snakeToString(struct snake *s);
//void initSnake(struct point[], struct point);
int isFreeSpace(struct point p);

char canvas[HEIGHT][WIDTH];

//struct point snakeArray1[HEIGHT*WIDTH];
//struct point snakeArray2[HEIGHT*WIDTH];
