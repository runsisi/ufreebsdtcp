# author: runsisi@hust.edu.cn
# date:   2013/08/24

.PHONY : all clean

CC := /opt/zte/x86_64_gcc4.5.2_glibc2.13.0/bin/x86_64-pc-linux-gnu-gcc
AR := /opt/zte/x86_64_gcc4.5.2_glibc2.13.0/bin/x86_64-pc-linux-gnu-ar

CODE_DIR := $(CURDIR)/../../..
ROOT_DIR := $(CURDIR)
TARGET := $(ROOT_DIR)/libbsdtcp.a

INC_DIRS := $(ROOT_DIR)/include \
			$(ROOT_DIR)/include/opt \
			$(CODE_DIR)/dps/pub/include \

SRC_DIRS := $(ROOT_DIR)/source

INCS := $(addprefix -I, $(INC_DIRS))
SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

MACROS := -D_KERNEL
CFLAGS := -MD -MP $(INCS) $(MACROS)

all : $(TARGET)
	@printf "\r\x1b[KCompilation done!\nBrought to u by runsisi@hust.edu.cn :)\n"

$(TARGET) : $(OBJS)
	@$(AR) -crs $@ $^

# a little trick to use as a progress indicator, it is not a shell variable!!!
i := 0

%.o : %.c
	$(eval i := $(shell expr $$(expr $(i) + 1) % 6))
	@printf .
	@$(CC) -c $(CFLAGS) -o $@ $<
	@if [ $(i) -eq 0 ]; then printf "\r\x1b[K"; fi;

-include $(DEPS)

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET)
