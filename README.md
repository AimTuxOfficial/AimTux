AimTux
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
* *Recoil Crosshair*
* *Skin Changer*
* *Knife Changer*
* *Chat Spammer*

===================

#### Compiling:
Compiling this project is **dependant on whether you're using a debian based system** or not, this is due to the `libstdc++` library, if you'd like to fix this, be my guest but for now there is a default `makefile` and a `cmake` file.

* *Compiling on Debian based systems like Ubuntu or LinuxMint*
 1. Make sure you're inside of the directory where you downloaded AimTux, now `cd` into the AimTux directory (`cd AimTux`)
 2. Create a static link for `libstdc++` with the command `ln -s 'g++ -print-file-name=libstdc++.a'`
 3. Download the required tools to compile AimTux `sudo apt-get install build-essential`
 4. Compile AimTux by entering the command `make`
 5. AimTux should now start compiling, if there are any errors, please report them [here](https://github.com/McSwaggens/AimTux/issues/)

* *Compiling on* **NON** *Debian based systems like Arch, Fedora etc..*
 1. Make sure you're inside of the directory where you downloaded AimTux, now `cd` into the AimTux directory (`cd AimTux`)
 2. Download the required tools to compile AimTux `sudo [YOUR PACKAGE MANAGER HERE] build-essential`
 3. Compile AimTux by entering the command `make`
 4. AimTux should now start compiling, if there are any errors, please report them [here](https://github.com/McSwaggens/AimTux/issues/)


#### Injecting:

x
x
x
x



#### Credits:
Special thanks to [@Aixxe](http://www.github.com/aixxe/) ([aixxe.net](http://www.aixxe.net)) for the skin changer and with the initial project, as well as helping this project with source code (Available on [@Aixxe's](http://www.github.com/aixxe/) github page.)

This project was also initially based upon Atex's [Linux Basehook](http://unknowncheats.me/forum/counterstrike-global-offensive/181878-linux-basehook.html).
