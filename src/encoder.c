#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"

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
    

   
    
    unsigned char buffer[30107];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
    
    // Print raw binary data in hexadecimal format
    for (size_t i = 0; i < bytesRead; i++) {
        fprintf(output, "%02X ", buffer[i]);  // Print each byte in hex
        if (i % 30 == 0) {
            fprintf(output, "\n");
        }
    }
    
    //fprintf(output, "width: %d\nheight: %d", width, height);
    fclose(output);
    fclose(file);
    return 0;
}
