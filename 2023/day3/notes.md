# DAY 3: Gear Ratios

### This time the solution is quite ugly and could be done much better

## Information

- An engine does not work, the cause is a missing engine part.
- **If you add up all the part numbers** in the engine schematic, it should be able to make out which part is missing.
- Data: Engine schematic
    - A lot of numbers and symbols.
    - A **.** does not count as a symbol.

## Challenge 1

- **Any number adjecent to a symbol**, even diagonally, is a part number and should be included in the sum.
- Sum up all the part numbers.

## Solution

- Put the data into an array.
- If you meet a number, check all 8 positions around each digit for a symbol.
- If found a valid part, add it to the sum

## Challenge 2

- A **gear** is any <b>*</b> symbol that is adjecent to **excatly two part numbers**.
- Its **gear ratio** is multiplication of both adjecent part numbers.
- Sum all gear ratios

## Solution

- Check lines for an asterisk.
- If an asterisk is found, search 8 places all around it for a digit.
    - If a digit is found, move left till and afterwards right, untill you get the whole number
    - Save it
    - Keep searching until all numbers are found
- If there are only two numbers multiply them and add them to the sum, otherwise don't save the numbers
