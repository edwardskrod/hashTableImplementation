hashTableImplementation
=======================


Author: Edward J Skrod
Date:  November 2013

Overview:

Hash Function
	The first part of the assignment requires that we write a hash function to use with unordered_set.  I named a struct PlayHasher and overloaded the parenthesis operator.   First I create a key by combining the strings Offense and Defense.   So MIA and ATL would look like "MIAATL".   Hashing this value alone (with a character to ASCII value hash) will give me 1024 unique integer values because there are 32 NFL teams.  To ensure that I had even more unique values, I added the down and yards to go.  Finally, I hashed the entire description string and added it to the value of hash.  The result was a very large unsigned integer.

Hash Table

For the Hash Table, I chose to use a vector of pointers to Lists of Plays.   The key is with the number of buckets.   Knowing that the list function will only need to calculate relevance for similar plays, I designed the hash and table to accommodate unique combinations of the Offense and Down.   This gave me 128 unique Lists of plays.   I hard code the Table Size in the constructor.  My hash function has been designed to assign a bucket in the hash table to each Offensive Team. Buckets are assigned in multiples of 4.  So  ARI is equal to 0 and ATL is equal to 4.   Then, I add the down number to the index.  So ARI in down 1 would be 1, ATL in down 2 would be assigned 6. The constructor takes the current table size, n, and dynamically instantiates n Lists, using the vector pushback function to store their memory addresses.  To insert into the table, one need only go to the bucket and then call pushback, theLists[0]->pushback(tempPlay);
