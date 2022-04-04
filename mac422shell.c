// Libs padrão
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// #include <stdlib.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <unistd.h>  fork e execve
// #include <sys/wait.h> wait

enum { LIBERA, PROTEGE, RODE, RODEVEJA, COMANDO_INVALIDO };

int traduz_comando(const char comando[]);
void executa_comando(int comando, const char argumento[]);

int main() {
  char input_cmd[64], input_arg[64];

  while (true) {
    printf("$ ");
    scanf("%s", input_cmd);
    scanf("%s", input_arg);
    const int cmd = traduz_comando(input_cmd);
    executa_comando(cmd, input_arg);
  }

  return (0);
}

/**
 * Transforma a string recebida em um identificador de comando. Caso a string
 * não seja referente a nenhum dos comandos conhecidos pelo programa, o
 * identificador obtido será `COMANDO_INVALIDO`.
 */
int traduz_comando(const char comando[]) {
  if (strcmp(comando, "protegepracaramba") == 0)
    return PROTEGE;
  else if (strcmp(comando, "liberageral") == 0)
    return LIBERA;
  else if (strcmp(comando, "rode") == 0)
    return RODE;
  else if (strcmp(comando, "rodeveja") == 0)
    return RODEVEJA;
  else
    return COMANDO_INVALIDO;
}

/**
 * Executa `comando` usando como argumento a string armazenada em `argumento`.
 */
void executa_comando(int comando, const char argumento[]) {
  switch (comando) {
  default:
    printf("ERRO: COMANDO NÃO IMPLEMENTADO AINDA!!!\n");
    break;
  }
}
