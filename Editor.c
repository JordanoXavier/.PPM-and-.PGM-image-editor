#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dadosArquivo{
    char tipo[3];
    int altura, largura;
    int max;
};

//Funções arquivo P3 - PPM
void lerP3(char tipo[3], FILE *arq);
void menuP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]);
void salvarP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]);
void grayscaleP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]);
void recorteP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]);
void greenscreenP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]);
void rotacaoP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3], int rotacoes);

//Funções arquivo P2 - PGM
void lerP2(char tipo[3], FILE *arq);
void menuP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]);
void salvarP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]);
void recorteP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]);
void rotacaoP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura], int rotacoes);
void greenscreenP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]);

void inicializaArquivo(); //função para abrir o arquivo e ver o formato


int main(){
    inicializaArquivo(); 
}


///Funções arquivo P3 - PPM
void rotacaoP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3], int rotacoes){
    //comparar a altura e a largura para saber se a imagem é quadrada ou não
    if(dados.altura == dados.largura){
        //rotacionar a imagem
        int matrizAux[dados.altura][dados.largura][3];
        int i, j, k;
        for(i = 0; i < dados.altura; i++){
            for(j = 0; j < dados.largura; j++){
                for(k = 0; k < 3; k++){
                    matrizAux[i][j][k] = matriz[i][j][k];
                }
            }
        }
        for(i = 0; i < dados.altura; i++){
            for(j = 0; j < dados.largura; j++){
                for(k = 0; k < 3; k++){
                    matriz[j][dados.altura - 1 - i][k] = matrizAux[i][j][k];
                }
            }
        }
        
        //printar a matriz e voltar ao menu quando tiver feito todas as rotações
        if(rotacoes == 1){
            printf("\nImagem rotacionada com sucesso!\n");
            for (i = 0; i < dados.altura; i++){
                for (j = 0; j < dados.largura; j++){
                    printf("%d %d %d ", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
                }
                printf("\n");
            }
            menuP3(dados, matriz);
        }
        else{ //ou rotacionar novamente
            rotacaoP3(dados, matriz, rotacoes - 1);
        }
    }
    else{ //se não for uma matriz quadrada terá que criar uma matriz quadrada para rotacionar
        //comparar altura e largura para criar uma matriz quadrada
        int coordenadaMaior;
        if(dados.altura > dados.largura)
            coordenadaMaior = dados.altura;
        else
            coordenadaMaior = dados.largura;
        int matrizQuad[coordenadaMaior][coordenadaMaior][3];

        //preencher a matriz quadrada com um valor negativo para diferenciar dos valores da imagem
        int i, j, k;
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                for(k = 0; k < 3; k++){
                    matrizQuad[i][j][k] = -1;
                }
            }
        }

        //preencher a matriz quadrada com os valores da imagem
        for(i = 0; i < dados.altura; i++){
            for(j = 0; j < dados.largura; j++){
                for(k = 0; k < 3; k++){
                    matrizQuad[i][j][k] = matriz[i][j][k];
                }
            }
        }

        //rotacionar a matriz quadrada
        int matrizAux[coordenadaMaior][coordenadaMaior][3];
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                for(k = 0; k < 3; k++){
                    matrizAux[i][j][k] = matrizQuad[i][j][k];
                }
            }
        }
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                for(k = 0; k < 3; k++){
                    matrizQuad[j][coordenadaMaior - 1 - i][k] = matrizAux[i][j][k];
                }
            }
        }

        //inverter a altura e largura e criar uma matriz nova com os valores da matriz quadrada
        int aux = dados.altura;
        dados.altura = dados.largura;
        dados.largura = aux;
        int matrizRotacionada[dados.altura][dados.largura][3];
        int lin=0, col=0;
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                if(matrizQuad[i][j][0] >= 0){
                    matrizRotacionada[lin][col][0] = matrizQuad[i][j][0];
                    matrizRotacionada[lin][col][1] = matrizQuad[i][j][1];
                    matrizRotacionada[lin][col][2] = matrizQuad[i][j][2];
                    col++;
                    if(col == dados.largura){
                        lin++;
                        col = 0;
                    }
                }
            }
        }
        
        //printar a matriz rotacionada e voltar ao menu quando estiver feito todas as rotações
        if(rotacoes == 1){
            printf("\nImagem rotacionada com sucesso!\n");
            for (i = 0; i < dados.altura; i++){
                for (j = 0; j < dados.largura; j++){
                    printf("%d %d %d  ", matrizRotacionada[i][j][0], matrizRotacionada[i][j][1], matrizRotacionada[i][j][2]);
                }
                printf("\n");
            }
            menuP3(dados, matrizRotacionada);
        }
        else{ //ou rotacionar novamente
            rotacaoP3(dados, matrizRotacionada, rotacoes-1);
        }
    }
}

