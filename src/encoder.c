#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./libraries/stb_image_write.h"


char* calculate_checksum(const char *binaryData) {
    uint8_t checksum = 0;

    // Iterate through the binary data in chunks of 8 bits (1 byte)
    for (size_t i = 0; i < strlen(binaryData); i += 8) {
        int byte = 0;
        for (int j = 0; j < 8; j++) {
            if (i + j < strlen(binaryData)) {
                byte |= (binaryData[i + j] - '0') << (7 - j);
            }
        }
        checksum += byte; // Add the byte to the checksum
    }

    char *binaryChecksum = (char *)malloc(9 * sizeof(char));
    if (binaryChecksum == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Convert the checksum to an 8-bit binary string
    for (int i = 7; i >= 0; i--) {
        binaryChecksum[7 - i] = (checksum & (1 << i)) ? '1' : '0';
    }
    binaryChecksum[8] = '\0'; 

    return binaryChecksum;
}

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
    return imageData;
}


void encode (char* imageData, const char* message, const char* key, int imageDataLength) {

    // Copy the original image data to the encoded image buffe
    char *keyBinary = stringToBinary(key);
    char *messageBinary = stringToBinary(message);
    char* checksum = calculate_checksum(message);
    int index = 7;
    for (size_t j = 0; j < strlen(messageBinary); j++) {
        imageData[index] = messageBinary[j];
        index += 8;
    }

    for (size_t t = 0; t < strlen(keyBinary); t++) {
        imageData[index] = keyBinary[t];
        index += 8;
    }

    for(int u = 0; u < 8; u++) {
        imageData[index] = checksum[u];
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
    int index = 0;
    
    
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
        index = i * 8 + 7;
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
    char *checksum = calculate_checksum(message);

    int checkSumPass = 1;
    index += 16; //shift the index by 2 bits to match the current index.
    for (int i = 0; i < 7; i++) {
        if (checksum[i] !=binaryStr[index + 8*i]) {
            printf("Data Lost/Message is incorrect");
            checkSumPass = 0;
        }
    }
    if (checkSumPass == 1) {
        printf("No Data Lost :)");
    }
    return message;
}



int main() {

    FILE *outputFile = fopen("./output/output.txt", "wb"); // Open output image file in write mode
    int width, height, channels;
    const char KEY[] = "|||";
    const char MESSAGE[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    
    unsigned char *inputFilePoint = stbi_load("./images/image.png", &width, &height, &channels, 0);
    if (outputFile == NULL) {
        printf("failed to create/open output image file");
        fclose(outputFile);
        return 1;
    }

    printf("filesize: %d x %d\n", width, height);

    char *imageData = imageToBinary(inputFilePoint, width, height, channels);
    encode(imageData, MESSAGE, KEY, width*height*channels);

    fprintf(outputFile, imageData, "%s");
    //unsigned char* actualImageData = binaryToImage(imageData, width, height, channels);
    unsigned char* actualImageData = binaryToImage(imageData, width, height, channels);
    

    if (stbi_write_png("./output/outputImage.png", width, height, channels, actualImageData, width * channels)) {
        printf("\nImage successfully written\n");
    } else {
        printf("\nFailed to write image\n");
    }
    

    printf("\ndecoded message: %s", decode(imageData, KEY));
    // Close the output file and free the image data from memory
    fclose(outputFile);
    stbi_image_free(inputFilePoint);

    return 0;
}


