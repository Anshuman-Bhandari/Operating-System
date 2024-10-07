#include <stdio.h>
#include <string.h>

void write_details(const char *filename, const char *details) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s", details);
    fclose(file);
}

void find_matching_lines(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    char line1[256], line2[256];

    if (f1 == NULL || f2 == NULL) {
        perror("Error opening files");
        return;
    }

    while (fgets(line1, sizeof(line1), f1)) {
        rewind(f2);
        while (fgets(line2, sizeof(line2), f2)) {
            if (strcmp(line1, line2) == 0) {
                printf("Matching line: %s", line1);
            }
        }
    }
    
    fclose(f1);
    fclose(f2);
}

int main() {
    printf("\nName - Anshuman Bhandari\nSection - A2\nRoll No.- 18\n\n");
    
    const char *my_details = "Name: Anshuman Bhandari\nAge: 20\nCity: Rishikesh\n";
    const char *friend_details = "Name: Aman Singh\nAge: 20\nCity: Dehradun\n";

    write_details("my_details.txt", my_details);
    write_details("friend_details.txt", friend_details);
    
    find_matching_lines("my_details.txt", "friend_details.txt");
    
    return 0;
}
