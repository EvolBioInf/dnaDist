/***** dnaDist.c ************************************************************
 * Description: Compute distances between DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Mar 2 11:37:31 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "gsl_rng.h"
#include "sequenceData.h"
#include "alignment.h"
#include "distance.h"
#include "interface.h"
#include "eprintf.h"

void scanFile(Args *args, int fd) {
  Sequence *seq = readFasta(fd);
  Alignment *al = seq2al(seq);
  jukesCantor(al);
  if(args->b || args->p) {
    gsl_rng *r = ini_gsl_rng(args);
    for(int i = 0; i < args->b; i++){
      jukesCantorBoot(al, r);
      printDist(al, args);
    }
    for(int i = 0; i < args->p; i++){
      jukesCantorPairBoot(al, r);
      printDist(al, args);
    }
    gsl_rng_free(r);
  } else {
    printDist(al, args);
  }
  freeSequence(seq);
  freeAlignment(al);
}

int main(int argc, char *argv[]) {
  Args *args = getArgs(argc, argv);

  setprogname2(argv[0]);
  if(args->v)
    printSplash(args);
  if(args->h || args->err)
    printUsage();
  if(args->nf == 0) {
    scanFile(args, 0);
  } else {
    for(int i = 0; i < args->nf; i++) {
      int fd = open(args->fi[i],O_RDONLY,0);
      if(fd < 0) {
	fprintf(stderr, "ERROR[dnaDist]: Could not open file %s\n", args->fi[i]);
	exit(-1);
      }
      scanFile(args, fd);
      close(fd);
    }
  }
  freeArgs(args);
  free(progname());
  return 0;
}

