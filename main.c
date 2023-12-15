#include <stdio.h>
#include <unistd.h>

int main()
{
    int id;
    id = fork();
    printf("%d\n", id);
    if(id == 0)
        printf("child\n");
    else
        printf("parent\n");
}