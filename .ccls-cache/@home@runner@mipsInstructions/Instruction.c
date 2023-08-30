/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Instruction{
  char *principalIns;
  char *memDir1;
  char *memDir2;
  char *memDir3;
};

struct Instruction* crearInstruccion(char* instructionString){
  struct Instruction* ins = (struct Instruction*)malloc(sizeof(struct Instruction));
  char delimitador[] = " ";
  ins -> principalIns = strtok(instructionString, delimitador);
  ins -> memDir1 = strtok(NULL, delimitador);
  ins -> memDir2 = strtok(NULL, delimitador);
  ins -> memDir3 = strtok(NULL, delimitador);
  return ins;
}

void mostrarIn(const struct Instruction* ins){
  if(ins != NULL){
    printf("instruccion: %s\n", ins->principalIns);
    printf("Dirección Memoria 1: %s\n", ins->memDir1);
    printf("Dirección Memoria 2: %s\n", ins->memDir2);
    printf("Dirección Memoria 3: %s\n", ins->memDir3);
  }
}
*/
