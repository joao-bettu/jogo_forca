#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

void abertura();
void forca(char *palavra, int tentativas, char *max_chutes);
bool achou_letra(char letra, int tentativas, char *max_chutes);
bool enforcou(int tentativas, char *max_chutes, char *palavra);
bool acertou(char *palavra, int tentativas, char *max_chutes);
int get_chute(char *max_chutes, int tentativas);
char *sortea_palavra(char *palavra);

int main(){
    char palavra[50], max_chutes[26];
    int tentativas = 0;

    sortea_palavra(palavra);

    abertura();

    do{
        forca(palavra, tentativas, max_chutes);
        printf("\n");
        tentativas = get_chute(max_chutes, tentativas);
    }while(!acertou(palavra, tentativas, max_chutes) && !enforcou(tentativas, max_chutes, palavra));

    printf("\n");
    if(enforcou(tentativas, max_chutes, palavra)){
        printf("Você perdeu! Tente novamente!\n");
    }
    if(acertou(palavra, tentativas, max_chutes)){
        printf("Você ganhou, parabéns!\n");
        printf("A palavra era: %s\n", palavra);
    }

    return 0;
}

void abertura(){
    printf("*********************\n");
    printf("*   Jogo da Forca   *\n");
    printf("*********************\n");
}
void forca(char *palavra, int tentativas, char *max_chutes){
    printf("\nTentativa %d!\n", tentativas);
    for(int i = 0; i < strlen(palavra); i++){
        if(achou_letra(palavra[i], tentativas, max_chutes)){
            printf("%c ", palavra[i]);
        }else{
            printf("_ ");
        }
    }
}
bool achou_letra(char letra, int tentativas, char *max_chutes){
    bool achou = false;
    for(int j = 0; j < tentativas; j++){
        if(max_chutes[j] == letra){
            achou = true;
            break;
        }
    }
    return achou;
}
bool enforcou(int tentativas, char *max_chutes, char *palavra){
    int erros = 0;
    char errados[5] = {NULL,NULL,NULL,NULL,NULL};

    for(int i = 0; i<tentativas; i++){
        bool existe = achou_letra(palavra[i], tentativas, max_chutes);
        if(!existe){
            errados[erros] = max_chutes[i];
            erros++;
        }
    }
    if(errados[0]!=NULL){
        printf("Errados: ");
        for(int i = 0; i < strlen(errados); i++){
            printf("%c ", errados[i]);
        }
    printf("\n");
    }
    return erros >= 5;
}
bool acertou(char *palavra, int tentativas, char *max_chutes){
    for(int i = 0; i < strlen(palavra); i++){
        if(!achou_letra(palavra[i], tentativas, max_chutes)){
            return false;
        }
    }
    return true;
}
int get_chute(char *max_chutes, int tentativas){
    char chute;
    
    printf("De o seu chute: ");
    scanf("%c", &chute);
    getchar();
    max_chutes[tentativas] = chute;
    tentativas++;
    return tentativas;
}
char *sortea_palavra(char *palavra){
    FILE *fp;
    int aleatorio, qntpalavras;

    fp = fopen("/home/ixcsoft/Documentos/Códigos/Alura/palavras.txt", "r+");
    if(fp==NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    fscanf(fp, "%d", &qntpalavras);

    srand(time(NULL));
    aleatorio = rand() % qntpalavras;

    for(int i = 0; i < aleatorio; i++){
        fscanf(fp, "%s", palavra);
    }

    fclose(fp);
    return palavra;
}