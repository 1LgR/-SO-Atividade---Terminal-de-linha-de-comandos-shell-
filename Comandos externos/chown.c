#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <novo_proprietario> <novo_grupo> <arquivo/diretorio> \n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[3]; // Caminho do arquivo/diretório
    uid_t owner = (uid_t) atoi(argv[1]); // Novo ID do proprietário
    gid_t group = (gid_t) atoi(argv[2]); // Novo ID do grupo

    if (chown(path, owner, group) == -1) {
        perror("Erro ao alterar proprietário/grupo");
        return EXIT_FAILURE;
    } else {
        printf("Proprietário/grupo de %s alterado para %d/%d\n", path, owner, group);
        return EXIT_SUCCESS;
    }
}
