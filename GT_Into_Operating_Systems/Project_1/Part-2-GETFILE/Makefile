CFLAGS := -Wall --std=gnu99 -g -Wno-format-security

ARCH := $(shell uname)
ifneq ($(ARCH),Darwin)
  LDFLAGS += -lpthread
endif

all: gfserver_main gfclient_download

gfserver_main: gfserver.o handler.o gfserver_main.o content.o
	$(CC) -o $@ $(CFLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) $(CURL_LIBS)

gfclient_download: gfclient.o workload.o gfclient_download.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS) 

.PHONY: clean

clean:
	rm -fr *.o gfserver_main gfclient_download