void greenscreenP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]){
    //abrir um novo arquivo e ler uma nova imagem
    FILE *arq;
    char nomeArquivo[50];
    int i, j;
    printf("Digite o nome ou diretorio da imagem P3 de frente que deseja usar: ");
    scanf("%s", nomeArquivo);
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        printf("\nErro ao abrir o arquivo\n");
        menuP3(dados, matriz);
    }

    //ler o arquivo
    struct dadosArquivo dados2;
    fscanf(arq, "%s", dados2.tipo);
    fscanf(arq, "%d %d", &dados2.altura, &dados2.largura);
    fscanf(arq, "%d", &dados2.max);
    int matriz2[dados2.altura][dados2.largura][3];
    for(i = 0; i < dados2.altura; i++){
        for(j = 0; j < dados2.largura; j++){
            fscanf(arq, "%d %d %d", &matriz2[i][j][0], &matriz2[i][j][1], &matriz2[i][j][2]);
        }
    }

    //verificar se a imagem da frente é maior que a imagem de fundo
    if(dados.altura < dados2.altura || dados.largura < dados2.largura){
        printf("\nErro: imagem de fundo menor que a imagem de frente\n");
        menuP3(dados, matriz);
    }
    //verificar se o tipo é o mesmo
    if(strncmp(dados2.tipo, "P3", 2)){//retorna 0 se forem iguais
        printf("\nErro: imagens de tipos diferentes\n");
        menuP3(dados, matriz);
    }

    //pegar o valor da cor que deseja remover
    int cor;
    printf("Digite o valor (de 0 a %d) da cor que deseja usar como mascara: ", dados.max);
    scanf("%d", &cor);

    //aplicar o greenscreen na matriz lida e passar pra matriz principal
    for(i = 0; i < dados2.altura; i++){
        for(j = 0; j < dados2.largura; j++){
            if(matriz2[i][j][0] != cor && matriz2[i][j][1] != cor && matriz2[i][j][2] != cor){
                matriz[i][j][0] = matriz2[i][j][0];
                matriz[i][j][1] = matriz2[i][j][1];
                matriz[i][j][2] = matriz2[i][j][2];
            }
        }
    }

    //printar a matriz com a imagem modificada
    printf("Imagem sobreposta com sucesso!\n");
    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            printf("%d %d %d  ", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
        }
        printf("\n");
    }

    menuP3(dados, matriz);
}

void recorteP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]){
    //ler o canto superior esquerdo e inferior direito da área a ser recortada
    int x1, y1, x2, y2;
    printf("Digite as coordenadas X1 e Y1 (comecando em 0) do canto superior esquerdo da area a ser recortada: ");
    scanf("%d %d", &x1, &y1);
    printf("Digite X2 e Y2 do canto inferior direito da area a ser recortada: ");
    scanf("%d %d", &x2, &y2);

    //verificar se os valores digitados estão dentro da matriz
    if(x1 < 0 || x1 > dados.altura || x2 < 0 || x2 > dados.altura || y1 < 0 || y1 > dados.largura || y2 < 0 || y2 > dados.largura){
        printf("Valores invalidos!\n");
        menuP3(dados, matriz);
    }
    //verificar se o canto superior esquerdo é menor que o inferior direito
    if(x1 > x2 || y1 > y2){
        printf("Valores invalidos!\n");
        menuP3(dados, matriz);
    }

    //recortar a matriz em uma nova matriz
    int alturaRecorte = x2 - x1 +1;
    int larguraRecorte = y2 - y1 +1;
    int matrizAux[alturaRecorte][larguraRecorte][3];
    int i, j;
    for(i = 0; i < alturaRecorte; i++){
        for(j = 0; j < larguraRecorte; j++){
            for(int k = 0; k < 3; k++){
                matrizAux[i][j][k] = matriz[i+x1][j+y1][k];
            }
        }
    }

    //printar a matriz auxiliar
    printf("\nImagem recortada:\n");
    for(i = 0; i < alturaRecorte; i++){
        for(j = 0; j < larguraRecorte; j++){
            printf("%d %d %d  ", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
        }
        printf("\n");
    }

    //atualizar os dados da imagem e retornar ao meu
    dados.altura = alturaRecorte;
    dados.largura = larguraRecorte;
    menuP3(dados, matrizAux);
}

void grayscaleP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]){
    int i, j, media;
    int matrizP2[dados.altura][dados.largura];
    for(i=0; i<dados.altura; i++){
        for(j=0; j<dados.largura; j++){
            media = (matriz[i][j][0] + matriz[i][j][1] + matriz[i][j][2])/3;
            matrizP2[i][j]= media;
        }
    }

    printf("\nMatriz convertida para P2 com sucesso!\n");
    for(i=0; i<dados.altura; i++){
        for(j=0; j<dados.largura; j++){
            printf("%d ", matrizP2[i][j]);
        }
        printf("\n");
    }

    menuP2(dados, matrizP2);
}

