
#define PORT 8080

typedef struct HTTP_request_struct
{
	char method[16];
	char filename[128];
	char os[64];
	char architecture[32];
} http_request_object;

typedef enum boolean { false, true } bool;

void server_start(void);
void server_listen(int);

void return_http_request(int, char*);
char* read_file_server_request(char*);
http_request_object get_http_request_data(int);

void concatenate(char*, char*, char*, size_t);
bool file_exists(char*);