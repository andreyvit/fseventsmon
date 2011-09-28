FSEvents command-line monitoring tool
=====================================

Uses FSEvents to monitor changes on your Mac's file system:

    $ ./fseventsmon /Users/andreyvit
    Monitoring /Users/andreyvit...
    /Users/andreyvit/Library/Saved Application State/com.googlecode.iterm2.savedState/  (ItemInodeMetaMod ItemModified ItemIsFile)
    /Users/andreyvit/Library/Saved Application State/com.sublimetext.2.savedState/  (ItemInodeMetaMod ItemModified ItemIsFile)
    /Users/andreyvit/Library/Cookies/  (ItemCreated ItemRenamed ItemModified ItemIsFile)
    /Users/andreyvit/.dropbox/  (ItemRemoved ItemModified ItemIsFile)
    ...


Installing
==========

Either build it from source (see below), or [download fseventsmon-1.0.zip](https://github.com/downloads/andreyvit/fseventsmon/fseventsmon-1.0.zip), extract it and copy into `/usr/local/bin` (pre-built binary works on 64-bit Macs only).


Building
--------

Clone this Git repository, then run make:

    git clone git://github.com/andreyvit/fseventsmon.git
    cd fseventsmon
    make
    sudo make install

You need to have Xcode installed for the build to work.
