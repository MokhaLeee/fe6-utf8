# fe6-utf8

Projects to introduce utf8-decoding for translation and development to [fireemblem6](https://github.com/StanHash/fe6), aimming to enable users to directly insert anti-huffmaned utf8 strings via FEBuilderGBA or buildfile.

---
## Usage
![Working in Process](https://img.shields.io/badge/working-in_process-blue)

Directly get the release, and apply the patch to fe6 clean rom, and use the generated gba rom as the baserom to do more hacks.

```c
// Recommanded definition for buildfile
#define FreeSpace 0x00A00000
#define TextTable NewTextTable

PUSH
    ORG 0x00800000
    TextTable:
POP
```

---
## Custom build

> <!> You need a linux envirment!
>
> For Windows user, it is recommended to use a ubuntu server or try [WSL](https://learn.microsoft.com/en-us/windows/wsl/install).

1. Install sub-modules

```bash
cd tools
git clone https://github.com/MokhaLeee/FE6-CLib.git
git clone https://github.com/StanHash/EventAssembler.git --recursive
```

2. Install dependence

```bash
sudo apt-get -y install binutils-arm-none-eabi \
    gcc-arm-none-eabi build-essential cmake re2c ghc \
    cabal-install libghc-vector-dev libghc-juicypixels-dev \
    python3-pip pkg-config libpng* bsidff

pip install pyelftools PyInstaller tmx six
```

3. Install DevkitPRO

```bash
wget https://apt.devkitpro.org/install-devkitpro-pacman
chmod +x ./install-devkitpro-pacman
sudo ./install-devkitpro-pacman
sudo dkp-pacman -S gba-dev

# Export vars
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=${DEVKITPRO}/devkitARM
export DEVKITPPC=${DEVKITPRO}/devkitPPC
export PATH=${DEVKITPRO}/tools/bin:$PATH
```

3. Build EA

    Get into **tools/EventAssembler** and then refer to [EA build note](https://github.com/StanHash/EventAssembler) to install [.NET](https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu).

```bash
# Install .NET
# refer to: https://learn.microsoft.com/en-us/dotnet/core/install/linux-scripted-manual#scripted-install
wget https://dot.net/v1/dotnet-install.sh -O dotnet-install.sh
chmod +x ./dotnet-install.sh
sudo ./dotnet-install.sh --channel 6.0

export DOTNET_ROOT=$HOME/.dotnet
export PATH=$PATH:$DOTNET_ROOT:$DOTNET_ROOT/tools
```

```bash
# Build EA
cd tools/EventAssembler
./build.sh
```

5. Put **Fire Emblem: Fūin no Tsurugi** clean rom named **fe6.gba** in the repo directory.

4. build:

```bash
make
```

You can configure on [lang.mk](./lang.mk) to choose how much utf8-characteres to be installed, for now, **EN** and **ZH-CN** is supported.

---
## Credit
- UTF8 decoding method and fonts collection are ported from [FEHHR](https://github.com/laqieer/FEHRR) by [@laqieer](https://github.com/laqieer)
- Hardcoded string is ported from [fe6-wizardry](https://github.com/StanHash/fe6-wizardry) by [@StanHash](https://github.com/StanHash)
