#include "table.h"
#include "row.h"
#include "pager.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

Table* db_open(const char* filename) {
  Pager* pager = pager_open(filename);
  uint32_t num_rows = pager->file_length / ROW_SIZE;

  Table* table = malloc(sizeof(Table));

  table->pager = pager;
  table->num_rows = num_rows;
  return table;
}

void db_close(Table* table) {
    Pager* pager = table->pager;

    // 写回并free页,并将页指针改成NULL
    // 完整页
    uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;
    
    for(uint32_t i=0;i<num_full_pages;i++){
        if(pager->pages[i] == NULL){
            continue;
        }
        page_flush(pager, i, PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    // partial page
    uint32_t num_addition_rows = table->num_rows % ROWS_PER_PAGE;

    if(num_addition_rows > 0){
        uint32_t page_num = num_full_pages;
        if(pager->pages[page_num] != NULL){
            page_flush(pager, page_num, num_addition_rows*ROW_SIZE);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }


    // 关闭文件描述符
    int result = close(pager->file_descriptor);
    if (result == -1) {
    printf("Error closing db file.\n");
    exit(EXIT_FAILURE);
    }
    
    // 清理遗漏的页缓存内存
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void* page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }

    free(pager);
    free(table);
}