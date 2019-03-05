/***** distance.c *********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jun  1 16:52:42 2015
 **************************************************/
#include <string.h>
#include <math.h>
#include "eprintf.h"
#include "alignment.h"

/* int round(double x) { */
/*   if(x - (int)x < 0.5) */
/*     return (int)x; */
/*   else */
/*     return (int)(x + 1); */
/* } */

void printDist(Alignment *al, Args *args) {
  printf("%d\n", (int)al->m);
  for(int i = 0; i < al->m; i++){
    int l = strlen(al->headers[i]) - 1;
    l = l < 10 ? l : 9;
    for(int j = 0; j < l; j++) {
      printf("%c", al->headers[i][j+1]);
    }
    for(int j = l; j < 10; j++)
      printf(" ");
    if(args->r == 1)
      printf("%.6f", al->rawDist[i][0]);
    else if(args->r == 2)
      printf("%.0f", round(al->rawDist[i][0] * al->n));
    else
      printf("%.6f", al->dist[i][0]);
    for(int j = 1; j < al->m; j++) {
      if(args->r == 1)
	printf(" %.6f", al->rawDist[i][j]);
      else if(args->r == 2)
	printf(" %.0f", round(al->rawDist[i][j] * al->n));
      else
	printf(" %.6f", al->dist[i][j]);
    }
    printf("\n");
  }
}
