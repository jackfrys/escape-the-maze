# Instructions

Launch the game from the terminal with `$ ./main`. (Run `./install_cxx` to install the required testing library.) Follow the prompt to choose a difficulty level.

Once in the maze, use the arrow keys to move the player, `blue`. Collect all the key fragments, `yellow`, to create the key, while avoiding the guards, `green`.

Once all key fragments have been collected, exit the maze and win by navigating to the lower right corner. Any contact with a guard will cause you to lose a life. When all lives are lost, the game is terminated.

To run the unit tests, first make sure that the `cxxtest` testing library is installed in the project folder. Run the `install_cxx` script to download and unpack it in the right place. Then invoke `make test` to build the tests and `./test` to run them.
