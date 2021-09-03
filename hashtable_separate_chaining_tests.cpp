#include "hashtable_separate_chaining.h"
#include <iostream>
#include <sstream>
int main() {
std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
HashTable<std::string> table(11);

std::cout << "initial size is " << table.size() << std::endl;
std::cout << "initial bucket count is " << table.bucket_count() << std::endl;
std::cout << "initial load factor is " << table.load_factor() << std::endl;
std::cout << "initial max load factor is " << table.max_load_factor() << std::endl;

std::cout << "insert several strings" << std::endl;
table.insert("And them who hold High Places");
table.insert("Must be the ones to start");
table.insert("To mold a new Reality");
table.insert("Closer to the Heart");
table.insert("The Blacksmith and the Artist");
table.insert("Reflect it in their Art");
table.insert("Forge their Creativity");
table.insert("Closer to the Heart");
table.insert("Philosophers and Plowmen");
table.insert("Each must know their Part");
table.insert("To sow a new Mentality");
table.insert("Closer to the Heart");
table.insert("You can be the Captain");
table.insert("I will draw the Chart");
table.insert("Sailing into Destiny");
table.insert("Closer to the Heart");
table.print_table();
HashTable<std::string> table245445(table);
table245445.print_table();
std::cout << "size is " << table.size() << std::endl;
std::cout << "bucket count is " << table.bucket_count() << std::endl;
std::cout << "load factor is " << table.load_factor() << std::endl;
std::cout << "max load factor is " << table.max_load_factor() << std::endl;

{
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table.print_table(ss);
  	std::cout << ss.str() << std::endl;
}

std::cout << "remove \"Philosophers and Plowmen\"" << std::endl;
table.remove("Philosophers and Plowmen");
std::cout << "remove \"Each must know their Part\"" << std::endl;
table.remove("Each must know their Part");

std::cout << "size is " << table.size() << std::endl;
std::cout << "bucket count is " << table.bucket_count() << std::endl;
std::cout << "load factor is " << table.load_factor() << std::endl;
std::cout << "max load factor is " << table.max_load_factor() << std::endl;

{
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table.print_table(ss);
  	std::cout << ss.str() << std::endl;
}

std::cout << "set max load factor to 2" << std::endl;
table.max_load_factor(2);
std::cout << "rehash the table to size 7" << std::endl;
table.rehash(7);

std::cout << "size is " << table.size() << std::endl;
std::cout << "bucket count is " << table.bucket_count() << std::endl;
std::cout << "load factor is " << table.load_factor() << std::endl;
std::cout << "max load factor is " << table.max_load_factor() << std::endl;

{
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table.print_table(ss);
  	std::cout << ss.str() << std::endl;
}

std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
size_t index = table.bucket("The Blacksmith and the Artist");
std::cout << " ==> bucket " << index << std::endl;
std::cout << "     which has " << table.bucket_size(index) << " elements" << std::endl;

std::cout << "make the table empty" << std::endl;
table.make_empty();

std::cout << "size is " << table.size() << std::endl;
std::cout << "bucket count is " << table.bucket_count() << std::endl;
std::cout << "load factor is " << table.load_factor() << std::endl;
std::cout << "max load factor is " << table.max_load_factor() << std::endl;

{
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table.print_table(ss);
  	std::cout << ss.str() << std::endl;
}

{
HashTable<int> table;
  for (int n = 0; n < 10; n++) {
      table.insert(n);
  }
  table.rehash(30);
  std::cout << "This should be 30: " << table.bucket_count() << std::endl;
  HashTable<int> table2(table);
  table.print_table();
  table2.print_table();
  HashTable<int> table3;
  table3 = table2;
  table3.print_table();
}
  
{
  std::cout << "rehash an empty table" << std::endl;
  HashTable<int> table;
  table.rehash(97);
  std::cout << "This should be 0: " << table.size() << std::endl;
  std::cout << "This should be 97: " << table.bucket_count() << std::endl;
}
{
  std::cout << "don't rehash if you don't have to" << std::endl;
  HashTable<int> table(100);
  std::cout << "This should be 100: " << table.bucket_count() << std::endl;
  for (int n = 1; n<10; n++) {
    table.insert(n);
  }
   std::cout << "This should be 100: " << table.bucket_count() << std::endl;
  table.max_load_factor(0.5);
   std::cout << "This should be 100: " << table.bucket_count() << std::endl;
}
    {
  std::cout << "rehash to 0" << std::endl;
  HashTable<int> table;
  table.insert(1);
  table.rehash(0);
  std::cout << "This should be >=1: " << table.bucket_count() << std::endl;

  HashTable<int> overload(3);
  overload.max_load_factor(1);
  overload.insert(0);
  overload.insert(1);
  overload.insert(2);
  overload.rehash(2);
}
    return 0;
}
