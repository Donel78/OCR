# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <unistd.h>
# include <SDL.h>
# include <err.h>
# include "SDL/SDL_image.h"

struct line
{
	int start;
	int end;
	int letter[200];
};
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
//void DetectLine(SDL_Surface *surface,struct line *sheet); 
# endif
