HEADERS  = gg.hh gg_window.hh gg_button.hh gg_element.hh
OBJECTS  = gg.o gg_window.o gg_button.o gg_element.o
MAINBODY = main.cc
CXXFLAGS = -g -pedantic -Wall -std=c++11 -Wfatal-errors -Werror

default: main

%.o: %.c $(HEADERS)
	g++ -c $< -o $@

main: $(OBJECTS)
	g++ $(OBJECTS) $(MAINBODY) -o $@ -lSDL2 -lSDL2_ttf

clean:
	-rm -f $(OBJECTS)
	-rm -f main
