#include "tree.h"
#include "row.h"
#include "cursor.h"
#include "table.h"
#include "pager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t* leaf_node_num_cells(void* node) {
    return (uint32_t*)((uint8_t*)node + LEAF_NODE_NUM_CELLS_OFFSET);
}

void* leaf_node_cell(void* node, uint32_t cell_num) {
    return (uint8_t*)node + LEAF_NODE_HEADER_SIZE + (cell_num * LEAF_NODE_CELL_SIZE);
}

uint32_t* leaf_node_key(void* node, uint32_t cell_num) {
    return (uint32_t*)leaf_node_cell(node, cell_num);
}

void* leaf_node_value(void* node, uint32_t cell_num) {
    return (uint8_t*)leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(void* node) {
    *leaf_node_num_cells(node) = 0;
}

// 叶子节点插入逻辑
void leaf_node_insert(Cursor* cursor, uint32_t key, const Row* value) {
    void* node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // 节点满了，教程后续会在这里实现节点分裂（Split）
        printf("Need to implement splitting a leaf node.\n");
        exit(EXIT_FAILURE);
    }

    if (cursor->cell_num < num_cells) {
        // 如果不是插入在最末尾，需要把后面的 Cell 往后挪一位，腾出空间
        for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
        memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1),
                LEAF_NODE_CELL_SIZE);
        }
    }

    // 更新 Cell 数量
    *(leaf_node_num_cells(node)) += 1;
    // 写入 Key
    *(leaf_node_key(node, cursor->cell_num)) = key;
    // 将结构体 Row 序列化并写入对应的 Value 内存区
    serialize_row(value, leaf_node_value(node, cursor->cell_num));
}

void print_constants(){
    printf("ROW_SIZE: %zu\n", ROW_SIZE);
    printf("COMMON_NODE_HEADER_SIZE: %zu\n", COMMON_NODE_HEADER_SIZE);
    printf("LEAF_NODE_HEADER_SIZE: %zu\n", LEAF_NODE_HEADER_SIZE);
    printf("LEAF_NODE_CELL_SIZE: %zu\n", LEAF_NODE_CELL_SIZE);
    printf("LEAF_NODE_SPACE_FOR_CELLS: %zu\n", LEAF_NODE_SPACE_FOR_CELLS);
    printf("LEAF_NODE_MAX_CELLS: %zu\n", LEAF_NODE_MAX_CELLS);
}

void print_leaf_node(void* node) {
  uint32_t num_cells = *leaf_node_num_cells(node);
  printf("leaf (size %d)\n", num_cells);
  for (uint32_t i = 0; i < num_cells; i++) {
    uint32_t key = *leaf_node_key(node, i);
    printf("  - %d : %d\n", i, key);
  }
}