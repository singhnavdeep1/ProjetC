#ifndef FONDEMENT_H
#define FONDEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

extern FILE *file;

struct noeud;
struct liste_noeud ;

struct noeud {
    bool est_dossier ;
    char nom[100];
    struct noeud* pere ;
    struct noeud* racine ;
    struct liste_noeud* fils ;
};
struct liste_noeud {
    struct noeud * no ;
    struct liste_noeud * succ ;
};
typedef struct noeud noeud ;
typedef struct liste_noeud liste_noeud ;


extern noeud *racine;
extern noeud *courant;

//instanciations d objets
extern noeud *creerRacine();
extern noeud *creerNoeud(noeud *pere,char *s,bool doss);

//initialisation du nom pour un noeud
extern void init_name(noeud *n,char *s);

//operations sur les noeuds qui modifient arbre
extern void ajoute_noeud(noeud *pere,noeud *enfant);
extern void supprimer_noeud(noeud *n);
extern void supprimer_liste(liste_noeud *liste);
extern void copie_noeud(noeud *dst, noeud *n,char *s, bool change_name);
extern void copie_liste(noeud *dst, liste_noeud *liste,char *s);
extern void enleve_fils(noeud *pere, noeud *fils);

//arret du programme a la rencontre d'une erreur
extern void fin(void);

#endif