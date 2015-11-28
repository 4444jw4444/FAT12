.phony all:
all: diskinfo disklist diskput diskget

diskinfo: diskinfo.c
	gcc diskinfo.c -g -O0 -lreadline -lhistory -ltermcap -o diskinfo

disklist: disklist.c
	gcc disklist.c -lreadline -lhistory -ltermcap -o disklist

diskget: diskget.c
	gcc diskget.c -lreadline -lhistory -ltermcap -o diskget

diskput: diskput.c
	gcc diskput.c -lreadline -lhistory -ltermcap -o diskput

.PHONY clean:
clean:
	-rm -rf *.o *.exe
