/* This is server program, which creates a server and listens for
    messages from clients */

/* TODO
1) server_init args
2) turning on bash
3) cfmakerow
*/

#include "my_server.h"

/* Mutexes for threads */
/* Connection type, TCP or UDP */
static int connection_type = NONE;

//---------------------------------------------------
int main(int argc, char** argv) {

    /* Choose connection type */;

    /* UDP connection by default */
    connection_type = UDP_CON;
    int ret = 0;
    int sk = 0;
    struct sockaddr_in sk_addr;
    /* Set up fixed amount of thread identifiers, each thread identifier associates
    with a particular client */
    pthread_t thread_ids[MAXCLIENTS];
    struct message* memory = NULL;
    struct server_info info;

    /* Basically bitmap */
    int id_map[MAXCLIENTS];

    
    ret = server_check_input(argc, argv, &connection_type);
    if (ret < 0) {
        printf("Incorrect option passed.\n");
        exit(EXIT_FAILURE);
    }

    info.thread_ids = thread_ids;
    /* Prepare server for main routine */
    ret =  server_init(connection_type, &sk, &sk_addr, id_map, &memory, mutexes, &info);
    if (ret < 0) {
        printf("Error initializing server.\n");
        close(sk);
        exit(EXIT_FAILURE);
    }

    /* Server operation */
    ret = server_routine(&info);
    if (ret < 0) {
        printf("Error in server operation.\n");
        close(sk);
        exit(EXIT_FAILURE);
    }

    return 0;
}