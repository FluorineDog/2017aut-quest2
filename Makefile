def:
	echo "Usage: make <container_name>"
	exit 1

vector:
	g++ -std=c++14 vector_test.cc -o vector_test
	./vector_test
