HEADERS  = gg.hh gg_window.hh gg_widget.hh gg_button.hh gg_baseGroup.hh gg_group.hh
OBJECTS  = gg.o gg_window.o gg_widget.o gg_button.o gg_baseGroup.o gg_group.o
MAINBODY = main.cc
CXXFLAGS = -g -pedantic

default: main

%.o: %.c $(HEADERS)
	g++ -c $< -o $@

main: $(OBJECTS)
	g++ $(OBJECTS) $(MAINBODY) -o $@ -lSDL2 -lSDL2_ttf

clean:
	-rm -f $(OBJECTS)
	-rm -f main
