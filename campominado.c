#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10
#define BOMBAS 15

int dentro(int i, int j){
    return i >= 0 && i < TAM && j >= 0 && j < TAM;
}

void inicializar(int campo[][TAM], int visivel[][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            campo[i][j] = 0;
            visivel[i][j] = 0;
        }
    }
}

void colocarbombas(int campo[][TAM]){
    int b = 0;
    while(b < BOMBAS){
        int i = rand() % TAM;
        int j = rand() % TAM;

        if(campo[i][j] != -1){
            campo[i][j] = -1;
            b++;
        }
    }
}

void calcularnumeros(int campo[][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(campo[i][j] == -1) continue;

            int cont = 0;
            for(int di = -1; di <= 1; di++){
                for(int dj = -1; dj <= 1; dj++){
                    if(dentro(i + di, j + dj) && campo[i + di][j + dj] == -1)
                        cont++;
                }
            }
            campo[i][j] = cont;
        }
    }
}

void mostrar(int visivel[][TAM]){
    printf("    ");
    for(int j = 0; j < TAM; j++)
        printf("%2d ", j);
    printf("\n");

    for(int i = 0; i < TAM; i++){
        printf("%2d  ", i);
        for(int j = 0; j < TAM; j++){
            if(visivel[i][j])
                printf("%2d ", visivel[i][j] - 1);
            else
                printf(" # ");
        }
        printf("\n");
    }
}

int abrir(int campo[][TAM], int visivel[][TAM], int l, int c){
    if(!dentro(l, c) || visivel[l][c]) return 0;

    visivel[l][c] = campo[l][c] + 1;

    if(campo[l][c] == 0){
        for(int di = -1; di <= 1; di++){
            for(int dj = -1; dj <= 1; dj++){
                abrir(campo, visivel, l + di, c + dj);
            }
        }
    }
    return campo[l][c] == -1;
}

int verificarvitoria(int campo[][TAM], int visivel[][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(campo[i][j] != -1 && !visivel[i][j])
                return 0;
        }
    }
    return 1;
}

int main(){
    int campo[TAM][TAM], visivel[TAM][TAM];
    int l, c;
    srand(time(NULL));
    inicializar(campo, visivel);
    colocarbombas(campo);
    calcularnumeros(campo);

    while(1){
        mostrar(visivel);
        printf("\nDigite a linha e a coluna (ex: 1 2): ");
        scanf("%d %d", &l, &c);

        if(abrir(campo, visivel, l, c)){
            printf("\nBOOM! Voce perdeu!\n");
            break;
        }

        if(verificarvitoria(campo, visivel)){
            printf("\nParabens! Voce venceu!\n");
            break;
        }
    }

    return 0;
}