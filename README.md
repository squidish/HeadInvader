# Head Invader

*Head Invader* is a synth-drenched twist on the classic *Space Invaders* formula. Instead of endless waves of aliens, you're facing down a **single enormous head** with a grudge and forty hit points. Inspired by the glitchy menace of *Tron*, the giant faces of *Zardoz*, and the deeply personal nightmare of being outwitted by your own forehead, *Head Invader* is a minimalist shooter built using **SFML 3.0** in C++.

---

## How to Play

-  Move left and right with the **arrow keys**
-  Press **spacebar** to fire your laser
-  The enemy head takes **40 hits to defeat**
-  If it reaches the bottom of the screen, you **lose**
-  After victory or defeat, you return to the menu
-  Choose from multiple heads — or load your own PNG!

---

##  How to Download and Run

### 💾 Prebuilt Executable

1. Download the latest zip from TBD
2. Unzip the folder
3. Run `HeadInvader.exe`

Make sure the following folders/files are present alongside the `.exe`:

HeadInvader/ \
├── HeadInvader.exe \
├── Heads/ \
│ ├── RickAndM.png \
│ ├── EasterHead.png \
│ └── Me.png \
├── music/ \
│ └── StockTune-City Lights Rushing By_1747174226.ogg \
├── arialceb.ttf \
├── SFML DLLs (if dynamically linked) \


---

##  How to Build from Source

###  Prerequisites

- A C++17–compatible compiler (e.g. MSVC 2022, Clang, etc.)
- [CMake 3.25+](https://cmake.org/download/)
- [SFML 3.0](https://www.sfml-dev.org/)
- [vcpkg](https://github.com/microsoft/vcpkg) (optional, recommended)

---

### ⚙️ Build with vcpkg (recommended)

1. Install vcpkg and SFML:
   ```bash
   vcpkg install sfml

2. Clone Project
   git clone https://github.com/yourname/head-invader.git
   cd head-invader

3. Configure with CMake:
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

4.Build:
   cmake --build build --config Release

5. Run:
   ./build/HeadInvader.exe

## Assets

All assets are included in the repository:

Heads/ – images for different enemy heads
music/ – synthwave soundtrack (.ogg)
arialceb.ttf – UI font

If you add your own head image, it must be in the same directory as the executable and a .png and then be select the custom head option via the in-game menu and type the name of the file.

## Credits & Licensing
Built using SFML 3.0

## Music: Neon Drift
Song by "https://stocktune.com/free-music/neon-dreams-drift-37322-41869

Game design and facial largeness by Christopher Kraken

## Follow & Feedback
Got feedback? Want to contribute a new head? Open an issue or PR on GitHub — or just email me your forehead.



















