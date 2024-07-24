#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>

//determinar o tamanho do buffer utilizado para armazenar os dados lidos do arquivo /proc/uptime
#define BUF_SIZE 128

int main() {

    //Utilizando o codigo do date para adquirir o horário atual
    struct timespec current_time;

    clock_gettime(CLOCK_REALTIME, &current_time);

    time_t atual = current_time.tv_sec;
    struct tm *tm_info;
    tm_info = localtime(&atual);

    //Estrutura para adquirir informações do sistema
    struct sysinfo info;

    //Obtém as informações do sistema
    if (sysinfo(&info) != 0) {
        perror("Erro ao obter informações do sistema");
        exit(EXIT_FAILURE);
    }
    /*Criação de variaveis de armazenamento e uma matriz, a fd é uma variavel 
    que será usada para armazenar o descritor de arquivo retornado pela função 
    open, a buf é uma matriz para armazenar os dados lidos do arquivo, e variavel 
    uptime  será usada para armazenar o tempo de atividade do sistema lido do arquivo 
    /proc/uptime*/
    int fd;
    char buf[BUF_SIZE];
    double uptime_segundos;

    //Abre o arquivo /proc/uptime para leitura
    fd = open("/proc/uptime", O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo /proc/uptime");
        exit(EXIT_FAILURE);
    }

    //Lê os valores de tempo total de atividade e tempo de ociosidade do sistema
    ssize_t ler_bytes = read(fd, buf, BUF_SIZE);
    if (ler_bytes == -1) {
        perror("Erro ao ler os valores de tempo de atividade e tempo ocioso");
        close(fd);
        exit(EXIT_FAILURE);
    }

    //Fecha o arquivo após a leitura dos valores
    close(fd);

    //Extrai os valores de tempo de atividade do sistema
    char *token = strtok(buf, " ");
    if (token == NULL) {
        perror("Erro ao extrair os valores de tempo de atividade e tempo ocioso");
        exit(EXIT_FAILURE);
    }
    uptime_segundos = atof(token);

    //Calcula o tempo de atividade em horas, minutos e segundos
    int horas = (int)uptime_segundos / 3600;
    int minutos = ((int)uptime_segundos % 3600) / 60;

    //Imprime o tempo de atividade no formato padrão do comando uptime
    printf(" %02d:%02d:%02d up %2d:%02d,  0 users,  load average: %.2f, %.2f, %.2f\n", 
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, horas, minutos, 
           info.loads[0] / (float)(1 << SI_LOAD_SHIFT),
           info.loads[1] / (float)(1 << SI_LOAD_SHIFT),
           info.loads[2] / (float)(1 << SI_LOAD_SHIFT));

    return 0;
}
