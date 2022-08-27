/*

Flyweight pattern lets you re-use immutable state variables thus saving RAM. 
It is an optimization technique.

As an example, consider the following:
1. You have a 'Forest' of 'Trees' (could be like 1000 of them)
2. Each tree is of a type (say 10 types 'TypeOne', 'TypeTwo' ... 'TypeTen'
3. Each tree has additional details like 'Location', 'Age'
4. You don't have to store TreeType for each of the tree object created
5. Instead, you can have a flyweight factory that stores all these types as a cache and your tree
object has reference to this type (thus saving space)

*/




#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


// TreeType is our flyweight object. It stores the static information of Tree Objects
class TreeType
{
private:
	string type;
public:
	TreeType(const string& t) : type(t) 
	{
		cout << "Constructor called for TreeType = " << type << endl;
	}
	~TreeType()
	{
		cout << "Destructor called for TreeType" << endl;
	}
};

class TreeTypeFactory
{
private:
	unordered_map<string, TreeType*> cache; // stores different TreeType objects 
public:
	TreeTypeFactory()
	{
		cache = {};
		cout << "Default Constructor of TreeTypeFactory" << endl;
	}
	TreeTypeFactory(const vector<string>& types)
	{
		cout << "Creating TreeTypeFactory" << endl;
		cache = {};
		for (auto t: types)
		{
			TreeType* tmp = new TreeType(t);
			cache[t] = tmp;
		}
	}
	TreeType*& GetTreeType(const string& t)
	{
		if (cache.find(t) == cache.end())
		{
			cout << "TreeType " << t << " not found in cache. Creating new one" << endl;
			TreeType* tmp = new TreeType(t);
			cache[t] = tmp;
			return tmp;
		}
		else
		{
			cout << "TreeType " << t << " already in memory" << endl;
			return cache[t];
		}
	}
	~TreeTypeFactory()
	{
		for (auto it = cache.begin(); it != cache.end(); it++)
			delete it->second;
		cout << "Destructor called for TreeTypeFactory" << endl;
	}
};

class Tree
{
private:
	int loc;
	int age;
	TreeType* &tt; // reference to the TreeType pointer
public:
	Tree(int l, int a, TreeType*& t) : loc(l), age(a), tt(t) 
	{
		cout << "Constructor of Tree called, new tree at " << l <<", " << age << " yrs old" << endl;
	};
	~Tree()
	{
		cout << "Destructor of Tree called" << endl;
	}
};

class Forest
{
private:
	int num_trees;
	vector<Tree*> trees;
	TreeTypeFactory*& ttf; // reference to a treetype factory
public:
	Forest(TreeTypeFactory*& f) : num_trees(0), trees({}), ttf(f)
	{
		cout << "Constructor of Forest called" << endl;
	}
	~Forest()
	{
		for (int i = 0; i < trees.size(); i++)
		{
			delete trees[i];
		}
		cout << "Destructor of Forest called" << endl;
	}
	void addTree(int l, int a, string t)
	{
		TreeType*& tt = ttf->GetTreeType(t);
		Tree* new_tree = new Tree(l, a, tt);
		trees.push_back(new_tree);
		num_trees++;
		cout << "New tree added to forest, num_trees = " << num_trees << endl;
	}
};

int main()
{
	TreeTypeFactory* ttf = new TreeTypeFactory({ "TypeOne", "TypeTwo", "TypeThree" });
	Forest* f = new Forest(ttf);
	f->addTree(1, 1, "TypeOne");
	f->addTree(2, 2, "TypeTwo");
	f->addTree(3, 3, "TypeThree");
	f->addTree(4, 4, "TypeFour");
	f->addTree(5, 5, "TypeFive");
	
	cout << endl;
	TreeTypeFactory ttf2;
	TreeTypeFactory* p = &ttf2;
	Forest* f2 = new Forest(p);
	f2->addTree(1, 1, "TypeOne");
	f2->addTree(7, 7, "TypeTwo");

	cout << endl;
	delete f;
	delete f2;
	delete ttf;
	return 0;
}