#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
#include <fstream>

struct Item{

	std::string name;
	int iid;
	double value;

	//Item (std::string nn, int ii, double dd) : name(nn), iid(ii), value(dd) {}

};

//Operátorok

std::ostream& operator<<(std::ostream& os, Item& i){

	os<<i.name<<' '<<i.iid<<' '<<i.value<<std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Item& i){
	
	std::string name;
	int id;
	double val;
	is>>name>>id>>val;
	if(!is) return is;
	Item itt{name, id, val};
	i=itt;

	return is;
}


//Print

template<typename C>
void print(C& cont){

	for(auto a : cont){
		std::cout<<a; 
	}

}

//Függvény objektumok

struct Compare_by_name{
	bool operator()(const Item& a, const Item& b)
		{return a.name < b.name; }
};

struct Compare_by_value{
	bool operator()(const Item& a, const Item& b)
		{return a.value > b.value; }
};

struct Find_name{
	std::string name;
	Find_name(std::string nn) : name(nn) {}

	bool operator()(Item& a){return a.name==name; }

};

struct Find_iid{
	int iid;
	Find_iid(int ii) : iid(ii) {}

	bool operator()(Item& a){return a.iid==iid; }

};


int main(){

	std::vector<Item> vi;

	const std::string str{"Items.txt"};
	std::ifstream ifs{str};
	if(!ifs) throw std::runtime_error("could not read from file: " + str);

	for(Item ii; ifs>>ii;) vi.push_back(ii);

	std::cout<<"Basic vector: "<<std::endl;
	print(vi);

	std::list<Item> li (vi.size());
	
	std::copy(vi.begin(), vi.end(), li.begin());

	std::sort(vi.begin(), vi.end(), Compare_by_name());
	
	std::sort(vi.begin(), vi.end(),
		[](const Item& a, const Item& b) {return a.iid < b.iid;});
	
	std::sort(vi.begin(), vi.end(), Compare_by_value());
	
	Item i1{"horse shoe", 99, 12.34};
	Item i2{"Canon S400", 9988, 499.99};

	vi.push_back(i1);
	vi.push_back(i2);
	//print(vi);

	//erase
	vi.erase(
		std::find_if(vi.begin(), vi.end(), Find_name("Telefon")));
	vi.erase(
		std::find_if(vi.begin(), vi.end(), Find_name("Egér")));

	vi.erase(
		std::find_if(vi.begin(), vi.end(), Find_iid(99)));
	vi.erase(
		std::find_if(vi.begin(), vi.end(), Find_iid(1)));

	std::cout<<std::endl<<"After erase: "<<std::endl;
	print(vi);

	li.sort(Compare_by_name());
	
	li.sort([](const Item& a, const Item& b) {return a.iid < b.iid;});
	
	li.sort(Compare_by_value());
		
	li.insert(li.begin(), i1);
	li.insert(li.begin(), i2);
  
	li.erase(
		std::find_if(li.begin(), li.end(), Find_name("Telefon")));
	li.erase(
		std::find_if(li.begin(), li.end(), Find_name("Egér")));

	std::cout<<std::endl<<"List after erase: "<<std::endl;
	print(li);

	return 0;
}
