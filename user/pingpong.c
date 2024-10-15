#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int par_to_chil[2];
    int chil_to_par[2];
    pipe(par_to_chil);
    pipe(chil_to_par);
    char buf[20] = {0};

    pid = fork();
    if(pid == 0){
        close(par_to_chil[1]);
        close(chil_to_par[0]);
        read(par_to_chil[0], buf, 4);
        printf("%d, received%s\n", getpid(), buf);
        write(chil_to_par[1], "pong", 4);
        exit(0)
    }
    else{
        close(par_to_chil[0]);
        close(chil_to_par[1]);
        write(par_to_chil[1], "ping", 4);
        read(chil_to_par[0], buf, 4);
        printf("%d, received%s\n", getpid, buf);
        exit(0)
    }
    
}