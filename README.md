# PortaPack Mayhem

[![Build Status](https://travis-ci.com/eried/portapack-mayhem.svg?branch=master)](https://travis-ci.com/eried/portapack-mayhem) [![buddy pipeline](https://app.buddy.works/eried/portapack/pipelines/pipeline/252276/badge.svg?token=48cd59d53de0589a8fbe26bc751d77a59a011cf72581da049343879402991c34 "buddy pipeline")](https://app.buddy.works/eried/portapack/pipelines/pipeline/252276) [![CodeScene Code Health](https://codescene.io/projects/8381/status-badges/code-health)](https://codescene.io/projects/8381) [![GitHub All Releases](https://img.shields.io/github/downloads/eried/portapack-mayhem/total)](https://github.com/eried/portapack-mayhem/releases) [![GitHub Releases](https://img.shields.io/github/downloads/eried/portapack-mayhem/latest/total)](https://github.com/eried/portapack-mayhem/releases/latest) [![Docker Hub Pulls](https://img.shields.io/docker/pulls/eried/portapack.svg)](https://hub.docker.com/r/eried/portapack) [![Discord Chat](https://img.shields.io/discord/719669764804444213.svg)](https://discord.gg/tuwVMv3)  [![Check bounties!](https://img.shields.io/bountysource/team/portapack-mayhem/activity?color=%2333ccff&label=bountysource%20%28USD%29&style=plastic)](https://www.bountysource.com/teams/portapack-mayhem/issues)

This is a fork of the [Havoc](https://github.com/furrtek/portapack-havoc/) firmware, which itself was a fork of the [PortaPack](https://github.com/sharebrained/portapack-hackrf) firmware, an add-on for the [HackRF](http://greatscottgadgets.com/hackrf/). A fork is a derivate, in this case one that has extra features and fixes when compared to the older versions.

[<img src="https://raw.githubusercontent.com/wiki/eried/portapack-mayhem/img/hw_overview_h2_front.png" height="400">](https://github.com/eried/portapack-mayhem/wiki/Hardware-overview) [<img src="https://raw.githubusercontent.com/wiki/eried/portapack-mayhem/img/hw_overview_h2_inside.png" height="400">](https://github.com/eried/portapack-mayhem/wiki/Hardware-overview#portapack-internals)

*[PortaPack H2+HackRF+battery](https://s.click.aliexpress.com/e/_dZ7lA96) (clone) with a custom [3d printed case](https://github.com/eried/portapack-mayhem/wiki/H2-Enclosure)*

# Quick overview

If you are new to *HackRF+PortaPack+Mayhem*, there is an awesome introductory video by [Tech Minds](https://www.youtube.com/channel/UC9a8Z6Sp6eb2s3O79pX5Zvg) available:

[![Setup and overview](https://img.youtube.com/vi/kjFB58Y1TAo/0.jpg)](https://www.youtube.com/watch?v=kjFB58Y1TAo)

# Frequently Asked Questions

This repository expands upon the previous work by many people and aims to constantly add new features, bugfixes and generate documentation to make further development easier.  [Collaboration](https://github.com/eried/portapack-mayhem/wiki/How-to-collaborate) is always welcomed and appreciated.

## Does it work on H1/H2 PortaPack?

Yes, both devices are the [same](https://github.com/eried/portapack-mayhem/wiki/First-steps). The one I am using to test all changes is this [PortaPack H2+HackRF+battery](https://s.click.aliexpress.com/e/_dZ7lA96), which is a kit that includes everything you need. Sadly, the people making the H2 never made the updated schematics available, which is not ideal (and goes against the terms of the license). Most members of the community are using a clone of the [PortaPack H1+HackRF+metal case](https://s.click.aliexpress.com/e/_dS6liw4), which does not include any battery functionality, but it is a cheaper alternative.

To support the people behind the hardware, please buy a genuine [HackRF](https://greatscottgadgets.com/hackrf/) and [PortaPack](https://store.sharebrained.com/products/portapack-for-hackrf-one-kit).

## Where is the latest firmware?

The current stable release is on the [![GitHub release (latest by date)](https://img.shields.io/github/v/release/eried/portapack-mayhem?label=Releases&style=social)](https://github.com/eried/portapack-mayhem/releases/latest) page. Follow the instructions you can find in the release description. There is also [nightly builds](https://github.com/eried/portapack-mayhem/releases/tag/nightly) generated periodically, which include the latest commits, but they may contain incomplete or buggy functionality.

## Is this the newest firmware for my PortaPack? 
Most probably: **YES**. *If you find new features somewhere else, please [suggest](https://github.com/eried/portapack-mayhem/issues/new/choose) them*.

## Which one is actually the newest?
There is a lot of confusion of which is the latest version because no old version used any actual "version number". Additionally, since the files were distributed on facebook groups, github issue links and similar temporal sources, then there was no central location for them. 

This fork (**Mayhem**) uses *major.minor.release* [semantic versioning](https://en.wikipedia.org/wiki/Software_versioning), so you can always compare your current version with the latest from [Releases](https://github.com/eried/portapack-mayhem/releases/latest).

## What about Havoc/GridRF/jamesshao8/jboone's?
* jboone's PortaPack: the [vanilla](https://en.wikipedia.org/wiki/Vanilla_software) experience
* Havoc: It was the most popular fork of jboone's PortaPack, currrently, it is not being maintained nor updated
* jamesshao8: He keeps his own version of the fork, while not attached as a fork to anything
* GridRF: They sell PortaPack clones with their own firmware based on a old version, which has no sourcecode available

## How can I collaborate
You can write [documentation](https://github.com/eried/portapack-mayhem/wiki), fix bugs and [answer issues](https://github.com/eried/portapack-mayhem/issues) or add new functionality. Please check the following [guide](https://github.com/eried/portapack-mayhem/wiki/How-to-collaborate) with details.

Consider that the hardware and firmware has been created and maintain by a [lot](https://github.com/mossmann/hackrf/graphs/contributors) of [people](https://github.com/eried/portapack-mayhem/graphs/contributors), so always try colaborating your time and effort first. For coding related questions, if something does not fit as an issue, please join our Discord by clicking the chat badge on [top](#portapack-mayhem).

As a last option, if you want to send money directly to me for getting more boards, antennas and such:

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CBPQA4HRRPJQ6&source=url)

## What if I really want to pay for something?
You can create a bounty and invite people to your own bounty. This will incentivize coders to work on a new feature, solving a bug or even writting documentation. Start a bounty by [creating](https://github.com/eried/portapack-mayhem/issues/new/choose) or [choosing](https://github.com/eried/portapack-mayhem/issues/) an existing issue. Then, go to [Bountysource](https://www.bountysource.com/) and post a bounty using the link to that specific [issue](https://www.bountysource.com/teams/portapack-mayhem/issues).

Promote your bounty over our Discord by clicking the chat badge on [top](#portapack-mayhem).

## What if I need help?
First, check the [documentation](https://github.com/eried/portapack-mayhem/wiki). If you find a bug or you think the problem is related to the current repository, please open an [issue](https://github.com/eried/portapack-mayhem/issues/new/choose).

You can reach the [official community](https://www.facebook.com/groups/177623356165819) in Facebook, and our Discord by clicking the chat badge on [top](#portapack-mayhem).

## What if I find incongruencies, or grammatical errors in the text?
If is on the [Wiki](https://github.com/eried/portapack-mayhem/wiki), you can modify it directly. If is on files of the repository, you can send corrections as [pull requests](https://github.com/eried/portapack-mayhem/wiki/How-to-collaborate#coding-new-stuff-or-fixing-bugs). As a last resource, open an [issue](https://github.com/eried/portapack-mayhem/issues/new/choose).


## Tools

You will need a few tools installed on your computer before you begin.

    GCC-ARM-Embedded - I am using the "9-2019-q4-major" release.
    CMake 2.8.9 or newer - Build system now uses CMake instead of GNU Make.
    PyYAML for Python 2.7 (for libopencm3, built by hackrf submodule).
    dfu-util 0.7 or newer - Used to load and run the stock HackRF firmware from RAM.

## Getting the Source Code

The source code is hosted on GitHub. Change to a directory where you want the source code, and clone the source repository.

git clone --recurse-submodules https://github.com/Acetolyne/portapack-havoc.git

Change directories into the cloned repository.

cd portapack-hackrf

## Building

Make a "build" directory and initialize the CMake build files into that directory:

mkdir build
cd build
cmake ..

Make the SPI flash binary image (which builds the bootstrap, application, and baseband binaries):

make firmware

The binary will be at "firmware/portapack-h1-havoc.bin". under the build directory that you are currently in.

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

2. Flash the havoc firmware with ```hackrf_spiflash -w portapack-h1-havoc.bin```

- If the hackrf_spiflash program is not available you have not built it yet. follow the directions below then try reflashing with the above command.


### Building the hackrf_spiflash utility

1. From the root of the git repository cd to hackrf/host/hackrf-tools/src

2. mkdir build 

3. cd build

4. cmake ..

5. make

6. make install

7. ldconfig

