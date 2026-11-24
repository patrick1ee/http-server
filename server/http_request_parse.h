#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char *method;      // points into the receive buffer, not NUL-terminated
    size_t      method_len;

    const char *target;      // raw request-target, still percent-encoded
    size_t      target_len;

    int         minor_version;   // 0 for HTTP/1.0, 1 for HTTP/1.1
} request_line;

int parse_request_line(const char *buf, size_t len, request_line *out);
