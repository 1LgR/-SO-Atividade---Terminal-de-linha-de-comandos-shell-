#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    //Verifica se foi fornecido o nome do arquivo como argumento
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //Obtém o nome do arquivo a ser removido
    char *nome_do_arquivo = argv[1];

    //Remove o arquivo especificado, usando a chamada de sistema unlink
    int resultado = unlink(nome_do_arquivo);
    if (resultado == -1) {
        perror("Erro ao remover arquivo");
        exit(EXIT_FAILURE);
    }

    printf("Arquivo %s removido com sucesso.\n", nome_do_arquivo);

    return 0;
}
