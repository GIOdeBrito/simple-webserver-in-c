#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// If the current system is a Linux OS
#ifdef __linux__ 
    #include <arpa/inet.h>
    #define ARPA_IS_INCLUDED
#endif

#define PORT 8080

// === FUNCTION PROTOTYPES ================================

void server_start(void);
void server_listen(int);
void request(int);
char* read_response_html(void);

// === FUNCTIONS ==========================================

int main (void)
{
    #ifdef ARPA_IS_INCLUDED
        printf("ARPA included.\nStarting server...\n\n");
        server_start();
    #else 
        #error "ARPA is not included."
        exit(-1);
    #endif

    printf("\n\nShutting down...\n");
    return 0;
}

void server_start (void)
{
    // Attempts to create the server's socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1)
    {
        perror("FAILED IN CREATING SERVER SOCKET");
        exit(-2);
    }

    // Set server structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    // Convert and attributes bytes for one that is network usable
    server_address.sin_port = htons(PORT);

    socklen_t server_len = sizeof(server_address);

    // Attemps to bind the server's socket
    int srv_socket_result = bind(server_socket, (struct sockaddr *)&server_address, server_len);
    if(srv_socket_result == -1)
    {
        perror("ERROR ON BINDING SERVER SOCKET");
        exit(-3);
    }

    // Makes server listen for incoming connections
    if(listen(server_socket, 10) == -1)
    {
        perror("SERVER ERROR WHEN ATTEMPTING TO LISTEN TO PORT:");
        perror((char *)PORT);
        exit(-4);
    }

    printf("Server is listening on PORT %d \n\n", PORT);

    while(1)
    {
        server_listen(server_socket);
    }

    close(server_socket);
    printf("Closing socket\n");
}

void server_listen (int srv_socket)
{
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(&client_address);

    // Accepts a connection from a client
    int client_socket = accept(srv_socket, (struct sockaddr *)&client_address, &client_len);
    if(client_socket == -1)
    {
        perror("FAILED TO ACCEPT REQUEST FROM CLIENT");
        exit(-5);
    }

    // Converts and store an IP address to a string
    char* client_from = inet_ntoa(client_address.sin_addr);
    // Converts from network to host
    int client_port = ntohs(client_address.sin_port);
    printf("Accepted connection from %s, PORT: %d \n", client_from, client_port);

    request(client_socket);

    close(client_socket);
}

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

char* read_response_html (void)
{
    FILE* fhtml = fopen("response.html", "r");

    // Gets the file's size
    fseek(fhtml, 0, SEEK_END);
    long f_size = ftell(fhtml);

    // Set the file to initial position
    fseek(fhtml, 0, SEEK_SET);

    // Allocates enough memory to store the file's content
    char* htmlcontent = (char*)malloc((f_size + 1) * sizeof(char));

    if(htmlcontent == NULL)
    {
        perror("FAILED AT ALLOCATING MEMORY FOR FILE'S LENGTH");
        exit(-6);
    }

    htmlcontent[0] = '\0';

    // Read the file's content to a variable
    size_t byte_read = fread(htmlcontent, 1, f_size, fhtml);
    htmlcontent[f_size] = '\0';

    fclose(fhtml);

    return htmlcontent;
}

