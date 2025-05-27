#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Book;

class Library : public std::enable_shared_from_this<Library> {
public:
  static std::shared_ptr<Library> create(const std::string &name);

  void addBook(std::shared_ptr<Book> book);

  std::shared_ptr<Book> lendBook(const std::string &title);

  void returnBook(std::shared_ptr<Book> book);

  const std::string &getName() const;

  void displayCatalog() const;

private:
  Library(const std::string &name);

  std::string name;
  std::vector<std::shared_ptr<Book>> books;
};
