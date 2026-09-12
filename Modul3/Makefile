CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Wstrict-prototypes -O0
PTHREAD_FLAGS := -pthread

PROGRAMS := Loop_NIM fork_NIM threadsatu_NIM threaddua_NIM singlethread_NIM threadtiga_NIM

.PHONY: all clean test

all: $(PROGRAMS)

Loop_NIM: Loop_NIM.c
	$(CC) $(CFLAGS) $< -o $@

fork_NIM: fork_NIM.c
	$(CC) $(CFLAGS) $< -o $@

threadsatu_NIM: threadsatu_NIM.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

threaddua_NIM: threaddua_NIM.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

singlethread_NIM: singlethread_NIM.c
	$(CC) $(CFLAGS) $< -o $@

threadtiga_NIM: threadtiga_NIM.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

test:
	bash test_modul3.sh

clean:
	rm -f $(PROGRAMS)
