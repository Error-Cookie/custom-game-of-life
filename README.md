# Custom Game of Life

My Custom Game of Life is a modified version of the original John [John Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) which has additional types of cells with their own rules. The game is played one a board with cells where each cell can have different states(cell types). Each generation the board is calculated new while cells can die, revive or spawn.

## Download

Coming Soon

## Usage

Create a file called 'input.txt' in the same directory as the executable. Samples can be found in the [tests](https://github.com/Error-Cookie/custom-game-of-life/tree/master/tests) directory or in the [sample.input.txt](https://github.com/Error-Cookie/custom-game-of-life/blob/master/sample.input.txt) file. At the beginning of the input file put the number of cells you want to place, any other cells will be generated as dead. Now for every line put three numbers. First one indicating the row of the block, counted from the top, beginning with zero and the second one indicating the column, counted from the left, also beginning with zero. The third number is the type of the block. The console will print a twelve by ten board with its generation number above it for every generation. There is an 500 milliseconds delay between every generation. These constants(width, height, delay) can be changed by editing the source code and recompiling it yourself.

## Cell Types
There are currently 6 different types of cells:
- '#' - dead
- '0' - alive
- '1' - permanent
- '2' - toxic
- '3' - generator
- '4' - exploding

The DEAD cells do not affect the game but can be revived when there are exactly three cells of any type around them.

The ALIVE cells die when there are not enough other cells around them. They need two or three cells around them to survive. When there are less or more they die.

The PERMANENT cells count as alive cells but cannot die.

The TOXIC cell is a permanent cell which kills all alive cells around it.

The GENERATOR is a permanent cell that generates alive cells which spawn around it. Some generations it doesn't spawn an alive cell. The spawned cells spawn on a random field around the generator cell.

The EXPLODING cell is generated when one dead cell is surrounded by eight alive cells. It lives for one generation and then explodes destroying all alive cells around it.

## License
[MIT](https://choosealicense.com/licenses/mit/)
