# mmedit

If you like this project and want to support its development:

[![Buy Me a Coffee](https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png)](https://www.buymeacoffee.com/mirosmar)

mmedit is a fork of the NotepadNext project that I created to meet my own needs. I couldn't find a text editor for Linux that combined speed, multi-cursor support, and good system integration (such as dark mode and polkit support).

This project owes its existence to the NotepadNext community and to my desire to add features that I personally needed. Over time, the code has also been improved with the assistance of AI models to achieve the level of usability, comfort, and stability I was aiming for.

## Platform

- Linux

## Building from source

### Install dependency
sudo apt update
sudo apt install cmake ninja-build build-essential qt6-base-dev qt6-base-private-dev libxkbcommon-dev libhunspell-dev

### Clone repo
git clone --depth=1 https://github.com/rosmapo/mmedit
cd mmedit

### Compilation
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build .

## Original Project

NotepadNext:
https://github.com/dail8859/NotepadNext

## License

MMEdit is licensed under the GNU General Public License v3.0 (GPL-3.0), following the original project.
