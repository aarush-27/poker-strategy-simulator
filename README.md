## Card Representation

In the program, each card in a standard 52-card deck is represented by an integer from **0 to 51**.

### Suit Encoding

| Suit     | Value |
| -------- | ----- |
| Hearts   | 0     |
| Diamonds | 1     |
| Clubs    | 2     |
| Spades   | 3     |

### Rank Encoding

| Rank  | Value |
| ----- | ----- |
| 2     | 0     |
| 3     | 1     |
| 4     | 2     |
| 5     | 3     |
| 6     | 4     |
| 7     | 5     |
| 8     | 6     |
| 9     | 7     |
| 10    | 8     |
| Jack  | 9     |
| Queen | 10    |
| King  | 11    |
| Ace   | 12    |

### Card Index Formula

Each card is encoded using the formula:

```
card = suit * 13 + rank
```

Examples:

| Card          | Value |
| ------------- | ----- |
| 2 of Hearts   | 0     |
| Ace of Hearts | 12    |
| 2 of Diamonds | 13    |
| King of Clubs | 37    |
| Ace of Spades | 51    |

### Extracting Rank and Suit

The program retrieves rank and suit using:

```
rank = card % 13
suit = card / 13
```

This representation allows the entire deck to be stored in a simple integer array.
