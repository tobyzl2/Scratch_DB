#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* buffer;
    size_t buffer_len;
    ssize_t input_len;
} InputBuffer;

InputBuffer* create_input_buffer() {
    InputBuffer* in_buf = (InputBuffer*) malloc(sizeof(InputBuffer));
    in_buf -> buffer = NULL;
    in_buf -> buffer_len = 0;
    in_buf -> input_len = 0;

    return in_buf;
}

void destroy_input_buffer(InputBuffer* in_buf) {
    free(in_buf -> buffer);
    free(in_buf);
}

void print_prompt() {
    printf("scratch > ");
}

void read_input(InputBuffer* in_buf) {
    ssize_t bytes_read = getline(&(in_buf->buffer), &(in_buf -> buffer_len), stdin);

    if (bytes_read <= 0) {
        puts("Error reading input!");
        exit(EXIT_FAILURE);
    }

    in_buf -> input_len = bytes_read - 1;
    in_buf -> buffer[bytes_read - 1] = '\0';
}

int main(int argc, char** argv) {
    InputBuffer* in_buf = create_input_buffer();

    while (1) {
        print_prompt();
        read_input(in_buf);

        if (strcmp(in_buf->buffer, ".exit") == 0) {
            destroy_input_buffer(in_buf);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command: %s\n", in_buf -> buffer);
        }
    }
}
