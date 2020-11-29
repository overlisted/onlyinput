CC = gcc
CFLAGS = -I. -O1 -g -Wall
LDFLAGS = -lX11 -lm -lpthread -lGL

MINGW32?=i686-w64-mingw32-

example.exe: example.c
	$(MINGW32)$(CC) -g -fno-ident -mwindows -m32 $(CFLAGS) -o $@ $^  -lgdi32 -lws2_32 -s -D_WIN32_WINNT=0x0600 -DWIN32 -liphlpapi -lopengl32 -DMINGW_BUILD

example: example.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: example
	./example

clean:
	rm example
	rm example.exe
