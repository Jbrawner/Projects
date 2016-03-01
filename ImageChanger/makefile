SRC=main3G.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C filter.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3G

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3G
run:
	./proj3G 3B_input.pnm out.pnm
pic:
	pnmtopng < out.pnm >test.png
	open test.png 
