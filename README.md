# -SO-Atividade---Terminal-de-linha-de-comandos-shell-
<br>

## Shell
<h3>Uma shell é um programa que fornece uma interface para o usuário interagir com o sistema operacional. Ela permite que os usuários executem comandos, programas e scripts, além de gerenciar arquivos e processos.</h3>

<hr>

### Comando externos
<p> Feitos no trabalho de chamadas de sistema, caso queira ler o readme das chamadas de sistemas:</p> 

1. [Chamadas de Sistemas](./Comandos%20externos/Comando.md)

## Modificações:
### Parte 1:
<h4>Tokenização: Para a shell começar a reconhecer os parâmetros passados para os executaveis do comandos externos, e para os comando internos, eu precisei fazer a tokenização da entrada, nesse caso eu criei um vetor para armazenar a entrada, e usando a função strtok eu separo o comando no vetor por espaços, então a cada espaço era armazenado uma string nova no vetor, assim, o primeiro valor do vetor seria o comando, e o restante seria os parâmetros.</h4>

### Parte 2:
<h4>Com a tokenização feita eu comecei a fazer os comandos internos.</h4>

## Comando internos:

### Exit:
<h4>Sai da bash usando a função exit.</h4>

### echo:
<h4>Imprime o primeiro parâmetro passado após o comando.</h4>

### pwd:
<h4>Adquire o diretorio atual de trabalho, primeiro cria-se um buffer para armazenar o diretorio, e depois armazela ele usando a função getcwd, após isso é só imprimir o buffer.</h4>

### cd:
<h4>Muda o diretório de trabalho atual. Recebe o caminho para o novo diretório como parâmetro. Se o diretório não existir ou não for acessível, exibe uma mensagem de erro.</h4>

### path:
<h4>Define ou exibe o caminho de diretórios usados para buscar executáveis. Ao definir um novo caminho, ele substitui o caminho atual. O valor pode ser especificado após o comando.</h4>

### history:
<h4>Exibe a lista de comandos anteriomente executados. Se passado o parâmetro "-c", limpa o histórico. Também permite a execução de um comando específico do histórico, usando um número associado ao comando.</h4>

### Parte 3:
<h4>Modifiquei a executação de comandos externos para ler os argumentos com base no vetor, dessa forma recuperando os parâmetros para acionar os comandos externos. Além disso, o execve busca o primeiro argumento digitado para juntar ao Path, dessa forma iniciando o executavel do comando, após isso usando a função data, o execve pega os parâmetros para executar o programa.</h4>
<hr>

## Conclusão:

<h4>O desenvolvimento da shell envolveu a implementação de funcionalidades básicas e a integração de comandos internos essenciais. Com a tokenização da entrada, foi possível separar comandos e parâmetros de forma eficiente. A adição de comandos internos como 'cd', 'path' e 'history' ampliou a funcionalidade da shell, permitindo navegação entre diretórios, manipulação do caminho de busca para executáveis e gerenciamento do histórico de comandos. As modificações na execução de comandos externos garantiram que argumentos fossem corretamente passados para os programas executáveis. Dessa forma, foi possivel fazer uma shell funcional, e com isso adiquiri bastante conhecimento, e entendimento de como uma shell funciona. </h4>