void salvarP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]){
    FILE *arq;
    char nomeArquivo[50];
    char extensao[5] = ".ppm";
    printf("Digite o nome ou diretorio que o arquivo .ppm sera salvo: ");
    scanf("%s", nomeArquivo);
    strcat(nomeArquivo, extensao);

    arq = fopen(nomeArquivo, "w"); 
    fprintf(arq, "%s", dados.tipo);
    fprintf(arq, "%d %d\n", dados.altura, dados.largura);
    fprintf(arq, "%d\n", dados.max);

    int i, j;
    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            fprintf(arq, "%d %d %d  ", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
        }
        fprintf(arq, "\n");
        printf("\n");
    }
    
    fclose(arq);
}

void menuP3(struct dadosArquivo dados, int matriz[dados.altura][dados.largura][3]){
    int opcao=0;
    printf("\n\nEscolha a opcao desejada:\n 1 - Recortar imagem\n 2 - Transformar em escala de cinza\n 3 - Aplicar filtro greenscreen\n 4 - Rotacionar imagem\n 5 - Sair (salvar imagem)\n");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            recorteP3(dados, matriz);
            break;
        case 2:
            grayscaleP3(dados, matriz);
            break;
        case 3:
            greenscreenP3(dados, matriz);
            break;
        case 4:
            printf("Escolha quantos graus rotacionar:\n 1 - 90    2 - 180    3 - 270\n");
            int rotacoes;
            scanf("%d", &rotacoes);
            rotacaoP3(dados, matriz, rotacoes);
            break;
        case 5:
            salvarP3(dados, matriz);
            break;
        default:
            printf("Opcao invalida\n");
            menuP3(dados, matriz);
            break;
    }
}

void lerP3(char tipo[3], FILE *arq){
    struct dadosArquivo dados;
    strcpy(dados.tipo, tipo);
    fscanf(arq, "%d %d", &dados.altura, &dados.largura);
    printf("Altura: %d, Largura: %d\n", dados.altura, dados.largura);
    fscanf(arq, "%d", &dados.max);
    printf("Valor maximo da cor: %d\n", dados.max);

    int matriz[dados.altura][dados.largura][3];
    int i, j;
    for(i=0; i<dados.altura; i++){
        for(j=0; j<dados.largura; j++){
            fscanf(arq, "%d %d %d", &matriz[i][j][0], &matriz[i][j][1], &matriz[i][j][2]);
        }
    }

    for(i=0; i<dados.altura; i++){
        for(j=0; j<dados.largura; j++){
            printf("%d %d %d  ", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
        }
        printf("\n");
    }

    menuP3(dados, matriz);
}


///Funções arquivo P2 - PGM
void greenscreenP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]){
    //abrir um novo arquivo e ler uma nova imagem
    FILE *arq;
    char nomeArquivo[50];
    int i, j;
    printf("Digite o nome ou diretorio da imagem P2 de frente que deseja usar: ");
    scanf("%s", nomeArquivo);
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        printf("\nErro ao abrir o arquivo\n");
        menuP2(dados, matriz);
    }

    //ler o arquivo
    struct dadosArquivo dados2;
    fscanf(arq, "%s", dados2.tipo);
    fscanf(arq, "%d %d", &dados2.altura, &dados2.largura);
    fscanf(arq, "%d", &dados2.max);
    int matriz2[dados2.altura][dados2.largura];
    for(i = 0; i < dados2.altura; i++){
        for(j = 0; j < dados2.largura; j++){
            fscanf(arq, "%d", &matriz2[i][j]);
        }
    }

    //verificar se a imagem da frente é maior que a imagem de fundo
     if(dados.altura < dados2.altura || dados.largura < dados2.largura){
        printf("\nErro: imagem de fundo menor que a imagem de frente\n");
        menuP2(dados, matriz);
    }
    //verificar se o tipo é o mesmo
    if(strncmp(dados.tipo, "P2", 2)){//retorna 0 para strings iguais
        printf("\nErro: imagens de tipos diferentes\n");
        menuP2(dados, matriz);
    }

    //pegar o valor da cor que deseja remover
    int cor;
    printf("Digite o valor (de 0 a %d) da cor que deseja usar como mascara: ", dados.max);
    scanf("%d", &cor);

    //aplicar o greenscreen na matriz lida e passar pra matriz principal
    for(i = 0; i < dados2.altura; i++){
        for(j = 0; j < dados2.largura; j++){
            if(matriz2[i][j] != cor){
                matriz[i][j] = matriz2[i][j];
            }
        }
    }

    //printar a matriz com a modificacao
    printf("Imagem sobreposta com sucesso!\n");
    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    menuP2(dados, matriz);
}

