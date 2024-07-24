#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    //Verifica se o número de argumentos está correto
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_diretorio>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Obtém o nome do diretório a partir dos argumentos de linha de comando
    char *nome_diretorio = argv[1];

    //Chama a função mkdir() para criar o diretório com o nome fornecido pelo usuário
    int resultado = rmdir(nome_diretorio);
    if (resultado == -1) {
        perror("Erro ao remover arquivo");
        exit(EXIT_FAILURE);
    } else {
        //Se o diretório foi criado com sucesso, exibe uma mensagem de sucesso
        printf("Diretório \"%s\" apagado com sucesso.\n", nome_diretorio);
    }

    return 0;
}
