#include "hashtable_open_addressing.h"

int main() {
std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
HashTable<std::string> table(11);
table.print_table();
std::cout << "initial size is " << table.size() << std::endl;
std::cout << "initial table size is " << table.table_size() << std::endl;

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

std::cout << "size is " << table.size() << std::endl;
std::cout << "table size is " << table.table_size() << std::endl;

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
std::cout << "table size is " << table.table_size() << std::endl;

{
  std::cout << "print the table" << std::endl;
  std::stringstream ss;
  table.print_table(ss);
  std::cout << ss.str() << std::endl;
}

std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
size_t index = table.position("The Blacksmith and the Artist");
std::cout << " ==> cell " << index << std::endl;

std::cout << "make the table empty" << std::endl;
table.make_empty();

std::cout << "size is " << table.size() << std::endl;
std::cout << "table size is " << table.table_size() << std::endl;

{
  std::cout << "print the table" << std::endl;
  std::stringstream ss;
  table.print_table(ss);
  std::cout << ss.str() << std::endl;
}


{
  // Anon.
  std::cout << "the empty table contains nothing" << std::endl;
  HashTable<int> table;
   std::cout << "this should be true: " << table.is_empty() << std::endl;
  std::cout << "this should be false: " << table.contains(0) << std::endl;
}
{
  // Anon.
  std::cout << "open addressing isn't confused by deleted values" << std::endl;
  HashTable<int> table(10);
  table.insert(3);
  table.insert(4);
  size_t index13 = table.position(13);
  table.print_table();
  table.insert(13);
  table.print_table();
  size_t index14 = table.position(14);
  table.remove(4);
  table.print_table();
  std::cout << table.position(13) << "=" << index13 << std::endl;
  std::cout << table.position(14) << "=" << index14 << std::endl;
  table.insert(14);
  table.print_table();
}
{
	HashTable<int> table(10);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	std::cout << table.size() << std::endl;
	table.insert(6);
	std::cout << table.size() << std::endl;
}
{
	HashTable<int> table(10);
	std::cout << table.remove(0) << std::endl;
	table.insert(1);
	std::cout << table.remove(1) << std::endl;
	table.insert(2);
	table.insert(21);
	table.insert(22);
	table.insert(23);
	std::cout << table.remove(22) << std::endl;
	table.print_table();
}
{
	HashTable<int> table(10);
	std::cout << table.contains(1) << std::endl;
	table.insert(1);
	std::cout << table.contains(1) << std::endl;
	table.insert(2);
	table.insert(22);
	table.insert(23);
	table.insert(25);
	std::cout << table.contains(23) << std::endl;
	std::cout << table.contains(2757) << std::endl;
	std::cout << table.size() << std::endl;
	table.insert(6);
	std::cout << table.size() << std::endl;
}
    return 0;
}