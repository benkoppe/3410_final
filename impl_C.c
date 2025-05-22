#include "coffee.h"
#include <pthread.h>
#include <unistd.h>

void *manager_C(void *arg) {
  coffee_grinder *grinder = (coffee_grinder *)arg;

  for (int i = 0; i < MAX_REFILLS; i++) {
    pthread_mutex_lock(grinder->mutex);
    while(grinder->beans == CAPACITY) {
      pthread_cond_wait(grinder->full_cv, grinder->mutex);
    }
    grinder->beans += BEANS_PER_CUP;
    pthread_mutex_unlock(grinder->mutex);
    pthread_cond_broadcast(grinder->empty_cv);
  }
  grinder->closed = 1;
  return NULL;
}

void *barista_C(void *arg) {
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
    pthread_cond_broadcast(grinder->full_cv);
  }

  return NULL;
}
