#include "Inventory.hpp"

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, "
            "prints details. If not, prints 'Inventory not found'."
         << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of "
            "all inventory belonging to the specified category. If the category "
            "doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") || (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, Inventory &inventory)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // remove the command from input
        string id = line.substr(5);

        // remove the whitespace
        id = id.substr(id.find_first_not_of(" \t"));

        inventory.findProduct(id);
    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        // remove the command from input
        string category = line.substr(13);

        // remove the whitespace
        category = category.substr(category.find_first_not_of(" \t"));

        inventory.listInventory(category);
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
}

void insertFindTest()
{
    HashTable<string, int> table(5);

    // insert and find
    table.insert("key1", 1);
    assert(*table.find("key1") == 1);

    // collision
    table.insert("key2", 2);
    table.insert("key3", 3);
    assert(*table.find("key2") == 2);
    assert(*table.find("key3") == 3);

    // no key
    assert(table.find("null") == nullptr);
}
void testInventory()
{
    Inventory inventory;

    inventory.load("amazon.csv");

    // existing product
    assert(inventory.findProduct("cc2083338a16c3fe2f7895289d2e98fe") == true);
    // non existing product
    assert(inventory.findProduct("INVALID_ID") == false);
    // existing category
    assert(inventory.listInventory("Stuffed Animals & Plush Toys") == true);
    // non exisiting category
    assert(inventory.listInventory("nocategory") == false);
}

int main(int argc, char const *argv[])
{
    // one at a time
    // insertFindTest();
    // testInventory();

    string line;
    bootStrap();

    Inventory inventory;
    inventory.load("amazon.csv");

    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, inventory);
        }
        else
        {
            cout
                << "Command not supported. Enter :help for list of supported commands"
                << endl;
        }
        cout << "> ";
    }
    return 0;
}
