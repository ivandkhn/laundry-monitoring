CONTIKI_PROJECT = sensor
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += helpers.c packet.c edgepool.c

CONTIKI = $(HOME)/contiki
CONTIKI_WITH_RIME = 1
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
include $(CONTIKI)/Makefile.include

SOURCEDIRS += $(CONTIKI)/contiki/platform/zoul
