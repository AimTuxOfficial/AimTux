![banner](http://aimtux.net/images/aimtux.png)

===================

[![Join the chat at https://www.gitter.im/AimTuxOfficial/lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://www.gitter.im/AimTuxOfficial/lobby)

Want to chat or play with other AimTux users? Join us on Gitter!

#### Features:

* *Aimbot*
* *Triggerbot*
* *AntiAim (Slow and Fast Spinbot, Jitter, Sideways, Backwards & Forwards, Left & Right, Static)*
* *Pitch (Up/Down/Front/Dance/Overflow Down)*
* *FakeLag*
* *AimStep*
* *AutoShoot*
* *AutoCrouch*
* *AutoStop*
* *AutoWall*
* *RCS*
* *Radar*
* *Box ESP (2D/3D)*
* *Name ESP*
* *Bone ESP*
* *Bomb ESP*
* *Bomb Timer*
* *Bomb Damage Indicator*
* *FOV ESP*
* *Weapons ESP*
* *Chams*
* *Glow*
* *Rank Viewer*
* *Tracer*
* *Bhop*
* *Autostrafe*
* *No Flash*
* *Airstuck*
* *Recoil Crosshair*
* *Skin Changer*
* *Knife Changer*
* *Clan Tag Changer*
* *Chat Spammer*
* *Kill Spammer*
* *Name Changer*
* *FOV Changer*
* *AutoAccept*

===================

## Compiling

**Note:** _Do NOT download or compile as the root user_

1. Make sure you're inside of the *AimTux* directory
2. Download the required tools to compile AimTux
    * **Debian-based:** `apt-get install cmake g++ gdb zlib1g-dev`
    * **Fedora:** `dnf install libstdc++-static cmake gcc-c++ gdb zlib-devel`
    * **Arch Linux:** `pacman -S base-devel cmake gdb` 
3. Generate a *makefile* with the command `cmake .`
4. Compile AimTux by entering `make`
4. AimTux should now start compiling, if there are any errors, please report them [here](https://github.com/McSwaggens/AimTux/issues/)

## Injecting
First of all, make sure you're in the directory where *AimTux* was built,

Type the command `./load`, you might be prompted to enter your password (injection requires root)

You should see a lot of text being printed out, most of which is not important,

if you see something like`$1 = (void *) 0x3690fa00` (yours will be different) that means that the injection was successfull.
However,
if you see this: `$1 = (void *) 0x0`, the `.so` file either couldn't be found or something has gone wrong.

AimTux should now be injected into the game, to confirm, you should see something like this in the top left hand corner of your screen.

![this](http://i.imgur.com/I2NSAia.png)

The above message will only be shown if you're in the main menu, additionally, you can check the *csgo* console for a message saying `AimTux was successfully injected.`.

## Un-injecting

If you want to unload the hack from the game, you will first need to launch the game with the command `~/.steam/steam/steamapps/common/Counter-Strike Global Offensive/csgo.sh -steam`, this will start the game normally.

Once again, make sure you're inside of the AimTux directory, and type `./uload`.

*AimTux* should now be unloaded from the game,

you can check the *csgo* console for a message saying `AimTux has been unloaded successfully.` to confirm.

## Reloading

If you would like to unload, compile and load the hack back into the game again (mostly for development) you can use the `./rload` command.

## Keeping up to date

AimTux is being updated constantly, if you want to stay up to date, do the following:

* Pull the latest updates from github
`git pull`

* Recompile the hack
```bash
cmake .
make
```

All done!

## Usage

Once injected, press the *insert* key to bring up the GUI, then start turning on hacks!

Have fun!

## Screenshots

![menu](http://i.imgur.com/GjdLRzW.jpg)
![hvh_menu](http://i.imgur.com/z8lNqeq.jpg)
![config_menu](http://i.imgur.com/UoxaHKZ.png)
![esp_chams](http://i.imgur.com/r8fk1Rt.jpg)
![bomb_esp](http://i.imgur.com/ZgMrHrr.jpg)

## Credits
Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also initially based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
