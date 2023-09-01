#include <unordered_map>

#include "book.hpp"

class BookRegistry {
  std::unordered_map<BookId, Book> books_;
public:
  bool create_book(BookId book_id) {
    auto result = books_.insert({book_id, Book{book_id}});
    return result.second;
  }
};
