# include "OCR.h"

int main(void)
{
  SDL_Surface          *screen;
  SDL_Surface          *img;
  Uint32 myPix = 0;
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;

  img = IMG_Load("Lorem.bmp");

  if (!img)
    errx(3, "can't load %s: %s", "lol.png", IMG_GetError());

  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) 
   {
     errx(1, "Couldn't set %dx%d video mode: %s\n",
     img->w, img->h, SDL_GetError());
   }
 
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  sleep(2);
 
  for (int i = 0; i < img->w; i++)
   {
     for (int j = 0; j < img->h; j++)
      {
         myPix = getpixel(screen, i, j);
         SDL_GetRGB(myPix, img->format, &r, &g, &b);
	 if( ( r + g + b ) / 3  < 127 )
	   putpixel(screen, i, j, SDL_MapRGB(img->format,  0 , 0 , 0 ));
			
         else 
	   putpixel(screen , i , j , SDL_MapRGB(img->format, 255 , 255 , 255));
				
     }
   }

  int white = 1;
  int cpt = 0;
  int endofline = 0;
  struct line *sheet = malloc(sizeof (struct line));
  for (int i = 0; i < img->h; i++)
   {
     sheet = realloc(sheet, sizeof(struct line));	
     for (int j = 0; j < img->w; j++)
      {
	if (white == 1)
	 {
	   myPix = getpixel(screen, j, i);
	   SDL_GetRGB(myPix, img->format, &r, &g, &b);
	   if (r == 0)
	    {
	      printf("%d\n", cpt);	
	      sheet[cpt].start = i;  
	      white = 0;
	    }
	  }
	else
	 {
	   myPix = getpixel(screen, j, i);
	   SDL_GetRGB(myPix, img->format, &r, &g, &b);
	     if (r == 0)
	      {
	        endofline = 0;
	      }
	 }
      }
     if (white == 0)
      {
        if (endofline == 0)
	  endofline = 1;

	else
	 {
	   sheet[cpt].end = i;  
	   white = 1;
	   cpt++;
	 }
      }
   }
/******************************* Affichage pour tester la segmentation *******************************************/
	int cpt3 = 0;
	while (cpt3 <= cpt)
	{
		int cpt2 = 0;
		for (int i = sheet[cpt3].start; i < sheet[cpt3].end; i++)
		{
			for (int j = 0; j < img->w; j++)
			{
				myPix = getpixel(screen, j, i);
				SDL_GetRGB(myPix, img->format, &r, &g, &b);
				putpixel(screen, j, cpt2, SDL_MapRGB(img->format,  r , g , b ));
			}
			cpt2++;
		}
  		SDL_UpdateRect(screen, 0, 0, img->w, img->h);
		sleep(1);
		cpt3++;
/*******************************************************************************************************************/
	} 
	SDL_Event	event;
  	if( SDL_Init(SDL_INIT_VIDEO)==-1 ) 
    	errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());

	for (;;) 
	{
		SDL_PollEvent( &event );
		switch (event.type) {
			case SDL_KEYDOWN: return 0;
			default: break;
		}
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(img);
}
