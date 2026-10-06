#ifndef STATEMENT_H
#define STATEMENT_H

#include "input_buffer.h"
#include "table.h"
#include "row.h" 

typedef enum { 
    PREPARE_SUCCESS, 
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR 
} PrepareResult;

typedef enum { 
    EXECUTE_TABLE_FULL, 
    EXECUTE_SUCCESS 
} ExecuteResult;

typedef enum { 
    STATEMENT_INSERT, 
    STATEMENT_SELECT 
} StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert; //只被insert语句使用
} Statement;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
ExecuteResult execute_statement(Statement* statement, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);

#endif // STATEMENT_H