#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"

char* stringToBinary(const char *str) {
    int len = strlen(str);
    int binaryLength = len * 8 + 1; 
    char *binaryStr = (char *)malloc(binaryLength * sizeof(char)); 
    if (binaryStr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        unsigned char byte = str[i];
        for (int bit = 7; bit >= 0; bit--) {
            binaryStr[j++] = (byte & (1 << bit)) ? '1' : '0'; 
        }
    }
    binaryStr[j] = '\0'; 

    return binaryStr; 
}

int main() {

    FILE *inputFile = fopen("./images/image.png", "rb");
    FILE *outputFile = fopen("./output/output.txt", "wb"); // Open output image file in write mode
    
    int fileSize;
    int width, height, channels;
    const char KEY[] = "|msg|";
    const char MESSAGE[] = "Gooo Dawgs! Sic 'em! Woof wOof wOOf woOf!";
    printf("%s", stringToBinary(KEY));
        printf("\n");
    printf("%s", stringToBinary(MESSAGE));


    
    unsigned char *inputFilePoint = stbi_load("./images/image.png", &width, &height, &channels, 0);
    if (outputFile == NULL) {
        printf("failed to create/open output image file");
        fclose(outputFile);
        return 1;
    }


    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    printf("filesize: %d\n", fileSize);
    fseek(inputFile, 0, SEEK_SET);
    

    // Calculate the total size of the image data
    size_t totalBytes = width * height * channels;
    printf("Total bytes: %zu\n", totalBytes); 

    // Write the raw image data to the file
    for (size_t i = 0; i < totalBytes; i++) {
        for (int j = 7; j >=0; j--) {
            fprintf(outputFile, "%d", (inputFilePoint[i] >> j) & 1);
        }
        fprintf(outputFile, " ");
        if ((i + 1) % 4 == 0) {
            fprintf(outputFile, "\n");
        }
    }
    
    //int hi = stbi_write_png(outputFile, width, height, inputFilePoint, width * channels);

    // Close the output file and free the image data from memory
    fclose(outputFile);
    stbi_image_free(inputFilePoint);

    return 0;
}