void rotacaoP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura], int rotacoes){
    //comparar a altura e a largura para saber se a imagem é quadrada ou não
    if(dados.altura == dados.largura){
        //rotacionar a matriz
        int matrizAux[dados.altura][dados.largura];
        int i, j;
        for(i = 0; i < dados.altura; i++){
            for(j = 0; j < dados.largura; j++){
                matrizAux[i][j] = matriz[i][j];
            }
        }
        for(i = 0; i < dados.altura; i++){
            for(j = 0; j < dados.largura; j++){
                matriz[j][dados.altura - 1 - i] = matrizAux[i][j];
            }
        }
        
        //printar a matriz e voltar ao menu quando tiver feito todas as rotações
        if(rotacoes == 1){
            printf("\nImagem rotacionada com sucesso!\n");
            for(i = 0; i < dados.altura; i++){
                for(j = 0; j < dados.largura; j++){
                    printf("%d ", matriz[i][j]);
                }
                printf("\n");
            }
            menuP2(dados, matriz);
        }
        else{ //ou rotacionar novamente
            rotacaoP2(dados, matriz, rotacoes - 1);
        }
    }
    else{ //se não for uma matriz quadrada terá que criar uma matriz quadrada para rotacionar
        //comparar altura e largura para criar uma matriz quadrada
        int coordenadaMaior;
        if(dados.altura > dados.largura)
            coordenadaMaior = dados.altura;
        else
            coordenadaMaior = dados.largura;
        int matrizQuad[coordenadaMaior][coordenadaMaior];

        //preencher a matriz quadrada com um valor negativo para diferenciar dos valores da imagem
        int i, j;
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                matrizQuad[i][j] = -1;
            }
        }

        //preencher a matriz quadrada com os valores da imagem
        for (int i = 0; i < dados.altura; i++){
            for (int j = 0; j < dados.largura; j++){
                matrizQuad[i][j] = matriz[i][j];
            }
        }

        //rotacionar a matriz quadrada
        int matrizAux[coordenadaMaior][coordenadaMaior];
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                matrizAux[i][j] = matrizQuad[i][j];
            }
        }
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                matrizQuad[j][coordenadaMaior - 1 - i] = matrizAux[i][j];
            }
        }

        //inverter a altura e largura e criar uma matriz nova com os valores da matriz quadrada
        int aux = dados.altura;
        dados.altura = dados.largura;
        dados.largura = aux;
        int matrizRotacionada[dados.altura][dados.largura];
        int lin=0, col=0;
        for(i = 0; i < coordenadaMaior; i++){
            for(j = 0; j < coordenadaMaior; j++){
                if(matrizQuad[i][j] >= 0){
                    matrizRotacionada[lin][col] = matrizQuad[i][j];
                    col++;
                    if(col == dados.largura){
                        lin++;
                        col = 0;
                    }
                }
            }
        }

        //printar a matriz rotacionada e voltar ao menu quando estiver feito todas as rotações
        if(rotacoes == 1){
            printf("\nImagem rotacionada com sucesso!\n");
            for(i = 0; i < dados.altura; i++){
                for(j = 0; j < dados.largura; j++){
                    printf("%d ", matrizRotacionada[i][j]);
                }
                printf("\n");
            }
            menuP2(dados, matrizRotacionada);
        }
        else{ //ou rotacionar novamente
            rotacaoP2(dados, matrizRotacionada, rotacoes-1);
        }
    }
}

