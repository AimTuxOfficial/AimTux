![banner](http://aimtux.net/images/aimtux.png)

===================

[![Join the chat at https://www.gitter.im/AimTuxOfficial/lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://www.gitter.im/AimTuxOfficial/lobby)

Want to chat or play with other AimTux users? Join us on Gitter!

## What is AimTux?

AimTux is a fully featured internal hack for *CounterStrike : Global Offensive* written in C++.


===================

## Compiling

**Note:** _Do NOT download or compile as the root user_

#### Download the dependencies required to build AimTux:
__Ubuntu:__
```bash
sudo apt-get install cmake g++ gdb libsdl2-dev zlib1g-dev git
```
__Arch:__
```bash
sudo dnf install cmake gcc-c++ gdb libstdc++-static mesa-libGL-devel SDL2-devel zlib-devel git
```
__Fedora:__
```bash
sudo pacman -S base-devel cmake gdb sdl2 git
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

**Note:** _The `4` in the command below specifies the amount of cpu "threads" or "cores" you wish to compile with (more = faster).

```bash
make -j 4
```

## Screenshots

![menu](http://i.imgur.com/SD7x7w2.png)
![skins](http://i.imgur.com/NTMy3EI.png)
![esp_chams](http://i.imgur.com/r8fk1Rt.jpg)

## Credits
Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also initially based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
