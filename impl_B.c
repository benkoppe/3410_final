#include "coffee.h"
#include <pthread.h>
#include <unistd.h>

void *manager_B(void *arg) {
  coffee_grinder *grinder = (coffee_grinder *)arg;

  for (int i = 0; i < MAX_REFILLS; i++) {
    pthread_mutex_lock(grinder->mutex);
    int full = grinder->beans == CAPACITY;
    pthread_mutex_unlock(grinder->mutex);

    pthread_mutex_lock(grinder->mutex);
    while (full) {
      pthread_mutex_unlock(grinder->mutex);
      pthread_mutex_lock(grinder->mutex);
      full = grinder->beans == CAPACITY;
    }
    grinder->beans += BEANS_PER_CUP;
    pthread_mutex_unlock(grinder->mutex);
  }
  pthread_mutex_lock(grinder->mutex);
  grinder->closed = 1;
  pthread_mutex_unlock(grinder->mutex);
  return NULL;
}

void *barista_B(void *arg) {
  coffee_grinder *grinder = (coffee_grinder *)arg;

  while (1) {
    pthread_mutex_lock(grinder->mutex);
    int empty_and_open = grinder->beans == 0 && !grinder->closed;
    pthread_mutex_unlock(grinder->mutex);

    pthread_mutex_lock(grinder->mutex);
    while (empty_and_open) {
      pthread_mutex_unlock(grinder->mutex);
      pthread_mutex_lock(grinder->mutex);
      empty_and_open = grinder->beans == 0 && !grinder->closed;
    }
    if (grinder->closed) {
      break;
    }
    grinder->beans -= BEANS_PER_CUP;
    pthread_mutex_unlock(grinder->mutex);
  }

  return NULL;
}
