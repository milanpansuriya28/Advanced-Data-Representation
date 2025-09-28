# CS 3503 Assignment 2 – Data Representation and Mapping

## Author
Milan H. Pansuriya

## Description
This project builds on Number Base Conversion adding advanced data representation features used in computer architecture.  
It introduces direct base conversions (octal, binary, hexadecimal) and several signed integer representations while reusing the test framework from Number Base Conversion file.

## What’s New  
- **Direct Mapping Functions**
  - `oct_to_bin` – convert octal to binary (3-bit mapping)
  - `oct_to_hex` – convert octal to hexadecimal through binary
  - `hex_to_bin` – convert hexadecimal to binary (4-bit mapping)
- **Signed Number Representations**
  - `to_sign_magnitude`
  - `to_ones_complement`
  - `to_twos_complement`
- Updated the Assignment 1 test framework to handle new functions.
  
## How to Compile and Run
1. Make sure **GCC** is installed on your system.  
2. Place all files in the same folder.  
3. Open a terminal or command prompt and navigate to that folder. 
4. Compile the program: `gcc -o convert main.c convert.c`
5. Run the program: `./convert`

## Files Included
- `convert.c` – Implementation of all conversion functions  
- `main.c` – Test driver and file I/O  
- `a2_test.txt` – Test cases  
- `README.md` – This file

## Notes for Beginners
- This code is written with extra comments to help understanding
- Each function does one specific task
- Variable names are descriptive
- Error handling is included for file operations
- The program maintains backward compatibility with Number Base Conversion file functions.

## References
Some resources that helped while completing this assignment:
- Assignment 2 instruction sheet (provided by the course)  
- YouTube videos on number system conversions and signed representations  
- C standard library documentation for string and file functions
