#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO 1024


void consertaLinha(char * linha){

    size_t tamanho = strlen(linha);
    if (linha[tamanho - 1] == '\n')
    {
        linha[tamanho - 1] = '\0';
    }
}

void separaComando(char * linha, char ** token, char ** comando) {
     
    token = strtok(linha," ");
    int i=0;

    while(token!=NULL)
    {
        comando[i]=token;      
        token = strtok(NULL," ");
        i++;
    }
    comando[i]=NULL;                     //set last value to NULL for execvp
}

void printaComandos(int contador, char** comando){
    int i = 0;
    contador=i;                           //get arg count
    for(i=0; i<contador; i++){
        printf("%s\n", comando[i]);      //print command/args
    }
        
}

void copiaComandos(char * progpath, char ** path, char ** comando){

    strcpy(progpath, path);           //copy /bin/ to file path
    strcat(progpath, comando[0]);            //add program to path

}

void deletaLinha(char * progpath){

    int i;
    for(i=0; i<strlen(progpath); i++)
    {    
        if(progpath[i]=='\n'){      
            progpath[i]='\0';
        }
    }

}

int main(){

    char linha[TAMANHO];     //linha para comando
    char* comando[100];     //comando do usuario
    char* path= "/bin/";   //caminho para o bin
    char progpath[20];    //arquivo para o path bin 
    char *token;         //Vamos usar pra separar os comandos 
    int contador;          
    int filho, i;

    while(1){

        printf("--- Meu terminal: "); 

        if(!fgets(linha, TAMANHO, stdin))//pega o comando, CTRL+D = break
        {                                       
            break;                                
        }

        consertaLinha(linha); //conserta bug da linha

        if(strcmp(linha, "exit")==0) //Verifica se o comando é exit
        {            
            break;
        }

        separaComando(linha, token, comando);
        printaComandos(contador, comando);
        copiaComandos(progpath, path, comando);
        deletaLinha(progpath);

        filho= fork();       //Processo filho

        if(filho==0){           
            execvp(progpath,comando);
            fprintf(stderr, "ERROR\n");

        }else{                    //Mudando para o processo pai
            wait(-1);
            printf("--- Esse é o pai! ---\n");
        }

    }
} 