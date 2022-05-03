//Creator: Me
//Creation Date: 03/XX/2022
//Last Edit: 5/2/2022 9:06PM
//Description: Header file for A Doubly Linked List 
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>

template <class T>
struct node
{
  T        info;
  node<T>* next;
  node<T>* prev;
};

template <class T>
class LinkedList
{
private:
  node<T>* first;
  node<T>* last;
  T        length;
public:
  class Iterator
  {
  private:
    node<T>* current;
  public:
    Iterator()
    {
      current = NULL;
    }
    Iterator(node<T>* ptr)
    {
      current = ptr;
    }
    T& operator*()
    {
      return current->info;
    }
    Iterator& operator++()
    {
      current = current->next;
      return *this;
    }
    Iterator& operator--()
    {
      current = current->prev;
      return *this;
    }
    bool operator==(const Iterator& right) const
    {
      return(current == right.current);
    }
    bool operator!=(const Iterator& right) const
    {
      return (current != right.current);
    }
  };
  LinkedList()
  {
    first = nullptr;
    last = nullptr;
    length = 0;
  }
  ~LinkedList()
  {
    destroy();
  }
  void destroy()
  {
    node<T>* h;

    while (first != NULL)
    {
      h = first;
      first = first->next;
      delete h;
    }
    length = 0;
  }
  LinkedList(const LinkedList<T>& other)
  {
    copy(other);
  }
  const LinkedList<T>& operator = (const LinkedList<T>& other)
  {
    if (this != &other)
    {
      destroy();
      copy(other);
    }
    return *this;
  }
  void copy(const LinkedList<T>& other)
  {
    length = other.length;

    if (other.first == NULL)
    {
      first = NULL;
    }

    else
    {
      first = new node<T>;
      first->info = other.first->info;

      node<T>* p = other.first->next;
      node<T>* q = first;

      while (p != NULL)
      {
        q->next = new node<T>;
        q = q->next;
        q->info = p->info;
        p = p->next;
      }
      q->next = NULL;
    }
  }
  void printList()
  {
    if (first == NULL) { std::cout << "\nThe list is empty.\n"; }
    else
    {
      node<T>* first_next = first;
      while (first_next != NULL)
      {
        std::cout << first_next->info << " ";
        first_next = first_next->next;
      }
      std::cout << "\n";
    }
  }
  void deleteItem(T item)
  {
    if (first == NULL) { std::cout << " The list is empty."; }
    else
    {
      node<T>* p = first;
      if (p == nullptr)
      {
        std::cout << "The list is empty. " << std::endl;
      }
      else if (p->info == item && p->next == nullptr)
      {
        delete p;
        first = nullptr;
        length--;
      }
      else if (p->info == item && p->next != nullptr) // deletes first if first is not the only node
      {
        first = p->next;
        p->next->prev = nullptr;
        p->next = nullptr;
        delete p; length--;
        std::cout << "\nThe number has been deleted\n" << std::endl;
      }
      else
      {
        while (p->next != nullptr && p->info != item)
        {
          p = p->next;
        }
        if (p->info == item)
        {
          p->prev->next = p->next;
          p->next->prev = p->prev;
          delete p; length--;
          std::cout << "\nThe number has been deleted\n" << std::endl;
        }
      }
    }
  }
  bool SearchItem(T const& item)
  {
    node<T>* p;
    if (first == nullptr)
    {
      return false;
    }
    if (last->info == item || first->info == item)
    {
      return true;
    }
    else
    {
      p = first;
      while (p->next != nullptr && p->info != item)
      {
        p = p->next;
      }
      if (p->info == item)
      {
        return true;
      }
    }
    return false;
  }
  void AddFront(T item)
  {
    node<T>* Node;
    Node = new node<T>;
    Node->info = item;
    Node->prev = NULL;
    Node->next = first;
    if (first == NULL)
    {
      last = Node;
      first = Node;
    }
    else
    {
      first->prev = Node;
      first = Node;
    }
    length++;
  }
  void AddBack(T item)
  {
    node<T>* Node;
    Node = new node<T>;
    Node->info = item;
    Node->next = NULL;
    Node->prev = last;
    if (first == NULL)
    {
      last = Node;
      first = Node;
    }
    else
    {
      last->next = Node;
      last = Node;
    }
    length++;
  }
  bool isEmpty()
  {
    return first == NULL;
  }
  int getLength()
  {
    return length;
  }
  Iterator lastnode()
  {
    first->prev = nullptr;
    node<T>* temp = first;
    while (temp->next != nullptr)
    {
      temp->next->prev = temp;
      temp = temp->next;
    }
    return Iterator(temp);
  }
  Iterator firstnode()
  {
    return Iterator(first);
  }
  Iterator end()
  {
    return Iterator(nullptr);
  }

};

#endif
