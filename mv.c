#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //Verifica se o número de argumentos está correto
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //Obtém os nomes dos arquivos de origem e destino
    char *arquivo_origem = argv[1];
    char *arquivo_destino = argv[2];

    /*Renomeia o arquivo de origem para o nome do arquivo de destino, utilizando a
    chamada de sistema rename*/
    int resultado = rename(arquivo_origem, arquivo_destino);
    if (resultado == -1) {
        perror("Erro ao renomear arquivo");
        exit(EXIT_FAILURE);
    }

    printf("Arquivo %s renomeado para %s com sucesso.\n", arquivo_origem, arquivo_destino);

    return 0;
}
