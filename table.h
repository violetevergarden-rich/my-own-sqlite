#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

typedef struct Pager_t Pager;

typedef struct Table_t {
  uint32_t num_rows;
  Pager* pager;
} Table;

void* row_slot(Table* table, uint32_t row_num);
Table* db_open(const char* filename);
void db_close(Table* table);

#endif // TABLE_H