/***** interface.h **********************************************************
 * Description: Distances between DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Mar  2 11:37:31 2019
 ****************************************************************************/
#ifndef INTERFACE
#define INTERFACE

/* define argument container */
typedef struct args{
  char    h; /* help message?         */
  char    v; /* version message?      */
  char    r; /* raw dinstances?       */
  char  err; /* error                 */
  int     b; /* bootstrap replicates  */
  int     p; /* pairwise bootstrap re */
  int     s; /* seed for random num   */
  char **fi; /* input files           */
  int    nf; /* number of input files */
} Args;

Args *getArgs(int argc, char *argv[]);
Args *newArgs();
void freeArgs(Args *args);
void printUsage();
void printSplash(Args *args);

#endif
