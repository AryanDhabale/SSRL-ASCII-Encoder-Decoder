#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./libraries/stb_image.h"

int main() {

    FILE *inputFile;
    FILE *outputHexFile;
    FILE *outputFile;
    int fileSize;
    size_t totalBytes;
    unsigned char *buffer; //pointer b/c we need to use malloc to make some memory for the whole file

    const char KEY[] = "|message|";
    const char MESSAGE[] = "Gooo Dawgs! Sic 'em! Woof wOof wOOf woOf!";
    for (int i = 0; i < strlen(KEY); i++) {
        printf("%02X", KEY[i]);
    }
        printf("\n");
    for (int i = 0; i < strlen(MESSAGE); i++) {
        printf("%02X", MESSAGE[i]);
    }
    /*
        NOTE: The stars before some variable names are used to designate pointers, as variables in C, unlike java
        are actual variables themselves, and not references to objects in memory. ex. if I do x = 10, and y = x, instead of 
        having y point to the same value x is pointing at, it just copies the values and has a whole seperate variable, which takes
        up more memory. The star however, makes it act like a variable in java, where it is just a pointer, and not the actual variable
    */
    inputFile = fopen("./images/image.png", "rb");  // Open PNG file in binary mode
    outputHexFile = fopen("./output/output.txt", "w");  // Open output hex file in write mode
    outputFile = fopen("./output/outputImage.png", "wb"); // Open output image file in write mode

    if (inputFile == NULL) {
        printf("Failed to open image file\n");
        return 1;
    }

    if (outputHexFile == NULL) {
        printf("Failed to open output file\n");
        fclose(outputHexFile);  
        return 1;
    }

    if (outputFile == NULL) {
        printf("failed to create/open output image file");
        fclose(outputFile);
        return 1;
    }


    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    

   
    
    /*
        NOTE: CHAR is used instead of INT because an int can store 4 bytes of data, whereas
        a char can only store upto one byte. Even though fread is parsing through the file one byte at a 
        time, since an int can store upto 4 bytes, it might lose some memory/data, or have some trouble parsing through
        the file data.
    */
    buffer = (unsigned char *)malloc(fileSize * sizeof(char));
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(inputFile);
        return 1;
    }

    // Read data into buffer (a temporary allocation of memory)
    totalBytes = fread(buffer, 1, fileSize, inputFile);
     if (totalBytes != (size_t)fileSize) {
        perror("Error reading file");
        fclose(inputFile);
        free(buffer);
        return 1;
    }
    
    
    // Print raw binary data in hexadecimal format
    for (size_t i = 0; i < totalBytes; i++) {
        fprintf(outputHexFile, "%02X ", buffer[i]);  // Print each byte in hex       
        //if (i % 30 == 0) {
          //  fprintf(outputHexFile, "\n");
        //}
    }


    
    //fprintf(output, "width: %d\nheight: %d", width, height);
    fclose(outputHexFile);
    fclose(inputFile);
    return 0;
}
