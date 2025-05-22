#ifndef COFFEE_H
#define COFFEE_H

#include <pthread.h>

#define BEANS_PER_CUP 3
#define CAPACITY 10
#define MAX_REFILLS 10

typedef struct {
  int beans;
  int closed;
  pthread_mutex_t *mutex;
  pthread_cond_t *full_cv;
  pthread_cond_t *empty_cv;
} coffee_grinder;

coffee_grinder *create_grinder(void);
void destroy_grinder(coffee_grinder *g);

void *manager_A(void *arg);
void *barista_A(void *arg);

void *manager_B(void *arg);
void *barista_B(void *arg);

void *manager_C(void *arg);
void *barista_C(void *arg);

#endif
