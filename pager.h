#ifndef PAGER_H
#define PAGER_H

#include <stddef.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)

typedef struct Pager_t {
  int file_descriptor;
  uint32_t file_length;
  void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void page_flush(Pager* pager, uint32_t page_num, uint32_t size);

#endif //PAGER_H