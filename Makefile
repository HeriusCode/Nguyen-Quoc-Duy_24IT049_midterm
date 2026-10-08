CC=cc
CFLAGS=-Wall -Wextra -Werror

OBJS=main.o options.o ls.o fileinfo.o display.o sort.o

myls: $(OBJS)
	$(CC) $(CFLAGS) -o myls $(OBJS)

main.o: main.c options.h ls.h
	$(CC) $(CFLAGS) -c main.c

options.o: options.c options.h
	$(CC) $(CFLAGS) -c options.c

ls.o: ls.c ls.h options.h fileinfo.h display.h sort.h
	$(CC) $(CFLAGS) -c ls.c

fileinfo.o: fileinfo.c fileinfo.h
	$(CC) $(CFLAGS) -c fileinfo.c

display.o: display.c display.h fileinfo.h options.h
	$(CC) $(CFLAGS) -c display.c

sort.o: sort.c sort.h fileinfo.h options.h
	$(CC) $(CFLAGS) -c sort.c

clean:
	rm -f $(OBJS) myls
