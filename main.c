#include "coffee.h"
#include <pthread.h>
#include <stdio.h>

#define NUM_BARISTAS 3

extern void *manager_A(void *arg);
extern void *barista_A(void *arg);

int main() {
  coffee_grinder *grinder = create_grinder();

  pthread_t manager_thread;
  pthread_t barista_thread[NUM_BARISTAS];

  pthread_create(&manager_thread, NULL, manager_A, grinder);
  for (int i = 0; i < NUM_BARISTAS; i++) {
    pthread_create(&barista_thread[i], NULL, barista_A, grinder);
  }

  pthread_join(manager_thread, NULL);
  for (int i = 0; i < NUM_BARISTAS; i++) {
    pthread_join(barista_thread[i], NULL);
  }

  destroy_grinder(grinder);
  return 0;
}
