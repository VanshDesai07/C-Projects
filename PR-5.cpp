#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Entity {
protected:
    string id;
    string name;

public:
    Entity(string id, string name) : id(id), name(name) {}
    virtual void displayInfo() const = 0; // Pure virtual function
    virtual ~Entity() {}
};

class Book : public Entity {
private:
    string author;
    bool isAvailable;

public:
    Book(string id, string title, string author)
        : Entity(id, title), author(author), isAvailable(true) {}

    void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Book borrowed successfully.\n";
        } else {
            cout << "Book is not available.\n";
        }
    }

    void returnBook() {
        isAvailable = true;
        cout << "Book returned successfully.\n";
    }

    bool getAvailability() const {
        return isAvailable;
    }

    void displayInfo() const override {
        cout << "Book ID: " << id << ", Title: " << name << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

class Patron : public Entity {
private:
    vector<string> borrowedBooks;

public:
    Patron(string id, string name) : Entity(id, name) {}

    void borrowBook(const string& bookId) {
        borrowedBooks.push_back(bookId);
        cout << name << " borrowed book ID: " << bookId << "\n";
    }

    void returnBook(const string& bookId) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookId) {
                borrowedBooks.erase(it);
                cout << name << " returned book ID: " << bookId << "\n";
                return;
            }
        }
        cout << "Book ID: " << bookId << " not found in borrowed list.\n";
    }

    void displayInfo() const override {
        cout << "Patron ID: " << id << ", Name: " << name << "\nBorrowed Books: ";
        if (borrowedBooks.empty()) {
            cout << "None\n";
        } else {
            for (const auto& bookId : borrowedBooks) {
                cout << bookId << " ";
            }
            cout << "\n";
        }
    }
};

class Transaction {
private:
    string transactionId;
    string bookId;
    string patronId;
    string type;
public:
    Transaction(string id, string bookId, string patronId, string type)
        : transactionId(id), bookId(bookId), patronId(patronId), type(type) {}

    void displayInfo() const {
        cout << "Transaction ID: " << transactionId << ", Type: " << type
             << ", Book ID: " << bookId << ", Patron ID: " << patronId << "\n";
    }
};

class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    void performTransaction(const string& transactionId, const string& bookId, const string& patronId, const string& type) {
        Book* selectedBook = nullptr;
        Patron* selectedPatron = nullptr;

        for (auto& book : books) {
            if (bookId == book.id) {
                selectedBook = &book;
                break;
            }
        }

        for (auto& patron : patrons) {
            if (patronId == patron.id) {
                selectedPatron = &patron;
                break;
            }
        }

        if (selectedBook == nullptr) {
            cout << "Book ID not found.\n";
            return;
        }

        if (selectedPatron == nullptr) {
            cout << "Patron ID not found.\n";
            return;
        }

        if (type == "Borrow") {
            if (selectedBook->getAvailability()) {
                selectedBook->borrowBook();
                selectedPatron->borrowBook(bookId);
                transactions.emplace_back(transactionId, bookId, patronId, type);
            } else {
                cout << "Book is not available for borrowing.\n";
            }
        } else if (type == "Return") {
            selectedBook->returnBook();
            selectedPatron->returnBook(bookId);
            transactions.emplace_back(transactionId, bookId, patronId, type);
        } else {
            cout << "Invalid transaction type.\n";
        }
    }

    void displayAllBooks() const {
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    void displayAllPatrons() const {
        for (const auto& patron : patrons) {
            patron.displayInfo();
        }
    }

    void displayAllTransactions() const {
        for (const auto& transaction : transactions) {
            transaction.displayInfo();
        }
    }
};

int main() {
    LibraryManagementSystem lms;

    lms.addBook(Book("B001", "C++ Programming", "Bjarne Stroustrup"));
    lms.addBook(Book("B002", "Clean Code", "Robert C. Martin"));

    lms.addPatron(Patron("P001", "Alice"));
    lms.addPatron(Patron("P002", "Bob"));

    lms.performTransaction("T001", "B001", "P001", "Borrow");
    lms.performTransaction("T002", "B001", "P001", "Return");
    lms.performTransaction("T003", "B002", "P002", "Borrow");

    cout << "\nBooks:\n";
    lms.displayAllBooks();

    cout << "\nPatrons:\n";
    lms.displayAllPatrons();

    cout << "\nTransactions:\n";
    lms.displayAllTransactions();

    return 0;
}
