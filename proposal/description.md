# Description

We will create a maze game where the user has to go navigate a randomly-generated environment, collecting key fragments as they go. When all key fragments are collected, the resulting key can be used to open the door at the end of the maze. THe user's character will be controller by arrow keys.

Working against the user, there are guards patrolling the maze. Get too close to a guard and the game is over.

Difficulty is increased by adding guards, key fragments, and size to the maze.

This game combines mechanics from traditional maze games as well as game that require escaping and collecting a series of objects, avoiding enemies, and escaping. This game combines different elements and creates a random, new environment each time with adjustable difficulty.

The different characters and items in the game will be represented as individual classes. They can keep track of their own locations and movements. The autonomous objects can thereby control themselves. We will likely also use a more complex object to manage the entire environment.

As we learn more about the available graphics libraries, we will possibly organize the functions we need into objects that are easier to reuse.

Since the number of objects on screen at once will be roughly constant within one game, memory usage during one game will likely be roughly constant as well. As one game ends, the objects left over from the previous game can be discarded or re-used in the next game.
