# HexDump
Basic program that can do a hex dump of a file to either the console or another file. Arguments/command-line options are included. If you want to write the hex dump to a file, the files come in pairs in the command. ie.:
"hexdump.exe Red.png Red.txt Green.png Green.txt" is where Red.png is hexdumped to Red.txt and Green.png is hexdumped to Green.txt.
There also commands included to format the hexdump:

With no command line options:

    00000000 89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52 .PNG........IHD</br>
    00000010 00 00 00 01 00 00 00 01 08 02 00 00 00 90 77 53 ..............w</br>
    00000020 de 00 00 00 01 73 52 47 42 00 ae ce 1c e9 00 00 .....sRGB......</br>
    00000030 00 04 67 41 4d 41 00 00 b1 8f 0b fc 61 05 00 00 ..gAMA......a..</br>
    00000040 00 09 70 48 59 73 00 00 0e c3 00 00 0e c3 01 c7 ..pHYs.........</br>
    00000050 6f a8 64 00 00 00 0c 49 44 41 54 18 57 63 f8 cf o.d....IDAT.Wc.</br>
    00000060 c0 00 00 03 01 01 00 63 24 55 d3 00 00 00 00 49 .......c$U.....</br>
    00000070 45 4e 44 ae 42 60 82                            END.B`.</br>

With -a or --address command:

    89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52 .PNG........IHD
    00 00 00 01 00 00 00 01 08 02 00 00 00 90 77 53 ..............w
    de 00 00 00 01 73 52 47 42 00 ae ce 1c e9 00 00 .....sRGB......
    00 04 67 41 4d 41 00 00 b1 8f 0b fc 61 05 00 00 ..gAMA......a..
    00 09 70 48 59 73 00 00 0e c3 00 00 0e c3 01 c7 ..pHYs.........
    6f a8 64 00 00 00 0c 49 44 41 54 18 57 63 f8 cf o.d....IDAT.Wc.
    c0 00 00 03 01 01 00 63 24 55 d3 00 00 00 00 49 .......c$U.....
    45 4e 44 ae 42 60 82                            END.B`.

With -t or --text command:

    00000000 89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52
    00000010 00 00 00 01 00 00 00 01 08 02 00 00 00 90 77 53
    00000020 de 00 00 00 01 73 52 47 42 00 ae ce 1c e9 00 00
    00000030 00 04 67 41 4d 41 00 00 b1 8f 0b fc 61 05 00 00
    00000040 00 09 70 48 59 73 00 00 0e c3 00 00 0e c3 01 c7
    00000050 6f a8 64 00 00 00 0c 49 44 41 54 18 57 63 f8 cf
    00000060 c0 00 00 03 01 01 00 63 24 55 d3 00 00 00 00 49
    00000070 45 4e 44 ae 42 60 82

With both commands:

    89 50 4e 47 0d 0a 1a 0a 00 00 00 0d 49 48 44 52
    00 00 00 01 00 00 00 01 08 02 00 00 00 90 77 53
    de 00 00 00 01 73 52 47 42 00 ae ce 1c e9 00 00
    00 04 67 41 4d 41 00 00 b1 8f 0b fc 61 05 00 00
    00 09 70 48 59 73 00 00 0e c3 00 00 0e c3 01 c7
    6f a8 64 00 00 00 0c 49 44 41 54 18 57 63 f8 cf
    c0 00 00 03 01 01 00 63 24 55 d3 00 00 00 00 49
    45 4e 44 ae 42 60 82
