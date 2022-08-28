/*

Singleton Pattern

Creates a single instance of the class which is global to all the programs

Not a good design pattern

*/


#include <iostream>

using namespace std;


// NOT THREAD SAFE IMPLEMENTATION
class MySingleton
{
public:
	static MySingleton* get_instance()
	{
		// lazy initialization
		if (instance == nullptr)
		{
			cout << "Instance not found, creating one" << endl;
			instance = new MySingleton();
		}
		return instance;
	}
private:
	MySingleton() { cout << "MySingleton Instance Created" << endl; }
	~MySingleton() {}

	// private copy constructor and move operator (optionally you can use delete and make them public)
	MySingleton(const MySingleton& copy) {};
	MySingleton& operator=(const MySingleton& copy) {}

	// static declaration makes this variable common across all the objects of this class
	// static declaration requires its initialization outside of object creation
	static MySingleton* instance;
};

MySingleton* MySingleton::instance = nullptr;

int main()
{
	MySingleton* t1 = MySingleton::get_instance();
	MySingleton* t2 = MySingleton::get_instance();
	return 0;
}