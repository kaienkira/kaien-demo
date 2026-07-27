src =\
main.cc \
shader_program.cc \
vertex_array.cc \
../glad/src/gl.c

debug:
	@g++ -g -std=c++20 -I../glad/include/ $(src) -o hello_world `pkgconf --libs glfw3`

clean:
	@rm -f hello_world
