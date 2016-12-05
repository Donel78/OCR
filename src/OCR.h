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

struct block
{
  int point;
  int height;
  int weight;

};
;
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

struct line* DetectLine(SDL_Surface *screen, SDL_Surface *surface,
                        struct line *sheet,int *cpt);

struct line* DetectChar(SDL_Surface *screen, SDL_Surface *surface,
                        struct line *sheet, int *cpt);

/*struct block* DetectBlock(SDL_Surface *screen, SDL_Surface *img,
                          struct block *block, int *cptblock);*/

void affiche_seg(SDL_Surface *surface, SDL_Surface *surface2,
                 struct line *sheet, int *cpt);

void Matrice(SDL_Surface *surface,SDL_Surface *img, struct line *sheet,
             int line, int letter);

# endif
