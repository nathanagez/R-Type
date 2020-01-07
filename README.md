![](https://cdn03.nintendo-europe.com/media/images/10_share_images/games_15/virtual_console_wii_u_7/H2x1_WiiUVC_RType_image1600w.jpg)
# R-Type
The purpose of this project was to create a one-to-four player game, using a client/server architecture. Peer-to-peer communication was not allowed.


## Build
### Unix System
```bash
mkdir build && cd build && conan install .. --build=missing && cmake
.. -G “Unix Makefiles” && cmake --build .
```
### Windows
For Windows, it generate a Visual Studio solution file

## Protocol
We have designed a binary protocol for client/server communications.
We used UDP for communications between the server and the clients. A second connection using
TCP have been tolerated but we had to provide a quite strong justification. In any event, ALL in-game communications had to use UDP.

## Libs
* SFML on the client side
* Sockets from scratch for the server (No BOOST lib)

## Engine (Evaluation)

> Your engine will be reviewed and we will focus on the following points:
>* Runtime extensibility: the ability to add systems to a game through the form of dynamic libraries,
scripts...
>* Compile-time safety: if your engine provides no type-safety at compile-time, using it may lead to
code that’s unclear
>* Ease of use: when encountering your engine for the first time, how easy is it to create a simple game
like Snake?
