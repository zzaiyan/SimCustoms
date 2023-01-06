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
  int _size;

public:
  Queue() : head(new _Node), tail(new _Node), _size(0) {
    head->next = tail, tail->pre = head;
  }

  bool empty() const { return _size == 0; }
  int size() const { return _size; }

  T &front() {
    if (_size > 0)
      return head->next->data;
    else {
      qDebug() << "队列为空！";
      return {};
    }
  }

  template <class R> void enqueue(R &&e) {
    _size++;
    auto newNode = new _Node{e, tail->pre, tail};
    newNode->pre->next = newNode->next->pre = newNode;
  }

  T dequeue() {
    if (_size-- > 0) {
      auto ret = head->next->data;
      auto del = head->next;
      del->pre->next = del->next;
      del->next->pre = del->pre;
      delete del;
      return ret;
    } else {
      qDebug() << "队列为空！";
      return {};
    }
  }
};

#endif // QUEUE_HPP
