ISO_FILES = mac422shell.c simple.c br-abnt2.map

all: ep.iso

ep.iso: $(ISO_FILES)
	mkisofs -o $@ $^

clean:
	rm -f ep.iso
