#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http_header.h"
#include "http_header_write.h"
#include "http_status.h"

ssize_t write_header(char *buf, size_t cap, const response_head *h) {
    size_t off = 0;
    int n;

    n = snprintf(buf + off, cap - off, "HTTP/1.1 %d %s\r\n",
                 (int)h->status, http_status_reason(h->status));
    if (n < 0 || (size_t)n >= cap - off) return -1;
    off += n;

    n = snprintf(buf + off, cap - off, "Content-Length: %zu\r\n", h->content_len);
    if (n < 0 || (size_t)n >= cap - off) return -1;
    off += n;

    if (h->content_type) {
        n = snprintf(buf + off, cap - off, "Content-Type: %s\r\n", h->content_type);
        if (n < 0 || (size_t)n >= cap - off) return -1;
        off += n;
    }

    if (h->close) {
        n = snprintf(buf + off, cap - off, "Connection: close\r\n");
        if (n < 0 || (size_t)n >= cap - off) return -1;
        off += n;
    }

    n = snprintf(buf + off, cap - off, "\r\n");
    if (n < 0 || (size_t)n >= cap - off) return -1;
    off += n;

    return off;
}
