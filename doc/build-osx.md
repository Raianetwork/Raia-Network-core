macOS Build Instructions and Notes
====================================
The commands in this guide should be executed in a Terminal application.
The built-in one is located in 
```
/Applications/Utilities/Terminal.app
```

Preparation
-----------
Install the macOS command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

Dependencies
----------------------

    brew install automake berkeley-db4@4 libtool boost miniupnpc openssl@1.1 pkg-config protobuf python qt@5 libevent qrencode

If you run into issues, check [Homebrew's troubleshooting page](https://docs.brew.sh/Troubleshooting).
See [dependencies.md](dependencies.md) for a complete overview.

Some have issues with brew not linking python. Might need to refer to a guide to make sure python is behaving. You might need to get `protobuf@3` instead of the default. I ran into some make deploy issues there. If you are just building for a local system, you probably don't need to run make deploy. After make, you can probably just do make install.

If you want to build the disk image with `make deploy` (.dmg / optional), you need RSVG:
```shell
brew install librsvg
```

## Berkeley DB
It is recommended to use Berkeley DB 4.8. If you have to build it yourself,
you can use [this](/contrib/install_db4.sh) script to install it
like so:

```shell
CFLAGS="-Wno-error=implicit-function-declaration" ./contrib/install_db4.sh .
```

```shell
brew install berkeley-db@4
brew link berkeley-db4 --force
```

**Note**: You only need Berkeley DB if the wallet is enabled (see [*Disable-wallet mode*](/doc/build-osx.md#disable-wallet-mode)).

## Build RAIA Network

1. Clone the RAIA Network source code:
    ```shell
    git clone https://github.com/Raianetwork/Raia-Network-core
    cd Raianetwork
    ```

2.  Build raianetwork-core:

    Configure and build the headless raianetwork binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.
    ```shell
    ./autogen.sh
    ./configure
    make
    ```

3.  It is recommended to build and run the unit tests:
    ```shell
    make check
    ```

4.  You can also create a  `.dmg` that contains the `.app` bundle (optional):
    ```shell
    make deploy
    ```

## `disable-wallet` mode
When the intention is to run only a P2P node without a wallet, RAIA Network may be
compiled in `disable-wallet` mode with:
```shell
./configure --disable-wallet
```

In this case there is no dependency on Berkeley DB 4.8 and SQLite.

Mining is also possible in disable-wallet mode using the `getblocktemplate` RPC call.

## Running
RAIA Network is now available at `./src/raianetworkd`

Before running, you may create an empty configuration file:
```shell
mkdir -p "/Users/${USER}/Library/Application Support/Raianetwork"

touch "/Users/${USER}/Library/Application Support/Raianetwork/raianetwork.conf"

chmod 600 "/Users/${USER}/Library/Application Support/Raianetwork/raianetwork.conf"
```

The first time you run raianetworkd, it will start downloading the blockchain. This process could
take many hours, or even days on slower than average systems.

You can monitor the download process by looking at the debug.log file:
```shell
tail -f $HOME/Library/Application\ Support/Raianetwork/debug.log
```

Other commands:
-------

    ./src/raianetworkd -daemon # Starts the raianetwork daemon.
    ./src/raianetwork-cli --help # Outputs a list of command-line options.
    ./src/raianetwork-cli help # Outputs a list of RPC commands when the daemon is running.

Using Qt Creator as IDE
------------------------
You can use Qt Creator as an IDE, for raianetwork development.
Download and install the community edition of [Qt Creator](https://www.qt.io/download/).
Uncheck everything except Qt Creator during the installation process.

1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "raianetwork-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installation)
10. Start debugging with Qt Creator

Notes
-----

* Tested on OS X 10.8 through 10.15 on 64-bit Intel processors only.

* Building with downloaded Qt binaries is not officially supported. 

* autoreconf (boost issue)
