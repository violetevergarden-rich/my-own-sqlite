#include "table.h"
#include "row.h"
#include "pager.h"
#include "tree.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

Table* db_open(const char* filename) {
    Pager* pager = pager_open(filename);

    Table* table = malloc(sizeof(Table));
    table->pager = pager;

    table->root_page_num = 0;

    if(pager->num_pages == 0){
        void* root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
    }

    return table;
}

void db_close(Table* table) {
    Pager* pager = table->pager;

    // 写回并free页,并将页指针改成NULL
    
    for(uint32_t i=0;i< pager->num_pages;i++){
        if(pager->pages[i] == NULL){
            continue;
        }
        page_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
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