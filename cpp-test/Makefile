.PHONY: \
default \
clean \
test_cmath \
test_concept \
test_deducing_this \
test_float \
test_float_exception \
test_multidimensional_subscript_operator \
test_static_lambda \
test_std_is_base_of \
test_std_conditional \
test_type_traits

CC = g++
CPP_FLAGS = -g -Wall -std=c++23

default: test_float

clean:
	rm -rf ./bin

test_cmath:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_concept:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_deducing_this:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_float:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_float_exception:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_multidimensional_subscript_operator:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_static_lambda:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_std_is_base_of:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_std_conditional:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@

test_type_traits:
	mkdir -p bin/
	$(CC) $(CPP_FLAGS) $@.cc -o bin/$@
	./bin/$@
