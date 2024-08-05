#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

std::string PATH = "./";

void process_command(std::string command) {
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
                std::cout << "cd: no such file or directory: " << args[1] << std::endl;
            }
        } else {
            std::cout << "cd: missing argument" << std::endl;
        }
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "PATH") {
        if (args[1] != nullptr) {
            PATH = args[1];
        } else {
            std::cerr << "PATH: missing argument" << std::endl;
        }
        delete[] cstr;
        return;
    }

    if (std::string(args[0]) == "history") {
        for (size_t i = 0; i < command_history.size(); ++i) {
            std::cout << i + 1 << ": " << command_history[i] << std::endl;
        }
        delete[] cstr;
        return;
    }

    std::string absolute_path = PATH + std::string(args[0]); 
    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            pid_t pid = fork();
            if (pid < 0) { // Erro
                std::cout << "Erro de execução!" << std::endl;
                delete[] cstr;
                return;
            } else if (pid == 0) { // Processo filho
                execve(absolute_path.c_str(), args.data(), NULL);
            } else { // Processo pai
                // Deve adicionar processo filho na lista (std::vector) 
                // de processos em execução para gerenciar background.
                // Processo pai espera processo filho terminar.
                waitpid(pid, nullptr, 0);
            }
        } else { // Arquivo não é executável
            std::cout << "permission denied: " << args[0] << std::endl;
        }
    } else { // Arquivo não existe
        std::cout << "Command not found: " << args[0] << std::endl;
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
