#include "coffee.h"
#include <stdlib.h>

coffee_grinder *create_grinder() {
  coffee_grinder *g = malloc(sizeof(coffee_grinder));
  g->beans = 0;
  g->closed = 0;
  g->mutex = malloc(sizeof(pthread_mutex_t));
  g->full_cv = malloc(sizeof(pthread_cond_t));
  g->empty_cv = malloc(sizeof(pthread_cond_t));
  pthread_mutex_init(g->mutex, NULL);
  pthread_cond_init(g->full_cv, NULL);
  pthread_cond_init(g->empty_cv, NULL);
  return g;
}

void destroy_grinder(coffee_grinder *g) {
  pthread_mutex_destroy(g->mutex);
  pthread_cond_destroy(g->full_cv);
  pthread_cond_destroy(g->empty_cv);
  free(g->mutex);
  free(g->full_cv);
  free(g->empty_cv);
  free(g);
}
