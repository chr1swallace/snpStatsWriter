#include <stdio.h>
#include <string.h>

void numstring(int idx, char *astr) {
  astr[0] = '4';
  astr[1] = '\0';
  switch(idx) {
  case 1 :
    astr[0] = '1';
    break;
  case 2 :
    astr[0] = '2';
    break;
  case 3 :
    astr[0] = '3';
    break;
  default:
    break;
  }
}

void allelestring(char *A1, char *A2, int idx, char *sep, char *nullallele, char *astr) {
  //  printf("alleles %s, %s, index %s\n",*A1,*A2,*idx);
  char def[4];
  def[0]=*nullallele;
  int a1_index=0;
  int a2_index;
  if(strlen(sep)>0) {
    a2_index=2;
    def[1]=*sep;
    def[2]=*nullallele;
    def[3]='\0';
  } else {
    a2_index=1;
    def[1]=*nullallele;
    def[2]='\0';
  }
  strcpy(astr,def);
  switch(idx) {
  case 1 :
    astr[a1_index] = *A1;
    astr[a2_index] = *A1;
    break;
  case 2 :
    astr[a1_index] = *A1;
    astr[a2_index] = *A2;
    break;
  case 3 :
    astr[a1_index] = *A2;
    astr[a2_index] = *A2;
    break;
  default:
    break;
  }
}

void write_simple(char *x, char **a1, char **a2, int *bp, int *dobp,
		      char **fsep, char **gsep,
		  int *num_coding, // use 1,2,3,4 (4=missing) for alleles, otherwise use letters given in a1, a2
		  char **nullallele, // value for missing alleles
		  int *transpose, // write one snp per line, instead of one sample per line
		      char **file, int *N, int *M,
		      char **rnames, char **cnames, int *iferror) {
  int nrow = *N;
  int ncol = *M;
  char *eol = "\n";
  char *na = "??";
  int i=0, j=0, ij=0;
  FILE * outfile;
  outfile = fopen(*file, "a");
  if (!outfile) {
    *iferror = 1;
    return;
  }

  char astr[4]; // to hold current allele string

  if(*transpose==1) {
    // format snp a1 a2 a1 a2 etc
    for(j=0; j<ncol; j++) {
      fputs(cnames[j],outfile);
      if(*dobp==1) {
	//	fputs(fsep[0],outfile);
	fprintf(outfile,"%s%d",fsep[0],bp[j]);
      }
      for(i=0, ij=j*nrow; i<nrow; i++, ij++) {
	fputs(fsep[0],outfile);
	if(*num_coding==1) {
	  numstring( (int) x[ij], astr);
	} else {
	  allelestring(a1[j], a2[j], (int) x[ij], gsep[0], nullallele[0], astr);
	}
	fputs(astr,outfile);
      }
      fputs(eol,outfile);
    }
  } else {
    // each line has format id a1 a2 a1 a2 etc
    for(i=0; i<nrow; i++) {
      fputs(rnames[i], outfile);
      //    fputs(" 1 0 0 M",outfile);
      for(j=0, ij=i; j<ncol; j++, ij+=nrow) {
	fputs(fsep[0],outfile);
	if(*num_coding==1) {
	  numstring( (int) x[ij], astr);
	} else {
	  allelestring(a1[j], a2[j], (int) x[ij], gsep[0], nullallele[0], astr);
	}
	fputs(astr,outfile);
      }
      fputs(eol,outfile);
    }
  }
  fclose(outfile);
  *iferror = 0;
  return;
}

