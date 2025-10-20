[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# Testing
In main, I added two test functions: ```insertFindTest()``` and ```testInventory()```. 

The first function is to test the ```find()``` and ```insert()``` functions from the HashTable class. They use the cassert library to ensure the correct key and values are inserted.

The second function tests finding categories and products that exist and don't exist after parsing the CSV.

# Cleanup
I had to change a few of the Product Name columns to not include extra quotations. The malformed quotes interrupted the parsing and would cause the program to break.
