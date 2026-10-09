#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include <sys/types.h>
#include <stddef.h>

typedef struct InputBuffer_t {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer(void);
void print_prompt(void);
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);

#endif // INPUT_BUFFER_H