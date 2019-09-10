typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

#define UNUSED_PARAM(param) ((void)((param)))

#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED COLOR(31,0,0)
#define WHITE COLOR(31,31,31)
#define GREEN COLOR(0, 31, 0)
#define BLACK 0

#define WIDTH 240 //this is the width of the GBA emulator

unsigned short *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int col, u16 color);
void drawRectangle(int row, int col, int width, int height, u16 color);
void drawHollowRectangle(int row, int col, int width, int height, u16 color);

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	// use the functions you wrote to draw a pretty picture here!

	setPixel(10, 10, RED);
	drawRectangle(20, 20, 60, 20, WHITE);
	drawHollowRectangle(40, 100, 40, 20, GREEN);

	while(1);
}

void setPixel(int row, int col, u16 color)
{ 
	//TODO: set the pixel at the particular row and column
    
    int index = (WIDTH) * (row) + (col);
    videoBuffer[index] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color)
{
	//TODO: Draws a rectangle of the particular width and height with the left-most pixel being located at (row, col)
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            setPixel(row + i, col + j, color);
        }
    }
    
}

void drawHollowRectangle(int row, int col, int width, int height, u16 color)
{
	//TODO: Draws a hollow rectangle of the particular width and height with the left-most pixel being located at (row, col)
	// MUST BE EFFICIENT - cannot be O(n*n) time
    for (int i = 0; i <= width; i++) {
        setPixel(row, col + i, color);
        setPixel(row + height, col + i, color);
    }

    for (int i = 0; i <= height; i++) {
        setPixel(row + i, col, color);
        setPixel(row + i, col + width, color);
    }
    


    UNUSED_PARAM(width);
}
