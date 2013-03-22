#include <stdio.h>


void write_phase(char *x, char **a1, char **a2, char **file, int *N, int *M,
		   char **rnames, char **cnames, int *iferror) {
  int nrow = *N;
  int ncol = *M;
  char *sep = ", ";
  char *eol = "\n";
  char *na = "??";
  char Nch[8];
  int i=0, j=0, ij=0;
  FILE * outfile;
  outfile = fopen(*file, "w");
  if (!outfile) {
    *iferror = 1;
    return;
  }

  // first line - number of samples
  int kk = sprintf(Nch,"%d",*N);
  fputs(Nch,outfile);
  fputs(eol,outfile);

  // second line - number of snps
  kk = sprintf(Nch,"%d",*M);
  fputs(Nch,outfile);
  fputs(eol,outfile);

  // third line - sample ids
  fputs("IND",outfile);
  for(i=0; i<nrow; i++) {
    fputs(sep,outfile);
    fputs(rnames[i], outfile);
  }
  fputs(eol,outfile);

  // 1 line per snp
  for(j=0; j<ncol; j++) {
    char alleles[4][3] = { {'?','?','\0'},
			   {a1[j][0],a1[j][0],'\0'},
			   {a1[j][0],a2[j][0],'\0'},
			   {a2[j][0],a2[j][0],'\0'} };
    fputs(cnames[j],outfile);
    for(i=0; i<nrow; i++) {
      int idx = (int) x[ij++];
      fputs(sep,outfile);
      fputs(alleles[idx],outfile);
    }
    fputs(eol,outfile);
  }
  //  fputs(eol, outfile);
  fclose(outfile);
  //  *iferror = 0;
  return;
}

