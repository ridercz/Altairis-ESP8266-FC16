# Altairis ESP8266-FC16 Library

**Library for using the FC-16 display module (based on MAX72xx) with ESP8266 (NodeMCU) and Arduino IDE.**

![FC-16](http://i.imgur.com/BfVPy8h.jpg)

There is a very nice display module with MAX7219 and four 8x8 matrix displays. And then there is a very nice Arduino-compatible board called *ESP8266* or *NodeMCU*. But there was no nice way to make them work together.

There was a way, using the *[LedControlSPIESP8266](https://github.com/labsud/LedControlSpipESP8266) Library* by LABsub, but it was not very nice way, not high-level enough. So I created a new library on top of it.

> **Disclaimer:** I'm web developer by trade, used to luxuries of C# and ASP.NET. Coding in C++ for Arduino is still kind of new to me and this is actually the first Arduino library I ever released. 

> If you notice some oddities in my code, please let me know, or even better, send a pull request.

## Features

* Supports any number of displays (1-8).
* Allows addressing of all displays in one go (for example, 4-matrix block is treated like one display with 8 rows and 64 colums).
* Support for showing bitmaps.
* Support for scrolling text. Not fancy Parola-like effects, but plain right-to-left scroll is good enough.

## How to Install and Use

1. Download and intall [LedControlSPIESP8266](https://github.com/labsud/LedControlSpipESP8266) library, which is prerequisite.
2. Download latest version from [Releases](https://github.com/ridercz/Altairis-ESP8266-FC16/releases) as a ZIP file and then use standard ZIP library install process. Or clone this repository into your `Libraries` folder.

For documentation see `examples` folder and [wiki](https://github.com/ridercz/Altairis-ESP8266-FC16/wiki).

## Development Note

I'm using Visual Studio 2015 and the "Visual Micro Arduino IDE" plugin for Arduino projects. There is appropriate `.sln` in the `project` folder. You can edit the `.ino`, `.h` and `.cpp` files in Arduino IDE or any other editor of your choice, just ignore the `project` folder.

## License

Copyright (c) Michal Altair Valasek, 2016

Licensed under terms of the MIT license.