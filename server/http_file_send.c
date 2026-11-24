#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include "http_file_send.h"
#include "http_header_write.h"
#include "http_status.h"

int send_file(int client_fd, const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
    char cwd[PATH_MAX];
    fprintf(stderr, "open failed: path=[%s] cwd=[%s]: %s\n",
            path, getcwd(cwd, sizeof cwd) ? cwd : "?");
    return -1;
}
    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) { close(fd); return -1; }
    
    // 1. Send the headers the normal way
    char hdr[256];
    response_head h = { .status = HTTP_STATUS_OK, .content_len = (long long) st.st_size, .content_type = "text/html", .close = true} ;
    ssize_t hlen = write_header(hdr, sizeof hdr, &h);
    
    printf("Sending header: %s\n", hdr);
    
    if (send(client_fd, hdr, hlen, MSG_NOSIGNAL) != hlen) { close(fd); return -1; }

    // 2. Send the body with sendfile, looping because it can send less than asked
    off_t offset = 0;
    while (offset < st.st_size) {
        ssize_t n = sendfile(client_fd, fd, &offset, st.st_size - offset);
        if (n < 0) {
            if (errno == EINTR) continue;   // interrupted, retry
            close(fd);
            return -1;                      // real error (client disconnected, etc.)
        }
        if (n == 0) break;                  // file shrank underneath us
    }

    close(fd);
    return 0;
}
