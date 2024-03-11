#include <stdio.h> // Eu incluo a biblioteca padrão de entrada e saída
#include <stdlib.h> // Eu incluo a biblioteca padrão
#include <sys/types.h> // Eu incluo definições de tipos de dados usados em chamadas de sistema
#include <unistd.h> // Eu incluo constantes e tipos usados em chamadas de sistema POSIX
#include <sys/wait.h> // Eu incluo declarações para esperar

#define BUFFER_SIZE 4 // Eu defino o tamanho do buffer para leitura e escrita

int value = 5; // Eu defino uma variável global 'value' e atribuo a ela o valor 5

int main() { // Aqui começa minha função principal
    pid_t pid; // Eu declaro uma variável 'pid' do tipo pid_t
    int p[2]; // Eu declaro um array 'p' de dois inteiros para uso no pipeline

    if (pipe(p) < 0) { // Eu crio um pipeline e verifico se houve erro na criação
        exit(1); // Se houve erro na criação do pipeline, eu termino o processo
    }

    pid = fork(); // Eu crio um processo filho idêntico ao processo pai e armazeno o PID do processo filho na variável 'pid'

    if (pid == 0) { // Se 'pid' é zero, então este é o processo filho
        close(p[0]); // Eu fecho o descritor de arquivo para leitura (filho)
        printf("Entrei no filho!\n"); // Eu imprimo uma mensagem indicando que este é o processo filho
        value += 15; // Eu adiciono 15 ao valor da variável 'value'
        write(p[1], &value, BUFFER_SIZE); // Eu escrevo o valor da variável 'value' no descritor de arquivo de escrita do pipeline
        close(p[1]); // Eu fecho o descritor de arquivo para escrita (filho)
        printf ("CHILD: value = %d\n",value); // Eu imprimo o valor da variável 'value' no processo filho
        return 0; // Eu retorno 0 para indicar que o processo filho terminou com sucesso
    } 
    else if (pid > 0) { // Se 'pid' é maior que zero, então este é o processo pai
        wait(NULL); // Eu, como processo pai, espero o processo filho terminar
        read(p[0], &value, BUFFER_SIZE); // Eu leio o valor da variável 'value' do descritor de arquivo de leitura do pipeline
        close(p[1]); // Eu fecho o descritor de arquivo para escrita (pai)
        close(p[0]); // Eu fecho o descritor de arquivo para leitura (pai)
        printf ("PARENT: value = %d\n",value); // Eu imprimo o valor da variável 'value' no processo pai
        return 0; // Eu retorno 0 para indicar que o processo pai terminou com sucesso
    }
}

