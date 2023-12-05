# DAY 5: If You Give A Seed A Fertilizer

## Information

- Help with food production using the Island Island Almanac.
- Data: Almanac
    - All the seeds that need to be planted.
    - Lists:
        - What type of soil to use with each kind of seed.
        - What type of fertilizer with each kind of soil.
        - What type of water to use with each kind of fertilizer.
        - And so on.
    - Each type of soil, fertilizer, etc. is identified with a number and they are reused in categories.
    - Almanac starts with which seeds need to be planted.
    - The rest of almanac contains a list of maps, which describe how to convert numbers from a **source** to **destination** category.
    - The map is described with **ranges**
    - Every line in a map contains three numbers:
        - ``dest src range``
    - Numbers that aren't mapped correspond to the same destination number.

## Challenge 1

- Map the seed to the location.
- Find **the lowest location number that corresponds to any of the initial seeds**.

## Solution

- Read Seed line and store in array.
- Map each category, save new numbers in the array.
    - If source in range :
        - ``Destination = destination_start + source - source_start``
- Traverse array and take smallest.

## Challenege 2

- The seeds line actually describes **range of seed numbers**.
- The initial values are actually in **pairs**.
- First value is **start** of the range and the second is **length** of the range.
- **What is the lowest location number that corresponds to any of the initial seed numbers?**

## Solution

