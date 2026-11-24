#ifndef HTTP_STATUS_H
#define HTTP_STATUS_H

typedef enum {
    HTTP_STATUS_OK                    = 200,
    HTTP_STATUS_CREATED               = 201,
    HTTP_STATUS_NO_CONTENT            = 204,

    HTTP_STATUS_MOVED_PERMANENTLY     = 301,
    HTTP_STATUS_FOUND                 = 302,
    HTTP_STATUS_NOT_MODIFIED          = 304,

    HTTP_STATUS_BAD_REQUEST           = 400,
    HTTP_STATUS_UNAUTHORIZED          = 401,
    HTTP_STATUS_FORBIDDEN             = 403,
    HTTP_STATUS_NOT_FOUND             = 404,
    HTTP_STATUS_METHOD_NOT_ALLOWED    = 405,
    HTTP_STATUS_TOO_MANY_REQUESTS     = 429,

    HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
    HTTP_STATUS_NOT_IMPLEMENTED       = 501,
    HTTP_STATUS_BAD_GATEWAY           = 502,
    HTTP_STATUS_SERVICE_UNAVAILABLE   = 503,
    HTTP_STATUS_VERSION_NOT_SUPPORTED = 505
} HttpStatus;

const char *http_status_reason(HttpStatus status);

#endif /* HTTP_STATUS_H */
