#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"

char* imageToBinary(unsigned char* inputFilePoint, int width, int height, int channels) {
    size_t totalBytes = width * height * channels;  // total number of bytes of image data
    size_t bufferSize = totalBytes * 8 + 1; // Each byte will be converted into 8 bits, plus 1 for null-terminator

    // Allocate memory for the buffer to store binary representation
    char* buffer = (char*)malloc(bufferSize);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int bufferIndex = 0;

    for (size_t i = 0; i < totalBytes; i++) {
        for (int j = 7; j >= 0; j--) {
            buffer[bufferIndex++] = (inputFilePoint[i] & (1 << j)) ? '1' : '0';
        }
    }
    buffer[bufferIndex] = '\0'; 

    return buffer;
}

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
    
    //int hi = stbi__png(outputFile, width, height, inputFilePoint, width * channels);
    fprintf(outputFile,imageToBinary(inputFilePoint, width, height, channels), "%s");
    // Close the output file and free the image data from memory
    fclose(outputFile);
    stbi_image_free(inputFilePoint);

    return 0;
}


