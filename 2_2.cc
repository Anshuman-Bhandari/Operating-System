#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    execlp("ls", "ls", NULL);
    perror("execlp terminated!");
    return 1;
}
