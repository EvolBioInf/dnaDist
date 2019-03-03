/***** interface.c **********************************************************
 * Description: Distances between DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Mar  2 11:37:31 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "eprintf.h"

Args *newArgs() {
  Args *args = (Args *)emalloc(sizeof(Args));
  args->h   = 0;
  args->v   = 0;
  args->err = 0;
  args->b   = 0;
  args->p   = 0;
  args->r   = 0;
  args->s   = 0;
  return args;
}

void freeArgs(Args *args) {
  free(args);
}

Args *getArgs(int argc, char *argv[]) {
  int c;
  char *optString = "hvrb:p:s:";
  Args *args = newArgs();

  while ((c = getopt(argc, argv, optString)) != -1) {
    switch(c) {
    case 'b': /* bootstrap replicates */
      args->b = atoi(optarg);
      break;
    case 'p': /* pairwise bootstrap replicates */
      args->p = atoi(optarg);
      break;
    case 's': /* seed for random number generator */
      args->s = atoi(optarg);
      break;
    case 'r': /* raw distances */
      args->r = 1;
      break;
    case 'h': /* help       */
      args->h = 1;
      break;
    case 'v': /* version    */
      args->v = 1;
      break;
    case '?':
      args->err = 1;
      if(optopt == 'i')
	fprintf(stderr, "Error: Option `%c` requires an argument.\n", optopt);
      else if(isprint(optopt))
	fprintf(stderr, "Error: Unknown option `%c`.\n", optopt);
      else
	fprintf(stderr, "Error: Unknown option character `\\x%x`.\n", optopt);
    default:
      args->err = 1;
      return args;
    }
  }
  args->fi = argv + optind;
  args->nf = argc - optind;

  return args;
}

void printUsage() {
  printf("Usage: %s [options] [inputFiles]\n", progname());
  printf("Jukes-Cantor distances between DNA sequences\n");
  printf("Example: %s -b 10000 alignment.fasta\n", progname());
  printf("Options:\n");
  printf("\t[-b <NUM> bootstrap replicates; default: no bootstrap]\n");
  printf("\t[-p <NUM> pairwise bootstrap replicates; default: no pairwise bootstrap]\n");
  printf("\t[-s <NUM> seed for random number generator; default: system]\n");
  printf("\t[-r raw distances; default: Jukes-Cantor]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print version & program information and exit]\n");
  exit(0);
}

void printSplash(Args *args) {
  printf("%s ", progname());
  int l = strlen(VERSION);
  for(int i = 0; i < l - 1; i++)
    printf("%c", VERSION[i]);
  printf(", %s\n", DATE);
  printf("Author: Bernhard Haubold\n");
  printf("License: GNU General Public License, https://www.gnu.org/licenses/gpl.html\n");
  printf("Bugs: haubold@evolbio.mpg.de\n");
  exit(0);
}
