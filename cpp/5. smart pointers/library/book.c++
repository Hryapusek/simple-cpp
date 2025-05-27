#include "book.h"
#include "library.h"

std::shared_ptr<Book> Book::create(const std::string &title,
                                   const std::string &author) {
  return std::shared_ptr<Book>(new Book(title, author));
}

void Book::setLibrary(std::weak_ptr<Library> lib) { library = lib; }

void Book::display() const {
  if (auto lib = library.lock()) {
    std::cout << "📖 " << title << " by " << author << " (Available at "
              << lib->getName() << ")\n";
  } else {
    std::cout << "📖 " << title << " by " << author << " (Library closed)\n";
  }
}

const std::string &Book::getTitle() const { return title; }

Book::Book(const std::string &title, const std::string &author)
    : title(title), author(author) {
  std::cout << "📘 Created: " << title << "\n";
}
