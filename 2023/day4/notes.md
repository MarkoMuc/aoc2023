# DAY 4: Scratchcards

## Information

- Your goal is to help with scratchcards.
- Each winning number doubles the point value of the card.
- Data: One scratchcard per line
    - Winning numbers are on the left(5 numbers).
    - The cards numbers are on the right(8 numbers).
    - Seperated by **|**

## Challenge 1

- Sum the point values of all scratchcards.

## Solution

- Put each winning number in a buffer.
- Tokenize the candidate numbers.
    - Compare with numbers in the winning buffer.
    - If the number is the same, multiply the points by 2.

## Challenge 2

- There is no such thing as points.
- You win an amount of scratchcards equals to amount of winning numbers.
- You win **copies** of the scratchcards below the winning card.
- Copies of scratchcards are scored like normal ones, but they have the same number as the card they copied.
- Including the original and copies, **how many total scratchcards do you end up with?**

## Solution

- Process all original cards and their "points".
- Save the "points" into an array.
- Create another copies array.
- Iterate the points array(i).
    - Iterate through the points of a game(j), start with offset 1.
        - Add amount of copies[i] plus 1 to copies[i+j].
- Sum the copies array and add 1 for each original.
