#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct MHD_Response *create_response(const char *message)
{
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(message), (void *) message, MHD_RESPMEM_PERSISTENT);
    if (!response)
    {
        printf("Failed to create response object.\n");
        exit(-1);
    }

    ret = MHD_add_response_header(response, MHD_HTTP_HEADER_CONTENT_TYPE, "text/html");
    if (ret == MHD_NO)
    {
        printf("Failed to add response header.\n");
        exit(-1);
    }

    return response;
}

enum MHD_Result handle_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    const char *page = "<html><head><style>body {background-color: lightblue;} h1 {color: white; text-align: center;}</style></head><body><h1>Hello, browser!</h1><img src='/image.jpg'></body></html>";
    struct MHD_Response *response;
    int ret;

    response = create_response(page);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    if (ret == MHD_NO)
    {
        printf("Failed to queue response.\n");
        exit(-1);
    }

    MHD_destroy_response(response);

    return MHD_YES;
}

int main()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
    {
        printf("Failed to start daemon.\n");
        exit(-1);
    }

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}
