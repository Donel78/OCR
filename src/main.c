# include "OCR.h"
# include <stdio.h>
# include <gtk/gtk.h>
# include <stdlib.h>

#define UNUSED(x) (void)(x)

/*********************** Loading Image *****************************/
void loading_image_clicked(GtkWidget *button, gpointer data);

/*********************** Display segmentation **********************/
void segmentation_clicked(GtkWidget *button, gpointer data);

SDL_Surface *img;
SDL_Surface *screen;
int cpt = 0;
struct line *sheet;
Uint8 r = 0;
Uint8 b = 0;
Uint8 g = 0;
Uint32 myPix = 0;


int main(int argc, char* argv[])
{
  
  GtkWidget *pWindow;
  GtkWidget *pVBox;
  GtkWidget *pHBox;
  GtkWidget *pButton[2];
  gtk_init(&argc, &argv);
  
sheet = malloc(sizeof (struct line));
  //struct block *block = malloc(sizeof (struct block));
  
  /* Initialisation window  */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "OCR");
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 1400, 1400);
  pVBox = gtk_box_new(TRUE, 0);
  gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

  /* Initialistion button  */
  pButton[1] = gtk_button_new_with_label("Charger une image");
  pButton[2] = gtk_button_new_with_label("Segmenter une image");
  
  gtk_box_pack_start(GTK_BOX(pVBox), pButton[1], TRUE, FALSE, 0);
  pHBox = gtk_box_new(TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pHBox), pButton[2], TRUE, FALSE, 0);
  
  /* Events Clicked  */
  g_signal_connect(G_OBJECT(pButton[1]), "button-press-event", G_CALLBACK(loading_image_clicked), NULL);
  g_signal_connect(G_OBJECT(pButton[2]), "button-press-event", G_CALLBACK(segmentation_clicked), NULL);

  gtk_widget_show_all(pWindow);
  gtk_main();

/* 
for (int i = 0; i < cpt; i++)
  for (int j = 0; sheet[i].letter[j] != '\0'; j = j + 2)
    Matrice (screen, img, sheet, i, j);
*/
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


/*********************** Display segmentation **********************/
void segmentation_clicked(GtkWidget *button, gpointer data)
{
  UNUSED(button);
  UNUSED(data);
  
  img = IMG_Load("Lorem.bmp");
  sheet = DetectLine(screen, img, sheet, &cpt);
  sheet = DetectChar(screen ,img, sheet, &cpt);
  affiche_seg(img, screen, sheet ,&cpt);
  
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

}

/*********************** Loading Image *****************************/
void loading_image_clicked(GtkWidget *button, gpointer data)
{
  UNUSED(button);
  UNUSED(data);

  img = IMG_Load("Lorem.bmp");
}
