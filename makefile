exec = spt.exe
src = $(wildcard src/*.c)

src_cs = src/LSystem/LSystem.cs

objects = $(src: .c=.o)
flags = -Lsrc/libraries/lib/x64/ -lSDL2 -lSDL2Main -I"src/include/"

$(exec): $(objects) $(src_cs)
	gcc $(objects) $(flags) -o $(exec)
	make build
%.o: %.c src/include/%.h
	gcc -c $(flags) $< -o $@

build: $(src_cs)
	csc $(src_cs)

