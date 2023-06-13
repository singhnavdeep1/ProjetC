#include "parser.h"

int nbr_word(char *s,char separator){
    int n=0;
    bool sep=true;
    for (unsigned i=0; i<strlen(s); ++i){
        if (s[i]==separator) sep=true;
        else{
            if (sep==true) ++n;
            sep=false;
        }
    }
    return n;
}

int word_len(char *s,char separator){
    assert(*s!=separator);
    unsigned i=0;
    while(*(s+i)!=separator && *(s+i)!='\0'){
        ++i;
    }
    return i;
}

char *extract_word(char *w,char separator, int *pl){
    assert(*w!=separator && *w!='\0');
    *pl=word_len(w,separator);
    char *s1=malloc((*pl+1)*sizeof(char));
    assert(s1!=NULL);
    memmove(s1,w,(*pl)*sizeof(char));
    *(s1+*pl)='\0';
    return s1;
}

char *next_word(char *w,char separator){
    unsigned i=0;
    while(*(w+i)!='\0'){
        if(*(w+i)!=separator) return (w+i);
        else i++;
    }
    return NULL;
}

set *make_set(char *s,char separator){
    set *id=malloc(sizeof(set));
    assert(id!=NULL);
    id->nb=nbr_word(s,separator);
    id->mots=malloc(id->nb*sizeof(char *));
    assert(id->mots!=NULL);
    char *chaine=next_word(s,separator);

    for(unsigned i=0; i<id->nb; ++i){
        int len=0;
        char *mot=extract_word(chaine,separator, &len);
        id->mots[i]=malloc((len+1)*sizeof(char));
        assert(id->mots[i]!=NULL);
        memmove(id->mots[i], mot, (len)*sizeof(char));
        *(id->mots[i]+(len))='\0';
        chaine=next_word(chaine+len,separator);
        free(mot);
    }
    return id;
}

void print_set(set *id){
    printf("nombre de mots: %d\n",id->nb);
    printf("liste des mots : \n");
    for (unsigned i=0; i<id->nb; ++i){
        printf("-   %s\n",id->mots[i]);
    }
}
void free_set(set *id){
    for(unsigned i=0; i<id->nb; ++i){
        free(id->mots[i]);
    }
    free(id->mots);
    free(id);
}