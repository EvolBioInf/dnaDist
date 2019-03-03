/***** distance.c *********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jun  1 16:52:42 2015
 **************************************************/
#include <string.h>
#include "eprintf.h"
#include "alignment.h"

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
    if(args->r)
      printf("%.6f", al->rawDist[i][0]);
    else
      printf("%.6f", al->dist[i][0]);
    for(int j = 1; j < al->m; j++) {
      if(args->r)
	printf(" %.6f", al->rawDist[i][j]);
      else
	printf(" %.6f", al->dist[i][j]);
    }
    printf("\n");
  }
}
