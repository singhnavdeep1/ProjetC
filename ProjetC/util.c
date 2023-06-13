#include "util.h"



//operations triviales diverses
void free_multi(set *id1, set *id2, set *id3){
    if(id1!=NULL)free_set(id1);
    if(id2!=NULL)free_set(id2);
    if(id3!=NULL)free_set(id3);
}

noeud *search_in_liste(liste_noeud *liste,char *nom){
    liste_noeud *tmp=liste;
    while(tmp!=NULL){
        if(strcmp(tmp->no->nom,nom)==0) return tmp->no;
        else tmp=tmp->succ;
    }
    return NULL;
}

bool contains(liste_noeud *liste, char *nom){
    liste_noeud *tmp=liste;
    while(tmp!=NULL){
        if(strcmp(tmp->no->nom,nom)==0) return true;
        tmp=tmp->succ;
    }
    return false;
}

int hauteur_noeud(noeud *n){ 
    noeud *tmp=n;
    int h=0; //hauteur racine = 0
    while(tmp!=racine){
        ++h;
        tmp=tmp->pere;
    }
    return h;
}
int nb_fils(noeud *n){
    liste_noeud *liste=n->fils;
    int i=0;
    while(liste!=NULL){
        ++i;
        liste=liste->succ;
    }
    return i;
}
bool is_correct(char *nom){
    if(strlen(nom)>99 || strlen(nom)==0) return false;
    for (unsigned i=0; i<strlen(nom); ++i){
        if(isalnum(nom[i])==0) return false;
    }
    return true;
}
bool endBySlash(char *nom){
    unsigned len=strlen(nom);
    if(nom[len-1]=='/')return true;
    return false;
}

void affiche_noeud(noeud *n){
    if(n==NULL) return;
    if(n==racine) printf("/ ");
    else printf("%s ",n->nom);
    printf(n->est_dossier ? "(D)   ->   " : "(F)   ->   ");
    if(n->pere==racine) printf("père : /,   ");
    else printf("père : %s,   ",n->pere->nom);
    int i=nb_fils(n);
    printf(i==0 ? "%d fils" : "%d fils : ",i);
    liste_noeud *liste=n->fils;
    while(liste!=NULL){
        printf("%s ",liste->no->nom);
        //printf(liste->no->est_dossier ? "(D)" : "(F)" );
        if(liste->succ!=NULL) printf(", ");
        liste=liste->succ;
    }
    puts("");
}
void print_noeud(noeud *n,int h){
    for(unsigned i=0; i<h; ++i){
        printf("  ");
    }
    if(h!=0)printf("|--");
    affiche_noeud(n);
    if(n->fils!=NULL) print_liste(n->fils,h+1);
}
void print_liste(liste_noeud *liste,int h){
    print_noeud(liste->no,h);
    if(liste->succ!=NULL){
        print_liste(liste->succ,h);
    }
}