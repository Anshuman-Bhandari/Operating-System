#include <stdio.h> 
#include <dirent.h>
int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("Can't open directory!\n");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL)
        printf("%s\n", entry->d_name);
    closedir(dir);
    return 0;
}
