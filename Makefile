function: lex.yy.o parser.tab.o function.o
	g++ -Wall -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp function.hpp
	g++ -Wall -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp function.hpp
	g++ -Wall -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d $<
function.o: function.cpp function.hpp
	g++ -Wall -c -o $@ $<


.PHONY: clean


clean:
	rm -f *~ *tab* *yy* *.o function
