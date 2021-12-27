#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* buffer;
    size_t buffer_len;
    ssize_t input_len;
} InputBuffer;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;


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

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    if ((*statement).type == STATEMENT_INSERT) {
        // insert
        puts("insert");
    }
    if ((*statement).type == STATEMENT_SELECT) {
        // select
        puts("select");
    }
}

int main(int argc, char** argv) {
    InputBuffer* in_buf = create_input_buffer();

    while (1) {
        print_prompt();
        read_input(in_buf);

        // meta command
        if ((in_buf -> buffer)[0] == '.') {
            MetaCommandResult mr = do_meta_command(in_buf);
            if (mr == META_COMMAND_SUCCESS) {
                continue;
            } else if (mr == META_COMMAND_UNRECOGNIZED_COMMAND) {
                printf("Unrecognized command '%s'\n", in_buf->buffer);
                continue;
            }
        }

        Statement statement;
        PrepareResult pr = prepare_statement(in_buf, &statement);
        if (pr == PREPARE_UNRECOGNIZED_STATEMENT) {
            printf("Unrecognized keyword at start of '%s'.\n", in_buf->buffer);
            continue;
        }

        execute_statement(&statement);
    }
}
