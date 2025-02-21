#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char* calculate_checksum(const char *binaryData);
char* stringToBinary(const char *str);

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
