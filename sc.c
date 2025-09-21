#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    int i;
    fork();
    for(i=0;i<10;i++){
        printf("\n%d",i);
    }
    return 0;
}