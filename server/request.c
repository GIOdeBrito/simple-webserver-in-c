
/* This file is responsible for handling the
client requests for the server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"

// If the current system is a Linux OS
#ifdef __linux__ 
    #include <arpa/inet.h>
    #define ARPA_IS_INCLUDED
#endif

void request (int client_socket)
{
    char success[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"; 
    char* html = read_response_html();

    size_t response_len = strlen(success) + strlen(html) + 1;
    char res[response_len];

    strcpy(res, success);
    strcat(res, html);
    free(html);

    send(client_socket, res, sizeof(res), 0);
}

