# CHESS ENGINE

## Alpha-Beta Pruning & PV splitting

This project implements both serial **Alpha-Beta Pruning** and **PV Splitting** and then tries to compare the performance against each other.

Run ```make clean``` and then ```make``` to compile. It uses ```GLib``` and if the ```make``` command generates errors related to ```GLib```, make sure you have ```GLib```. You can get it by running ```brew install glib```.

> **_NOTE:_** More on GLib: <https://docs.gtk.org/glib/struct.ThreadPool.html>

To start the game:

```bash
./Chess.exe [AI Type]  [depth]  [thread num]
[USAGE]
        [AI Type]:      The method chosen: Serial(1) or parallel(2).
                        Default: 1
        [maxDepth]:     The depth of the search.
                        Default: 5
        [nThreads]:     The number of the thread created.
                        Default: 5

Example: ./Chess.exe 2 4 6
    The above command runs the chess with pv-splitting with 4 depth
    and 6 threads. 

```

Once the game starts, a chess board with be displayed on the terminal and will ask for user input. User input is of the format initial piece location and then the final piece location.
For example:

```bash
MacBook-Pro src % ./Chess.exe 2 4 6 
Starting Game

    a b c d e f g h 
    - - - - - - - - 
1  |r|k|b|q|*|b|k|r|  1
2  |p|p|p|p|p|p|p|p|  2
3  | | | | | | | | |  3
4  | | | | | | | | |  4
5  | | | | | | | | |  5
6  | | | | | | | | |  6
7  |P|P|P|P|P|P|P|P|  7
8  |R|K|B|Q|+|B|K|R|  8
    - - - - - - - - 
    a b c d e f g h 

PLAYER INPUT FORMAT IS: INITIAL DESTINATION

Your Turn: 
a7 a5
```

User will always play as the white player and the computer will always play as the black player. Inputting a valid move will change the state of the board after which the computer will play its move recording both the time it took to play that move in a ```.txt``` file with the name convention: ```time_$AI_Type$.txt```. For example the above execution will generate a time file named ```time_2.txt```. After the move ```a7 a5``` the new board state will be printed out.

```bash
Your Turn: 
a7 a5
    a b c d e f g h 
    - - - - - - - - 
1  |r|k|b|q|*|b|k|r|  1
2  |p|p|p|p|p|p|p|p|  2
3  | | | | | | | | |  3
4  | | | | | | | | |  4
5  |P| | | | | | | |  5
6  | | | | | | | | |  6
7  | |P|P|P|P|P|P|P|  7
8  |R|K|B|Q|+|B|K|R|  8
    - - - - - - - - 
    a b c d e f g h 

Computer's Turn: 

```

Now the computer will proceed with its turn and this will continue till one player wins the game.

> **_NOTE:_** Pawn promotion and castling has not been implemented yet.
