#Generated from ./sem/Makefile.in
all: all-ack

all-ack:
all-gnu:

makefiles: Makefile
Makedepend-ack Makedepend-gnu: 
	sh ../generate.sh ./sem ../obj-ack/ ../obj-gnu

Makefile: Makefile.in Makedepend-ack Makedepend-gnu
	sh ../generate.sh ./sem ../obj-ack/ ../obj-gnu
	@echo
	@echo *Attention*
	@echo Makefile is regenerated... rerun command to see changes
	@echo *Attention*
	@echo

depend: depend-ack
all-ack: ../obj-ack//libsem.a

../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_m_create.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_b_create.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_c_create.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_take.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_give.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_delete.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_value.o)
../obj-ack//libsem.a: ../obj-ack//libsem.a(sem_flush.o)

../obj-ack//libsem.a:
	ar cr ../obj-ack//libsem.a ../obj-ack//./sem/*.o
	rm ../obj-ack//./sem/*.o

../obj-ack//libsem.a(sem_m_create.o): sem_m_create.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_m_create.o sem_m_create.c
../obj-ack//libsem.a(sem_b_create.o): sem_b_create.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_b_create.o sem_b_create.c
../obj-ack//libsem.a(sem_c_create.o): sem_c_create.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_c_create.o sem_c_create.c
../obj-ack//libsem.a(sem_take.o): sem_take.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_take.o sem_take.c
../obj-ack//libsem.a(sem_give.o): sem_give.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_give.o sem_give.c
../obj-ack//libsem.a(sem_delete.o): sem_delete.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_delete.o sem_delete.c
../obj-ack//libsem.a(sem_value.o): sem_value.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_value.o sem_value.c
../obj-ack//libsem.a(sem_flush.o): sem_flush.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./sem/sem_flush.o sem_flush.c

all-gnu: ../obj-gnu/libsem.a

../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_m_create.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_b_create.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_c_create.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_take.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_give.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_delete.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_value.o
../obj-gnu/libsem.a: ../obj-gnu/./sem/sem_flush.o

../obj-gnu/libsem.a:
	gar cr ../obj-gnu/libsem.a $?

../obj-gnu/./sem/sem_m_create.o: sem_m_create.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_m_create.o sem_m_create.c

../obj-gnu/./sem/sem_b_create.o: sem_b_create.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_b_create.o sem_b_create.c

../obj-gnu/./sem/sem_c_create.o: sem_c_create.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_c_create.o sem_c_create.c

../obj-gnu/./sem/sem_take.o: sem_take.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_take.o sem_take.c

../obj-gnu/./sem/sem_give.o: sem_give.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_give.o sem_give.c

../obj-gnu/./sem/sem_delete.o: sem_delete.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_delete.o sem_delete.c

../obj-gnu/./sem/sem_value.o: sem_value.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_value.o sem_value.c

../obj-gnu/./sem/sem_flush.o: sem_flush.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./sem/sem_flush.o sem_flush.c




clean::
	rm -f ../obj-ack//./sem/*
	rm -f ../obj-gnu/./sem/*

include Makedepend-ack
include .depend-ack

include Makedepend-gnu
include .depend-gnu
