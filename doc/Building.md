# Building mmedit

To build mmedit you will need CMake, a compatible C++ compiler, the Qt libraries, and the mmedit source code.

Here's instructions for ubuntu/debian. Should be same across all distros as long as you get the packages.

```sh
export DISTRIBUTION=AppImage
export EXTRA_PLATFORM_PLUGINS="libqwayland-generic.so"

sudo apt update
sudo apt install -y \
  cmake \
  ninja-build \
  file \
  libxkbcommon-dev \
  libxkbcommon-x11-0 \
  fuse \
  libxcb-cursor-dev \
  libcups2-dev \
  libglib2.0-0 \
  libglib2.0-dev \
  libproxy1v5 \
  libproxy-dev \
  qt6-base-dev \
  qt6-base-dev-tools \
  qt6-tools-dev \
  qt6-tools-dev-tools \
  qt6-wayland \
  qt6-wayland-dev \
  libqt6waylandclient6 \
  qml6-module-qtwayland-compositor \
  libqt6core5compat6 \
  libqt6core5compat6-dev \
  qt6-base-private-dev

cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DAPP_DISTRIBUTION=$DISTRIBUTION
cmake --build build --target appimage --parallel
```


