#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int traduz_comando(char comando[]);
void executa_comando(int comando, char argumento[]);
void executa_chmod(char permissao_str[4], char arquivo[]);
void executa_main_thread(char executavel[]);

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
    return 1;
  else if (strcmp(comando, "liberageral") == 0)
    return 2;
  else if (strcmp(comando, "rodeveja") == 0)
    return 3;
  else if (strcmp(comando, "rode") == 0)
    return 4;
  else
    return 5;
}

/**
 * Executa `comando` usando como argumento a string armazenada em `argumento`.
 */
void executa_comando(int comando, char argumento[]) {
  switch (comando) {
  case 1:
    executa_chmod("000", argumento);
    break;
  case 2:
    executa_chmod("777", argumento);
    break;
  case 3:
    executa_main_thread(argumento);
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
void executa_chmod(char permissao_str[4], char arquivo[]) {
  mode_t permissao;
  permissao = strtol(permissao_str, 0, 8);
  chmod(arquivo, permissao);
}

void executa_main_thread(char executavel[]){
  int pid, stat;
  pid = fork();
  if(pid != 0) { /* pai */
    waitpid(pid, &stat, 0);
    printf("\n PROCESSO RETORNOU COM STATUS %d", stat);
  }
  else { /* filho */  
     execve(executavel, NULL, NULL); /* passamos um arquivo binário sem argumentos */
  }
}
