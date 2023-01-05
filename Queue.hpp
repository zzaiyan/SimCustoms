#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <QDebug>

template <class T> class Queue {
public:
  struct _Node { // List Node
    T data = {};
    _Node *pre = nullptr;
    _Node *next = nullptr;
  };

protected:
  _Node *head, *tail;

public:
  Queue() : head(new _Node), tail(new _Node) {
    head->next = tail, tail->pre = head;
  }

  bool empty() { return head->next == tail; }

  T &front() { return head->next->data; }

  template <class R> void enqueue(R &&e) {
    auto newNode = new _Node{e, tail->pre, tail};
    newNode->pre->next = newNode->next->pre = newNode;
  }

  T dequeue() {
    auto ret = head->next->data;
    auto del = head->next;
    del->pre->next = del->next;
    del->next->pre = del->pre;
    delete del;
    return ret;
  }
};

#endif // QUEUE_HPP
