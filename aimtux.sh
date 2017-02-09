#!/bin/sh
csgo_pid=$(pidof csgo_linux64)
grep -q libAimTux.so /proc/$csgo_pid/maps;
injected=$?

#Credit: Aixxe @ aixxe.net
function load
{
    if [[ -z "$csgo_pid" ]]; then
        /bin/echo -e "\e[31mCSGO needs to be open before you can inject.\e[0m"
        exit 1
    fi

    if [[ $injected == 0 ]]; then
        /bin/echo -e "\e[33mAimTux is already injected. Aborting.\e[0m"
        exit
    fi

    input="$(
    sudo gdb -n -q -batch \
      -ex "attach $csgo_pid" \
      -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
      -ex "call \$dlopen(\"$(pwd)/libAimTux.so\", 1)" \
      -ex "detach" \
      -ex "quit"
    )"

    last_line="${input##*$'\n'}"

    if [ "$last_line" != "\$1 = (void *) 0x0" ]; then
        /bin/echo -e "\e[32mSuccessfully injected!\e[0m"
    else
        /bin/echo -e "\e[31mInjection failed, make sure you've compiled.\e[0m"
        exit 1
    fi

    grep -q libAimTux.so /proc/$csgo_pid/maps;
    injected=$?
}

#Credit: Aixxe @ aixxe.net
function uload
{
    if [[ -z "$csgo_pid" ]]; then
        /bin/echo -e "\e[31mCSGO needs to be open before you can unload AimTux.\e[0m"
        exit 1
    fi

    if [[ $injected == 0 ]]; then
    sudo gdb -n -q -batch \
        -ex "attach $(pidof csgo_linux64)" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "set \$dlclose = (int(*)(void*)) dlclose" \
        -ex "set \$library = \$dlopen(\"$(pwd)/libAimTux.so\", 6)" \
        -ex "call \$dlclose(\$library)" \
        -ex "call \$dlclose(\$library)" \
        -ex "detach" \
        -ex "quit"
    else
        /bin/echo -e "\e[33mAimTux is not loaded yet. Aborting.\e[0m"
        exit
    fi

    grep -q libAimTux.so /proc/$csgo_pid/maps;
    injected=$?
}

function rload
{
    if [[ $injected == 0 ]]; then
        uload
    fi

    cmake .
    make -j$(cat /proc/cpuinfo | grep "^processor" | wc -l) "$@"
    load
}

function update
{
    git pull
    git submodule update --init --recursive --remote
    cmake .
    make -j$(cat /proc/cpuinfo | grep "^processor" | wc -l) "$@"
}

if [[ ! -d ".git" ]]; then
    /bin/echo "We have detected that you have downloaded aimtux-master.zip from the GitHub website. This is the WRONG way to download AimTux. Please download AimTux with the command 'git clone --recursive https://github.com/AimTuxOfficial/AimTux'"
    exit 1
fi

case "$1" in
  load)
    load
    ;;
  uload)
    uload
    ;;
  rload)
    rload
    ;;
  update)
    update
    ;;
  *)
    echo "Usage: $0 {load|uload|rload|update}"
esac
