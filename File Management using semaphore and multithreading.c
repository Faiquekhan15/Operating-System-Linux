#include<string.h>

#include <semaphore.h>

#include <sys/ioctl.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/ipc.h>

#include <sys/sem.h>

#include <stdio.h>

#include <semaphore.h>

#include <stdlib.h>

#include <unistd.h>

int counter1;
int counter2;

int buffer1[2000000];
int buffer2[2000000];

sem_t p1;
sem_t p2;
sem_t p3;
sem_t p4;

struct myfile {
  char * filename;
};

void * process1(void * arg) {
  struct myfile * thread = arg;
  FILE * f1;
  f1 = fopen(thread->filename, "r");
  char ch1;
  if (f1 == NULL) {
    printf("Sorry Unable to open file1\n");
  } else {
    sem_wait(&p1);
    int i = 0;
    while (i < 10) {
      ch1 = fgetc(f1);
      buffer1[counter1] = ch1;
      counter1++;
      sem_post(&p3);
      i++;
    }
  }

}
void * process2(void * arg) {
  struct myfile * thread = arg;
  counter2 = counter1;
  FILE * f2;
  f2 = fopen(thread->filename, "r");
  char ch;
  if (f2 == NULL) {
    printf("Sorry Unable to open file1\n");
  } else {
    for (int z = 0; z < 10; z++) {
      sem_wait(&p2);
    }
    int s = 0;
    while (s < 10) {
      ch = fgetc(f2);
      buffer1[counter2] = ch;
      counter2++;
      sem_post(&p3);
      s++;
    }
  }
}

void * process3(void) {

  for (int o = 0; o < counter2; o++) {
    sem_wait(&p3);
  }
  for (int k = 0; k < counter2; k++) {
    buffer2[k] = buffer1[k];
    sem_post(&p4);
  }
}

void * process4(void) {

  sem_wait(&p4);
  for (int k = 0; k < 40; k++) {
    putchar(buffer2[k]);
  }
  for (int v = 0; v < 10; v++) {
    sem_post(&p2);
  }

}

int main(int args, char ** argv) {
  printf("\n***********FILE MANAGEMENT SYSTEM****** \n");
  printf("\nOutput is\n\n");
  struct myfile thread1;
  struct myfile thread2;
  thread1.filename = argv[1];
  thread2.filename = argv[2];

  pid_t tid1;
  tid1 = fork();

  sem_init(&p1, 0, 10);
  sem_init(&p2, 0, 10);
  sem_init(&p3, 0, 1);
  sem_init(&p4, 0, 1);
  int flag = 1;
  while (flag != 0) {
    if (tid1 > 0) {
      process1(&thread1);
      process2(&thread1);
      process3();
      process4();
    } else {
      tid1 = fork();
    }
    flag = 0;
  }
  sem_destroy(&p1);
  sem_destroy(&p2);
  sem_destroy(&p3);
  sem_destroy(&p4);
  printf("\n");

  return 0;

}
