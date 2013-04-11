#include "../include/rw_lock.h"

int pthread_rw_init(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  rwl->readers = 0;
  rwl->writing = 0;
  pthread_mutex_init(&rwl->r_lock, NULL);
  pthread_cond_init(&rwl->w_cond, NULL);

  return 1;
}

int pthread_rw_destory(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  pthread_mutex_destroy(&rwl->r_lock);
  pthread_cond_destroy(&rwl->w_cond);

  return 1;
}

int pthread_r_lock(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  pthread_mutex_lock(&rwl->r_lock);
  while(rwl->writing == 1)
    pthread_cond_wait(&rwl->w_cond, &rwl->r_lock);
  rwl->readers += 1;
  pthread_mutex_unlock(&rwl->r_lock);
}

int pthread_r_unlock(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  pthread_mutex_lock(&rwl->r_lock);
  rwl->readers -= 1;
  if (rwl->readers == 0)
    pthread_cond_signal(&rwl->w_cond);
  pthread_mutex_unlock(&rwl->r_lock);

  return 1;
}

int pthread_w_lock(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  pthread_mutex_lock(&rwl->r_lock);
  while(rwl->readers > 0)
    pthread_cond_wait(&rwl->w_cond, &rwl->r_lock);
  
  rwl->writing = 1;

  return 1;
}

int pthread_w_unlock(struct rw_lock *rwl)
{
  if (rwl == NULL)
    return -1;

  rwl->writing = 0;
  pthread_cond_signal(&rwl->w_cond);
  pthread_mutex_unlock(&rwl->r_lock);

  return 1;
}
