#include "fondement.h"

//instanciations d objets
noeud* creerRacine(){
    noeud *n=malloc(sizeof(noeud));
    assert(n!=NULL);
    n->est_dossier=true;
    n->pere=n;
    n->racine=n;
    n->fils=NULL;
    init_name(n,"");
    return n;
}

void init_name(noeud *n,char *s){
    for(unsigned i=0; i<strlen(s);++i){
        n->nom[i]=s[i];
    }
    n->nom[strlen(s)]='\0';
}

noeud *creerNoeud(noeud *pere,char *s,bool doss){
    noeud *n=malloc(sizeof(noeud));
    assert(n!=NULL);
    n->est_dossier=doss;
    n->pere=pere;
    n->racine=racine;
    n->fils=NULL;
    init_name(n,s);
    return n;
}
//operations sur les noeuds qui modifient arbre
void ajoute_noeud(noeud *pere,noeud *enfant){
    if(pere->fils==NULL){
        pere->fils=malloc(sizeof(liste_noeud));
        assert(pere->fils!=NULL);
        pere->fils->no=enfant;
        pere->fils->succ=NULL;
    }else{
        liste_noeud *liste=pere->fils;
        while(liste->succ!=NULL){
            liste=liste->succ;
        }
        liste->succ=malloc(sizeof(liste_noeud));
        assert(liste->succ!=NULL);
        liste->succ->no=enfant;
        liste->succ->succ=NULL;
    }
}

void supprimer_noeud(noeud *n){
    if(n->fils==NULL){
        free(n);
    }else{
        supprimer_liste(n->fils);
        free(n->fils);
        free(n);
    }
}
void supprimer_liste(liste_noeud *liste){
    if(liste->succ==NULL){
        supprimer_noeud(liste->no);
    }else{
        supprimer_liste(liste->succ);
        free(liste->succ);
        supprimer_noeud(liste->no);
    }
}

void copie_noeud(noeud *dst, noeud *n,char *s, bool change_name){
    noeud *copie=NULL;
    if(change_name==true) copie=creerNoeud(dst, s, n->est_dossier);
    else copie=creerNoeud(dst, n->nom, n->est_dossier);
    ajoute_noeud(dst, copie);
    if(n->fils!=NULL){
        copie_liste(copie, n->fils,NULL);
    }
}
void copie_liste(noeud *dst, liste_noeud *liste,char *s){
    copie_noeud(dst, liste->no,s,0);
    if(liste->succ!=NULL){
        copie_liste(dst,liste->succ,s);
    }
}

void enleve_fils(noeud *pere, noeud *enfant){
    if(pere==NULL || enfant==NULL || pere->fils==NULL) return;
    if(pere->fils->no==enfant){
        liste_noeud *liste=pere->fils->succ;
        free(pere->fils);
        pere->fils=liste;
    }else{
        liste_noeud *pred=NULL;
        liste_noeud *courant=pere->fils;
        liste_noeud *suivant=courant->succ;
        while(courant->no!=enfant && suivant!=NULL){
            pred=courant;
            courant=suivant;
            suivant=suivant->succ;
        }
        if(courant->no==enfant){
            free(pred->succ);
            pred->succ=suivant;
        }
    }
}

void fin(void){
    printf("Arret du programme\n");
    supprimer_noeud(racine);
    int closed=fclose(file);
    if(closed!=0)perror("Nous rencontrons des problèmes dans la fermeture du ficher");
    exit(0);
}
