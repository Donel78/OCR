# include "OCR.h"


void DetectLine(SDL_Surface *img ,struct line *sheet, int *cpt)
{


  int white = 1;
  int endofline = 0;
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















}

