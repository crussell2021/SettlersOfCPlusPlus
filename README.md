# SettlersOfCPlusPlus

## Project Setup
Additional SDL files and .dll files are needed to compile. You can find them here: https://www.libsdl.org/, and a good guide to setting up SDL2 here: https://lazyfoo.net/tutorials/SDL/index.php#Event%20Driven%20Programming.

In the Makefile, you'll need to change the SDL2_SHARED_DIR_PATH variable to match where you've placed all your SDL2 files. All folders from SDL2 extensions (Image, TTF, etc.) are combined in the same directory.
