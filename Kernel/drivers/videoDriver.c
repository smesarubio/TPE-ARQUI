#include <stdint.h>
#include <videoDriver.h>
#include <syscalls.h>
#include <colors.h>
#include <fonts.h>
#include <time.h>

extern int get_seconds();
struct vbe_mode_info_structure
{
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));

typedef struct vbe_mode_info_structure *VBEInfoPtr;
unsigned int WIDTH = 1024;
unsigned int HEIGHT = 768;
unsigned int PIXEL_SIZE = 3; //bytes por pixel 
unsigned int DEFAULT_BG_COLOUR = BACKGROUND;
unsigned int DEFAULT_FONT_COLOUR = FOREGROUND;

unsigned int USER_LENGHT=0;//14
unsigned int lineCounter=0;


VBEInfoPtr VBE_mode_info = (VBEInfoPtr)0x0000000000005C00;

typedef struct
{
    uint32_t defaultBGColour;
    uint32_t defaultFontColour;
    int currentX;
    int currentY;
    uint32_t offset;
    uint32_t width;
    uint32_t height;
	int userLen;
	// uint32_t firstLine;
	// uint32_t firstLineWidth;
} t_screen;

t_screen * screen;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y){
    uint8_t *framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset] = (hexColor) & 0xFF; //AZUL
    framebuffer[offset+1] = (hexColor>>8) & 0xFF ; //VERDE
    framebuffer[offset+2] = (hexColor>>16) & 0xFF; // ROJO
}

void setVideoUserLen(int len){
	screen->userLen = len;
}

void load_video(){

    screen->defaultBGColour = BACKGROUND;
    screen->defaultFontColour = FOREGROUND;
    screen->currentX = 2;
    screen->offset=0;
    screen->currentY = 28;
	screen->width = WIDTH;
    screen->height = HEIGHT;
	paint(screen->defaultBGColour);
	//welcomeMessage();
	/*
	printCharAt('S', 1, 28);
	printCharAt('S', 400, 400);
	printCharAt('a', 408, 400);
	printCharAt('n', 408+8, 400);
	printCharAt('c', 408+8+8, 400);
	printCharAt('h', 408+8+8+8, 400);
	printCharAt('u', 408+8+8+8+8, 400); */
}

void paint(uint32_t color){
		
	for (unsigned int i = 0; i < WIDTH; i++)
	{
		for (unsigned int j = 0; j < HEIGHT; j++)
		{
			putPixel(color, i, j);
		}
	}	

}

void clear(){
	screen->currentX = 2;
    screen->offset=0;
    screen->currentY = 28;
	paint(BACKGROUND);
}

void paintTransition(){
	for (unsigned int i = 0; i < HEIGHT; i++)
	{
		for (unsigned int j = 0; j < WIDTH; j++)
		{
			putPixel(BACKGROUND, j, i);
		}
		}
}


void cursor() {
    int changeDetected = 0;
    if(!changeDetected && ticks_elapsed() % 9  ==0){
            changeDetected=1;
            writeStatic('_');
            if(ticks_elapsed()%18==0){
                writeStatic(' ');
            }
        }
        if(changeDetected &&  ticks_elapsed() %6 !=0){
            changeDetected=0;
        }
}

void stopCursor() {
    writeStatic(' ');
}

void writeStatic(char c){
	printCharAt(c, screen->currentX, screen->currentY);
}


void printInScreen(char * c, int len){
	for (int i = 0; c[i] != 0 && i<len; i++){
		write(c[i]);
	}
}


void write(char c){
	if(c == 10){
		printNewLine();
		return;
	}
	if(c == '\b'){
		printBackspace();
		return;
	}
	if(c == '\t'){
		printTab();
		return;
	}
	printCharAt(c, screen->currentX, screen->currentY);
	screen->currentX += 8;
	if (screen->currentX>= screen->width){
		screen->currentX = 2;
		screen->currentY += 16;
	}
}

void hola(){
	//_syscall(SYS_WRITE_ID, " Kachu puta ", 30, screen->defaultBGColour, screen->defaultFontColour, 0);
}


void printTab(){
	for (int i = 0; i < 8; i++)
	{
		write(' ');
	}
}

void printNewLine(){
	screen->currentY += 16;
	screen->currentX = 0;
}

void printBackspace(){
	screen->currentX -= 8;
	//printCharAt(0, screen->currentX+1, screen->currentY+1);
	if(screen->currentX<=screen->userLen*8){
		screen->currentX += 8;
	}else{
		printCharAt(0, screen->currentX, screen->currentY);
	}
	return;
}

void printCharAt(char c, int x0, int y0){
	uint8_t *  s = getCharMap(c);
	int h = 16;
	for (int i = 0; i < h; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			int bit = (s[i] >> j) & 1;
			if(bit == 1){
				putPixel(FOREGROUND, x0, y0);
			}else if(bit == 0){
				putPixel(BACKGROUND, x0, y0);
			}
			x0++;
		}
		y0++;
		x0 -= 8;
	}
}
