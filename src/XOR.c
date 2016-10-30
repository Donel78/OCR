#include <stdio.h>
#include <stdlib.h>


int tab[3][4];
int x = 1;
int y = 0;
float h = 0.5;
float z = 0.5;
int bh , bz = 1;
float nPoids[7][7];


/********************* Initialisation avant l'algorythme backprop ***********************/
int main()
{

tab[0][0] = 0;
tab[0][1] = 0;
tab[0][2] = 0;

tab[1][0] = 1;
tab[1][1] = 0;
tab[1][2] = 1;

tab[2][0] = 0;
tab[2][1] = 1;
tab[2][2] = 1;

tab[3][0] = 1;
tab[3][1] = 1;
tab[3][2] = 0;

for(int i = 0 ; i < 7 ; i++)
{
  for(int j = 0 ; j < 7 ; j++)
    {
      nPoids[i][j] = 0;
    }
}

}


int main()
{


}
/**********************************************************************************************/
