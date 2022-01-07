# War Simulation - a Card Game
Simulation of the popular card game called "War". Created as a project during classes at University. Command line applicataion, no graphical user interface.

The game can be played on different deck sizes. The possible options are: 20, 24, 28, 32, 36, 40, 44, 48, 52.

There are two playing modes available:
mode A - in the event of a war, the player that has no more cards in hand loses. 
mode B - in the event of a war, the player that still has cards in hand, puts the cards needed to finish the war first on the pile of his opponent and then on his own pile. 

The application can run as a simple game simulation - iteration mode 1 or as experiment - iteration mode 0. In this case it runs 1000 times for every mode and deck size and gathers data such as: which player won the game, mean value of moves it took the players to finish the game and the ranks of the hands of both players at the beginning of the game (calculated as the sum of card values).
