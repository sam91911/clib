main: libserver.a libhttp.a

CFLAGS= -w -O2 -c

libserver.a: server.c server.h
	gcc $(CFLAGS) $< -o $@
libhttp.a: http.c http.h
	gcc $(CFLAGS) $< -o $@
