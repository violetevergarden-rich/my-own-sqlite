#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include "row.h"
#include "pager.h"

#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

typedef struct {
  uint32_t num_rows;
  Pager* pager;
} Table;

void* row_slot(Table* table, uint32_t row_num);
Table* db_open(const char* filename);
void db_close(Table* table);

#endif // TABLE_H