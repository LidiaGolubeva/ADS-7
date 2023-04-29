// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
  struct Item {
    T data;
    Item* next;
    Item* prev;
  };
  Item* head;
  Item* tail;
  TPQueue::Item* create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
  }

 public:
  TPQueue() : head(nullptr), tail(nullptr) { }
  ~TPQueue() {
    while (head) {
      pop();
    }
  }
  void push(const T& new_data) {
    if (head == nullptr) {
      head = create(new_data);
      tail = head;
    } else if (tail->data.prior >= new_data.prior) {
      if (tail->data.ch == new_data.ch) {
        tail->data = new_data;
      } else {
        tail->next = create(new_data);
        tail->next->prev = tail;
        tail = tail->next;
      }
    } else if (head == tail) {
      tail->prev = create(new_data);
      head = tail->prev;
      head->next = tail;
    } else {
      Item* item = tail;
      while (item != head && item->data.prior < new_data.prior) {
        item = item->prev;
      }
      if (item->data.prior > new_data.prior) {
        Item* new_item = new Item;
        new_item->next = item->next;
        new_item->prev = item;
        new_item->data = new_data;
        item->next->prev = new_item;
        item->next = new_item;
      }
      if (item == head && item->data.prior < new_data.prior) {
        head->prev = create(new_data);
        head = head->prev;
        head->next = item;
      }
    }
  }
  T pop() {
    if (!head) {
      throw std::string("Empty!");
    } else {
      Item* item = head->next;
      T data = head->data;
      delete head;
      head = item;
      return data;
    }
  }
  void print() const {
    Item* item = head;
    while (item) {
      std::cout << item->data << " ";
      item = item->next;
    }
    std::cout << std::endl;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
