# PortaPack Carnage

This is a fork of the [Mayhem](https://github.com/eried/portapack-mayhem/) firmware, which itself was a fork of the [PortaPack](https://github.com/sharebrained/portapack-hackrf) firmware, an add-on for the [HackRF](http://greatscottgadgets.com/hackrf/). A fork is a derivate, in this case one that has extra features and fixes when compared to the older versions.

[<img src="https://raw.githubusercontent.com/wiki/eried/portapack-mayhem/img/hw_overview_h2_front.png" height="400">](https://github.com/eried/portapack-mayhem/wiki/Hardware-overview) [<img src="https://raw.githubusercontent.com/wiki/eried/portapack-mayhem/img/hw_overview_h2_inside.png" height="400">](https://github.com/eried/portapack-mayhem/wiki/Hardware-overview#portapack-internals)

*[PortaPack H2](https://s.click.aliexpress.com/e/_dSMPvNo) (clone) with a custom [3d printed case](https://github.com/eried/portapack-mayhem/wiki/H2-Enclosure)*

# Quick overview


## Does it work on H1/H2 PortaPack?

Yes, both devices are the [same](https://github.com/eried/portapack-mayhem/wiki/First-steps). The one I am using to test all changes is this [PortaPack H2+HackRF+battery](https://s.click.aliexpress.com/e/_dSMPvNo), which is a kit that includes everything you need. Sadly, the people making the H2 never made the updated schematics available, which is not ideal (and goes against the terms of the license).

To support the people behind the hardware, please buy a genuine [HackRF](https://greatscottgadgets.com/hackrf/) and [PortaPack](https://store.sharebrained.com/products/portapack-for-hackrf-one-kit).


## What about Havoc/GridRF/jamesshao8/jboone's?
* jboone's PortaPack: the [vanilla](https://en.wikipedia.org/wiki/Vanilla_software) experience
* Havoc: It was the most popular fork of jboone's PortaPack, currrently, it is not being maintained nor updated
* jamesshao8: He keeps his own version of the fork, while not attached as a fork to anything
* GridRF: They sell PortaPack clones with their own firmware based on a old version, which has no sourcecode available

## Resources
You can reach the [official community](https://www.facebook.com/groups/177623356165819) in Facebook. 


## Tools

You will need a few tools installed on your computer before you begin.

    GCC-ARM-Embedded - I am using the "9-2019-q4-major" release.
    CMake 2.8.9 or newer - Build system now uses CMake instead of GNU Make.
    PyYAML for Python 2.7 (for libopencm3, built by hackrf submodule).
    dfu-util 0.7 or newer - Used to load and run the stock HackRF firmware from RAM.

## Getting the Source Code

The source code is hosted on GitHub. Change to a directory where you want the source code, and clone the source repository.

git clone --recurse-submodules https://github.com/Acetolyne/portapack-carnage.git

Change directories into the cloned repository.

cd portapack-hackrf

## Building

Make a "build" directory and initialize the CMake build files into that directory:

mkdir build
cd build
cmake ..

Make the SPI flash binary image (which builds the bootstrap, application, and baseband binaries):

make firmware

The binary will be at "firmware/portapack-h1-havoc.bin". under the build directory that you are currently in. (TODO binary location possibly needs updated)

## Flashing Firmware

Once you have built the binary, you must program it into the HackRF One SPI flash.
Flashing

If you do not already have the firmware on your HackRF the follow the "install firmware" instructions.
If you previously had the firmware and only want to update it with the latest and greatest then follow the "update firmware" instructions below.

### Install Firmware for Linux

install dfu-util typically with ```sudo apt install dfu-util```

Plug the HackRF into a USB port on your computer.

Hold down the HackRF DFU button. Press and release the HackRF reset button. Wait a second or two. Then release the DFU button. The HackRF is now in DFU mode.

Program the HackRF's SPI flash:

make program

When finished, press the reset button on the HackRF. The PortaPack code is now running from the SPI flash on the HackRF.

### Update firmware


1. Put the HackRF into DFU mode by doing one of the below.

- In the havoc UI go to the main menu and choose HackRF and choose yes when it asks you if you want to go to HackRF mode.

- Hold the DFU button ( the button nearest to the antenna ) and press the reset button while still holding the DFU button wait a couple seconds then release the DFU button.

2. cd to the firmware

2. Flash the havoc firmware with ```hackrf_spiflash -w portapack-h1-havoc.bin``` (TODO again file name may be different now)

- If the hackrf_spiflash program is not available you have not built it yet. follow the directions below then try reflashing with the above command.


### Building the hackrf_spiflash utility

1. From the root of the git repository cd to hackrf/host/hackrf-tools/src

2. mkdir build 

3. cd build

4. cmake ..

5. make

6. make install

7. ldconfig

