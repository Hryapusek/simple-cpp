#include <memory>
#include <string>
#include <vector>

class Book;
class Library;

class Member {
public:
  Member(const std::string &name);

  void borrow(std::shared_ptr<Book> book);

  void returnBook(std::shared_ptr<Library> lib, const std::string &title);

  void displayBooks() const;

private:
  std::string name;
  std::vector<std::shared_ptr<Book>> borrowed;
};
