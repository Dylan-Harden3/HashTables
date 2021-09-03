#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
template <class Key, class Hash=std::hash<Key>>
class HashTable {
	//size of hash table and amount of buckets to tell if we need to rehash
	size_t size_;
	size_t buckets;
	//2d vector to store the keys, in this implementation we just add the key to the vector at its hash value
	std::vector<std::vector<Key>> table;
	float maxload = 1;
	public:
	//constructors 
	HashTable():size_(0),buckets(11),table(){
		table.resize(buckets);
	}
	explicit HashTable(size_t b):size_(0),buckets(b),table(){
		table.resize(buckets);
	}
	//check if the hash table is empty
	bool is_empty() const {
		if(size_ == 0 ){
			return true;
		}
		return false;
	}
	size_t size() const {
		return size_;
	}
	//clear the hash table
	void make_empty() {
		table.clear();
		table.resize(buckets);
		size_ = 0;
	}
	//insert a key 
	bool insert(const Key& in){
		//find the hash value of the key
		size_t index = bucket(in);
		//check if the key is stored already
		for(size_t i=0;i<table[index].size();i++){
			if(in == table[index][i]){
				return false;
			}
		}
		//add the key
		table[index].push_back(in);
		size_++;
		//check if the load factor exceeds maxload
		if(load_factor() > maxload){
			rehash(0);
		}
		return true;
	}
	//remove a key
	size_t remove(const Key& in){
		//find the hash vaue of the key
		size_t index = bucket(in);
		//search the vector at the keys hash value and if it is found erase it
		for(size_t i=0;i< table[index].size();i++){
			if(in == table[index][i]){
				table[index].erase(table[index].begin()+i);
				size_--;
				return 1;
			}
		}
		return 0;
	}
	//check if a key is in the hash table
	bool contains(const Key& in) const {
		//find the hash vaue of the key
		size_t index = Hash{}(in) % buckets;
		//search the vector at the keys hash value
		for(size_t i=0;i<table[index].size();i++){
			if(in == table[index][i]){
				return true;
			}
		}
		return false;
	}
	size_t bucket_count() const {return buckets;}
	//find the number of keys in a certain bucket
	size_t bucket_size(size_t index) const {
		if(index >= buckets || index < 0){
			throw std::out_of_range("out of range");
		}
		return table[index].size();
	}
	//find which bucket a key will be inserted in
	size_t bucket(const Key& in) const {return ((Hash{}(in))%buckets);}
	float load_factor() const {
		float s = size_;
		float b = buckets;
		return s/b;
	}
	//find or set the max load factor 
	float max_load_factor() const {return maxload;} 
	void max_load_factor(float n) {
		if(n <= 0){
			throw std::invalid_argument("negative max load factor");
		}
		maxload = n;
		if(maxload < load_factor()){
			rehash(0);
		}
	}
	//rehash to a specific table size
	void rehash(size_t n) {
		//make a copy of the old table
		std::vector<std::vector<Key>> temp = table;
		//check that we are not trying to make a table that is the same size as the current table or size 0
		if(n!= buckets && n!=0){
			//store the size and the desired number of buckets
			float s = size_;
			float b = n;
			//if the new load factor is <= the max load factor
			if(s/b <= maxload){
				//resize the table to the new size
				buckets = n;
				size_ = 0;
				table.clear();
				table.resize(buckets);
				//take every value from the old table and add it to the new one
				for(size_t i=0;i<temp.size();i++){
					for(size_t j=0;j<temp[i].size();j++){
						insert(temp[i][j]);
					}
				}
			}else{
				//if the new load factor is to be too large rehash to a size of size/maxload
				buckets = size_/maxload;
				//make sure new table size is prime
				if(!isprime(buckets)){
					buckets = nextprime(buckets);
				}
				//resize the table and copy in all the values
				size_ = 0;
				table.clear();
				table.resize(buckets);
				for(size_t i=0;i<temp.size();i++){
					for(size_t j=0;j<temp[i].size();j++){
						insert(temp[i][j]);
					}
				}
			}
		//if n == 0 then we assume a new size of old size*2
		}else if(n == 0){
				buckets = buckets*2;
				//find the next prime number which is to be the new table size
				if(!isprime(buckets)){
					buckets = nextprime(buckets);
				}
				//resize the table and copy in all the values
				size_ = 0;
				table.clear();
				table.resize(buckets);
				for(size_t i=0;i<temp.size();i++){
					for(size_t j=0;j<temp[i].size();j++){
						insert(temp[i][j]);
					}
				}
		}
	}
	//print the hash table
	void print_table(std::ostream& o=std::cout) const {
		if(size_ == 0){
			o << "<empty>" << std::endl;
			return;
		}
		for(size_t i=0;i<table.size();i++){
			o << i;
			for(size_t j=0;j<table[i].size();j++){
				o << "-> " << table[i][j];
			}
			o << std::endl;
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

#endif  // HASHTABLE_SEPARATE_CHAINING_H