#include <stdint.h>
#include <videoDriver.h>
#include <fonts.h>

struct vbe_mode_info_structure {
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
} __attribute__ ((packed));

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
    int defaultBGColour;
    int defaultFontColour;
    uint32_t currentX;
    uint32_t currentY;
    uint32_t offset;
    uint32_t width;
    uint32_t height;
   // uint32_t firstLine;
    //uint32_t firstLineWidth;
} t_screen;

t_screen * screen;

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y){
    uint8_t *framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset] = (hexColor) & 0xFF; //AZUL
    framebuffer[offset+1] = (hexColor>>8) & 0xFF ; //VERDE
    framebuffer[offset+2] = (hexColor>>16) & 0xFF; // ROJO
}

void load_video(){

    screen->defaultBGColour = DEFAULT_BG_COLOUR;
    screen->defaultFontColour = DEFAULT_FONT_COLOUR;
    screen->currentX = 0;
    screen->offset=0;
    screen->currentY = 0;
	screen->width = WIDTH;
    screen->height = HEIGHT;
	paint(DEFAULT_BG_COLOUR);
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


void newLine(){
	/*  if(screen->height-screen->currentY <=CHAR_HEIGHT){
            screen->currentY -=CHAR_HEIGHT;
        }else{
            screen->currentY+=CHAR_HEIGHT;
            
        } */
	screen->currentY+=CHAR_HEIGHT;
    screen->currentX=0; 
}




void deleteChar(){
    if(screen->currentX<=USER_LENGHT*CHAR_WIDTH && lineCounter==0){
      return;  
    } 
    if(screen->currentX==0){
        if(screen->currentY==0 ){
            return;
        }
    screen->currentY-=CHAR_HEIGHT;
    lineCounter--;
       screen->currentX=screen->width-(2*CHAR_WIDTH);
    }
    screen->currentX-=CHAR_WIDTH;
    putChar(' ',BACKGROUND,BACKGROUND,0);
}


void putChar(char c, colorscheme fontColor, colorscheme bgColor, int next){
	char *map = getCharMap(c);
    
    uint32_t x = screen->currentX+screen->offset;
    uint32_t y = screen->currentY;
  
    
    if(x+(2*CHAR_WIDTH)-screen->offset >= screen->width){ 
    
        y+=CHAR_HEIGHT;
        lineCounter++;
        newLine();
        
    }
    if(c=='\n'){
        lineCounter=0;
        newLine();
        return ;
    }
    if(c=='\b'){
        deleteChar();
        return ;
    }

    for(int i=0;i<CHAR_HEIGHT;i++){
        for(int j=0;j<CHAR_WIDTH;j++){
            int8_t isFont = (map[i] >> (CHAR_WIDTH - j - 1)) & 0x01;  //-1 para no romper el decalaje, primera vez tengo q decalar 7
            if (isFont) {
                putPixel(x, y, fontColor);
            } else {
                putPixel(x, y, bgColor);
            }
            x++;
        }
        x=screen->currentX+screen->offset;
        y++;
    }
    
    if(next){
        screen->currentX+=CHAR_WIDTH;
    }
}