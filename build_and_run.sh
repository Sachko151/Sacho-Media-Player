gcc `pkg-config --cflags gtk+-3.0` main.c -o output.out `pkg-config --libs gtk+-3.0` -rdynamic -lvlc
./output.out