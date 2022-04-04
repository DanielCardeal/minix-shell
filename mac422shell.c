// Libs padrão
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
// #include <sys/types.h>
// #include <unistd.h>  fork e execve
// #include <sys/wait.h> wait

enum { LIBERA, PROTEGE, RODE, RODEVEJA, COMANDO_INVALIDO };

int traduz_comando(const char comando[]);
void executa_comando(int comando, const char argumento[]);
void executa_chmod(const char permissao_str[4], const char arquivo[]);

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
  case PROTEGE:
    executa_chmod("000", argumento);
    break;
  case LIBERA:
    executa_chmod("777", argumento);
    break;
  default:
    printf("ERRO: COMANDO NÃO IMPLEMENTADO AINDA!!!\n");
    break;
  }
}

/**
 * Altera as permissões de `arquivo` baseado em uma string de permissões no
 * padrão do comando *chmod* (p. exe. "755").
 */
void executa_chmod(const char permissao_str[4], const char arquivo[]) {
  const mode_t permissao = strtol(permissao_str, 0, 8);
  chmod(arquivo, permissao);
}
