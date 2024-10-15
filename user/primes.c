#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void trans(int pl[2], int pr[2]){
    int buf;
    int buf2;
    
    read(pl[0], &buf, sizeof(buf));
    if(buf == 0)
        exit(0);
    printf("prime %d\n", buf);
    while(read(pl[0], &buf2, sizeof(buf2)) != 0){
        if(buf2 % buf != 0){
            write(pr[1], &buf2, sizeof(buf2));
        }
    }
    close(pl[0]);
    close(pr[1]);
}

void process(int pl[2]){
    close(pl[1]);
    int pr[2];
    pipe(pr);
    trans(pl,pr);

    if(fork() == 0){
        process(pr);
    }
    else{
        close(pr[0]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *argv[]){
    int firstp[2];
    pipe(firstp);

    for(int i = 2; i <= 35; i++){
        write(firstp[1], &i, sizeof(i));
    }
    if(fork() == 0) {
        process(firstp);
    }
    else{
        close(firstp[1]);
        close(firstp[0]);
        wait(0);
    }
    exit(0);
}