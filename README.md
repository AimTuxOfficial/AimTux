<p align="center">
<img src="http://i.imgur.com/mCtrbIN.png">
</p>
===================


# Please Note that AimTux-Fuzion Requires Additional Packages. See Below!
[![Join the chat at https://gitter.im/Aimtux-Fuzion/Lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://gitter.im/Aimtux-Fuzion/Lobby#)

Want to chat or play with other Fuzion users? Join us on Gitter!

## What is Fuzion?

A fully featured internal hack for *CounterStrike : Global Offensive* written in C++.


## Compiling

**Note:** _Fuzion Requires an additional package for Lua._

**Note:** _Do NOT download or compile as the root user._

#### Download the dependencies required to build Fuzion:


If you're having problems compiling make sure you've got the latest version of `g++`.

[How to update g++](https://github.com/AimTuxOfficial/AimTux/wiki/Updating-your-compiler)

==================

#### Attention! You need lua and xdo to compile Fuzion. Please don't skip this!

__Ubuntu-Based / Debian:__
```bash
sudo apt-get install cmake g++ gdb git libsdl2-dev zlib1g-dev liblua5.3 libxdo-dev
```
__Arch:__
```bash
sudo pacman -S base-devel cmake gdb git sdl2 lua xdotool
```
__Fedora:__
```bash
sudo dnf install cmake gcc-c++ gdb git libstdc++-static mesa-libGL-devel SDL2-devel zlib-devel lua-devel libX11-devel libxdo-devel
```

__Gentoo:__
```bash
sudo emerge cmake dev-vcs/git gdb libsdl2 mesa lua xdotool
```
===================

#### Download Fuzion:

```bash
git clone --recursive https://github.com/LWSS/Fuzion
```

```bash
cd Fuzion
```

===================


#### Compile with build script

You can build easily with the included build script.
```bash
./build
```
You can later update with 
```bash
./update
```

## Injecting

First of all, make sure CSGO is open, it doesn't matter whether you're in game or not. However, it is not recommended to inject while CSGO is loading into a map. 

Navigate to the directory where AimTux-Fuzion was built if you haven't ready.

```bash
cd Fuzion
```

Now, you can inject the hack with the `load` script

```bash
./load
```

You might be prompted to enter in your password, this is because the injection script requires root access.

The text printed out during injection is not important. 

If the injection was successful you'll see a message at the bottom saying `Successfully injected!`, however, if the message says `Injection failed`, then you've most likely done something wrong.

Now, go back into csgo, if you're in the main menu of the game you should see a banner in the top left like so:

![this](http://i.imgur.com/Gb0SV1u.png)

## Using the hack

Now that Fuzion has been injected into the game, press <kbd>Insert</kbd> on your keyboard to open the hack menu (<kbd>ALT</kbd>+<kbd>I</kbd> if you're using a laptop).

If you want to change skins, create and load configs or open the player list, you can find those buttons at the top of the screen.

## Unloading the hack

If you wish to unload the hack from the game, you can do so by entering the command:

```bash
./uload
```

## Configs

Configs are stored in a hidden directory in your home folder. Specifically 

```
~/.config/Fuzion
```

Each `config.json` is stored in a seperately named folder (The name you see in-game, in the config window). 

To add a config, create a folder inside of the `~/.config/Fuzion` folder with a name of your choice, and paste the `config.json` inside of that folder.

To see hidden folders inside your home folder, press <kbd>CTRL</kbd>+<kbd>H</kbd> when using a file manager.

On your Command line, You can also add the -a flag on ls     `ex: ls -la ~/` 

## Grenade Configs

```
~/.config/FuzionGH
```

Each `config.json` is stored in the folder named after them map name.

To add a config, copy the folder containing it to `~/.config/FuzionGH`


## Screenshots
![franklin](http://i.imgur.com/a964edK.jpg)
![menu](http://i.imgur.com/AOSjO6S.jpg)
![swag](http://i.imgur.com/Okzvm5r.jpg)
![fuzion](http://i.imgur.com/5fZDVHa.jpg)

## Credits
Special thanks to the Original AimTux project: https://github.com/AimTuxOfficial/AimTux

Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also originally based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
