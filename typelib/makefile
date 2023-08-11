main: libtype.a liblist.a libstack.a libxxhash.a libmersenne.a libdarray.a libqueue.a libdict.a
CFLAGS = -w -O2

libtype.a: type.c type.h dict.h darray.h
	gcc $(CFLAGS) -c $< -o $@
libdict.a: dict.c dict.h xxhash.h mersenne.h
	gcc $(CFLAGS) -c $< -o $@
libqueue.a: queue.c queue.h
	gcc $(CFLAGS) -c $< -o $@
libdarray.a: darray.c darray.h
	gcc $(CFLAGS) -c $< -o $@
libmersenne.a: mersenne.c mersenne.h
	gcc $(CFLAGS) -c $< -o $@
libxxhash.a: xxhash.c xxhash.h
	gcc $(CFLAGS) -c $< -o $@
liblist.a: list.c list.h
	gcc $(CFLAGS) -c $< -o $@
libstack.a: stack.c stack.h list.h
	gcc $(CFLAGS) -c $< -o $@
