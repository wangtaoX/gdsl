#ifndef __BITMAP_H
#define __BITMAP_H

#include <stddef.h>

/* Use unsigned int */
typedef unsigned int bit_elem_type;

/* bitmap */
struct bitmap
{
  size_t bit_cnt; 
  bit_elem_type *bit_map;
};
#endif
