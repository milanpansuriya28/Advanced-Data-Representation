# CS 3503 Assignment 2 – Data Representation and Mapping

## Author
Milan H. Pansuriya

## Description
This project builds on Number Base Conversion adding advanced data representation features used in computer architecture.  
It introduces direct base conversions (octal, binary, hexadecimal) and several signed integer representations while reusing the test framework from Number Base Conversion file.

## What the Program Does
The program includes:
- **Direct Mapping Conversions**
  - `oct_to_bin` – octal to binary using 3-bit mapping
  - `oct_to_hex` – octal to hexadecimal through binary
  - `hex_to_bin` – hexadecimal to binary using 4-bit mapping
- **Signed Number Representations**
  - `to_sign_magnitude`
  - `to_ones_complement`
  - `to_twos_complement`
- Automated testing that compares function output to expected results.
  
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

## References
Some resources that helped while completing this assignment:
- Assignment 2 instruction sheet (provided by the course)  
- YouTube videos on number system conversions and signed representations  
- C standard library documentation for string and file functions
