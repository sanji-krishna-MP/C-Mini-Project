#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Function to send an email with attachments
int send_email_with_attachment(const char *file_path1, const char *file_path2) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;
    curl_mime *mime;
    curl_mimepart *part;

    // SMTP server and authentication details
    const char *smtp_server = "smtp://smtp.gmail.com:587"; // Use TLS (port 587)
    const char *username = "sanjimurali08@gmail.com";     // Replace with your email
    const char *password = "zhzqfxsfblofkiga";            // Replace with your App Password
    const char *recipient_email = "gurucharancl@gmail.com"; // Constant recipient email

    curl = curl_easy_init();
    if (curl) {
        // Set SMTP server and authentication details
        curl_easy_setopt(curl, CURLOPT_URL, smtp_server);
        curl_easy_setopt(curl, CURLOPT_USERNAME, username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        //for Specifying sender and recipients
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, username);
        recipients = curl_slist_append(recipients, recipient_email);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Create MIME structure for email
        mime = curl_mime_init(curl);

        // Add the email body
        part = curl_mime_addpart(mime);
        curl_mime_data(part, "Hello,\r\nPlease find the attached quiz answers and questions.\r\n", CURL_ZERO_TERMINATED);

        // Attach the first file (test.txt - questions)
        part = curl_mime_addpart(mime);
        curl_mime_filedata(part, file_path1); // Specify the file to attach (questions)

        // Attach the second file (test2.txt - answers)
        part = curl_mime_addpart(mime);
        curl_mime_filedata(part, file_path2); // Specify the file to attach (answers)

        // Set the MIME structure
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Email sent successfully with attachments to %s!\n", recipient_email);
        }

        // Cleanup
        curl_mime_free(mime);
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Error: Unable to initialize CURL.\n");
        return 1;
    }

    return 0;
}

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

    printf("Starting...\n");

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

    printf("Answers saved to test2.txt.\n");

    // Send the email with the quiz files as attachments
    const char *quiz_file_path1 = "D:\\c files checker\\test.txt";  // Original questions file
    const char *quiz_file_path2 = "D:\\c files checker\\test2.txt"; // Answers file

    // Send the email with the files as attachments
    return send_email_with_attachment(quiz_file_path1, quiz_file_path2);
}
