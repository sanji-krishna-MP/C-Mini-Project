#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *pF = fopen("D:\\c files checker\\test.txt", "r");
    FILE *pF1 = fopen("D:\\c files checker\\test2.txt", "a");

    // Ensure files opened correctly
    if (pF == NULL || pF1 == NULL) {
        printf("Error opening file(s).\n");
        return 1;
    }

    char buffer[250];  // Buffer to hold lines from the file
    char answer;       // To store the user's answer
    int line_count = 0; // Line counter for each question

    printf("Starting the quiz...\n");

    // Read and process lines from the input file
    while (fgets(buffer, sizeof(buffer), pF)) {
        // Remove any trailing newlines or carriage returns
        buffer[strcspn(buffer, "\r\n")] = 0;

        // Print each line (question or option)
        printf("%s\n", buffer);

        // Count lines until a full question block is displayed
        line_count++;

        // If the question block is complete (1 question + 4 options)
        if (line_count == 5) {
            printf("Enter your answer: ");

            // Clear the input buffer before reading the answer
            scanf(" %c", &answer);

            // Write the answer to the output file
            fprintf(pF1, "%c\n", answer);

            // Reset line counter for the next question block
            line_count = 0;
        }
    }

    // Close the files
    fclose(pF);
    fclose(pF1);

    printf("Quiz completed. Answers saved to test2.txt.\n");
    return 0;
}