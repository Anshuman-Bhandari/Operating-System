#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

void write_details(const char *filename, const char *details) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    write(fd, details, strlen(details));
    close(fd);
}
void read_file(const char *filename) {
    char buffer[BUFFER_SIZE];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    printf("Contents of %s:\n", filename);
    while (read(fd, buffer, sizeof(buffer) - 1) > 0) {
        buffer[BUFFER_SIZE - 1] = '\0';
        printf("%s", buffer);
    }
    close(fd);
}
int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    const char *my_details = "Name: Anshuman Bhandari\nAge: 20\nCity: Rishikesh\n";
    const char *friend_details = "Name: Aman Singh\nAge: 20\nCity: Dehradun\n";
    write_details("my_details.txt", my_details);
    write_details("friend_details.txt", friend_details);
    FILE *my_file = fopen("my_details.txt", "r");
    FILE *friend_file = fopen("friend_details.txt", "r");
    if (!my_file || !friend_file) {
        perror("fopen FAILED!");
        exit(1);
    }
    char my_line[BUFFER_SIZE];
    while (fgets(my_line, sizeof(my_line), my_file)) {
        rewind(friend_file);
        char friend_line[BUFFER_SIZE];
        while (fgets(friend_line, sizeof(friend_line), friend_file)) {
            if (strcmp(my_line, friend_line) == 0)
                printf("Matching line: %s", my_line);
        }
    }
    fclose(my_file);
    fclose(friend_file);
    return 0;
}