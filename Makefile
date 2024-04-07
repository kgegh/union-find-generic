tests: tests.cpp
	g++ tests.cpp -lgtest -lgtest_main -o tests
	./tests
	rm tests
