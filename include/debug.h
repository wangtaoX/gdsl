#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdlib.h>

#define ASSERT(CONDITION)   \
  if (CONDITION) { } else { \ 
     printf("ASSERT ERROR : FILE[%s] LINE[%d]\n", __FILE__, __LINE__);\
     exit(0);\
    }

#endif
