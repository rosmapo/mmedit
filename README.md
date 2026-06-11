# mmedit

mmedit is a Linux-focused fork of NotepadNext.

The project is based on the original NotepadNext source code and includes custom modifications, fixes and Linux-specific improvements.

## Platform

- Linux

## Building from source

### Install dependency
sudo apt update  
sudo apt install cmake ninja-build build-essential qt6-base-dev qt6-base-private-dev libxkbcommon-dev

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
