#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

#include "http_status.h"

typedef struct {
     HttpStatus status;
     size_t content_len;
     const char *content_type;   // NULL = omit
      bool close;
} response_head;


ssize_t write_header(char *buf, size_t cap, const response_head *h);
