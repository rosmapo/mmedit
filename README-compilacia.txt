# install dependency
sudo apt update
sudo apt install cmake ninja-build build-essential qt6-base-dev qt6-base-private-dev libxkbcommon-dev

# clone repo
git clone --depth=1 https://github.com/rosmapo/mmedit
cd mmedit

# compilation
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build .