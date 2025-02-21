#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./libraries/stb_image_write.h"

char* imageToBinary(unsigned char* inputFilePoint, int width, int height, int channels) {
    size_t totalBytes = width * height * channels;  // total number of bytes of image data
    size_t bufferSize = totalBytes * 8 + 1; // Each byte will be converted into 8 bits, plus 1 for null-terminator

    // Allocate memory for the buffer to store binary representation
    char *buffer = (char*)malloc(bufferSize);
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

unsigned char* binaryToImage(const char *binaryData, int width, int height, int channels) {
    size_t totalBytes = width * height * channels;

    unsigned char *imageData = (unsigned char*)malloc(totalBytes);
    if (imageData == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Convert the binary data back into raw pixel data (image)
    int byteIndex = 0;
    
    for (size_t i = 0; i < totalBytes; i++) {
        unsigned char pixelValue = 0;
        // Each pixel is represented by 8 bits in the binary string
        for (int j = 7; j >= 0; j--) {
            pixelValue |= (binaryData[byteIndex++] - '0') << j;
        }
        imageData[i] = pixelValue;
    }
    printf("end");
    return imageData;
}


void encode (char* imageData, char* message, char* key, int imageDataLength) {

    // Copy the original image data to the encoded image buffe
    
    int index = 7;
    for (size_t j = 0; j < strlen(message); j++) {
        imageData[index] = message[j];
        index += 8;
    }

    for (size_t t = 0; t < strlen(key); t++) {
        imageData[index] = key[t];
        index += 8;
    }
}

char* decode(char *binaryStr, const char *key) {
    size_t len = strlen(binaryStr);
    char *keyInBinary = stringToBinary(key);
    int keyStreak = 0;
    int keyLength = strlen(key);
    size_t numBytes = len / 8;
    size_t extractedLength = 0;
    
    
    // Allocate space for the extracted bits (as a string)
    char *hiddenBits = malloc(numBytes + 1);
    if (!hiddenBits) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    
    // Extract the 8th bit (index 7) from each 8-character group.
    for (size_t i = 0; i < numBytes; i++) {
        // The LSB of the i-th byte is at position (i * 8 + 7)
        hiddenBits[i] = binaryStr[i * 8 + 7];
        extractedLength++;
        if (keyInBinary[keyStreak] == binaryStr[i * 8 + 7]) {
            keyStreak++;
        } else if (binaryStr[i * 8 + 7] == 48) {
            keyStreak = 1;
        } else {
            keyStreak = 0;
        }
        if (keyStreak == keyLength*8) {
            break;
            printf("loop is not broken out of");
        }
    }

    hiddenBits[extractedLength] = '\0';

    
    // Now, every group of 8 bits in hiddenBits will form one ASCII character.
    size_t messageLength = (extractedLength / 8) - strlen(key);
    char *message = malloc(messageLength+1);
    if (!message) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(hiddenBits);
        return NULL;
    }
    for (size_t i = 0; i < messageLength; i++) {
        int asciiVal = 0;
        // Process 8 bits for one character.
        for (int j = 0; j < 8; j++) {
            asciiVal = (asciiVal << 1) | (hiddenBits[i * 8 + j] - '0');
        }
        message[i] = (char)asciiVal;
    }
    message[messageLength] = '\0';
    
    free(hiddenBits);
    return message;
}



int main() {

    FILE *outputFile = fopen("./output/output.txt", "wb"); // Open output image file in write mode
    int width, height, channels;
    const char KEY[] = "|||";
    const char MESSAGE[] = "whatevre you want this to be gngo";
    
    unsigned char *inputFilePoint = stbi_load("./images/image.png", &width, &height, &channels, 0);
    if (outputFile == NULL) {
        printf("failed to create/open output image file");
        fclose(outputFile);
        return 1;
    }

    printf("filesize: %d x %d\n", width, height);

    char *imageData = imageToBinary(inputFilePoint, width, height, channels);
    char *keyBinary = stringToBinary(KEY);
    char *messageBinary = stringToBinary(MESSAGE);
    encode(imageData, messageBinary, keyBinary, width*height*channels);

    fprintf(outputFile, imageData, "%s");

    //unsigned char* actualImageData = binaryToImage(imageData, width, height, channels);
    unsigned char* actualImageData = binaryToImage(imageData, width, height, channels);
    

    if (stbi_write_png("./output/outputImage.png", width, height, channels, actualImageData, width * channels)) {
        printf("Image successfully written\n");
    } else {
        printf("Failed to write image\n");
    }
    

    printf("\ndecoded message: %s", decode(imageData, KEY));
    // Close the output file and free the image data from memory
    fclose(outputFile);
    stbi_image_free(inputFilePoint);

    return 0;
}


