# Match 3


## Description

Test task from SberGames. Given a 6x6 field with 4 types of chips, except 0 or nullptr. Chips drops down after matching 3 in a row. Implement a function that determines whether there is at least one possible move on the field. You can swap two vertical or horizontal neighbours.

## Solutions

1. Naive algorithm: let's go over all the possible movements(O(N^2)) of the chips and check if it turns out 3 in a row. To check all rows and columns for a given filed we need O(N^2). Total complexity: O(N^4).
2. Note that after swapping two cells of the field, no more than two columns or lines will be changed. Then it is enough for us to check only them. Total complexity is O(N^3)
3. Remains to learn how to check a column or row faster than O(N). Focus on the row where we changed the i'th element. It is enough to check only the previous two and the next two cells. Obviously, if there was not 3 in a row on the field, then after the made move there will be not more than 5. This optimization allows checking only adjacent cells to 'i' and reduces the checking of the row to a constant.
4. To complete task, I wrote preprocessing before analize the move. We need to check that current field has not 3 in a row/column. Otherwise delete such cells and move non-empty chips to bottom.

## License

MIT
