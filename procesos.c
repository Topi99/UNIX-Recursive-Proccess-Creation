#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*----------------------------------------------------------------

*

* Programación avanzada: Manejo de procesos

* Fecha: 31 - Marzo - 2020

* Autor: A01703266 Topiltzin Hernández Mares
         A01703280 Carlos Alfonso Sánchez Rosales

*

*--------------------------------------------------------------*/

int crearProcesos(int, int);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("usage: %s number", argv[0]);
    return -2;
  }

  if (atoi(argv[1]) <= 0 || (atof(argv[1]) - atoi(argv[1])) != 0 ) {
    printf("%s: the parameter must be a positive integer number", argv[0]);
    return -3;
  }

  crearProcesos(0, atoi(argv[1]));

  return 0;
}

int crearProcesos(int actual, int hasta) {
  // Caso base
  if (actual - 1 == hasta) {
    return 1;
  }

  // Imprimimos identación
  for (int i = 0; i < actual; i++) {
    printf(" ");
  }

  // Imprime información
  printf("PPID = %i PID = %i NIVEL = %i\n", getppid(), getpid(), actual);

  // Dormimos un segundo
  sleep(1);

  // Creamos procesos hijos
  for (int i = 0; i <= actual; i++) {
    // Creamos nuevo procso
    int pid;
    if ( (pid = fork()) < 0) {
      perror("fork");
      return -3;
    }

    if (pid == 0) {
      // Llamamos recursivamente
      crearProcesos(actual + 1, hasta);
      exit(0);
    } else {
      // Esperamos a que termine el proceso hijo
      wait(NULL);
    }
  }

  return 0;
}