#ifndef METACOMMAND_H
#define METACOMMAND_H

typedef struct InputBuffer_t InputBuffer;
typedef struct Table_t Table;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer,Table* table);

#endif //METACOMMAND