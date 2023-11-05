#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processFile(char *inputFileName, int isEncrypting); //process the input file
void processLine(char *line, FILE *outputFile, int isEncrypting); // processing the input file line by line
char *changeFileExtension(char *originalName, char *newExtension); // changes filename extension to correspond with encrypt or decrypt
int hexCharToInt(char c); // helps to ensure the correct conversion of characters during the encryption and decryption processes.

int main(int argc, char *argv[]) { //handling command-line arguments and orchestrating the code logic.
    if (argc < 2 || argc > 3) { // checks if user had the correct number of command-line arguments.
        printf("Usage: cryptoMagic [-E | -D] <filename>\n");  // informing the user to state the correct command line of either -E or -D
        return 1; // signals to the user that there is an error in their inputs.
    }
    int isEncrypting = 1; // indicates utility is in encryption mode
    char *inputFileName = (argc == 3) ? argv[2] : argv[1]; 
    if (argc == 3 && strcmp(argv[1], "-D") == 0) {
        isEncrypting = 0; //indicates utility is in decryption mode
    }
    processFile(inputFileName, isEncrypting); //ensures the processing of the input file for the correct mode
    return 0;
}

void processFile(char *inputFileName, int isEncrypting) { // defines the process file function, which takes two parameters.
    FILE *inputFile = fopen(inputFileName, "r"); //opens the input file
    char *outputFileName = changeFileExtension(inputFileName, isEncrypting ? "crp" : "txt"); // calculates the name of the output file name & runs a crp or txt extension.
    FILE *outputFile = fopen(outputFileName, "w"); // opens output file with the name determined in the previous step.
    char line[isEncrypting ? 121 : 256]; // declares an array called line. if encryption is true array is set to 121. ; otherwise, it's set to 256. This array is used to store lines read from the input file.
    while (fgets(line, sizeof(line), inputFile)) { // while loop that iterates through the input file.
        processLine(line, outputFile, isEncrypting); // processing these 3 threads
    }
    fclose(inputFile); // after parsing through this file it gets closed to release system resources.
    fclose(outputFile); // after parsing through this file it gets closed to release system resources.
    free(outputFileName); // after parsing through this file it gets closed to release system resources.
}

void processLine(char *line, FILE *outputFile, int isEncrypting) { // defines the processing function which takes three parameters
    char *ptr = line, buffer[3] = {0}; // buffer array used to store temporary character data during the processing of the loop.
    while (*ptr != '\0' && *ptr != '\n') { // iterates through the input character lines until it encounters either the end of the string ('\0') or a newline character ('\n')
        if (isEncrypting) { // checks if encrypt is the right protocol to perform.
            if (*ptr == '\t') {
                fputs("TT", outputFile); // This action is part of the character transformation process specific to encryption, if the current character pointed to by ptr is a Tab character ('\t'), it writes the string "TT" to the outputFile using fputs.
            } else { //executes when encrypting is false
                int outChar = *ptr - 16; //character processing; This line subtracts 16 from the ASCII value of the character pointed to by ptr and assigns the result to the integer variable outChar. This is a basic character transformation step.
                if (outChar < 32) { // This condition checks if the calculated outChar value is less than 32.

                    outChar = (outChar - 32) + 144; //If outChar is less than 32, this line further transforms the character value by subtracting 32 and then adding 144, to ensure that the ensure that the character value remains within the printable ASCII character range.
                }
                fprintf(outputFile, "%02X", outChar); // Converts to hexadecimal and stores the output in the output file.
            }
        } else {
            if (*ptr == 'T' && *(ptr + 1) == 'T') { // checks if pointer array = to T
                fputc('\t', outputFile); // if both TT conditions are true it's replaced with t.
                ptr++; // Skip the next 'T'
            } else { // When the code does not encounter the 'TT' pattern, it proceeds to process the characters in pairs.
                buffer[0] = *ptr; // assigning the characters to temporary arrays for further processing.
                buffer[1] = *(ptr + 1); // assigning the characters to temporary arrays for further processing.
                int outChar = hexCharToInt(buffer[0]) * 16 + hexCharToInt(buffer[1]); // it converts the characters in buffer from hexadecimal representation to an integer value, using the new character value outChar.
                outChar += 16; // After the initial calculation, 16 is added to outChar
                if (outChar > 127) {
                    outChar = (outChar - 144) + 32;
                } // This condition checks if outChar is greater than 127, which is outside the printable ASCII character range. If outChar is greater than 127, it undergoes additional transformation:outChar is first subtracted by 144, bringing it within the printable ASCII range.Then, it is further transformed by adding 32. This ensures that the character remains within the range of printable ASCII characters.
                fputc(outChar, outputFile); // writes the transformed character to the outputFile
                ptr++; // Skip the next character
            }
        }
        ptr++;
    }
    fputc('\n', outputFile); // writes a newline character ('\n') to the outputFile. This is typically done to separate lines of text in the output file, providing a line break.
}

char *changeFileExtension(char *originalName, char *newExtension) { // defines the function which takes 2 parameters
    char *newName = malloc(strlen(originalName) + strlen(newExtension) + 1); // This line dynamically allocates memory for a new string, newName, that will hold the modified file name. 
    strcpy(newName, originalName); // This line copies the original file name, originalName, into the newly allocated memory for newName.
    char *lastDot = strrchr(newName, '.'); // This line searches for the last occurrence of a dot ('.') in the newName string. This is used to identify the current file extension.
    if (lastDot) *lastDot = '\0'; // If a dot is found, this line replaces the dot with a null terminator, effectively truncating the file name at the position of the last dot. This step removes the current file extension.
    strcat(newName, "."); // This line appends a dot ('.') to the end of the newName string, preparing it for the new file extension.
    strcat(newName, newExtension); // This line appends the new file extension specified in newExtension to the newName string
    return newName; //  the modified newName string is returned. It represents the original file name with the changed file extension.
}

int hexCharToInt(char c) { // This line defines the function, which takes a single parameter, c, representing a hexadecimal character to be converted.
    if (c >= '0' && c <= '9') return c - '0'; // If c is a character between '0' and '9', it means c represents a digit in the range 0-9. In this case, the function directly converts the character to its corresponding integer value by subtracting the ASCII value of '0' (which is 48). For example, if c is '5', the function returns 5 as an integer.
    return c >= 'A' && c <= 'F' ? c - 'A' + 10 : c - 'a' + 10; // If c is not a digit (i.e., it's an uppercase letter from 'A' to 'F' or a lowercase letter from 'a' to 'f'), it represents a hexadecimal character from A to F (or a to f).In this case, the function returns the integer value corresponding to the hexadecimal character. It does this by:If c is an uppercase letter ('A' to 'F'), it calculates the integer value by subtracting the ASCII value of 'A' (which is 65) and adding 10. For example, if c is 'B', the function returns 11 as an integer.If c is a lowercase letter ('a' to 'f'), it follows the same logic but subtracts the ASCII value of 'a' (which is 97). For example, if c is 'c', the function returns 12 as an integer.
}
