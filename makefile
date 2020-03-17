src=$(wildcard ./*.cpp)
obj=$(patsubst ./%.cpp, ./%.o, $(src))

target=main

$(target): $(src)
	g++ -std=c++11 $(src) -o $(target) -g

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@
				
.PHONY:clean
clean:
	rm $(obj) $(target)
