#include <stdio.h>
#include <unistd.h>

int main() {
    
    printf("A\n");
    fork();
    sleep(1);
    printf("B\n");

    return 0;
}