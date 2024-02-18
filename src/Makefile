CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

obj-m := bokasan.o

# set KDIR to path of target kernel
KDIR := /usr/src/kernels/4.19.90-52.22.v2207.ky10.x86_64
MY_CFLAGS += -g -DDBUG -Wall -D_FORTIFY_SOURCE=0

bokasan-objs := process_handle.o hook.o alloc.o page.o kasan.o report.o config.o

all:
	make -C $(KDIR) "M=$(shell pwd)" modules EXTRA_CFLAGS=""

debug:
	make -C $(KDIR) "M=$(shell pwd)" modules EXTRA_CFLAGS="$(MY_CFLAGS)"

clean:
	make -C $(KDIR) "M=$(shell pwd)" clean
