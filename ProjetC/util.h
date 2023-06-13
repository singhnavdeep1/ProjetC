#ifndef UTIL_H
#define UTIL_H


#include "parser.h"
#include "fondement.h"


//operations triviales diverses
extern void free_multi(set *id1, set *id2, set *id3);
extern noeud *search_in_liste(liste_noeud *liste,char *nom);
extern bool contains(liste_noeud *liste, char *nom);
extern int hauteur_noeud(noeud *n);
extern int nb_fils(noeud *n);
extern bool is_correct(char *nom);
extern bool endBySlash(char *nom);
extern void affiche_noeud(noeud *n);
extern void print_noeud(noeud *n,int h);
extern void print_liste(liste_noeud *liste,int h);


#endif