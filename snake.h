#define WIDTH 80
#define HEIGHT 25
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define sentinel makePoint(-1, -1)

struct point{
	int x;
	int y;
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
void printSnake(struct point s[]);
struct point head(struct point[]);
struct point tail(struct point[]);
int moveSnake(struct point[], int, int);
int moveSnakeAI(struct point[], int *direction);
void insertHead(struct point[], struct point);
void insertTail(struct point[], struct point);
void removeHead(struct point[]);
void removeTail(struct point[]);
void snakeToString(struct point[]);
//void initSnake(struct point[], struct point);
int isFreeSpace(struct point);

char canvas[HEIGHT][WIDTH];

struct point snakeArray1[HEIGHT*WIDTH];
struct point snakeArray2[HEIGHT*WIDTH];
