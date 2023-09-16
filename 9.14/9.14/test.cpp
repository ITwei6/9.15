#include <iostream>
using namespace std;
#include "mymap.h"
#include "myset.h"
#include "RBTree.h"


int main()
{

	tao::map<int, int> m;
	m.insert(make_pair(2, 2));
	m.insert(make_pair(1, 1));
	m.insert(make_pair(3, 3));
	m.insert(make_pair(4, 4));


	tao::map<int, int>::iterator mit = m.begin();
	while (mit != m.end())
	{
		//cout << mit->first << " " << mit->second << endl;
		//mit->first = 1;
		mit->second = 2;
		++mit;
	}

	tao::set<int> s;
	s.insert(10);
	s.insert(25);
	s.insert(3);
	s.insert(2);
	s.insert(24);
	s.insert(21);
	s.insert(12);
	tao::set<int>::iterator it=s.begin();
	while (it != s.end())
	{
		//cout << *it << " ";
		//*it += 10;
		++it;
	}


}