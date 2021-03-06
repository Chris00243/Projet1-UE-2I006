#include <stdlib.h>
#include <stdio.h>
#include "Reseau.h"

unsigned static int NUM = 1;

/********** FONCTIONS Noeud *************************************/

Noeud* initialiser_Noeud(double x, double y)
{

	Noeud* N = (Noeud*)malloc(sizeof(Noeud));

	if(N==NULL)return NULL;

	N->num=NUM;
	NUM++;

	N->x=x;
	N->y=y;

	N->voisins = initialiser_CellNoeud();
	if(n->voisins==NULL) return NULL;	
		
	return n;
}

/******* FONCTIONS CellNoeud ******************************************/

CellNoeud* initialiser_CellNoeud()
{
	CellNoeud *CN = (CellNoeud*)malloc(sizeof(CellNoeud));
	
	if(CN==NULL) return NULL;

	CN->nd = NULL;
	CN->suiv = NULL;
	return CN;
}

CellNoeud* creer_cellNoeud(Noeud *N)
{
	CellNoeud *CN = initialiser_cellNoeud();
	Cn->nd = N;
	return CN;
}

/* compte le nombre des voisins d'un noeud */
int compteNbVoisins(CellNoeud *CN)
{
	if(CN->nd== NULL) return 0;
	
	return 1 + compteNbVoisins(CN->suiv)+compteNbVoisins(CN->nd->voisins);

}


/******* FONCTIONS COMMODITES ******************************************/

CellCommodite* initialiser_CellCommodite(Noeud* N1, Noeud* N2)
{

	CellCommodite* cc = (CellCommodite*)malloc(sizeof(CellCommodite));

	if(cc==NULL)return NULL;

	cc->extrA=N1;
	cc->extrB=N2;
	cc->suiv=NULL;
			
	return cc;
}

/******* FONCTIONS Reseau ******************************************/

Reseau* initialiser_Reseau(int gamma, int num)
{
	Reseau* r = (Reseau*)malloc(sizeof(Reseau));

	if(r==NULL)return NULL;

	r->nbNoeuds = num;
	r->gamma = gamma;
	r->noeuds = NULL;
	r->commodites = NULL;

	return r;
}

/************* ins�rer un Noeud dans un CellNoeud ************/
/* Cette fonction sera utilis�e pour ajouter les noeuds voisins d'un noeud X. Il suffira donc de passer le X->voisins et les coordon�es x, y du noeud � ins�rer */

CellNoeud* inserer_CN_N(CellNoeud* CN, double x, double y)
{
	CellNoeud *B = NULL;

	if(CN->nd==NULL){

		B = creer_CellNoeud( initialiser_Noeud(x,y) );
		CN->nd=B;
		return CN;
		
	}

	B = recherche_CN_N(CN, x, y);

	if(B==NULL){

		B = creer_CellNoeud( initialiser_Noeud(x,y) );
		B->suiv = CN;
		return B;
	}

	printf("\nNoeud d�j� stock�\n");
	return CN;

}

CellCommodite* inserer_RCom_Com(CellCommodite *RCom, CellCommodite *Com)
{
	Com->suiv =RCom;
	return Com;

}


/**** Recherche : Les fonctions ******/

Noeud* recherche_CN_N(CellNoeud *CN, double x, double y)
{

	
	Noeud *B = NULL;
	
	while(CN){
		
		B = recherche_N_N(CN->nd, x, y);
		if(B!=NULL) return B;
		
		CN = CN->suiv;
	
	}
	
	return B;
}

Noeud* recherche_N_N(Noeud N, double x, double y)
{
	while(N){

		if(N==NULL) return NULL;

		if(N->x==x && N->y==y){

			printf("\nNoeud trouv�\n");
			return CN->nd;
		}

		recherche_CN_N(N->voisins, x, y);	
	}
}

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
	Noeud* B = recherche_CN_N(R->noeuds, x, y);

	if(B!=NULL) return B;

	CellNoeud *C = creer_CellNoeud( initialiser_Noeud(x, y) );
	C->suiv = R->noeuds;
	R->noeuds = C;

	R->nbNoeuds=NUM-1;
	
	printf("\nNoeud cr�� \n");
	return C->nd;
}

/******* Reconstitution : Fonctions **************/
 
Reseau* reconstitueReseauListe(Chaines* C)
{
	Reseau *R = initialiser_Reseau(C->gamma, comptePointsTotal(C));

	CellChaine *CC = C->chaines;
	CellPoint *CP = CC->points;
	CellPoint *CP_voisins = CP->suiv;

	while(CC){
			
		
		CellNoeud *N;

		if(CP!=NULL){

			 Noeud *R = recherche_CN_N(R->noeuds, CP->x, CP->y);

			 if(R==NULL){
	
				N = creer_CellNoeud( initialiser_Noeud( CP->x, CP->y) );
				
				CellNoeud* extrA = N; // sauvegarde du premier point
				CP = CP->suiv;				
		
				while(CP){
	
					N->nd->voisins = inserer_CN_N( N->nd->voisins, CP->x, CP->y );

					N = N->nd->voisins;

					CP= CP->suiv;
				}
		
				extrA->suiv = R->noeuds;
				R->noeuds = extrA;
				R->commodites = inserer_RCom_Com(R->commodites, initialiser_cellCommodite(extrA->nd, N->nd);

			}else{
				Noeud* extr = R;
				CP = CP->suiv;				
		
				while(CP){
	
					R->voisins = inserer_CN_N( R->voisins, CP->x, CP->y );

					N = R->voisins;

					CP= CP->suiv;
				}
		
				R->commodites = inserer_RCom_Com(R->commodites, initialiser_cellCommodite(extr, N->nd);
			  }
   		}

		CC = CC->suiv;

	}

	return R;
}

/* compte le nombre de commodit�s */

int nbCommodite(Reseau *R)
{
	int nbCom = 0;

	CellCommodite *Com = R->commodites;

	while(Com){

		nbCom++;
		Com = Com->suiv;
	}

	return nbCom;

}

/* compte le nombre des liaisons */

int nbLiaison(Reseau *R)
{
	int nbLiaison = 0;

	while(R->noeuds != NULL){

		nbLiaison += compteNbVoisins(R->noeuds);
		R->noeuds = R->noeuds->suiv;

	}


}

