/***** alignment.h ********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jun  1 19:37:00 2015
 **************************************************/
#ifndef ALIGNMENT
#define ALIGNMENT

#include "sequenceData.h"
#include "gsl_rng.h"

typedef struct alignment{
  char **al;       /* nucleotide alignment */
  long m;          /* number of sequences in alignment */
  long n;          /* number of nucleotides per sequence in alignment */
  char **headers;  /* headers of sequences */
  long *poly;      /* polymorphic positions in alignment */
  long *nuc;       /* positions consisting solely of canonical nucleotides */
  char *polInd;    /* is position polymorphic? */
  char *nucInd;    /* does position consist of nucleotides only? */
  int *winNumNuc;  /* number of canonical nucleotides per window */
  int numWin;      /* the number of windows */
  float *polyFreq; /* frequency of minor allele */
  long numPoly;    /* number of polymorphic positions in alignment */
  long numNuc;     /* number of positions consisting solely of canonical nucleotides */
  double **dist;   /* distance matrix */
  double **rawDist;  /* raw distances */
  double **oriDist;  /* original raw distances */
}Alignment;

void freeAlignment(Alignment *al);
void jukesCantor(Alignment *al);
void jukesCantorBoot(const Alignment *al, const gsl_rng *r);
void jukesCantorPairBoot(const Alignment *al, const gsl_rng *r);
Alignment *seq2al(Sequence *seq);

#endif
