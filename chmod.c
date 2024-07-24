#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <permissões_octal> <arquivo/diretorio> \n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[2]; // Caminho do arquivo/diretório
    mode_t mode = (mode_t) strtol(argv[1], NULL, 8); // Permissões em octal

    if (chmod(path, mode) == -1) {
        perror("Erro ao alterar permissões");
        return EXIT_FAILURE;
    } else {
        printf("Permissões de %s alteradas para %o\n", path, mode);
        return EXIT_SUCCESS;
    }
}
