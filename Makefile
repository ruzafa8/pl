FUENTEFLEX = lexer
FUENTEBISON = parser
FUENTE = main
PRUEBA = file

all: compile

compile:
	flex $(FUENTEFLEX).l
	bison $(FUENTEBISON).y -yd -g -v
	gcc -o $(FUENTE) -g lex.yy.c y.tab.c bool.c expression.c hash_table.c statement.c ExpressionStatement.c -lfl -ly

clean:
	rm $(FUENTE) lex.yy.c y.tab.c y.tab.h

run:
	./$(FUENTE) $(PRUEBA)

