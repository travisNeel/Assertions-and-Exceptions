// Travis Neel
// Excceptions/assertions
// different examples and circumstances you would use exceptions


#include <iostream>
#include <cassert>
#include <exception>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;
bool debug=true;

// staic_assert can be used when working with templates, in this case to make sure our data can be
// operated on or accumulated; so it must be a numeric short, int, long, double, etc.
template <class T>
class Bag {
private:
	T number;
public:
	//static_assertion
	void setNumber(T n){
		static_assert(isnumber(n), "This data type is not compatible! ");
		number=n;
	}
};

//static asserts can be used to check if copy constructors work
class Ex1 {
public:
	int data=0;
	Ex1();
	Ex1(int n){
		data=n;
	}
	Ex1(const Ex1& e){
		data=e.data;
	}
};

// try-catch to avoid dividing by zero
int divide(int a, int b){
	//assert(b>0)		can use assert here too
	if (b==0) throw "Cannot divide by zero!\n";
	return a/b;
}

// function returning an error if operation fails
int numberCubed(int n){
	int cubed=n*n*n;
	if((cubed/3)==n) return cubed;
	return MATH_ERRNO;
}

// another function returning an error message

int deleteNode(int *node){

	string error="Node points to NULL!";
	if (!node) {
		delete node;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int main(){
	std::cout << "starting Assertions Practice..\n\n";
	
	double n=9.0;
	double n_invalid=-3.0;
	int zero=0;


	// checks to see if the class construction is legal by seeing if the copy constructor
	// is implemented before it tries to copy an object
	if (debug)static_assert(is_copy_constructible<Ex1>::value,"Must implement copy constructor first! ");
	Ex1 ex1(5), ex2(ex1);

	if (debug) assert(n>0); // precondition test the n is greater than zero
	auto square_root_of_n=sqrt(n);
	assert(square_root_of_n*square_root_of_n==n); // postcondition test to verify that the answer is correct
	
	cout<<"n = "<<n<<" and the square root of n = "<<square_root_of_n<<"\n\n";
	
	// running a loop through a structure that may have a starting value of -1
	// use assert to make sure you dont fall into an infinite loop
	auto some_data=3;
	auto some_invalid_data=-1;
	
	assert(some_data>0); //assert that some data is greater than 0
	
	for (int i=0; i<some_data; ++i){
		cout<<"for loop test \n";
	}

	// divide by zero try-catch
	try{
		int product = divide(n, n_invalid);
		cout << product << endl;
	}catch (const char* msg) {
		cerr << msg << endl;
	}
	
	// with zero as dividend
	try{
		int product = divide(n, zero);
		cout << product << endl;
	}catch (const char* msg) {
		cerr << msg << endl;
	}
	
	// another try catch example
	try {
      throw 78;
	} catch (int i) {
  cout<<"caught integer i, which equals "<<i<<endl;
	}
	
	// range error check with a vector
	try{
		vector<int> v(10);
		v.at(11);
	}catch	(exception &e){
		cout<<"error! "<<e.what()<<"out of range!\n";
	}
	
	
	std::cout << "\n..ending\n";
    return 0;
}
