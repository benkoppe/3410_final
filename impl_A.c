#include "coffee.h"
#include <pthread.h>
#include <unistd.h>

void *manager_A(void *arg) {
  coffee_grinder *grinder = (coffee_grinder *)arg;

  for (int i = 0; i < MAX_REFILLS; i++) {
    pthread_mutex_lock(grinder->mutex);
    while (grinder->beans == CAPACITY) {
      pthread_cond_wait(grinder->full_cv, grinder->mutex);
    }
    grinder->beans += BEANS_PER_CUP;
    pthread_mutex_unlock(grinder->mutex);
    pthread_cond_signal(grinder->empty_cv);
  }
  pthread_mutex_lock(grinder->mutex);
  grinder->closed = 1;
  pthread_mutex_unlock(grinder->mutex);

  return NULL;
}

void *barista_A(void *arg) {
  coffee_grinder *grinder = (coffee_grinder *)arg;

  while (1) {
    pthread_mutex_lock(grinder->mutex);
    while (grinder->beans == 0 && !grinder->closed) {
      pthread_cond_wait(grinder->empty_cv, grinder->mutex);
    }
    if (grinder->closed) {
      pthread_mutex_unlock(grinder->mutex);
      break;
    }
    grinder->beans -= BEANS_PER_CUP;
    pthread_mutex_unlock(grinder->mutex);
    pthread_cond_signal(grinder->full_cv);
  }

  return NULL;
}
