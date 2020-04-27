# Focus
Focus (Board Game)
[![asciicast](https://asciinema.org/a/xfSZIlrkSyhbYbSkXhlOcXpwF.svg)](https://asciinema.org/a/xfSZIlrkSyhbYbSkXhlOcXpwF)
### Dependencies
[CMake](https://cmake.org/download/) is the easiest way to build the files.

#### Macintosh
Mac systems come pre-installed with ncurses so it should run instantly

#### Linux
##### Ubuntu
Make sure to install the following ncurses libraries using 

``` sudo apt-get install libncurses5-dev libncursesw5-dev```
##### Other
Finding ncurses might be a pain from some users as where it's installed varies from user to user

One user suggested the use of 
```
set( CURSES_INCLUDE_PATH "/usr/include")
set( CURSES_LIBRARY "/usr/lib/libncurses.so")
```

This'll differ from user to user due to how linux installs stuff from user to user.

### Running
Once you've got the game compiled, run it in an external terminal(Not the one that comes with CLion).

Make sure to put the terminal to full screen.

Enjoy!