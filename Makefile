def:
	echo "Usage: make <container_name>"
	exit 1

vector:
	g++ -std=c++14 vector_test.cc -o vector.test -msse4.2

debug_vector:
	g++ -g -std=c++14 vector_test.cc -o vector.test -msse4.2

