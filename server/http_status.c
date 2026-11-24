#include "http_status.h"

const char *http_status_reason(HttpStatus status) {
    switch (status) {
        case HTTP_STATUS_OK:                    return "OK";
        case HTTP_STATUS_CREATED:               return "Created";
        case HTTP_STATUS_NO_CONTENT:            return "No Content";
        case HTTP_STATUS_MOVED_PERMANENTLY:     return "Moved Permanently";
        case HTTP_STATUS_FOUND:                 return "Found";
        case HTTP_STATUS_NOT_MODIFIED:          return "Not Modified";
        case HTTP_STATUS_BAD_REQUEST:           return "Bad Request";
        case HTTP_STATUS_UNAUTHORIZED:          return "Unauthorized";
        case HTTP_STATUS_FORBIDDEN:             return "Forbidden";
        case HTTP_STATUS_NOT_FOUND:             return "Not Found";
        case HTTP_STATUS_METHOD_NOT_ALLOWED:    return "Method Not Allowed";
        case HTTP_STATUS_TOO_MANY_REQUESTS:     return "Too Many Requests";
        case HTTP_STATUS_INTERNAL_SERVER_ERROR: return "Internal Server Error";
        case HTTP_STATUS_NOT_IMPLEMENTED:       return "Not Implemented";
        case HTTP_STATUS_BAD_GATEWAY:           return "Bad Gateway";
        case HTTP_STATUS_SERVICE_UNAVAILABLE:   return "Service Unavailable";
        case HTTP_STATUS_VERSION_NOT_SUPPORTED: return "HTTP Version Not Supported";
    }
    return "Unknown";
}
