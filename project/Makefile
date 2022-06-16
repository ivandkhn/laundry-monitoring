CONTIKI_PROJECT = sensor
all: $(CONTIKI_PROJECT)

PROJECT_SOURCEFILES += helpers.c packet.c

CONTIKI = $(HOME)/contiki
CONTIKI_WITH_RIME = 1
include $(CONTIKI)/Makefile.include

SOURCEDIRS += $(CONTIKI)/contiki/platform/zoul
