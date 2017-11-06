/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: RPC File Client, connection-oriented, use TCP        */
/*********************************************************************/

/* RPC file transfer client : client.c - Simple client of the FileReadWrite service. */

#include <stdio.h>
#include <libgen.h>
#include <rpc/rpc.h>

#include "FileReadWrite.h"
#include "Timer.h"

int
main(int argc, char ** argv)
{
    /* require hostname/ip address to make connection */
    if (argc != 3) {
        fprintf(stderr, "usage: %s hostname filePath\n", argv[0]);
        exit(1);
    }

    CLIENT *clientHandle;
    char *serverName = argv[1];
    READ_ARGS read_args;
    DATA *data;

    /* creates socket and a client handle*/
    clientHandle = clnt_create(serverName, FILEREADWRITE, VERSION, "tcp");
    if (clientHandle == NULL) {
        /* unable to contact server */
        clnt_pcreateerror(serverName);
        exit(2);
    }

    /* put file path in read_args */
    read_args.filename = argv[2];
    /* first read, set offset to 0, start from beginning of file */
    read_args.offset = 0;

    /* call to remote read procedure */
    if ( (data = read_1(&read_args, clientHandle)) == NULL) {
        /* unable to run remote procedure read_1()*/
        clnt_perror(clientHandle, serverName);
        exit(3);
    }
    double wc, us, sys;
    Timer_start();

    // open file on local for append, create if not exist
    FILE *fp;
    fp = fopen(basename(read_args.filename), "a");

    // write the first chunk of data to file
    fwrite(data->buffer, 1, data->length, fp);

    // if more data to be written read all the file in a loop
    while (data->moreData) {
        read_args.offset += data->length;

        if ( (data = read_1(&read_args, clientHandle)) == NULL) {
            /* unable to run remote procedure read_1()*/
            clnt_perror(clientHandle, serverName);
            exit(3);
        }
        fwrite(data->buffer, 1, data->length, fp);
    }

    fclose(fp);

    /* closes socket */
    clnt_destroy(clientHandle);

    Timer_elapsedTime(&wc, &us, &sys);
    printf("wallclock %lf, user %lf, system time %lf\n", wc, us, sys);

    return 0;
}