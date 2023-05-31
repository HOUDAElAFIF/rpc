#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include <rpc/types.h>
#include <rpc/xdr.h>

#define Pg 0x33333333
#define vers 1
#define pc 1

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Utilisation : %s <adresse_serveur> <message>\n", argv[0]);
        exit(1);
    }

    CLIENT *cl;
    char *result;
    char *server = argv[1];
    char *msg = argv[2];

    cl = clnt_create(server, Pg, vers, "tcp");
    if (cl == NULL) {
        clnt_pcreateerror(server);
        exit(1);
    }

    if (callrpc(server, Pg, vers, pc, xdr_wrapstring, &msg, xdr_wrapstring, &result) != 0) {
        clnt_perror(cl, server);
        exit(1);
    }

    printf("Résultat : %s\n", result);

    clnt_destroy(cl);
    exit(0);
}