void recorteP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]){
    //ler o canto superior esquerdo e inferior direito da área a ser recortada
    int x1, y1, x2, y2;
    printf("Digite as coordenadas X1 e Y1 (comecando em 0) do canto superior esquerdo da area a ser recortada: ");
    scanf("%d %d", &y1, &x1);
    printf("Digite X2 e Y2 do canto inferior direito da area a ser recortada: ");
    scanf("%d %d", &y2, &x2);

    //verificar se os valores digitados estão dentro da matriz
    if(x1 < 0 || x1 > dados.altura || x2 < 0 || x2 > dados.altura || y1 < 0 || y1 > dados.largura || y2 < 0 || y2 > dados.largura){
        printf("Valores invalidos!\n");
        menuP2(dados, matriz);
    }
    //verificar se o canto superior esquerdo é menor que o inferior direito
    if(x1 > x2 || y1 > y2){
        printf("Valores invalidos!\n");
        menuP2(dados, matriz);
    }

    //recortar a matriz
    int alturaRecorte = x2 - x1 +1;
    int larguraRecorte = y2 - y1 +1;
    int matrizRecorte[alturaRecorte][larguraRecorte];
    int i, j;
    for(i = 0; i < alturaRecorte; i++){
        for(j = 0; j < larguraRecorte; j++){
            matrizRecorte[i][j] = matriz[x1 + i][y1 + j];
        }
    }
 
    //printar a matriz recortada
    printf("\nImagem recortada com sucesso!\n");
    for(i = 0; i < alturaRecorte; i++){
        for(j = 0; j < larguraRecorte; j++){
            printf("%d ", matrizRecorte[i][j]);
        }
        printf("\n");
    }
    
    //atualizar os dados da imagem e retornar ao menu
    dados.altura = alturaRecorte;
    dados.largura = larguraRecorte;
    menuP2(dados, matrizRecorte);
}

void salvarP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]){
    FILE *arq;
    char nomeArquivo[50];
    char extensao[5] = ".pgm";
    printf("Digite o nome ou diretorio que o arquivo .pgm sera salvo: ");
    scanf("%s", nomeArquivo);
    strcat(nomeArquivo, extensao);

    arq = fopen(nomeArquivo, "w"); 
    
    fprintf(arq, "%s", dados.tipo);
    fprintf(arq, "%d %d\n", dados.altura, dados.largura);
    fprintf(arq, "%d\n", dados.max);
    int i, j;
    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            fprintf(arq, "%d ", matriz[i][j]);
        }
        fprintf(arq, "\n");
    }

    fclose(arq);
}

void menuP2(struct dadosArquivo dados, int matriz[dados.altura][dados.largura]){
    int opcao=0;
    printf("\n\nEscolha a opcao desejada:\n 1 - Recortar imagem\n 2 - Transformar em escala de cinza\n 3 - Aplicar filtro greenscreen\n 4 - Rotacionar imagem\n 5 - Sair (salvar imagem)\n");
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            recorteP2(dados, matriz);
            break;
        case 2:
            printf("O formato P2 ja esta em escala de cinza\n");
            menuP2(dados, matriz);
            break;
        case 3:
            greenscreenP2(dados, matriz);
            break;
        case 4:
            printf("Escolha quantos graus rotacionar:\n 1 - 90    2 - 180    3 - 270\n");
            int rotacoes;
            scanf("%d", &rotacoes);
            rotacaoP2(dados, matriz, rotacoes);
            break;
        case 5:
            salvarP2(dados, matriz);
            break;
        default:
            printf("Opcao invalida\n");
            menuP2(dados, matriz);
            break;
    }
}

void lerP2(char tipo[3], FILE *arq){
    //ler os dados do cabeçalho do arquivo na struct
    struct dadosArquivo dados;
    strcpy(dados.tipo, tipo);
    fscanf(arq, "%d %d", &dados.altura, &dados.largura);//pega duas palavras da segunda linha
    printf("Altura: %d, Largura: %d\n", dados.altura, dados.largura);
    fscanf(arq, "%d", &dados.max);//pega a terceira linha
    printf("Valor maximo da cor: %d\n", dados.max);

    int matriz[dados.altura][dados.largura];
    int i, j;
    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            fscanf(arq, "%d", &matriz[i][j]);//ler a matriz	
        }
    }
    fclose(arq);

    for(i = 0; i < dados.altura; i++){
        for(j = 0; j < dados.largura; j++){
            printf("%d ", matriz[i][j]);//printar matriz
        }
        printf("\n");
    }

    menuP2(dados, matriz);
}


///função inicial 
void inicializaArquivo(){
    printf("---Editor de imagens PGM(P2) e PPM(P3)---\n\n\n");
    printf("Digite o nome do arquivo ou o diretorio: ");
    char nome[100];
    scanf("%s", nome);

    FILE *arq = fopen(nome, "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }

    char tipo[3];
    fgets(tipo, 10, arq);//pega a primeira linha inteira
    printf("\nTipo do arquivo: %s", tipo);

    if(!strncmp(tipo, "P2", 2))//strncmp retorna 0 para strings iguais
        lerP2(tipo, arq);
    else if (!strncmp(tipo, "P3", 2)){
        lerP3(tipo, arq);
    }
    else{
        printf("Formato invalido\n");
    }
}

