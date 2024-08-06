#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>
#include <sstream>

std::string PATH = "./Comandos externos/";
std::vector<std::string> comando_history;

void process_command(std::string command);

void executar_history(size_t command_index) {
    if (command_index >= 1 && command_index <= comando_history.size()) {
        process_command(comando_history[command_index - 1]);
    } else {
        std::cerr << "history: numero de comando invalido: " << command_index << std::endl;
    }
}

void process_command(std::string command) {
    comando_history.push_back(command);

    std::vector<char*> args;
    char *cstr = new char[command.length() + 1];
    std::strcpy(cstr, command.c_str());
    char *token = std::strtok(cstr, " ");
    while (token != nullptr) {
        args.push_back(token);
        token = std::strtok(nullptr, " ");
    }
    args.push_back(nullptr);

    if (args.empty()) {
        delete[] cstr;
        return;
    }

    // Comandos internos
    if (std::string(args[0]) == "exit") {
        delete[] cstr;
        exit(0);
    }
    
    if (std::string(args[0]) == "echo") {
        std::cout << args[1] << std::endl;
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "pwd") {
        char buffer[1024];
        getcwd(buffer, 1024);
        std::cout << buffer << std::endl;
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "cd") {
        if (args[1] != nullptr) {
            if (chdir(args[1]) != 0) {
                std::cerr << "cd: arquivo ou diretorio nao encontrado: " << args[1] << std::endl;
            }
        } else {
            std::cerr << "cd: faltando argumento" << std::endl;
        }
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "PATH") {
        if (args[1] != nullptr) {
            PATH = args[1];
            std::cout << "PATH atualizado para: " << PATH << std::endl;
        } else {
            std::cerr << "PATH: faltando argumento" << std::endl;
        }
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "history") {
        if (args[1] == nullptr) {
            for (size_t i = 0; i < comando_history.size(); ++i) {
                std::cout << i + 1 << ": " << comando_history[i] << std::endl;
            }
        } else if (std::string(args[1]) == "-c") {
            comando_history.clear();
            std::cout << "History limpo." << std::endl;
        } else {
            try {
                size_t command_index = std::stoi(args[1]);
                executar_history(command_index);
            } catch (std::invalid_argument&) {
                std::cerr << "history: argumento invalido: " << args[1] << std::endl;
            }
        }
        delete[] cstr;
        return;
    }

    // Tentar executar o comando externo
    std::string absolute_path = PATH + "/" + std::string(args[0]);
    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            pid_t pid = fork();
            if (pid < 0) { // Erro
                std::cerr << "Erro de execução!" << std::endl;
                delete[] cstr;
                return;
            } else if (pid == 0) { // Processo filho
                execve(absolute_path.c_str(), args.data(), nullptr);
                // Se execve falhar
                std::cerr << "Erro ao executar o comando." << std::endl;
                exit(1);
            } else { // Processo pai
                waitpid(pid, nullptr, 0);
            }
        } else { // Arquivo não é executável
            std::cerr << "permissao negada: " << args[0] << std::endl;
        }
    } else { // Arquivo não existe
        std::cerr << "Comando nao encontrado: " << args[0] << std::endl;
    }

    delete[] cstr;
}

int main() {
    while (true) {
        std::cout << "$> ";
        std::string command;
        getline(std::cin, command);
        process_command(command);
    }
    return 0;
}
