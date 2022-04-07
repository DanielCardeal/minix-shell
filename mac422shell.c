/*
** EP1 - MAC422
** ------------
** Nome: Daniel Pessoa Cardeal, NUSP: 10693170
** Nome: Caio Danta Simão Ugeda, NUSP: 11796868
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROTEGE 1
#define LIBERA 2
#define RODE 3
#define RODEVEJA 4
#define COMANDO_INEXISTENTE 5

int traduz_comando(char comando[]);
void executa_comando(int comando, char argumento[]);
void executa_chmod(char permissao_str[4], char arquivo[]);
void executa_e_espera(char executavel[]);
void executa_e_sai(char executavel[]);

int main(int argc, char **argv) {
  char input_cmd[64], input_arg[64];
  int cmd;

  while (1) {
    printf("$ ");
    scanf("%s", input_cmd);
    scanf("%s", input_arg);
    cmd = traduz_comando(input_cmd);
    executa_comando(cmd, input_arg);
  }

  return (0);
}

/**
 * Transforma a string recebida em um identificador de comando. Caso a string
 * não seja referente a nenhum dos comandos conhecidos pelo programa, o
 * identificador obtido será `COMANDO_INVALIDO`.
 */
int traduz_comando(char comando[]) {
  if (strcmp(comando, "protegepracaramba") == 0)
    return PROTEGE;
  else if (strcmp(comando, "liberageral") == 0)
    return LIBERA;
  else if (strcmp(comando, "rodeveja") == 0)
    return RODEVEJA;
  else if (strcmp(comando, "rode") == 0)
    return RODE;
  else
    return COMANDO_INEXISTENTE;
}

/**
 * Executa `comando` usando como argumento a string armazenada em `argumento`.
 */
void executa_comando(int comando, char argumento[]) {
  switch (comando) {
  case PROTEGE:
    executa_chmod("000", argumento);
    break;
  case LIBERA:
    executa_chmod("777", argumento);
    break;
  case RODEVEJA:
    executa_e_espera(argumento);
    break;
  case RODE:
    executa_e_sai(argumento);
    break;
  default:
    printf("ERRO: COMANDO INVÁLIDO\n");
    break;
  }
}

/**
 * Altera as permissões de `arquivo` baseado em uma string de permissões no
 * padrão do comando *chmod* (p. exe. "755").
 */
void executa_chmod(char permissao_str[4], char arquivo[]) {
  mode_t permissao;
  permissao = strtol(permissao_str, 0, 8);
  chmod(arquivo, permissao);
}

/**
 * Executa o arquivo apontado por `executável` sincronamente. Escreve na tela o
 * status de saída do programa.
 */
void executa_e_espera(char executavel[]) {
  int pid, stat;
  pid = fork();
  if (pid != 0) {
    waitpid(pid, &stat, 0);
    printf("\nPROCESSO RETORNOU COM STATUS %d\n", stat);
  } else {
    execve(executavel, NULL, NULL);
  }
}

/**
 * Executa o arquivo apontado por `executável` assincronamente.
 */
void executa_e_sai(char executavel[]) {
  int pid, stat;
  pid = fork();
  if (pid == 0) {
    close(0);
    execve(executavel, NULL, NULL);
  }
}
