#include <stdio.h>


int main() {
    FILE *file = fopen("./images/image.png", "rb");  // Open PNG file in binary mode
    FILE *output = fopen("./.txt/output.txt", "w");  // Open output file in write mode

    if (file == NULL) {
        printf("Failed to open image file\n");
        return 1;
    }

    if (output == NULL) {
        printf("Failed to open output file\n");
        fclose(file);  // Close the image file if output file fails to open
        return 1;
    }
    
    unsigned char buffer[5];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    
    // Print raw binary data in hexadecimal format
    for (size_t i = 0; i < bytesRead; i++) {
        fprintf(output, "%02X ", buffer[i]);  // Print each byte in hex
    }

    fclose(output);
    fclose(file);

    return 0;
}
