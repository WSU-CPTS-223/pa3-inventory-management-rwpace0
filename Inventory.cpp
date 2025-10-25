#include "Inventory.hpp"

string Inventory::removeQuotes(const string &s)
{
  if (s.size() >= 2 && s.front() == '"' &&
      s.back() == '"')                // if size < 2 the string is malformed
    return s.substr(1, s.size() - 2); // remove the first and last index
  return s;
}

// this function has to consider commas inside fields with quotes
void Inventory::load(const string &filename)
{
  ifstream file(filename);
  string line;

  getline(file, line); // skip header

  // important columns to display to the user
  const int UNIQ_ID_COL = 0;
  const int PRODUCT_NAME_COL = 1;
  const int CATEGORY_COL = 4;
  const int SELLING_PRICE_COL = 7;
  const int DESCRIPTION_COL = 10;

  while (getline(file, line))
  {
    vector<string> cols;
    string field;
    bool inQuotes = false;

    // parse csv and removing commas and quotes in fields with them
    for (int i = 0; i < line.length(); i++)
    {
      char c = line[i];
      if (c == '"')
      {
        inQuotes = !inQuotes;
      }
      else if (c == ',' && !inQuotes)
      {
        cols.push_back(removeQuotes(field));
        field.clear();
      }
      else
      {
        field += c;
      }
    }
    // add the last field
    cols.push_back(removeQuotes(field));

    // only process if we have enough columns
    if (cols.size() > DESCRIPTION_COL)
    {
      Product p;
      p.uniq_id = cols[UNIQ_ID_COL];
      p.product_name = cols[PRODUCT_NAME_COL];
      string categoryStr = cols[CATEGORY_COL];
      p.price = cols[SELLING_PRICE_COL];
      p.description = cols[DESCRIPTION_COL];

      // split categories by |
      stringstream catSS(categoryStr);
      string cat;
      while (getline(catSS, cat, '|'))
      {
        cat = removeQuotes(cat);
        cat = cat.substr(cat.find_first_not_of(" \t"),
                         cat.find_last_not_of(" \t") -
                             cat.find_first_not_of(" \t") +
                             1); // take out whitespace
        if (!cat.empty() && cat != "\"\"")
          p.categories.push_back(cat);
      }

      if (p.categories.empty())
      {
        p.categories.push_back("N/A");
      }

      // insert products by id into hash table
      productsID.insert(p.uniq_id, p);

      // hash categories
      for (const string &c : p.categories)
      {
        // find product id and store pointer in category vector
        auto *list = productsCategory.find(c);
        if (list)
        {
          list->push_back(productsID.find(p.uniq_id));
        }
        else
        {
          productsCategory.insert(c, {productsID.find(p.uniq_id)});
        }
      }
    }
  }
}

bool Inventory::findProduct(const string &id)
{
  Product *p = productsID.find(id);
  if (!p)
  {
    cout << "Inventory not found" << endl;
    return false;
  }

  cout << "ID: " << p->uniq_id << "\n"
       << "Name: " << p->product_name << "\n"
       << "Price: " << p->price << "\n"
       << "Categories: ";
  for (auto &c : p->categories)
    cout << c << "|";

  cout << "\nDescription: " << p->description << endl;
  return true;
}

bool Inventory::listInventory(const string &category)
{
  auto *list = productsCategory.find(category);

  if (!list)
  {
    cout << "Invalid Category" << endl;
    return false;
  }
  for (Product *p : *list)
  {
    cout << p->uniq_id << " - " << p->product_name << "\n";
  }
  return true;
}