# c-CATch
A portation of my game CATch, using SDL

The Original game can be found here: [http://victorswelt.de/catch.html](http://victorswelt.de/catch.html)

## Building the game
You need the package `libsdl1.2-dev`
Under Debian / Ubuntu, you can install it by running


`sudo apt-get install libsdl1.2-dev`


to build the game, run:


`gcc -lSDL -o c-CATch catch.c BitmapFontRenderer.c PidginImage.c`


After that you can start it by running


`./c-CATch`

Or, if you want to start the game in fullscreen mode

`./c-CATch -fs`

## Controls
* Up / Down Arrows -    Change Menu Entry
* Return           -    Select Menu Entry
* F                -    Toggle Fullscreen (Only supported with X11)
* Space            - Press to charge jump
* ESCape           -   Closes the program
