#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    //Verifica se o número de argumentos está correto
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_diretorio>\n", argv[0]);
        return EXIT_FAILURE;
    }

    //Obtém o nome do diretório a partir dos argumentos de linha de comando
    char *nome_diretorio = argv[1];

    //Chama a função mkdir() para criar o diretório com o nome fornecido
    if (mkdir(nome_diretorio, 0777) == -1) {
        //Em caso de erro, exibe uma mensagem de erro
        perror("Erro ao criar diretório");
        return EXIT_FAILURE;
    } else {
        //Se o diretório foi criado com sucesso, exibe uma mensagem de sucesso
        printf("Diretório \"%s\" criado com sucesso.\n", nome_diretorio);
        return EXIT_SUCCESS;
    }
}
