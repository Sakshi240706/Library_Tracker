#include <iostream>
#include <vector>
#include <string>

// Book class: represents a single book
class Book {
private:
    std::string name;
    std::string author;
    bool borrowed;

public:
    // Constructor
    Book(const std::string& n, const std::string& a)
        : name(n), author(a), borrowed(false) {}

    // Getters
    std::string getName() const { return name; }
    std::string getAuthor() const { return author; }
    bool isBorrowed() const { return borrowed; }

    // Setters
    void setBorrowed(bool status) { borrowed = status; }
};

// Library class: manages a collection of books and provides core APIs
class Library {
private:
    std::vector<Book> books;

public:
    // Add a new book
    void addBook(const std::string& name, const std::string& author) {
        books.emplace_back(name, author);
        std::cout << "Book added successfully!\n";
    }

    // Borrow a book by index (returns false if invalid)
    bool borrowBook(size_t index) {
        if (index >= books.size()) {
            std::cout << "Invalid book index.\n";
            return false;
        }
        if (books[index].isBorrowed()) {
            std::cout << "Book is already borrowed.\n";
            return false;
        }
        books[index].setBorrowed(true);
        std::cout << "Book borrowed successfully!\n";
        return true;
    }

    // Return a book by index (returns false if invalid)
    bool returnBook(size_t index) {
        if (index >= books.size()) {
            std::cout << "Invalid book index.\n";
            return false;
        }
        if (!books[index].isBorrowed()) {
            std::cout << "Book is not currently borrowed.\n";
            return false;
        }
        books[index].setBorrowed(false);
        std::cout << "Book returned successfully!\n";
        return true;
    }

    // List all books
    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }
        std::cout << "\nAll Books:\n";
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i << ". "
                      << books[i].getName()
                      << " by " << books[i].getAuthor()
                      << " [" << (books[i].isBorrowed() ? "Borrowed" : "Available") << "]\n";
        }
    }

    // List borrowed books only
    void displayBorrowedBooks() const {
        bool found = false;
        std::cout << "\nBorrowed Books:\n";
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].isBorrowed()) {
                std::cout << i << ". "
                          << books[i].getName()
                          << " by " << books[i].getAuthor()
                          << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books are currently borrowed.\n";
        }
    }

    // Returns the current number of books
    size_t bookCount() const { return books.size(); }
};

// Main executor function: interactive console
int main() {
    Library lib;
    int choice;
    std::cout << "====== Library Tracker ======\n";
    do {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Borrow Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Display All Books\n";
        std::cout << "5. Display Borrowed Books\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline for getline inputs

        if (choice == 1) {
            std::string name, author;
            std::cout << "Enter book name: ";
            std::getline(std::cin, name);
            std::cout << "Enter author: ";
            std::getline(std::cin, author);
            lib.addBook(name, author);
        }
        else if (choice == 2) {
            lib.displayBooks();
            if (lib.bookCount() == 0) continue;
            std::cout << "Enter book index to borrow: ";
            size_t idx;
            std::cin >> idx;
            lib.borrowBook(idx);
        }
        else if (choice == 3) {
            lib.displayBooks();
            if (lib.bookCount() == 0) continue;
            std::cout << "Enter book index to return: ";
            size_t idx;
            std::cin >> idx;
            lib.returnBook(idx);
        }
        else if (choice == 4) {
            lib.displayBooks();
        }
        else if (choice == 5) {
            lib.displayBorrowedBooks();
        }
        else if (choice == 0) {
            std::cout << "Exiting Library Tracker. Goodbye!\n";
        }
        else {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
