![banner](http://aimtux.net/gh-banner.png)

===================

[![Join the chat at https://www.gitter.im/AimTuxOfficial/lobby](https://img.shields.io/gitter/room/TechnologyAdvice/Stardust.svg?style=flat-square)](https://www.gitter.im/AimTuxOfficial/lobby)

Want to chat or play with other AimTux users? Join us on Gitter!

#### Features:

* *Aimbot*
* *Triggerbot*
* *AntiAim (Spinbot, Jitter, Sideways, Backwards, Static up / down)*
* *AimStep*
* *AutoShoot*
* *AutoCrouch*
* *AutoStop*
* *RCS*
* *Box ESP*
* *Name ESP*
* *Bone ESP*
* *Chams*
* *Tracer*
* *Bhop*
* *No Flash*
* *Airstuck*
* *Recoil Crosshair*
* *Skin Changer*
* *Knife Changer*
* *Chat Spammer*

===================

## Compiling:
Compiling this project is **dependant on whether you're using a debian based system** or not, this is due to the `libstdc++` library, if you'd like to fix this, be my guest but for now there is a default `makefile` and a `cmake` file.

### Compiling on Debian based systems like Ubuntu or LinuxMint
1. Make sure you're inside of the *AimTux* directory
2. Create a static link for `libstdc++` with the command `ln -s $(g++ -print-file-name=libstdc++.a)`
3. Download the required tools to compile AimTux `sudo apt-get install build-essential`
4. Compile AimTux by entering the command `make`
5. AimTux should now start compiling, if there are any errors, please report them [here](https://github.com/McSwaggens/AimTux/issues/)

### Compiling on *NON* Debian based systems like Arch, Fedora etc..
1. Make sure you're inside of the *AimTux* directory
2. Create a static link for `libstdc++` with the command `ln -s $(g++ -print-file-name=libstdc++.a)`
3. Download the required tools to compile AimTux
    * **Fedora:** `dnf install @development-tools`
    * **Arch Linux:** `pacman -S base-devel gdb` 
4. Compile AimTux by entering the command `make`
5. AimTux should now start compiling, if there are any errors, please report them [here](https://github.com/McSwaggens/AimTux/issues/)


## Injecting
First of all, make sure you're in the directory where *AimTux* was built,

Type the command `./load`, you might be prompted to enter your password (injection requires root)

You should see a lot of text being printed out, most of which is not important,

if you see something like`$1 = (void *) 0x3690fa00` (yours well be different) that means that the injection was successfull.
However,
if you see this: `$1 = (void *) 0x0`, the `.so` file either couldn't be found or something has gone wrong.

AimTux should now be injected into the game, to confirm, you should see something like this in the top left hand corner of your screen.

![this](http://i.imgur.com/I2NSAia.png)

The above message will only be shown if you're in the main menu, aditionally, you can check the *csgo* console for a message saying `AimTux was successfully injected.`.

## Un-injecting

Once again, make sure you're inside of the AimTux directory, and type `./uload`.

*AimTux* should now be unloaded from the game,

you can check the *csgo* console for a message saying `AimTux has been unloaded successfully.` to confirm.

## Reloading

If you would like to unload, compile and load the hack back into the game again (mostly for development) you can use the `./rload` command.

#### Credits:
Special thanks to [@aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@aixxe's](http://www.github.com/aixxe/) github page.)

This project was also initially based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
