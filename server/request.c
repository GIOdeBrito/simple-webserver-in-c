
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

void return_http_request (int client_socket, char* filename)
{
    char success[] = "HTTP/2 200 OK\r\nContent-Type: text/html\r\n\r\n";

	char* htmlcontent = read_file_server_request(filename);

    size_t response_len = strlen(success) + strlen(htmlcontent) + 1;
    char res[response_len];

    strcpy(res, success);
    strcat(res, htmlcontent);

    free(htmlcontent);

    send(client_socket, res, sizeof(res), 0);
}

char* read_file_server_request (char* filename)
{
	char filepath[256];

	concatenate("../public", "/index.html", filepath, sizeof(filepath));

	printf("PATH: %s\n", filepath);

	FILE* fhtml = fopen(filepath, "r");

	// If the file does not exists, send it to the error
	if(fhtml == NULL)
	{

	}

    // Gets the file's size
    fseek(fhtml, 0, SEEK_END);

    size_t f_size = ftell(fhtml);

    // Set the file to its initial position
    fseek(fhtml, 0, SEEK_SET);

    // Allocates enough memory to store the file's content
    char* htmlcontent = (char*) malloc((f_size + 1) * sizeof(char));

    if(htmlcontent == NULL)
    {
        perror("FAILED AT ALLOCATING MEMORY FOR FILE'S LENGTH");
        exit(-6);
    }

    htmlcontent[0] = '\0';

    // Read the file's content to a variable
    fread(htmlcontent, 1, f_size, fhtml);
    htmlcontent[f_size] = '\0';

    fclose(fhtml);

    return htmlcontent;
}

http_request_object get_http_request_data (int client_socket)
{
	// Where full request string will be stored
	char buffer[1024];

	// Reads the full header of the HTTP request and assings the output to buffer
	recv(client_socket, buffer, sizeof(buffer) - 1, 0);

	char* token = strtok(buffer, " ");
	http_request_object req_object = {};
	int i = 0;

	while(token)
	{
		//printf("TOKEN: %s\n", token);

		switch(i)
		{
			case 0: {
				strcpy(req_object.method, token);
			}
			break;
			case 1: {
				strcpy(req_object.filename, token);
			}
			break;
			case 6: {
				strcpy(req_object.os, token);
			}
			break;
			case 7: {
				strcpy(req_object.architecture, token);
			}
			break;
		}

		token = strtok(NULL, " ");

		i++;
	}

	return req_object;
}
