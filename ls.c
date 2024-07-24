#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //Definir o diretório a ser listado
    char *dir;
    if (argc == 1) {
        //Se nenhum diretório for especificado, use o diretório atual
        dir = getcwd(NULL, 0);
        if (dir == NULL) {
            perror("Erro ao obter diretório atual");
            exit(EXIT_FAILURE);
        }
    } else {
        dir = argv[1];
    }

    //Abrir o diretório
    DIR *dp = opendir(dir);
    if (dp == NULL) {
        perror("Erro ao abrir diretório");
        exit(EXIT_FAILURE);
    }

    //Ler e imprimir os nomes dos arquivos no diretório
    struct dirent *entrada;
    while ((entrada = readdir(dp)) != NULL) {
        if (strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0) {
            printf("%s ", entrada->d_name);
        }
    }
    printf("\n");

    //Fechar o diretório
    closedir(dp);

    /*Liberar memória alocada para o nome do diretório. Isso acontece 
    por que a função getcwd() para obter o diretório atual em um programa C,
    pode alocar dinamicamente memória para armazenar o caminho do diretório atual.*/
    if (argc == 1) {
        free(dir);
    }

    return 0;
}
