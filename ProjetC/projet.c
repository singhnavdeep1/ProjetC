#include "projet.h"

noeud *racine=NULL;
noeud *courant=NULL;
FILE *file=NULL;
int ligne=0;

void ls(set *id){ 
    if(id->nb!=1){
        printf("erreur l.%d : nombre d'arguments invalide pour la commande ls.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    noeud *tmp=courant;
    liste_noeud *liste=tmp->fils;
    while(liste!=NULL){
        printf("%s   ", liste->no->nom);
        liste=liste->succ;
    }
    puts("");
    free_set(id);
}
void cd(set *id){
    if (id->nb>2){
        printf("erreur l.%d : nombre d'arguments invalide pour la commande cd.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    if (id->nb==1){ 
        courant=racine;
        free_multi(id,NULL,NULL);
        return;
    }
    noeud *tmp=NULL;
    set *chemin=make_set(id->mots[1],'/');
    if(isAbsolute(id->mots[1])) tmp=goTo(racine,chemin);
    else tmp=goTo(courant,chemin);
    if(tmp==NULL || endBySlash(id->mots[1])){
        printf("erreur l.%d : le chemin %s est invalide.\n",ligne,id->mots[1]);
        free_multi(id,chemin,NULL);
        fin(); 
    }
    if(tmp->est_dossier==false){
        printf("erreur l.%d : le chemin %s mène à un fichier.\n",ligne,id->mots[1]);
        free_multi(id,chemin,NULL);
        fin(); 
    }
    courant=tmp;
    free_multi(id,chemin,NULL);
}

void pwd(set *id){
    if(id->nb!=1){
        printf("erreur l.%d : nombre d'arguments invalide pour la commande pwd.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    set *chem=get_Chemin_Absolu(courant);
    printf("/");
    for(unsigned i=0; i<chem->nb; ++i){
        printf("%s",chem->mots[i]);
        if(i!=chem->nb-1) printf("/");
    }
    puts("");
    free_multi(id,chem,NULL);
 
}
void create(set *id, bool doss){
    if(id->nb!=2){
        printf("erreur l.%d : nombre d'arguments invalide pour la commande %s\n",ligne,id->mots[0]);
        free_multi(id,NULL,NULL);
        fin();
    }
    if(contains(courant->fils,id->mots[1])){
        printf("erreur  l.%d : le dossier %s contient déjà un élément %s.\n",ligne,courant->nom,id->mots[1]);
        free_multi(id,NULL,NULL);
        fin();
    }
    if(!is_correct(id->mots[1])){
        printf("erreur  l.%d : le nom %s est invalide, seuls les chiffres et les lettres sont acceptés et au plus 99 caractères.\n",ligne,id->mots[1]);
        free_multi(id,NULL,NULL);
        fin();
    }
    char *nom=id->mots[1];
    noeud *n=creerNoeud(courant,nom,doss);
    ajoute_noeud(courant,n);
    free_multi(id,NULL,NULL);
}
void rm(set *id){
    if(id->nb!=2){
        printf("erreur l.%d : nombre d'arguments invalide pour la commande rm.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    set *chem=make_set(id->mots[1],'/');
    noeud *tmp=NULL;
    if(isAbsolute(id->mots[1])) tmp=goTo(racine,chem);
    else tmp=goTo(courant,chem);
    if(tmp==NULL || endBySlash(id->mots[1])){
        printf("erreur  l.%d : le chemin %s est invalide.\n",ligne,id->mots[1]);
        free_multi(id,chem,NULL);
        fin();
    }
    if(isParent(courant,tmp)){
        printf("erreur  l.%d : impossible de supprimer la cible est parent du noeud courant.\n",ligne);
        free_multi(id,chem,NULL);
        fin();
    }
    enleve_fils(tmp->pere,tmp);
    supprimer_noeud(tmp);
    free_multi(id,chem,NULL);

}
void cp(set *id){
    if(id->nb!=3){
        printf("erreur  l.%d : nombre d'arguments invalide pour la commande cp.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    if(endBySlash(id->mots[1]) || endBySlash(id->mots[2])){
        printf("erreur  l.%d : un chemin ne peut finir par / .\n",ligne);
        free_set(id);
        fin();
    }
    set *chem1=make_set(id->mots[1],'/');
    set *chem2=make_set(id->mots[2],'/');
    char *new_name=chem2->mots[chem2->nb-1];
    if(!is_correct(new_name)){
        printf("erreur  l.%d : le nom %s est invalide.\n",ligne,new_name);
        free_multi(id,chem1,chem2);
        fin();
    }
    
    noeud *tmp1=NULL;
    noeud *tmp2=NULL;
    if(isAbsolute(id->mots[1])) tmp1=goTo(racine,chem1);
    else tmp1=goTo(courant,chem1);
    if(isAbsolute(id->mots[2])) tmp2=goTo_bis(racine,chem2);
    else tmp2=goTo_bis(courant,chem2);

    if (tmp1==NULL){
        printf("erreur  l.%d : le chemin %s est invalide.\n",ligne,id->mots[1]);
        free_multi(id,chem1,chem2);
        fin();
    }
    if (tmp2==NULL || tmp2->est_dossier==false){
        printf("erreur  l.%d : le chemin %s est invalide.\n",ligne,id->mots[2]);
        free_multi(id,chem1,chem2);
        fin();
    }
    if(contains(tmp2->fils,new_name)){
        printf("erreur  l.%d : la cible contient déjà un fils %s.\n",ligne,new_name);
        free_multi(id,chem1,chem2);
        fin();
    }
    if(isParent(tmp2,tmp1)){
        printf("erreur  l.%d : le dossier de destination est fils du noeud source.\n",ligne);
        free_multi(id,chem1,chem2);
        fin();
    }
    copie_noeud(tmp2,tmp1,new_name,1);
    free_multi(id,chem1,chem2);
}
void mv(set *id){
    if(id->nb!=3){
        printf("erreur  l.%d : nombre d'arguments invalide pour la commande cp.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    if(endBySlash(id->mots[1]) || endBySlash(id->mots[2])){
        printf("erreur  l.%d : un chemin ne peut finir par / .\n",ligne);
        free_set(id);
        fin();
    }

    set *chem1=make_set(id->mots[1],'/');
    set *chem2=make_set(id->mots[2],'/');
    char *new_name=chem2->mots[chem2->nb-1];

    if(!is_correct(new_name)){
        printf("erreur  l.%d : le nom %s est invalide.\n",ligne,new_name);
        free_multi(id,chem1,chem2);
        fin();
    }
    noeud *tmp1=NULL;
    noeud *tmp2=NULL;
    if(isAbsolute(id->mots[1])) tmp1=goTo(racine,chem1);
    else tmp1=goTo(courant,chem1);
    if(isAbsolute(id->mots[2])) tmp2=goTo_bis(racine,chem2);
    else tmp2=goTo_bis(courant,chem2);

    if (tmp1==NULL){
        printf("erreur  l.%d : le chemin %s est invalide.\n",ligne,id->mots[1]);
        free_multi(id,chem1,chem2);
        fin();
    }
    if (tmp2==NULL || tmp2->est_dossier==false){
        printf("erreur  l.%d : le chemin %s est invalide.\n",ligne,id->mots[2]);
        free_multi(id,chem1,chem2);
        fin();
    }
    if(contains(tmp2->fils,new_name)){
        printf("erreur  l.%d : le dossier cible contient déjà un fils %s.\n",ligne,new_name);
        free_multi(id,chem1,chem2);
        fin();
    }
    if(isParent(tmp2,tmp1)){
        printf("erreur  l.%d : le dossier de destination est fils du noeud source.\n",ligne);
        free_multi(id,chem1,chem2);
        fin();
    }
    enleve_fils(tmp1->pere,tmp1);
    init_name(tmp1,new_name);
    ajoute_noeud(tmp2,tmp1);
    tmp1->pere=tmp2;
    free_multi(id,chem1,chem2);
}

void print(set *id){ 
    if(id->nb!=1){
        printf("erreur  l.%d : nombre d'arguments invalide pour la commande print.\n",ligne);
        free_multi(id,NULL,NULL);
        fin();
    }
    puts("");
    print_noeud(racine,0);
    puts("");
    free_multi(id,NULL,NULL);
}







