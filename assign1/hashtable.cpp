#include <iostream>
#include <string>
#include <vector>
#include <fstream>

enum SlotSize
{
	MaxSlots = 3
};

enum BucketSize
{
	MaxBuckets = 30
};

const int TableSize = 20;

class Slot
{	
	public:
		Slot()
		{
			// this->key = ;
			// this->value = NULL;
		}

		std::string key;
		std::string value;
};

class Bucket
{
	public:
		Bucket() 
		{
			this->count = 0;
			this->overflow = -1;
			this->slots.resize(MaxSlots);

		}

		short int count;
		short int overflow;
		std::vector<Slot> slots;
};

class HashTable
{
	public:
		HashTable()
		{
			for(int i = 0; i < MaxBuckets; ++i)
			{
				table.resize(i+1);
				Bucket *b = new Bucket();
				table.push_back(*b);
				delete b;
			}
			this->DataIn();
		}

		std::vector<Bucket> table;

		void DataIn()
		{
			std::string key;
			std::string value;
			std::ifstream file ("datain.dat");
			if(file.is_open())
			{
				int i = 0;
				while(file.good())
				{
					getline(file, key);
					value = key.substr(10, 20);
					key.resize(10);
					// this->table.at(i).slots.at(0).key = this->Hash(key);
					// std::cout << this->Hash(key) << std::endl;
					// this->table.at(i).slots.at(0).value = key.substr(10, 20);
					// std::cout << "Value: " << value << std::endl;
					// std::cout << i << std::endl;
					++i;
				}
			}
			// int hash_index = int(key[2]) + int(key[4]) + int(key[6]);
		}

		void Insert(std::string key, std::string value)
		{
			int count = NULL;
			int index = this->CollissionCheck(key);
			bool overflow = false;
			std::cout << "Index is: " << index << std::endl;
			if(index != 0)
			{
				//collission is true
				if(table.at(index).count >= 3)
				{
					//over flow is true
					int of_index = this->CheckAvailableOverflow(key);
					count = this->table.at(of_index).count++;
					this->table.at(of_index).slots.at(count).key = this->Hash(key);
					this->table.at(of_index).slots.at(count).value = value;
					std::cout << "HEre";
					this->table.at(index).overflow = of_index;							
				}
				else 
				{
					count = this->table.at(index).count++;
					this->table.at(index).slots.at(count).key = key;
					this->table.at(index).slots.at(count).value = value;

				}							

			}
			else
			{
				// no collission
				// fresh key
				index = CheckAvailablePrimary();
				this->table.at(index).slots.at(0).key = this->Hash(key);
				std::cout << this->table.at(index).slots.at(0).key << std::endl;
				std::cout << this->Hash(key);
				this->table.at(index).slots.at(0).value = value;
				this->table.at(index).count++;
			}								
		}

		int CheckAvailablePrimary()
		{
			for(std::vector<int>::size_type i = 0; i != this->table.size(); ++i)
			{
				if(this->table.at(i).count == 0)
				{
					// std::cout << "i is: " << i << std::endl;
					return i;
				}
			}

			return 0;
		}

		int CheckAvailableOverflow(std::string key)
		{
			for(std::vector<int>::size_type i = 10; i != this->table.size(); ++i)
			{
				for(std::vector<int>::size_type j = 0; j != this->table.at(i).slots.size(); ++j)
				{
					if(this->table.at(i).slots.at(0).key == key)
					{
						std::cout << "i is: " << i << std::endl;
						return i;
					}
				}
			}

			return 10;
		}

		int CollissionCheck(std::string key)
		{
			for(std::vector<int>::size_type i = 0; i != this->table.size(); ++i)
			{
				for(std::vector<int>::size_type j = 0; j != this->table.at(i).slots.size(); ++j)
				{
					// std::cout << "test: " << this->table.at(i).slots.at(0).key << std::endl;
					// std::cout << "test2: " << key <<
					if(this->table.at(i).slots.at(0).key == key)
					{
						std::cout << "i is: " << i << std::endl;
		
						return i;
					}
				}
			}

			return 0;
		}
	// private:
		int Hash(std::string key)
		{
			return (int(key[2]) + int(key[4]) + int(key[6])) % TableSize;
		}
};

int main(void)
{
	HashTable ht;
	ht.Insert("Thsadbaradfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	ht.Insert("Thsijsdfoj", "Jones");
	// std::string test = 5;
	// std::cout << test;
	//std::cout << ht.table.front().count;
	// ht.Insert("Bob");
	// std::cout << std::endl << hash_index << std::endl;
	std::vector<Bucket> table;
	return 0;
}

// Hash Table is just an array of buckets