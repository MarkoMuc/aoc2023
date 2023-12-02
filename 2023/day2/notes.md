# DAY 2: Cube Conundrum

## Information

- A bag with cubes, the cubes are Red, Green or Blue.
- Each time the game is played, a secret number of each color is in the bag.
- Goal is to figure out information about the number of cubes.
- To get information, a handful of cubes is taken out, shown and put back in. This is done few times per game.
- Data : One game per line
    - Game ID : semi-colon seperated list of subsets of cubes that were revealed, ends with ``\n``

## Challenge 1

- Determine which game can be played, **if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes**
- Question : **What is the sum of the IDs of those games?**

## Solution

- Read line by line :
    - Save ID
    - Look for RGB values
        - If larger, break and go to next line
        - Else keep checking
    - Add ID to the sum, if you didn't break

## Challenge 2

- In each game you played what is the **fewest number of cubes of each color that could have been in the bag to make the game possible?**
- The power of a set of cubes is the minimum amount of R,G,B cubes multiplies together.
- **What is the sum of the power of these sets?**

## Solution

- Read line by line:
    - Look for RGB values
        - Take max of R,G,B
        - Multiply them together

