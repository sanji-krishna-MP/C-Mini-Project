#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int is_valid_decryption(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        
        if (!isprint(ch) && !isspace(ch)) {
            fclose(file);
            return 0; 
        }
    }
    fclose(file);
    return 1; 

int main() {
    FILE *encrypted, *decrypted;
    char ch;
    int key;
    int found = 0;

    // Open the encrypted file(give your file location)
    encrypted = fopen("D:\\c files checker\\encryptedfile.txt", "r");
    if (encrypted == NULL) {
        printf("Error in opening the encrypted file\n");
        return 1;
    }

    
    for (key = 1; key <= 255; key++) {
        // Rewind the file pointer to the start for each key
        rewind(encrypted);

       
        char temp_filename[50];
        sprintf(temp_filename, "D:\\c files checker\\temp_decrypted.txt");
        decrypted = fopen(temp_filename, "w");
        if (decrypted == NULL) {
            printf("Error in creating temporary decrypted file\n");
            fclose(encrypted);
            return 1;
        }

        
        while ((ch = fgetc(encrypted)) != EOF) {
            fputc(ch - key, decrypted);
        }

        fclose(decrypted);

        // FOR VALIDATION
        if (is_valid_decryption(temp_filename)) {
            printf("Decryption successful with key: %d\n", key);
            printf("Decrypted data saved in: D:\\c files checker\\decryptedfile.txt\n");

            
            rename(temp_filename, "D:\\c files checker\\decryptedfile.txt");

            found = 1;
            break;
        }
    }

    fclose(encrypted);

    if (!found) {
        printf("Decryption failed. No valid key found.\n");
    }

    return 0;
}
