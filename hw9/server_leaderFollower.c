#include <sys/types.h>
#include <signal.h>
#include <sys/uio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

#define BACKLOG 200
// if more than BACKLOG clients in the server accept queue, client connect will fail

#define N_THREADS 10

struct Queue
{
    pthread_mutex_t lock;
    char* fileName[BACKLOG];
    int client_socket[BACKLOG];
    int top;  
};

struct Thread_data
{
    int id;
    pthread_t thread_id;
};

void push(struct Queue *queue, char *str, int client_socket)
{
    pthread_mutex_lock(&(queue->lock));
    queue->fileName[queue->top] = str;
    queue->client_socket[queue->top] = client_socket;
    ++queue->top;
    pthread_mutex_unlock(&(queue->lock));
}

void error(char *msg)
{
    fprintf(stderr, "ERROR: %s failed\n", msg);
    exit(-1);
}


struct sockaddr_in make_server_addr(short port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    return addr;
}

int create_server_socket(short port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    struct sockaddr_in my_addr = make_server_addr(port);
    if ( s == -1 )
        error("socket()");
    bind(s, (struct sockaddr*)&my_addr, sizeof my_addr);
    listen(s, BACKLOG);
    return s;
}

void get_file_request(int socket, char *fileName)
{
    char buf[BUFSIZ];
    int n = read(socket, buf, BUFSIZ);
    if ( n < 0 )
        error("read from socket");
    buf[n] = '\0';
    strcpy(fileName, buf);
    // printf("Server got file name of '%s'\n", fileName);
}

void write_file_to_client_socket(char *file, int socket)
{
    char buf[BUFSIZ];
    int n;
    int ifd = open(file, O_RDONLY);
    if ( ifd == -1 )
        error("open()");
    while ( (n = read(ifd, buf, BUFSIZ)) > 0 )
        write(socket, buf, n);
    close(ifd);
}



void handle_request(int client_socket, struct Queue *queue)
{
    char fileName[BUFSIZ];
    get_file_request(client_socket, fileName);
    push(queue, fileName, client_socket);
    // write_file_to_client_socket(fileName, client_socket);
    close(client_socket);
}

void time_out(int arg)
{
    fprintf(stderr,  "Server timed out\n");
    exit(0);
}

void set_time_out(int seconds)
{
    struct itimerval value = {0};
    value.it_value.tv_sec = seconds;
    setitimer(ITIMER_REAL, &value, NULL);
    signal(SIGALRM, time_out);
}

void *thread_work(void *in)
{
    struct Queue *queue = (struct Queue*) in;
    while(1) {
        pthread_mutex_lock(&(queue->lock));
        int top = queue->top - 1;
        if(top >= 0){
             write_file_to_client_socket(queue->fileName[top], queue->client_socket[top]);
             --queue->top;
        }
        pthread_mutex_unlock(&(queue->lock));
    }
}

void create_thread_pool(struct Queue *queue)
{
    int i;
    struct Thread_data thread_args[N_THREADS];
    for( i = 0; i < N_THREADS; ++i) 
    {
        struct Thread_data * t = &thread_args[i];
        pthread_create(&t->thread_id, NULL, thread_work, queue);
    }
}

void accept_client_requests(int server_socket)
{
    int client_socket;
    struct Queue queue;
    queue.top = 0;
    pthread_mutex_init(&(queue.lock), NULL);
    create_thread_pool(&queue);
    struct sockaddr_in client_addr;
    socklen_t sin_size = sizeof client_addr;
    set_time_out(5);
    while ( (client_socket =
        accept(server_socket, (struct sockaddr*)&client_addr, &sin_size)) > 0 )
    {
        set_time_out(5);
        handle_request(client_socket, &queue);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if ( argc != 2 )
        error("usage: server port");
    short port = atoi(argv[1]);
    int server_socket = create_server_socket(port);
    accept_client_requests(server_socket);
    shutdown(server_socket, 2);
    return 0;
}
