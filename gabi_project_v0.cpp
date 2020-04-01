//domain
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>

class Notion
{
	private:
		std::string name;
	public:
		Notion():name{""}
		{
			std::cout<<"implicit constructor...\n";
			std::cout<<"implicit constructor done...\n";
		}

		Notion(std::string _name):name{_name}
		{
			std::cout<<"explicit constructor...\n";
			std::cout<<"explicit constructor done...\n";
		}
		
		Notion(const Notion& _notion):name{_notion.name}
		{
			std::cout<<"copy constructor...\n";
			std::cout<<"copy constructor done...\n";
		}



		std::string get_name() const;
		

		Notion& operator=(const Notion&);
		bool operator==(const Notion&) const;
		friend std::istream& operator>>(std::istream& is,Notion& n);
		friend std::ostream& operator<<(std::ostream& os,const Notion& n);
		~Notion();
};

std::istream& operator>>(std::istream& is,Notion& n)
{
	is>>n.name;
	return is;
}

std::ostream& operator<<(std::ostream& os,const Notion& n)
{
	os<<n.name;
	return os;
}

bool Notion::operator==(const Notion& other) const
{
	return this->name == other.name;
}


std::string Notion::get_name() const
{
	return this->name;
}



Notion& Notion::operator=(const Notion& other)
{
	std::cout<<"copy operator...\n";
	this->name = other.name;
	std::cout<<"copy operator done...\n";
	return *this;
}

Notion::~Notion()
{
std::cout<<"destructor...\n";
std::cout<<"destructor done...\n";

}

template <typename TElem>
class Repo
{
	protected:
		std::vector<TElem> elems;
	public:
		Repo()
		{
		}

		Repo(const Repo& other)
		{
		this->elems = other.elems;
		}

		//C
		void store(const TElem& key)
		{
			auto b = this->elems.begin();
			auto e = this->elems.end();
			auto pos = std::find_if(b,e, [&key] (const TElem& s) { return s == key; } );			
			if (pos!=e)
				throw std::string{"existing element!"};
			this->elems.push_back(key);
		}
	
		//R
		const TElem& get_element(TElem& key)
		{
			auto b = this->elems.begin();
			auto e = this->elems.end();
			auto pos = std::find_if(b,e, [&key] (const TElem& s) { return s == key; } );			
			if (pos==e)
				throw std::string{"inexisting element!"};
			
			return *pos;
		}
		
		const std::vector<TElem>& get_all() const
		{
			return this->elems;
		}

		int size() const
		{
			return this->elems.size();
		}

		//U
		void update(const TElem& key)
		{
			auto b = this->elems.begin();
			auto e = this->elems.end();
			auto pos = std::find_if(b,e, [&key] (const TElem& s) { return s == key; } );			
			if (pos==e)
				throw std::string{"inexisting element!"};

			this->elems[pos-b] = key;
		}

		//D
		TElem remove(const TElem& key)
		{
			auto b = this->elems.begin();
			auto e = this->elems.end();
			auto pos = std::find_if(b,e, [&key] (const TElem& s) { return s == key; } );			
			if (pos==e)
				throw std::string{"inexisting element!"};


			TElem elem = *pos;
			this->elems.erase(pos);
			return elem;

		}

		~Repo(){}
};


class NotionRepository:public Repo<Notion>
{
	public:
		NotionRepository():Repo<Notion>{}
		{
		std::cout<<"starting notion repository constructor ...\n";
		};

		~NotionRepository(){}
};

class NotionValidator
{
	public:
		void validate_notion(const Notion&);
};

void NotionValidator::validate_notion(const Notion& notion)
{
	std::string error="";
	if (notion.get_name()=="")
		error+="invalid name!\n";
	std::cout<<error<<"\n";
	if (error.size()>0)
		throw error;
}

