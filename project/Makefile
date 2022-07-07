CONTIKI_PROJECT = sensor
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += helpers.c packet.c

CONTIKI = $(HOME)/contiki
CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include

CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

SOURCEDIRS += $(CONTIKI)/contiki/platform/zoul
