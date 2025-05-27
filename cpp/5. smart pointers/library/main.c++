#include "book.h"
#include "library.h"
#include "member.h"

int main() {
  // Create library through factory
  auto centralLib = Library::create("Central Library");

  // Add books through factory
  auto book1 = Book::create("1984", "George Orwell");
  auto book2 = Book::create("Dune", "Frank Herbert");
  centralLib->addBook(book1);
  centralLib->addBook(book2);

  // Create members
  Member alice("Alice");
  Member bob("Bob");

  // Simulate borrowing
  auto borrowedBook = centralLib->lendBook("1984");
  if (borrowedBook)
    alice.borrow(borrowedBook);

  borrowedBook = centralLib->lendBook("Dune");
  if (borrowedBook)
    bob.borrow(borrowedBook);

  // Display status
  centralLib->displayCatalog();
  alice.displayBooks();
  bob.displayBooks();

  // Return books
  alice.returnBook(centralLib, "1984");
  bob.returnBook(centralLib, "Dune");

  // Final status
  centralLib->displayCatalog();

  return 0;
}