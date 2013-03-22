#include <stdio.h>
#include <string.h>

void allelestring(int idx, char *astr) {
  //  printf("alleles %s, %s, index %s\n",*A1,*A2,*idx);
  switch(idx) {
  case 1 :
    strcpy(astr,"1 0 0");
    break;
  case 2 :
    strcpy(astr,"0 1 0");
    break;
  case 3 :
    strcpy(astr,"0 0 1");
    break;
  default:
    strcpy(astr,"0 0 0");
    break;
  }
}

void write_impute(char *x, char **a1, char **a2, int *bp, char **file, int *N, int *M,
		  char **rnames, char **cnames, char **snpid, int *iferror) {
  int nrow = *N;
  int ncol = *M;
  char *sep = " ";
  char *eol = "\n";
  char *na = "??";
  int i=0, j=0, ij=0;
  FILE * outfile;
  outfile = fopen(*file, "w");
  if (!outfile) {
    *iferror = 1;
    return;
  }

  char astr[6]; // to hold current allele string

// each line has format SNPj rs bp A1 A2 p11 p12 p22 p11 p12 p22 etc
  ij=0;
  for(j=0; j<ncol; j++) {
    fprintf(outfile,"%s %s %d %s %s",snpid[j],cnames[j],bp[j],a1[j],a2[j]);
    for (i=0; i<nrow; i++) {
       fputs(sep,outfile);
       allelestring((int) x[ij++], astr);
       fputs(astr,outfile);
    }
    fputs(eol,outfile);
  }

  fclose(outfile);
  *iferror = 0;
  return;
}

