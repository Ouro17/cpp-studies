#include "LibraryCard.hpp"
#include <iostream>
#include <ostream>

LibraryCard::LibraryCard(std::string cardholderName) {
  this->cardholderName = cardholderName;
  this->booksCheckedOut = 0;
}

void LibraryCard::checkoutBook() { this->booksCheckedOut++; }

void LibraryCard::returnBook() {
  if (this->booksCheckedOut > 0) {
    this->booksCheckedOut--;
  }
}

std::string LibraryCard::getCardholderName() const {
  return this->cardholderName;
}

int LibraryCard::getBooksCheckedOut() const { return this->booksCheckedOut; }

void LibraryCard::print() const {
  std::cout << getCardholderName() << " has " << getBooksCheckedOut()
            << " book(s) checked out" << std::endl;
}