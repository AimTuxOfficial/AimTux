![banner](http://elite4.tk/supreme.png)

===================

## What is Supreme Hack?

Supreme is a upgraded hack based on AimTux and fully featured internal hack for *CounterStrike : Global Offensive* written in C++.

##WARNING!

Here i only adding good stuff from GitHub sources or commits.For my addings i use BitBucket with closed source if you want access for this write to me.

## Compiling

**Note:** _Do NOT download or compile as the root user_

#### Download the dependencies required to build Supreme:

__Ubuntu-Based / Debian:__
```bash
sudo apt-get install cmake g++ gdb git libsdl2-dev zlib1g-dev
```

If you're having problems compiling make sure you've got the latest version of `g++`.

[How to update g++](https://github.com/AimTuxOfficial/AimTux/wiki/Updating-your-compiler)

==================

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

#### Download Supreme:

```bash
git clone --recursive https://github.com/BlastWorld/Supreme
```

```bash
cd Supreme
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

Navigate to the directory where Supreme was built if you haven't ready.

```bash
cd Supreme
```

Now, you can inject the hack with the `load` script

```bash
./load
```

You might be prompted to enter in your password, this is because the injection script requires root access.

You should see a lot of text being printed out, most of which is not important,

If the injection was successfull you'll see a message at the bottom saying `Successfully injected!`, however, if the message says `Injection failed`, then you've most likely done something wrong.

Now, go back into csgo, if you're in the main menu of the game you should see the Supreme banner in the top left like so:

![this](http://aimtux.net/images/screenshot4.png)

## Using the hack

Now that Supreme has been injected into the game, press <kbd>Insert</kbd> on your keyboard to open the hack menu (<kbd>ALT</kbd>+<kbd>I</kbd> if you're using a laptop).

If you want to change skins, create and load configs or open the player list, you can find those buttons at the top of the screen.

## Unloading the hack

If you wish to unload the hack from the game, you can do so by entering the command:

```bash
./uload
```

## Updating Supreme

We add and improve and fix things almost every day with Supreme. We don't have a fixed release schedule, we just add things to it when they're ready. Because of this, Supreme will need to update a lot.

If you don't update once a day then we recommend at LEAST update once a week, and ALWAYS update after a CSGO update, just to make sure we fix anything that's broken.

We provide a script included in the Supreme folder that updates Supreme for you. To use it, just run:

```
./update
```

And it will download and compile without any effort. Once it's done, happy hacking!

## Configs

Configs are stored in a hidden directory in your home folder. Specifically 

```
~/.config/Supreme
```

Grenade Helper
```
~/.config/SupremeGH
```

Each `config.json` is stored in a seperately named folder (The name you see in-game, in the config window). 

To add a config, create a folder inside of the `~/.config/Supreme` folder with a name of your choice, and paste the `config.json` inside of that folder.

To add a config for grenade helper, create a folder inside of the `~/.config/SupremeGH` folder with a name of your choice, and paste the `config.json` inside of that folder.

To see hidden folders inside your home folder, press <kbd>CTRL</kbd>+<kbd>H</kbd> when using a file manager.

## Contributing to Supreme

If you wish to contribute code to this opensource project, please keep some things mind before creating a *pull request*:
 - Make sure you're using the correct [code style](https://github.com/AimTuxOfficial/AimTux/wiki/Code-Style).
 - Make sure your commits are clean and straight forward ( no junk commits )
 - Explain what you've done in your pull request.


## Screenshots

![menu](http://aimtux.net/images/screenshot1.png)
![skins](http://aimtux.net/images/screenshot2.png)
![esp_chams](http://aimtux.net/images/screenshot3.jpeg)

## Credits
Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also originally based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
