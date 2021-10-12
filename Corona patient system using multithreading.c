#include<string.h>

#include <pthread.h>

#include <sys/ioctl.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/ipc.h>

#include <sys/syscall.h>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>


int Corona_patient_count = 0;
int Flue_patient_count = 0;

int recover = 0;
int flue = 0;
int effected = 0;

struct ownthread {
  pthread_mutex_t mutex;
  pthread_cond_t condition;
  pid_t id;
  int state;
};

void * Flue_patient(void * arg) {
  Flue_patient_count++;
  flue++;
  struct ownthread * thread1 = arg;
  pthread_mutex_lock( & thread1 -> mutex);
  thread1 -> id = syscall(SYS_gettid);
  printf("He is a Flue patient \n");
  thread1 -> state = 1;
  pthread_cond_signal( & thread1 -> condition);
  pthread_mutex_unlock( & thread1 -> mutex);
  return NULL;
}

void * Corona_patient(void * arg) {
  Corona_patient_count++;

  struct ownthread * thread2 = arg;
  pthread_mutex_lock( & thread2 -> mutex);
  thread2 -> id = 0;
  thread2 -> id = syscall(SYS_gettid);

  if (rand() % 2 == 0) {
    printf("He is Suffering From Corona\n");
    printf("The patient is Tested Again For Corona\n");
    if (rand() % 2 == 0) {
      effected++;

      printf("Case Positive :: Notrecovered\n");
    } else {
      recover++;
      printf("Case Negative :: Recovered\n");
    }
  } else {
    printf("He is Not Suffering From Corona\n");
    printf("The patient is Tested Again For Corona\n");
    if (rand() % 2 == 0) {
      printf("Case Negative :: Not a Corona patient\n");
      flue++;
    } else {
      effected++;
      printf("Case postive :: Corona Patient\n");
    }
  }
  thread2 -> state = 1;
  pthread_cond_signal( & thread2 -> condition);
  pthread_mutex_unlock( & thread2 -> mutex);
  return NULL;

}
int main() {
  int input;

  pthread_t tid;
  struct ownthread thread;
  pthread_cond_init( & thread.condition, NULL);
  pthread_mutex_init( & thread.mutex, NULL);
  printf("((((((********************************))))))\n");
  printf("((((((***********COVID-19*************))))))\n");
  printf("((((((*******ManagementSystem*********))))))\n");
  printf("((((((********************************)))))\n\n");

  printf("Enter Number of Patients Enter in Hospital for Corona Test \n");
  scanf("%d", & input);
  for (int i = 0; i < input; i++) {
    int j = rand() % 2;
    if (j == 0) {
      pthread_mutex_lock( & thread.mutex);
      thread.state = 0;
      pthread_create( & tid, NULL, & Flue_patient, & thread);
    } else if (j == 1) {
      pthread_mutex_lock( & thread.mutex);
      thread.state = 0;
      pthread_create( & tid, NULL, & Corona_patient, & thread);

    } else {
      while (!thread.state) {
        pthread_cond_wait( & thread.condition, & thread.mutex);
      }
    }
    printf("\nPatient ID =%d\n", thread.id);
    pthread_mutex_unlock( & thread.mutex);
    pthread_join(tid, NULL);

  }

  pthread_mutex_destroy( & thread.mutex);
  pthread_cond_destroy( & thread.condition);

  printf("\n\t(**Overall evaluation Report**)\n");

  printf("\nNumber of the total patient =%d\n", Flue_patient_count + Corona_patient_count);

  printf("\nNumber of carona patient =%d\n", Corona_patient_count);
  printf("\nNumber of flue patient =%d\n", Flue_patient_count);
  printf("\nNumber of  patient Still infected =%d\n", effected);

  printf("\nNumber of  potecial patient =%d\n", (recover + flue));

}
