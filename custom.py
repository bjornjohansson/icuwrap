CPPFLAGS = '`icu-config --cppflags` `pkg-config --cflags libcurl` `pkg-config --cflags libxml++-2.6` -Wall -pedantic-errors'
LINKFLAGS = '`icu-config --ldflags` `pkg-config --libs libcurl` `pkg-config --libs libxml++-2.6`'
CPPDEFINES = []
LIBPATH = []
