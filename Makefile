TARGETS=dict fhandler option menus input
HEADERS=fhandler.h option.h menus.h input.h
CFLAGS=-g

OBJ=$(addsuffix .o, $(TARGETS))

dict: $(OBJ)
	gcc $(CFLAGS) -o $@ $(OBJ)

run: dict
	./dict

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm dict || true
	rm *.o  || true