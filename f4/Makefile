CC:=gcc
CCFLAGS:=-Wall -Wextra
BIN:=.

q1: q1/q1.c
	$(CC) $(CCFLAGS) q1/q1.c -o mycat

q1_alt: q1/q1_alt.c mycat
	$(CC) $(CCFLAGS) q1/q1_alt.c -o mycat

q2: q2/q2.c
	$(CC) $(CCFLAGS) q2/q2.c -o mychmod

q4_stat: q4/q4_stat.c
	$(CC) $(CCFLAGS) q4/q4_stat.c -o q4_stat

q4_access: q4/q4_access.c
	$(CC) $(CCFLAGS) q4/q4_access.c -o q4_access

q4_atomic:
	$(CC) $(CCFLAGS) q4/q4_atomic.c -o q4_atomic

q5: q5/q5.c
	$(CC) $(CCFLAGS) q5/q5.c -o mypwd