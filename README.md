#TwitCrusader

[![TwitCrusader](http://www.twitcrusader.org/logo.png)](http://www.twitcrusader.org/)

TwitCrusader is Twitter Client For Linux Desktop

##Branchs
* [builds] TwitCrusader Linux-PackageBuild (deb, pkgbuild, rpm, and other) 

* [experimental] TwitCrusader unstable code, testing and other. PTKDev test only.
		
* [nightly] TwitCrusader unstable code, testing and other. Please commit here.
	
* [nightly-cpp]	TwitCrusader++ is fork of TwitCrusader, More information on github.com/KernelMonkey/TwitCrusaderpp

## Are You A Developer?

Development Guidelines (Italian): http://dev.it.twitcrusader.org/

Developers Of TwitCrusader (Italian): http://it.twitcrusader.org/about/

##Required

* gcc or cc
* pkg-config
* intltool
* libcurl >= 7.21.0
* gtk+-2.4 >= 2.24.4
* oauth >= 0.9.1
* libxml-2.0 >= 2.6.32
* libnotify >= 0.7.3

### Compile - Makefile
    $ ./autogen.sh
    $ ./configure
    $ make
    $ su
    # make install

#### Unistalling - Makefile
    $ su
    # make uninstall

##Debug

After installation run:

    $ twc --debug

To have more details run:

    $ gdb twc

( make sure you have gdb installed )


## Support

You can find us on this web source:

WebSite: http://www.twitcrusader.org/

IRC: chat.freenode.net at #teamtwc

Twitter: @teamtwc
