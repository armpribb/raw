# raw

A command line tool to output a hex code representation of the input. Input sources can be console / command line prompt or a list of files. The result can either be written to console / command line, copied to clipboard (currently Windows only), or written to a file (in development). The format of the hex code representation is configurable via command line options and includes the following options (to be extended in the future): hex prefix (with/without), byte separator, byte group size, upper-/lowercase.

## why

I came up with the idea because I often have to generate binary test data (e.g. certificates or keys in DER or PKCS#7 format), which need to be hardcoded into test code. Any kind of binary data obviously needs to be represented in hex code format to be stored. The output of OS native tools like `hexdump` (Linux) or `Format-Hex` (Windows) often needs further processing to effectively be used in C++ code (removing addresses, adding hex prefix, use different byte separators). This little convenience tool shall make that whole process easier...

## use

    $ raw -h
    get hex-code representation of any cleartext or binary input
    Usage:
      raw [OPTION...]

      -i, --input arg            choose input [console|file] (default: console)
      -o, --output arg           choose output [clipboard|console|file]
                                 (default: clipboard)
      -f, --file arg             specify file(s) to convert (multiple possible
                                 with additional flag each)
      -n, --n-byte-group arg     group n bytes together (default: 1)
      -p, --hex-prefix           add '0x' prefix to hex values
      -s, --group-separator arg  choose byte group separator (default:  )
      -u, --uppercase            use uppercase hex values
      -v, --verbose              verbose output
      -h, --help                 print help

## build

    $ mkdir build && cd build
    $ cmake ..
    $ cmake --build .

Of course you may also use any other C/C++ compiler and/or generator, e.g.:

    $ mkdir build && cd build
    $ CC=clang CXX=clang++ cmake -G Ninja ..
    $ ninja raw

## future

- store formatting configuration in file
- load formatting configuration from file (default)
- clipboard support for Linux
- more formatting options
