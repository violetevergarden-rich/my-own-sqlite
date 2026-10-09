#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

typedef struct Pager_t Pager;

#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct Table_t {
  uint32_t num_rows;
  Pager* pager;
} Table;

Table* db_open(const char* filename);
void db_close(Table* table);

#endif // TABLE_H