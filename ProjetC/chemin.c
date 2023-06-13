#include "chemin.h"

//operations sur les chemins
noeud *goTo(noeud *src, set *chem){
    noeud *tmp=src;
    for (unsigned i=0; i<chem->nb; ++i){
        if(strcmp(chem->mots[i],"..")==0) tmp=tmp->pere;
        else{
            tmp=search_in_liste(tmp->fils,chem->mots[i]);
            if (tmp==NULL) return NULL;
            if(tmp->est_dossier==false && i!=chem->nb-1) return NULL;
        }
    }
    return tmp;
}
noeud *goTo_bis(noeud *src,set *chem){
    noeud *tmp=src;
    if(chem->nb==1) return tmp;
    for (unsigned i=0; i<(chem->nb)-1; ++i){
        if(strcmp(chem->mots[i],"..")==0) tmp=tmp->pere;
        else{
            tmp=search_in_liste(tmp->fils,chem->mots[i]);
            if (tmp==NULL || tmp->est_dossier==false) return NULL;
        }
    }
    return tmp;
}

set *get_Chemin_Absolu(noeud *n){
    noeud *tmp=n;
    set *id=malloc(sizeof(set));
    assert(id!=NULL);
    id->nb=hauteur_noeud(tmp);
    id->mots=malloc((id->nb)*sizeof(char *));
    assert(id->mots!=NULL);
    for(unsigned i=0; i<id->nb; ++i){
        id->mots[(id->nb)-1-i]=malloc((strlen(tmp->nom)+1)*sizeof(char));
        assert(id->mots[(id->nb)-1-i]!=NULL);
        memmove(id->mots[(id->nb)-1-i],tmp->nom,(strlen(tmp->nom)+1)*sizeof(char)); 
        tmp=tmp->pere;
    }
    return id;
}
bool isAbsolute(char *s){
    if (strlen(s)!=0 && s[0]=='/') {
        return true;
    }
    else{
        return false;
    }
}
bool isParent(noeud *pfils,noeud *ppere){
    noeud *tmp=pfils;
    do{ 
        if(tmp==ppere) return true;
        else tmp=tmp->pere;
    }while(tmp!=racine);
    return false;
}