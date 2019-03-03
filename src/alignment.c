/***** alignment.c ********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Jun  1 19:36:57 2015
 **************************************************/
#include <math.h>
#include <string.h>
#include "eprintf.h"
#include "sequenceData.h"
#include "alignment.h"

/* findPoly: fills an array of positions that are polymorphic 
*     and consist solely of the four canonical nucleotides.
*/
void findPoly(Alignment *al){
  int i, j, c, p;
  int *dic;

  dic = getRestrictedDnaDictionary(NULL);
  al->poly = (long *)emalloc(al->n*sizeof(long));
  al->nuc = (long*)emalloc(al->n*sizeof(long));
  al->polyFreq = (float *)emalloc(al->n*sizeof(float));
  al->polInd = (char *)emalloc(al->n*sizeof(char));

  al->numPoly = 0;
  al->numNuc = 0;
  for(i=0;i<al->n;i++){
    p = 0;
    if(dic[(int)al->al[0][i]])
      c = 1;
    else
      continue;
    for(j=1;j<al->m;j++){
      if(!dic[(int)al->al[j][i]]){
	c = 0;
	break;
      }
      if(al->al[0][i] != al->al[j][i])
	p = 1;
    }
    if(c){
      al->nuc[al->numNuc++] = i;
      if(p){
	al->poly[al->numPoly] = i;
	al->polyFreq[al->numPoly] = 1.;
	for(j=1;j<al->m;j++)
	  if(al->al[j][i] == al->al[0][i])
	    al->polyFreq[al->numPoly]++;
	al->polyFreq[al->numPoly] /= (float)al->m;
	if(al->polyFreq[al->numPoly] > 0.5)
	  al->polyFreq[al->numPoly] = 1. - al->polyFreq[al->numPoly];
	al->numPoly++;
        al->polInd[i] = 1;
      }else
        al->polInd[i] = 0;
    }
  }
  if(al->numPoly)
    al->poly = (long *)erealloc(al->poly,al->numPoly*sizeof(long));
  if(al->numNuc)
    al->nuc = (long *)erealloc(al->nuc,al->numNuc*sizeof(long));
  if(al->numPoly)
    al->polyFreq = (float *)erealloc(al->polyFreq,al->numPoly*sizeof(float));
  free(dic);
}

Alignment *seq2al(Sequence *seq) {
  Alignment *al = (Alignment *)emalloc(sizeof(Alignment));
  al->m = seq->numSeq;
  al->headers = seq->headers;
  al->n = seq->borders[0];
  al->al = (char **)emalloc(al->m * sizeof(char *));
  int l1 = seq->borders[0];
  for(int i = 1; i < seq->numSeq; i++) {
    int l2 = seq->borders[i] - seq->borders[i-1] - 1;
    if(l2 != l1) {
      fprintf(stderr, "ERROR[dnaDist]: Entries in alignment are not of equal length: seq(%d): %d vs. seq(%d): %d.\n", 1, l1, i+1, l2);
      fprintf(stderr, "ERROR[dnaDist]: Please make sure the sequences are aligned and try again.\n");
      exit(-1);
    }
  }
  al->al[0] = seq->seq;
  for(int i = 1; i < seq->numSeq; i++)
    al->al[i] = seq->seq + seq->borders[i-1] + 1;

  al->numPoly = 0;
  al->poly = NULL;
  al->polInd = NULL;
  al->nucInd = NULL;
  al->dist = (double **)emalloc(al->m * sizeof(double *));
  al->rawDist = (double **)emalloc(al->m * sizeof(double *));
  al->oriDist = (double **)emalloc(al->m * sizeof(double *));
  for(int i = 0; i < al->m; i++){
    al->dist[i] = (double *)emalloc(al->m * sizeof(double));
    al->rawDist[i] = (double *)emalloc(al->m * sizeof(double));
    al->oriDist[i] = (double *)emalloc(al->m * sizeof(double));
  }
  return al;
}

void freeAlignment(Alignment *al){
  int i;

  free(al->al);
  if(al->poly)
    free(al->poly);
  if(al->polyFreq)
    free(al->polyFreq);
  if(al->nuc)
    free(al->nuc);
  if(al->polInd)
    free(al->polInd);
  for(i=0;i<al->m;i++) {
    free(al->dist[i]);
    free(al->rawDist[i]);
    free(al->oriDist[i]);
  }
  free(al->dist);
  free(al->rawDist);
  free(al->oriDist);
  free(al);
}

void rawDist(Alignment *al){
  int i, j, k;

  if(al->poly == NULL)
    findPoly(al);
  for(i=0;i<al->m-1;i++){
    al->rawDist[i][i] = 0.;
    for(j=i+1;j<al->m;j++){
      al->rawDist[i][j] = 0.;
      for(k=0;k<al->numPoly;k++)
	if(al->al[i][al->poly[k]] != al->al[j][al->poly[k]])
	  al->rawDist[i][j]++;
      al->rawDist[i][j] /= al->n;
      al->rawDist[j][i] = al->rawDist[i][j];
      al->oriDist[i][j] = al->rawDist[i][j];
      al->oriDist[j][i] = al->rawDist[i][j];
    }
  }
  al->rawDist[i][i] = 0;
}

void jcd(double **d, int n) {
  int i, j;

  for(i = 0; i < n-1; i++)
    for(j = i + 1; j < n; j++) {
      if(d[i][j])
        d[i][j] = -3. / 4. * log(1. - 4. / 3. * d[i][j]);
      else
        d[i][j] = 0.;
      d[j][i] = d[i][j];
    }
}

void jukesCantor(Alignment *al) {
  int i, j;

  rawDist(al);
  for(i = 0; i < al->m - 1; i++) {
    al->dist[i][i] = 0.;
    for(j = i + 1; j < al->m; j++) {
      al->dist[i][j] = al->rawDist[i][j];
      al->dist[j][i] = al->dist[i][j];
    }
  }
  al->dist[i][i] = 0.;
  jcd(al->dist, al->m);
}

void jukesCantorPairBoot(const Alignment *al, const gsl_rng *r){
  int i, j;

  for(i = 0; i < al->m; i++) {
    for(j = 0; j < al->m; j++) {
      if(i != j) {
        al->dist[i][j] = gsl_ran_binomial(r,al->oriDist[i][j],al->n) / (double)al->n;
	al->rawDist[i][j] = al->dist[i][j];
	al->rawDist[j][i] = al->dist[i][j];
      }
    }
  }
  jcd(al->dist, al->m);
}

void jukesCantorBoot(const Alignment *al, const gsl_rng *r){
  size_t i, j, k, p;

  for(i = 0; i < al->m - 1; i++)
    for(j = i + 1; j < al->m; j++)
      al->dist[i][j] = 0.;
  for(i = 0; i < al->n; i++){
    p = gsl_rng_uniform(r) * al->n;
    if(al->polInd[p])
      for(j = 0; j < al->m - 1; j++)
        for(k = j + 1; k < al->m; k++)
          if(al->al[j][p] != al->al[k][p])
            al->dist[j][k]++;
  }
  for(i = 0; i < al->m - 1; i++) {
    for(j = i + 1; j < al->m; j++) {
      al->dist[i][j] /= al->n;
      al->rawDist[i][j] = al->dist[i][j];
      al->rawDist[j][i] = al->dist[i][j];
    }
  }
  jcd(al->dist,al->m);
}
