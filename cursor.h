#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "tree.h"

typedef struct Table_t Table;

typedef struct Cursor_t {
  Table* table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table;  // Indicates a position one past the last element
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);
Cursor* table_find(Table* table, uint32_t key);
NodeType get_node_type(void* node);
void set_node_type(void* node, NodeType type);

#endif // CURSOR_H