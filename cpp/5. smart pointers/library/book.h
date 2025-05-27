#include <iostream>
#include <memory>
#include <vector>

class Library;

class Book {
public:
  static std::shared_ptr<Book> create(const std::string &title,
                                      const std::string &author);

  void setLibrary(std::weak_ptr<Library> lib);

  void display() const;

  const std::string &getTitle() const;

private:
  Book(const std::string &title, const std::string &author);

  std::string title;
  std::string author;
  std::weak_ptr<Library> library;
};
