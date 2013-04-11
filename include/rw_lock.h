#ifndef __RWLOCK_H
#define __RWLOCK_H

#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>

/* readers-writer lock, implement it use the pthread 
 * mutex and condition variable */
struct rw_lock
{
  size_t readers;
  bool writing;
  pthread_mutex_t r_lock;
  pthread_cond_t w_cond;
};

/* readers-writer lock operations */
int pthread_r_lock(struct rw_lock *rwl);
int pthread_r_unlock(struct rw_lock *rwl);
int pthread_w_lock(struct rw_lock *rwl);
int pthread_w_unlock(struct rw_lock *rwl);
int pthread_rw_init(struct rw_lock *rwl);
int pthread_rw_destory(struct rw_lock *rwl);



#endif
