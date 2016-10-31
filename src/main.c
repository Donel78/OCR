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
/******************************  Line Detections ***************************/
  struct line *sheet = malloc(sizeof (struct line));
  for (int i = 0; i < img->h; i++)
   {
     sheet = realloc(sheet, (cpt + 1) * sizeof(struct line));	
     for (int j = 0; j < img->w; j++)
      {
	if (white == 1)
	 {
	   myPix = getpixel(screen, j, i);
	   SDL_GetRGB(myPix, img->format, &r, &g, &b);
	   if (r == 0)
	    {
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
/************************************************************************/

  int cptline = 0;
  int cptletter = 0;
/*********************** Char Detections *******************************/
  while (cptline < cpt)
  { 	
  	  white = 1;
 	  endofline = 0;
	  for (int i = 0; i < img->w; i++)
	  {
	  	  for (int j = sheet[cptline].start; j < sheet[cptline].end; j++)
		  {
			  if (white == 1)
			  {
				  myPix = getpixel(screen, i, j);
				  SDL_GetRGB(myPix, img->format, &r, &g, &b);
				  if (r == 0)
				  {

					  sheet[cptline].letter[cptletter] = i;   
					  cptletter++;
					  white = 0;
				  }
			  }
			  else
			  {
				  myPix = getpixel(screen, i, j);
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
				  sheet[cptline].letter[cptletter] = i;  
				  white = 1;
				  cptletter++;
			  }
		  }
	  }
	sheet[cptline].letter[cptletter] = '\0';  
	cptletter = 0;
	cptline++;
  }
/************************************************************************************************/
/*************************** Affichage pour tester la segmentation *******************************/
  int cpt3 = 0;
  while (cpt3 < cpt)
  {	
	  for (int j = 0; j < img->w; j++)
	  {		
		  putpixel(screen, j ,sheet[cpt3].start , SDL_MapRGB(img->format,  0 , 0 , 255 ));
		  putpixel(screen , j , sheet[cpt3].end , SDL_MapRGB(img->format, 0 ,0 , 255));
	  }
	  cpt3++;
	  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  }	

  int cpt4 = 0;
  int h = 0;
  while (cpt4 < cpt)
  {
	while ((sheet[cpt4].letter[h] != '\0'))
	{	
	  for (int j = sheet[cpt4].start; j < sheet[cpt4].end; j++)
	  {			
		  putpixel(screen, sheet[cpt4].letter[h], j,SDL_MapRGB(img->format,  255 , 0 , 0));
		  putpixel(screen,  sheet[cpt4].letter[h + 1], j, SDL_MapRGB(img->format,  255 , 0 , 0));
	  }
	  h++;
	}
	h = 0;
	cpt4++;
	 SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  }



/************************************************************************************************/

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
	free(sheet);
}
