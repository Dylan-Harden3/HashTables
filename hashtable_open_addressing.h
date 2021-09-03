#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
template <class Key, class Hash=std::hash<Key>>
class HashTable {
	public:
	//use enum use in order to define the buckets as either empty, used, or deleted
	enum use {empty,used,deleted};
	private:
	//size of hash table and amount of buckets to tell if we need to rehash
	size_t size_;
	size_t buckets;

	float maxload = 0.5;
	public:
		//vector which stores the Key along with the use we defined abovd
		std::vector<std::pair<Key,use>> table;
	//find the current load factor of the hash table
	float load_factor() const {
		float s = size_;
		float b = buckets;
		return s/b;
	}
	//constructors
	HashTable():size_(0),buckets(11),table(){
		table.resize(11);
	}
	explicit HashTable(size_t b):size_(0),buckets(b), table(){
		table.resize(buckets);
	}
	//check if the hash table is empty
	bool is_empty() const {
		if(size_ == 0){
			return true;
		}
		return false;
	}
	//find the amount of keys being stored and the number of buckets
	size_t size() const {return size_;}
	size_t table_size() const {return buckets;}
	//function to clear the hash table
	void make_empty() {
		table.clear();
		table.resize(buckets);
		size_ = 0;
	}
	//insert a key, force a rehash if doing so causes the load factor to exceed the maxload
	bool insert(const Key& in) {
		//if the key is already in the hash table then do nothing
		if(contains(in)){
			return false;
		}
		//find the hash value for the key
		size_t index = position(in);
		//update the size
		size_++;
		//add the key at the index we found
		table[index] = std::make_pair(in,used);
		//if the load factor exceeds the maxload then rehash
		if(load_factor() > maxload){
			rehash();
		}
		return true;
	}
	//remove a key from the hash table
	size_t remove(const Key& in){
		//if the key is not in the hash table do nothing 
		if(!contains(in)){
			return 0;
		}
		//find the hash value of the key
		size_t index = position(in);
		table[index].second = deleted;
		size_--;
		return 1;
	}
	//contains function to check if a key is stored in the table already
	bool contains(const Key& in) const {
		if(is_empty() == true){
			return false;
		}
		//find the hash value of the key
		size_t index = position(in);
		//check that the key is at its hash value and check that it is currently in use
		if(table[index].first == in && table[index].second == used){
			return true;
		}
		return false;
	}
	//find the position of a key
	size_t position(const Key& in) const {
		//use the hash function entered to find the hash value
		size_t index = Hash{}(in) % buckets;
		//keep going until we find an empty bucket
		while(table[index].second != empty){
			if(table[index].first == in){
				return index;
			}
			index++;
			index %= buckets;
		}
		return index;
	}
	//function to rehash if needed 
	void rehash() {
		//make a copy of the old table
		std::vector<std::pair<Key,use>> temp = table;
		size_t oldb = buckets;
		buckets = buckets*2;
		//double the amount of buckets and if the new number is not prime round it to the next prime number
		if(!isprime(buckets)){
			buckets = nextprime(buckets);
		}
		size_ = 0;
		//clear the table and make it the new size
		table.erase(table.begin(),table.end());
		table.resize(buckets);
		//copy all the keys from the old table into the new one
		for(size_t i=0;i<oldb;i++){
			if(temp[i].second == used){
				insert(temp[i].first);
			}
	
		}
	}
	//function to print the hash table
	void print_table(std::ostream& o=std::cout) const {
		if(size_ == 0){
			o << "<empty>" << std::endl;
			return;
		}
		for(size_t i=0;i<buckets;i++){
			if(table[i].second == used){
				o << i << "->" << table[i].first << std::endl;
			}
		}
	}
	//utility functions used when rehashing to find the next prime number which will be the size
	bool isprime(size_t n){
		if(n<=1) return false;
		if(n<=3) return true;
		if(n%2 == 0 || n%3 == 0) return false;
		for(int i=5; i*i<=n; i=i+6){
			if (n%i == 0 || n%(i+2) == 0){
				return false;
			}
		}
    return true;
	}

	size_t nextprime(size_t n){
		if(n<=1) return 2;
		size_t prime = n;
		bool found = false;
		while(!found){
			prime++;
			if(isprime(prime)){
				found = true;
			}
		}
		return prime;
	}
};

#endif  // HASHTABLE_OPEN_ADDRESSING_H