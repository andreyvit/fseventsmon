build: fseventsmon

clean:
	-rm fseventsmon

fseventsmon: fseventsmon.c
	gcc -o fseventsmon -framework CoreFoundation -framework CoreServices fseventsmon.c

install: build
	cp fseventsmon /usr/local/bin

.PHONY: build clean install
