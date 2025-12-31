#ifndef UPDATE_REQUEST_H
#define UPDATE_REQUEST_H
typedef struct
{
    char id [32];
    char name [256];
    char description [1024];

} update_request_t;

#endif /* UPDATE_REQUEST_H */
