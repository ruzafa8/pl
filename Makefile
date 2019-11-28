FUENTEFLEX = lexer
FUENTEBISON = parser
FUENTE = main

all: compile

compile:
	flex $(FUENTEFLEX).l
	bison $(FUENTEBISON).y -yd
	gcc -o $(FUENTE) lex.yy.c y.tab.c -lfl -ly

clean:
	rm $(FUENTE) lex.yy.c y.tab.c y.tab.h

run:
	./$(FUENTE) < $(PRUEBA)

