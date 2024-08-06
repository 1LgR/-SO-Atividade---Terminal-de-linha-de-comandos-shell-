#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    //Verifica se o número de argumentos está correto
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_origem> <arquivo_destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //Define os nomes dos arquivos de origem e destino
    const char *sourcefn = argv[1];
    const char *targetfn = argv[2];

    //Abre o arquivo de origem para leitura
    int source = open(sourcefn, O_RDONLY);
    if (source == -1) {
        perror("Erro ao abrir o arquivo de origem");
        exit(EXIT_FAILURE);
    }

    //Verifica se o arquivo de origem pode ser lido
    if (access(sourcefn, R_OK) == -1) {
        perror("Arquivo de origem não pode ser lido");
        close(source);
        exit(EXIT_FAILURE);
    }

    //Verifica se o arquivo de destino já existe
    if (access(targetfn, F_OK) != -1) {
        fprintf(stderr, "O arquivo destino já existe\n");
        close(source);
        exit(EXIT_FAILURE);
    }

    //Abre o arquivo de destino para escrita, criando-o se não existir
    int target = open(targetfn, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (target == -1) {
        perror("Erro ao abrir o arquivo de destino");
        close(source);
        exit(EXIT_FAILURE);
    }

    //Verifica se o arquivo de destino pode ser escrito
    if (access(targetfn, W_OK) == -1) {
        perror("O arquivo destino não possui permissão de escrita");
        close(source);
        close(target);
        exit(EXIT_FAILURE);
    }

    //Define um buffer para armazenar os dados a serem copiados
    char buf[1024];
    int s;

    //Lê o conteúdo do arquivo de origem e escreve no arquivo de destino
    while ((s = read(source, buf, 1024)) != 0) {
        if (s == -1) {
            perror("Erro ao ler o arquivo de origem");
            close(source);
            close(target);
            exit(EXIT_FAILURE);
        }

        if (write(target, buf, s) == -1) {
            perror("Erro ao escrever no arquivo de destino");
            close(source);
            close(target);
            exit(EXIT_FAILURE);
        }
    }

    //Fecha os arquivos
    close(source);
    close(target);

    return 0;
}
