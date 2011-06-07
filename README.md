#TwitCrusader

TwitCrusader is Twitter Client For Linux Desktop

## How to Install

### Before to start!

#### Ubuntu/Debian

First you have to install dependencies:

    # apt-get update
    # apt-get install build-essential libgtk2.0 libgtk2.0-dev libcurl-ocaml-dev libssl-dev libxml2 libxml2-dev
    # apt-get install liboauth0 

Then fix your GTK path:

    $ export CPATH=$CPATH:/usr/include/gtk-2.0
    $ export CPATH=$CPATH:/usr/include/glib-2.0/
    $ export CPATH=$CPATH:/usr/lib/glib-2.0/include/
    $ export CPATH=$CPATH:/usr/include/pango-1.0/
    $ export CPATH=$CPATH:/usr/lib/gtk-2.0/include/
    $ export CPATH=$CPATH:/usr/include/atk-1.0/

#### Archlinux

    # pacman -Syu
    # pacman -S gtk2 liboauth

### Compile

#### Makefile

    $ ./autogen.sh
    $ ./configure
    $ make
    # sudo make install

### Unistalling

    # make uninstall

### GIT Branch

#### Stable

Stable Version Of TwitCrusader

#### Beta

Beta Version Of TwitCrusader

#### Nightly

Unstable Version Of TwitCrusader

#### Experimental

New Features For Nightly Version Of TwitCrusader


## Support

You can find us on this web source:

WebSite: http://www.twitcrusader.org/

Source: https://github.com/PTKDev/

IRC: chat.freenode.net at #teamtwc
