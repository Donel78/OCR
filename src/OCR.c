# include "OCR.h"
 
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}
/*
struct block *DetectBlock(SDL_Surface *screen, SDL_Surface *img,
                          struct block *block,int *cptblock)
{
  int endofblock = 0;
  int white = 1;
  int blanck = 0;
  Uint8 r = 0;
  Uint8 b = 0;
  Uint8 g = 0;
  Uint32 myPix = 0;

  for (int i = 0; i < img->h; i++)
  {
    block = realloc(block, (*cptblock + 1) * sizeof (struct block));
    for (int j = 0; j < img->w; j++)
    { 
      if (white == 1)
      {
        myPix = getpixel(screen,j ,i);
        SDL_GetRGB(myPix, img->format, &r, &g, &b);
          if (r == 0)
          {
            block.point = i;
            white = 0;
          }  
      }
      else
      {
        myPix = getpixel(screen, j, i);
        SDL_GetRGB(myPix img->format, &r, &g, &b)
        if (r == 0)
        {
          endofblock = 0;
        }
      }
     if (white == 0)
     {
       if (endofblock == 0)
         endofblock = 1;
     }
     else
     {
        block[*cptblock].weight = i;
        block[*cptblock].height = j;
        white = 1;
        (*cptblock)++;
        printf("%d\n",*cptblock);
     }
   
    }
  }
  return block;

}
*/
struct line *DetectLine(SDL_Surface *screen, SDL_Surface *img,
                        struct line *sheet,int *cpt)
{
  int endofline = 0;
  int white = 1;
  Uint8 r = 0;
  Uint8 b = 0;
  Uint8 g = 0;
  Uint32 myPix = 0;

  for (int i = 0; i < img->h; i++)
   {
     sheet = realloc(sheet, (*cpt + 1) * sizeof(struct line));	
     for (int j = 0; j < img->w; j++)
      {
	if (white == 1)
	 {
	 myPix = getpixel(screen, j, i);
	 SDL_GetRGB(myPix, img->format, &r, &g, &b);
	   if (r == 0)    {
	      sheet[*cpt].start = i;
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
	   sheet[*cpt].end = i;
	   white = 1;
	   (*cpt)++;
	 }
      }
   }
  return sheet;
}
struct line* DetectChar(SDL_Surface *screen ,SDL_Surface *img,
                        struct line *sheet,int *cpt)
{
 int white = 0;
 int endofline = 0;
  Uint8 r = 0;
  Uint8 b = 0;
  Uint8 g = 0;
  Uint32 myPix = 0;
  int cptline = 0;
  int cptletter = 0;

  while (cptline < *cpt)
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
  return sheet;
}  

void affiche_seg(SDL_Surface *img, SDL_Surface *screen, struct line *sheet,
                 int *cpt)
{
  int cpt3 = 0;
  int cpt4 = 0;
  int h = 0;

  while (cpt3 < *cpt)
  {	
	  for (int j = 0; j < img->w; j++)
	  {		
		  putpixel(screen, j ,sheet[cpt3].start , SDL_MapRGB(img->format,
                                                         0 , 0 , 255 ));
		  putpixel(screen , j , sheet[cpt3].end , SDL_MapRGB(img->format,
                                                         0 ,0 , 255));
	  }
	  cpt3++;
	  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  }	

  while (cpt4 < *cpt)
  {
	while ((sheet[cpt4].letter[h] != '\0'))
	{	
	  for (int j = sheet[cpt4].start; j < sheet[cpt4].end; j++)
	  {			
		  putpixel(screen, sheet[cpt4].letter[h], j,SDL_MapRGB(img->format,
                                                           255 , 0 , 0));
		  putpixel(screen,  sheet[cpt4].letter[h + 1], j, SDL_MapRGB(img->format,
                                                                 255 , 0 , 0));
	  }
	  h++;
	}
	h = 0;
	cpt4++;
 
	 SDL_UpdateRect(screen, 0, 0, img->w, img->h);
}

}


void Matrice(SDL_Surface *screen, SDL_Surface *img, struct line *sheet,
             int line, int letter)
{
  Uint8 r = 0;
  Uint8 b = 0;
  Uint8 g = 0;
  Uint32 myPix = 0;

  int l = sheet[line].end - sheet[line].start;
  int c = sheet[line].letter[letter + 1] - sheet[line].letter[letter];
  int mat[l][c];
  for (int i = 0; i < l; i++)
  {
    for(int j = 0; j < c; j++)
    {
          myPix = getpixel(screen,sheet[line].letter[letter] + j,
                           sheet[line].start + i);

				  SDL_GetRGB(myPix, img->format, &r, &g, &b);
          printf("%d\n",r);
				  if (g == 0)
          {
           mat[i][j] = 1; 
          }
          else
          {
           mat[i][j] = 0; 
          }
    }

  }
for (int i = 0; i < l; i++)
{
  for (int j = 0; j < c; j++)
  {
  printf("%d",mat[i][j]);
  }
  puts("");
}
 sleep(1);
}


