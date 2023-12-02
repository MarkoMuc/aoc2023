# DAY 1 Notes Trebuchet?!

## Information

- Calibration document needs to be read.
- Calibration values are two digit values.
- Data: Calibration document
    - Consists of lines of text.
    - Each line contains a calibration value. They need to be recovered.
    - The digits are in range 1 to 9.

## Challenge 1

- On each line the calibration value can found by combining the **first** and **last** digit to form a single **two-digit** number.
- *What is the sum of all of the calibration values?*

## Solution

- If only one digit is in the line, then this digit also counts as the last digit.
- Parse line one character at a time:
    - If the character is a digit, then take the value.
        - If its the first digit found, set it as first and last value.
        - Otherwise set it as last value.

## Challenge 2

- Same as before, but the digit **can also be spelled with letters, e.g one, two, three,...**

## Solution

- Parse the line
    - If the first character in the line is a digit, do the same as challenge 1.
    - Otherwise check if its a spelled digit:
        - Take a substring of 3, 4 and at the end 5 characters, from the first one.
        - Compare the substring.
            - If true return the value and exit function.
            - Otherwise check with one character larger substring.
    - Shift the line one character to the left
