#include <stdio.h>
#include <string.h>

void allelestring(char *A1, char *A2, int idx, char *astr) {
  //  printf("alleles %s, %s, index %s\n",*A1,*A2,*idx);
  char def[] = "? ?";
  strcpy(astr,def);
  switch(idx) {
  case 1 :
    astr[0] = *A1;
    astr[2] = *A1;
    break;
  case 2 :
    astr[0] = *A1;
    astr[2] = *A2;
    break;
  case 3 :
    astr[0] = *A2;
    astr[2] = *A2;
    break;
  default:
    break;
  }
}

void write_mach(char *x, char **a1, char **a2, char **file, int *N, int *M,
		   char **rnames, char **cnames, int *iferror) {
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

  char astr[4]; // to hold current allele string

// each line has format fam 1 0 0 sex a1 a2 a1 a2 etc
  for(i=0; i<nrow; i++) {
    fputs(rnames[i], outfile);
    fputs(" 1 0 0 M",outfile);
    for (j=0, ij=i; j<ncol; j++, ij+=nrow) {
       fputs(sep,outfile);
       allelestring(a1[j], a2[j], (int) x[ij], astr);
       fputs(astr,outfile);
    }
    fputs(eol,outfile);
  }

  fclose(outfile);
  *iferror = 0;
  return;
}

