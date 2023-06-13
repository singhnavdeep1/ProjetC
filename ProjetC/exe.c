#include "projet.h"

int main(int argc, char* argv[]){

    racine=creerRacine();
    courant=racine;

        
    if (argc != 2)printf("error : nombre d'argument incorrect.\n");
    else {

    file=fopen(argv[1], "r");
        if(file==NULL){
            perror("Nous rencontrons des problèmes dans l'ouverture du fichier");
        }else{

            char content[256];

            while(fgets(content,256,file)!=NULL){ 
                ++ligne;
                int content_size=strlen(content);
    
                if(content[content_size-1]=='\n')content[content_size-1]='\0';
                else content[content_size]='\0';

                if((strcmp(content,"")!=0)){
                    set *id=make_set(content,' ');
                    if(id->nb>0){
                        
                        if(strcmp(id->mots[0], "ls")==0){
                            ls(id);

                        }else if(strcmp(id->mots[0], "mkdir")==0){
                            create(id, true);

                        }else if(strcmp(id->mots[0],"touch")==0){
                            create(id, false);

                        }else if(strcmp(id->mots[0], "cd")==0){
                            cd(id);

                        }else if(strcmp(id->mots[0], "pwd")==0){
                            pwd(id);

                        }else if(strcmp(id->mots[0],"rm")==0){
                            rm(id); 

                        }else if(strcmp(id->mots[0],"cp")==0){
                            cp(id);

                        }else if(strcmp(id->mots[0],"mv")==0){
                            mv(id);

                        }else if(strcmp(id->mots[0],"print")==0){
                            print(id);
                            
                        }else{
                            printf("erreur  l.%d : commande %s introuvable.\n",ligne,id->mots[0]);
                            free_set(id);
                            fin();
                        }
                    }else {
                        free_set(id);
                       
                    }
                }
            }
            supprimer_noeud(racine);
            int closed=fclose(file);
            if(closed!=0)perror("Nous rencontrons des problèmes dans la fermeture du ficher");
        }
    }
}

