#include <stdlib.h>
#include <stdio.h>
#include "Chaine.h"
#include <string.h>

int main(int argc, char* argv[])
{
	
	if(argc!=3)
	{
	fprintf(stderr,"\nPb arguments! \n\n");
	exit(1);
	}

	char *nomfic_1, *nomfic_2;

	nomfic_1 = strdup(argv[1]);
	nomfic_2 = strdup(argv[2]);

	FILE *f, *g;

	f = fopen(nomfic_1,"r");
	Chaines* C;	

	if(f!=NULL){
		C=lectureChaine(f);
		fclose(f);
	}

	g = fopen(nomfic_2,"w");

	if(f!=NULL){
		ecrireChaineTxt(C, f);
		fclose(g);
	}
	
	

	return 0;

}