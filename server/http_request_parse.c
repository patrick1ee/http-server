
#include <string.h>

#include "http_request_parse.h"

#define MAX_LINE 8192

static bool is_tchar(unsigned char c) {
    // RFC 9110 token characters
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || strchr("!#$%&'*+-.^_`|~", c);
}

// Returns 0 on success, -1 if more data is needed, else an HTTP status.
int parse_request_line(const char *buf, size_t len, request_line *out) {
    enum { METHOD, TARGET, VERSION } state = METHOD;
    size_t target_start = 0, target_end = 0, ver_start = 0, method_end = 0;
    size_t limit = len < MAX_LINE ? len : MAX_LINE;

    for (size_t i = 0; i < limit; i++) {
        unsigned char c = buf[i];

        switch (state) {
        case METHOD:
            if (c == ' ') {
                if (i == 0) return 400;              // empty method
                method_end = i;
                target_start = i + 1;
                state = TARGET;
            } else if (!is_tchar(c) || i >= 16) {
                return 400;
            }
            break;

        case TARGET:
            if (c == ' ') {
                if (i == target_start) return 400;   // empty target / double space
                target_end = i;
                ver_start = i + 1;
                state = VERSION;
            } else if (c < 0x20 || c >= 0x7F || c == '#') {
                return 400;                          // control, non-ASCII, fragment
            }
            break;

        case VERSION:
            if (c == '\r') {
                if (i + 1 >= len) return -1;         // need the '\n'
                if (buf[i + 1] != '\n') return 400;
                if (i - ver_start != 8 || memcmp(buf + ver_start, "HTTP/1.", 7))
                    return 400;
                char minor = buf[ver_start + 7];
                if (minor != '0' && minor != '1') return 505;

                // Method allowlist and target checks (starts with '/',
                // %-escapes) can go here or in a later stage.
                out->method = buf;               out->method_len = method_end;
                out->target = buf + target_start; out->target_len = target_end - target_start; 
		out->minor_version = minor - '0';
                return 0;
            }
            if (c < 0x20 || c >= 0x7F) return 400;   // includes bare '\n', NUL
            break;
        }
    }
    return (len >= MAX_LINE) ? 414 : -1;             // hit the cap, or just incomplete
}
