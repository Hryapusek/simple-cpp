#include "member.h"
#include "book.h"
#include "library.h"

Member::Member(const std::string &name) : name(name) {}

void Member::borrow(std::shared_ptr<Book> book) {
  borrowed.push_back(book);
  std::cout << name << " borrowed " << book->getTitle() << "\n";
}

void Member::returnBook(std::shared_ptr<Library> lib,
                        const std::string &title) {
  auto it = std::find_if(borrowed.begin(), borrowed.end(),
                         [&](const auto &b) { return b->getTitle() == title; });

  if (it != borrowed.end()) {
    lib->returnBook(*it);
    borrowed.erase(it);
    std::cout << name << " returned " << title << "\n";
  }
}

void Member::displayBooks() const {
  std::cout << "\n👤 " << name << "'s books (" << borrowed.size() << "):\n";
  for (const auto &book : borrowed) {
    book->display();
  }
}
