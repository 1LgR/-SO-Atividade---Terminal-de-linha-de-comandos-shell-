#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 4096  //Tamanho do buffer de leitura

int main(int argc, char *argv[]) {
    //Verifica se o número de argumentos está correto
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo1> [<arquivo2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //Buffer de leitura
    char buf[BUF_SIZE];

    /*for para ler desde o segundo arquivo 
    (porque o primeiro é sempre o nome do programa). 
    Ele vai até o final da lista de arquivos.*/
    for (int i = 1; i < argc; i++) {
        //Abre o arquivo atual para leitura
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            perror("Erro ao abrir arquivo");
            exit(EXIT_FAILURE);
        }

        //Lê e exibe o conteúdo do arquivo
        ssize_t bytes_lidos;
        while ((bytes_lidos = read(fd, buf, BUF_SIZE)) > 0) {
            //Escreve o conteúdo lido no stdout
            buf[bytes_lidos] = '\0'; // Adiciona o caractere nulo para garantir que o buffer seja tratado como uma string
            printf("%s", buf);
        }

        //Verifica erros de leitura
        if (bytes_lidos == -1) {
            perror("Erro ao ler arquivo");
            exit(EXIT_FAILURE);
        }

        //Fecha o arquivo
        if (close(fd) == -1) {
            perror("Erro ao fechar arquivo");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
