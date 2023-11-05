# MiniProject1
Repository for Ivan and I to upload our code for Mini Project 1 in Engg 1410
# CryptoMagic Utility

CryptoMagic is a command-line utility for encrypting and decrypting text files. It offers a simple and effective way to secure your data or reverse the encryption process.

## About

CryptoMagic is a utility designed to process text files for encryption and decryption. It provides essential features for securing your data or reversing the encryption process. The utility ensures the correct handling of character encoding and file extension changes.

## Input and Output

- **Input**: CryptoMagic accepts text files as input for both encryption and decryption. You specify the input file using the command line as follows:

- Use `-E` for encryption mode.
- Use `-D` for decryption mode.

- **Output**: CryptoMagic generates an output file with the same name as the input file but with the appropriate file extension (`.crp` for encryption, `.txt` for decryption). The output file contains the processed data.


## Getting Started

To get started with CryptoMagic, follow these steps:

### Prerequisites

- Ensure you have a C compiler installed (e.g., GCC).
- You may need to have the appropriate development tools for your system.

#### Compile the code: 
$ gcc cryptomagic.c -o cryptomagic

### Run CryptoMagic:

$ ./cryptomagic [-E | -D] <filename>

Use -E for encryption mode.
Use -D for decryption mode.


Usage
CryptoMagic can be used to encrypt or decrypt text files. Simply provide the appropriate command-line options, and the utility will handle the rest. It ensures character encoding and file extension changes to match the selected mode.

Features
Encryption and Decryption: Securely encrypt and decrypt text files.
Character Processing: Handles character encoding and transformation during the process.
File Extension Change: Automatically changes the file extension to match the selected mode.

