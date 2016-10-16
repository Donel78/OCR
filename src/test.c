#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

Uint32 getpixel(SDL_Surface *image , int x , int y);

int main(int argc, char *argv[])

{

int continuer = 1;

SDL_Event event;
SDL_Surface *ecran = NULL , *ecran2 = NULL;
SDL_Rect position;

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    ecran = SDL_SetVideoMode(1500, 1500, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    ecran2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    SDL_WM_SetCaption("OCR" , NULL);
    //SDL_FillRect(ecran2, NULL, SDL_MapRGB(ecran->format, 17, 255, 255));
    ecran2 = SDL_LoadBMP("image.bmp");
    SDL_BlitSurface(ecran2, NULL, ecran, &position);
    SDL_Flip(ecran);
	
printf(" %d ",getpixel(ecran2 , 0 , 0));


    while( continuer )
    {
    SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
			continuer = 0;
			break;

        }
    }
    SDL_FreeSurface(ecran2);
    SDL_Quit(); // Arrêt );de la SDL

    return EXIT_SUCCESS; // Fermeture du programme

}


Uint32 getpixel(SDL_Surface *image , int x , int y)
{

	int bpp = image->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;
	switch(bpp){
	case 1 :
		return *p;
		break;
	case 2 :
		return *(Uint16 *)p;
		break;
	case 3 :
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 << p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2];
		break;
	case 4 :
		return *(Uint32 *)p;
		break;
	default : 
		return 0;
	}





}



