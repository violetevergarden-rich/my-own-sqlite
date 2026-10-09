#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Table_t Table;

typedef struct Cursor_t {
  Table* table;
  uint32_t row_num;
  bool end_of_table;  // Indicates a position one past the last element
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif // CURSOR_H