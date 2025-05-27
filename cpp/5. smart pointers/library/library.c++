#include "library.h"
#include "book.h"

std::shared_ptr<Library> Library::create(const std::string &name) {
  return std::shared_ptr<Library>(new Library(name));
}

void Library::addBook(std::shared_ptr<Book> book) {
  book->setLibrary(weak_from_this());
  books.push_back(book);
}

std::shared_ptr<Book> Library::lendBook(const std::string &title) {
  auto it = std::find_if(books.begin(), books.end(),
                         [&](const auto &b) { return b->getTitle() == title; });

  if (it != books.end()) {
    auto book = *it;
    books.erase(it);
    return book;
  }
  return nullptr;
}

void Library::returnBook(std::shared_ptr<Book> book) {
  book->setLibrary(weak_from_this());
  books.push_back(book);
}

const std::string &Library::getName() const { return name; }

void Library::displayCatalog() const {
  std::cout << "\n🏛️ " << name << "'s Catalog (" << books.size()
            << " books):\n";
  for (const auto &book : books) {
    book->display();
  }
}

Library::Library(const std::string &name) : name(name) {}
