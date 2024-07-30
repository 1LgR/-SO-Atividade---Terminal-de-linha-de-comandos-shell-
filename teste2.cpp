#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>

void process_command(std::string command) {
    // Se for comando interno...
    if (command == "exit")
        exit(0);

    if (command == "pwd") {
        char buffer[1024];
        getcwd(buffer, 1024);
        std::cout << buffer << std::endl;
        return;
    }

    if (command.substr(0, 2) == "cd") {
        std::string path = command.substr(3);
        if (chdir(path.c_str()) != 0) {
            std::cout << "cd: no such file or directory: " << path << std::endl;
        }
        return;
    }

    std::vector<char*> args;
    char *cstr = new char[command.length() + 1];
    std::strcpy(cstr, command.c_str());
    
    char *token = std::strtok(cstr, " ");
    while (token != nullptr) {
        args.push_back(token);
        token = std::strtok(nullptr, " ");
    }
    args.push_back(nullptr);

    std::string absolute_path = "./" + std::string(args[0]); 
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
