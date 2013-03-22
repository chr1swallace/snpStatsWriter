#include <stdio.h>
#include <string.h>

/* Chris Wallace <chris.wallace@cimr.cam.ac.uk> */
/* GPL */

/* 2.1 Beagle file format */
/*   Beagle input files have a simple format: rows are variables and columns are individuals. */
/* Here is an example of a Beagle file with three individuals and three genotyped markers: */
/* Example 1 - Sample Beagle file */
/* I       id            1001   1001    1002    1002    1003    1003 */
/* A       diabetes      1      1       2       2       2       2 */
/* M       rs2289311     A      G       G       G       A       G */
/* M       rs1248628     T      T       T       C       T       T */
/* M       rs10762764    G      T       T       T       G       T */

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


void write_beagle(char *x, char **a1, char **a2, int *bp, int *trait,
		  char **gfile, char **mfile, int *N, int *M, int *Ntrait,
		  char **rnames, char **cnames, int *iferror) {
  int nrow = *N;
  int ncol = *M;
  int ntrait = *Ntrait;
  char *sep = " ";
  char *eol = "\n";
  char *na = "??";
  int i=0, j=0, ij=0;
  FILE * outfile_geno;
  FILE * outfile_markers;
  outfile_geno = fopen(*gfile, "w");
  if (!outfile_geno) {
    *iferror = 1;
    return;
  }
  outfile_markers = fopen(*mfile, "w");
  if (!outfile_markers) {
    *iferror = 1;
    return;
  }

  // markers file
  for(j=0; j<ncol; j++) {
    fprintf(outfile_markers,"%s %d %s %s\n",cnames[j],bp[j],a1[j],a2[j]);
  }

  char astr[4]; // to hold current allele string

  // header
  fprintf(outfile_geno,"I id" );
  for(i=0; i<nrow; i++) {
    fputs(sep,outfile_geno);
    fputs(rnames[i],outfile_geno);
    fputs(sep,outfile_geno);
    fputs(rnames[i],outfile_geno);
  }
  fputs(eol,outfile_geno);

  // trait?
  if(ntrait>0) {
    fprintf(outfile_geno,"A trait" );
    for(i=0; i<nrow; i++) {
      fprintf(outfile_geno," %d %d",trait[i],trait[i]);
    }
    fputs(eol,outfile_geno);
  }

// each line has format M rs A1 A2 A1 A2
  for(j=0; j<ncol; j++) {
    fprintf(outfile_geno,"M %s",cnames[j]);
/*     fputs("SNP", outfile_geno); */
/*     fputs(j, outfile_geno); */
/*     fputs(sep,outfile_geno); */
/*     fputs(rnames[i], outfile_geno); */
/*     fputs(" 1 0 0 M",outfile_geno); */
    for (i=0; i<nrow; i++) {
       fputs(sep,outfile_geno);
       allelestring(a1[j], a2[j], (int) x[ij++], astr);
       fputs(astr,outfile_geno);
    }
    fputs(eol,outfile_geno);
  }

  fclose(outfile_geno);
  fclose(outfile_markers);
  *iferror = 0;
  return;
}

