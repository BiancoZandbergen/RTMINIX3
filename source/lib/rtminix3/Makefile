#Generated from ./rtminix3/Makefile.in
all: all-ack

all-ack:
all-gnu:

makefiles: Makefile
Makedepend-ack Makedepend-gnu: 
	sh ../generate.sh ./rtminix3 ../obj-ack/ ../obj-gnu

Makefile: Makefile.in Makedepend-ack Makedepend-gnu
	sh ../generate.sh ./rtminix3 ../obj-ack/ ../obj-gnu
	@echo
	@echo *Attention*
	@echo Makefile is regenerated... rerun command to see changes
	@echo *Attention*
	@echo

depend: depend-ack
all-ack: ../obj-ack//librt.a

../obj-ack//librt.a: ../obj-ack//librt.a(rt_set_sched_edf.o)
../obj-ack//librt.a: ../obj-ack//librt.a(rt_set_sched_rm.o)
../obj-ack//librt.a: ../obj-ack//librt.a(rt_set_edf.o)
../obj-ack//librt.a: ../obj-ack//librt.a(rt_set_rm.o)
../obj-ack//librt.a: ../obj-ack//librt.a(rt_nextperiod.o)
../obj-ack//librt.a: ../obj-ack//librt.a(rt_set_sched_bridge.o)

../obj-ack//librt.a:
	ar cr ../obj-ack//librt.a ../obj-ack//./rtminix3/*.o
	rm ../obj-ack//./rtminix3/*.o

../obj-ack//librt.a(rt_set_sched_edf.o): rt_set_sched_edf.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_set_sched_edf.o rt_set_sched_edf.c
../obj-ack//librt.a(rt_set_sched_rm.o): rt_set_sched_rm.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_set_sched_rm.o rt_set_sched_rm.c
../obj-ack//librt.a(rt_set_edf.o): rt_set_edf.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_set_edf.o rt_set_edf.c
../obj-ack//librt.a(rt_set_rm.o): rt_set_rm.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_set_rm.o rt_set_rm.c
../obj-ack//librt.a(rt_nextperiod.o): rt_nextperiod.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_nextperiod.o rt_nextperiod.c
../obj-ack//librt.a(rt_set_sched_bridge.o): rt_set_sched_bridge.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./rtminix3/rt_set_sched_bridge.o rt_set_sched_bridge.c

all-gnu: ../obj-gnu/librt.a

../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_set_sched_edf.o
../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_set_sched_rm.o
../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_set_edf.o
../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_set_rm.o
../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_nextperiod.o
../obj-gnu/librt.a: ../obj-gnu/./rtminix3/rt_set_sched_bridge.o

../obj-gnu/librt.a:
	gar cr ../obj-gnu/librt.a $?

../obj-gnu/./rtminix3/rt_set_sched_edf.o: rt_set_sched_edf.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_set_sched_edf.o rt_set_sched_edf.c

../obj-gnu/./rtminix3/rt_set_sched_rm.o: rt_set_sched_rm.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_set_sched_rm.o rt_set_sched_rm.c

../obj-gnu/./rtminix3/rt_set_edf.o: rt_set_edf.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_set_edf.o rt_set_edf.c

../obj-gnu/./rtminix3/rt_set_rm.o: rt_set_rm.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_set_rm.o rt_set_rm.c

../obj-gnu/./rtminix3/rt_nextperiod.o: rt_nextperiod.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_nextperiod.o rt_nextperiod.c

../obj-gnu/./rtminix3/rt_set_sched_bridge.o: rt_set_sched_bridge.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./rtminix3/rt_set_sched_bridge.o rt_set_sched_bridge.c




clean::
	rm -f ../obj-ack//./rtminix3/*
	rm -f ../obj-gnu/./rtminix3/*

include Makedepend-ack
include .depend-ack

include Makedepend-gnu
include .depend-gnu
