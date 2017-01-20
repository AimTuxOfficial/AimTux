![banner](http://aimtux.net/images/banner.png)

===================

[![Join the chat at https://www.gitter.im/AimTuxOfficial/lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://www.gitter.im/AimTuxOfficial/lobby)

Want to chat or play with other AimTux users? Join us on Gitter!

## What is AimTux?

AimTux is a fully featured internal hack for *CounterStrike : Global Offensive* written in C++.


## Compiling

**Note:** _Do NOT download or compile as the root user_

#### Download the dependencies required to build AimTux:
__Ubuntu-Based / Debian:__
```bash
sudo apt-get install cmake g++ gdb git libsdl2-dev zlib1g-dev
```
__Arch:__
```bash
sudo pacman -S base-devel cmake gdb git sdl2
```
__Fedora:__
```bash
sudo dnf install cmake gcc-c++ gdb git libstdc++-static mesa-libGL-devel SDL2-devel zlib-devel
```

__Gentoo:__
```bash
sudo emerge cmake dev-vcs/git gdb libsdl2 mesa
```

===================

#### Download AimTux:

```bash
git clone https://github.com/McSwaggens/AimTux
```

```bash
cd AimTux
```

===================

#### Generate a makefile

```bash
cmake .
```

#### Compile with make

**Note:** _The `4` in the command below specifies the amount of cpu "threads" or "cores" you wish to compile with (more = faster)._

```bash
make -j 4
```

## Injecting

First of all, make sure CSGO is open, it doesn't matter whether you're in game or not.

Navigate to the directory where AimTux was built if you haven't ready.

```bash
cd AimTux
```

Now, you can inject the hack with the `load` script

```bash
./load
```

You might be prompted to enter in your password, this is because the injection script requires root access.

You should see a lot of text being printed out, most of which is not important,

If you see something like`$1 = (void *) 0x3690fa00` (yours will be different) it means that the injection was successfull.
However,
if you see `$1 = (void *) 0x0`, the `.so` file either couldn't be found or something has gone wrong.

Now, go back into csgo, if you're in the main menu of the game you should see the AimTux banner in the top left like so:

![this](http://aimtux.net/images/screenshot4.png)

## Using the hack

Now that AimTux has been injected into the game, press the **insert** key on your keyboard to open the hack menu (**Fn + Delete** if you're using a laptop).

If you want to change skins, create and load configs or open the player list, you can find those buttons at the top of the screen.

## Unloading the hack

If you wish to unload the hack from the game, you can do so by entering the command:

```bash
./uload
```

## Configs

Configs are stored in a hidden directory in your home folder. Specifically 

```
~/.configs/AimTux
```

Each config.json is stored in a seperately named folder (The name you see in-game, in the config window). 

To add a config, create a folder inside of the `~/.configs/AimTux` folder with a name of your choice, and paste the `config.json` inside of that folder.

To see hidden folders inside your home folder, press CTRL+H when using a file manager.

## Contributing to AimTux

If you wish to contribute code to this opensource project, please keep some things mind before creating a *pull request*:
 - Make sure you're using tabs instead of spaces.
 - Curly braces are to be placed on a new line.
 - Make sure your commits are clean and straight forward ( no junk commits )
 - Explain what you've done in your pull request.


## Screenshots

![menu](http://aimtux.net/images/screenshot1.png)
![skins](http://aimtux.net/images/screenshot2.png)
![esp_chams](http://aimtux.net/images/screenshot3.jpeg)

## Credits
Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also originally based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
