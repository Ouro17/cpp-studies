#ifndef LIBRARYCARD_H
#define LIBRARYCARD_H

#include <string>


class LibraryCard{
    public:
    LibraryCard(std::string cardholderName);
    void checkoutBook();
    void returnBook();
    std::string getCardholderName() const;
    int getBooksCheckedOut() const;
    void print() const;

    private:
    std::string cardholderName;
    int booksCheckedOut;
};

#endif