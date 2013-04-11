#include "../include/rw_lock.h"
#include <fcntl.h>
#include <string.h>

#define THREAD_NUM 10


struct str_
{
  char str[20];
  struct rw_lock rwl;
};
void *thread_r(void *arg)
{
  struct str_ *s = (struct str_ *)arg;
  char str[20];
  while (1) {
    pthread_r_lock(&s->rwl);
    strcpy(str, s->str);
    pthread_r_unlock(&s->rwl);

    printf("thread read : %s\n", str);
    sleep(2);
  }

  pthread_exit(0);
}

void *thread_w(void *arg)
{
  struct str_ *s = (struct str_ *)arg;
  
  pthread_w_lock(&s->rwl);
  s->str[0] = 'C';
  s->str[1] = 'e';
  s->str[2] = '\0';
  sleep(5);
  pthread_w_unlock(&s->rwl);
  sleep(5);
  pthread_w_lock(&s->rwl);
  s->str[0] = 'T';
  s->str[1] = 'o';
  s->str[2] = '\0';
  sleep(5);
  pthread_w_unlock(&s->rwl);

  pthread_exit(0);
}

int main()
{
  int f, i;
  struct str_ s;
  pthread_t t;

  pthread_rw_init(&s.rwl);
  strcpy(s.str, "Linux");
  s.str[5] = '\0';

  for (i = 0; i<2; i++)
    pthread_create(&t, NULL, thread_r, (void *)&s);
  pthread_create(&t, NULL, thread_w, (void *)&s);

  sleep(20);
  printf("main thread : %s\n", s.str);
}