class NotionService
{
	private:
		NotionValidator& validNotion;
		NotionRepository& repoNotion;
	public:
		NotionService(NotionValidator& _validNotion,NotionRepository& _repoNotion):validNotion{_validNotion},repoNotion{_repoNotion}
		{
		std::cout<<"explicit constructor for service notion...\n";
		}



		~NotionService()
		{
		std::cout<<"destructor for service notion...\n";

		}
};

class Console
{
	
	private:
		typedef void (Console::*MFP)(std::istream&);
		NotionService& srvNotion;
		std::unordered_map<std::string,MFP>  commands;
		void ui_add_notion(std::istream&);
	public:
		Console(NotionService& _srvNotion):srvNotion{_srvNotion}
		{
		std::cout<<"explicit constructor for console...\n";
		commands["add_notion"]=&Console::ui_add_notion;
		}

		void run();

		~Console()
		{
		std::cout<<"destructor for console...\n";
		}
};

void Console::ui_add_notion(std::istream& is)
{
	std::string notion_name;
	is>>notion_name;
	
}

void Console::run()
{

	std::string cmd;
	while(1)
	{
		std::cin>>cmd;
		if (cmd=="exit")
			return;
		const auto& it = this->commands.find(cmd);
		auto e = this->commands.end();
		if (it!=e)
		{
			auto command = this->commands[cmd];
			(this->*command)(std::cin);
		}
		else
		{
			std::cout<<"invalid command!\n";
		}
	}
}


void test_domain()
{
std::cout<<"starting domain tests...\n";
Notion n;
Notion n1{"jordan"};
Notion n2{n1};
Notion *nn = new Notion{"jordan"};
Notion m;
m = n2;
assert(n1 == n2);
assert(n.get_name()=="");


assert(n1.get_name()=="jordan");
assert(m.get_name()=="jordan");


delete nn;
std::cout<<"finishing domain tests...\n";

}


void test_validator_notion()
{
std::cout<<"starting validator for notion tests...\n";

Notion n1{"jordan"};
NotionValidator notion_validator;
try
{
notion_validator.validate_notion(n1);
assert(true);
}
catch( const std::string& exc)
{
assert(false);
}

Notion n{""};
try
{
notion_validator.validate_notion(n);
assert(false);
}
catch (const std::string& exc)
{
assert(true);
}

std::cout<<"finishing validator for notion tests...\n";
}

void test_repo_notion()
{
std::cout<<"starting repository for notion tests...\n";
NotionRepository nr;
assert(nr.size()==0);
Notion n{"jordan"};
nr.store(n);
assert(nr.size()==1);
try
{
nr.store(n);
assert(false);
}
catch(const std::string& exc)
{
assert(exc=="existing element!");
}

Notion n1{"jordan"};
nr.update(n1);
Notion key{"jordan"};
const Notion& found = nr.get_element(key);
std::cout<<found.get_name()<<"\n";
assert(found.get_name()=="jordan");

Notion sters = nr.remove(key);
assert(sters.get_name()=="jordan");
assert(nr.size()==0);

try
{
nr.remove(key);
assert(false);
}
catch(const std::string& exc)
{
assert(exc=="inexisting element!");
}

Notion n3{"curry"};
Notion n4{"iverson"};
nr.store(n3);
nr.store(n4);

for(const auto& x: nr.get_all())
{
	std::cout<<x<<"\n";
}
std::cout<<"finishing repository for notion tests...\n";

}

void test_service_notion()
{
std::cout<<"starting service for notion tests...\n";
NotionValidator nv;
NotionRepository nr;
NotionService ns{nv,nr};

std::cout<<"finishing service for notion tests...\n";
}


void test_all()
{
std::cout<<"starting all tests...\n";
test_domain();
test_validator_notion();
test_repo_notion();
test_service_notion();


std::cout<<"finishing all tests...\n";
}


int main()
{
test_all();
NotionValidator nv;
NotionRepository nr;
NotionService ns{nv,nr};
Console ui{ns};
ui.run();
return 0;
}
