#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "HashTable.hpp"

class Inventory
{
private:
  // Uniq Id, Product Name, Brand Name, Asin, Category, Upc Ean Code, List
  // Price, Selling Price, Quantity, Model Number, About Product, Product
  // Specification, Technical Details, Shipping Weight, Product Dimensions,
  // Image, Variants, Sku, Product Url, Stock, Product Details, Dimensions,
  // Color, Ingredients, Direction To Use, Is Amazon Seller, Size Quantity
  // Variant, Product Description
  struct Product
  {
    string uniq_id;
    string product_name;
    vector<string> categories;
    string price;
    string description;
  };

  HashTable<string, Product> productsID;
  HashTable<string, vector<Product *>> productsCategory;

public:
  string removeQuotes(const string &s);

  void load(const string &filename);

  // bool return type for assert testing
  bool findProduct(const string &id);

  bool listInventory(const string &category);
};

#endif