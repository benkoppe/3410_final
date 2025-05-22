#include "coffee.h"
#include <pthread.h>
#include <stdio.h>

#define NUM_BARISTAS 300

extern void *MANAGER_FUNC(void *arg);
extern void *BARISTA_FUNC(void *arg);

int main() {
  coffee_grinder *grinder = create_grinder();

  pthread_t manager_thread;
  pthread_t barista_thread[NUM_BARISTAS];

  pthread_create(&manager_thread, NULL, MANAGER_FUNC, grinder);
  for (int i = 0; i < NUM_BARISTAS; i++) {
    pthread_create(&barista_thread[i], NULL, BARISTA_FUNC, grinder);
  }

  pthread_join(manager_thread, NULL);
  for (int i = 0; i < NUM_BARISTAS; i++) {
    pthread_join(barista_thread[i], NULL);
  }

  destroy_grinder(grinder);
  return 0;
}
