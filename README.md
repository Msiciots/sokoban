# Sokoban
The Sokoban game is implemented with C++ and Qt5. You could custom the game maps by youself.
## Overview
The game start menu.

<img src="https://github.com/Msiciots/sokoban/raw/master/screenshot/start_menu.png" width="30%">

The game screenshots.

<img src="https://github.com/Msiciots/sokoban/raw/master/screenshot/game.png" width="80%">

### Custom your maps.  
This is the map of above game screenshot in the maps folder. And the follow are definitions.  
First integer -> column  
Second integer -> row  
0 -> blank  
1 -> wall  
2 -> ground  
3 -> box  
4 -> flag  
5 -> player  
6 -> box on flag  
7 -> player on flag  

```
$ cat maps/map2.txt
10 9
1 1 1 1 1 1 1 1 1 1
1 1 1 2 2 2 1 4 2 1
1 1 1 2 2 3 2 2 4 1
1 1 2 2 3 4 1 3 2 1
1 1 2 1 1 3 1 2 1 1
1 2 2 2 4 2 2 3 2 1
1 2 4 2 1 2 2 2 2 1
1 1 1 1 1 1 1 5 1 1
1 1 1 1 1 1 1 1 1 1 
```
## Build & Run
Set up executable environment
```
# preinstall : g++, make
$ sudo apt-get install -y qt5-default
```
Run the executable game file directly.
```
$ ./sokoban
```
If you make some changes on codes, building before running
```
$ make
$ ./sokoban
```
## Future work
Implement "undo move" functionality with stack data structure.