#Generated from ./klog/Makefile.in
all: all-ack

all-ack:
all-gnu:

makefiles: Makefile
Makedepend-ack Makedepend-gnu: 
	sh ../generate.sh ./klog ../obj-ack/ ../obj-gnu

Makefile: Makefile.in Makedepend-ack Makedepend-gnu
	sh ../generate.sh ./klog ../obj-ack/ ../obj-gnu
	@echo
	@echo *Attention*
	@echo Makefile is regenerated... rerun command to see changes
	@echo *Attention*
	@echo

depend: depend-ack
all-ack: ../obj-ack//libklog.a

../obj-ack//libklog.a: ../obj-ack//libklog.a(klog_set.o)
../obj-ack//libklog.a: ../obj-ack//libklog.a(klog_copy.o)

../obj-ack//libklog.a:
	ar cr ../obj-ack//libklog.a ../obj-ack//./klog/*.o
	rm ../obj-ack//./klog/*.o

../obj-ack//libklog.a(klog_set.o): klog_set.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./klog/klog_set.o klog_set.c
../obj-ack//libklog.a(klog_copy.o): klog_copy.c
	cc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-ack//./klog/klog_copy.o klog_copy.c

all-gnu: ../obj-gnu/libklog.a

../obj-gnu/libklog.a: ../obj-gnu/./klog/klog_set.o
../obj-gnu/libklog.a: ../obj-gnu/./klog/klog_copy.o

../obj-gnu/libklog.a:
	gar cr ../obj-gnu/libklog.a $?

../obj-gnu/./klog/klog_set.o: klog_set.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./klog/klog_set.o klog_set.c

../obj-gnu/./klog/klog_copy.o: klog_copy.c
	gcc -O -D_MINIX -D_POSIX_SOURCE -c -o ../obj-gnu/./klog/klog_copy.o klog_copy.c




clean::
	rm -f ../obj-ack//./klog/*
	rm -f ../obj-gnu/./klog/*

include Makedepend-ack
include .depend-ack

include Makedepend-gnu
include .depend-gnu
