#include <iostream>
#include "LargeInt.h"

void IterateFront(LargeInt<int>& L1, LinkedList<int>::Iterator i)
{
  std::cout << "\n";
  LinkedList<int> l = L1.getList();
  (L1.getNegative() == true) ? std::cout << "-": std::cout << "";
  for (auto i = l.firstnode(); i != l.end(); ++i)
  {
    std::cout << *i << "";
  }
  std::cout << "\n";
}
void IterateFront(LinkedList<int>& l, LinkedList<int>::Iterator i)
{
  std::cout << "\n";
  //(L1.getNegative() == true) ? std::cout << "-" : std::cout << "";
  for (auto i = l.firstnode(); i != l.end(); ++i)
  {
    std::cout << *i << "";
  }
  std::cout << "\n";
}

int main()
{ 
  std::string input1; std::string input2;
  LargeInt<int> L1; LargeInt<int> L2;
  LinkedList<int> List;
  LinkedList<int>::Iterator iterator;
  std::cout << "Enter the first number: "; std::cin >> input1;
  std::cout << "Enter the second number: "; std::cin >> input2;
  L1.setList(input1);
  L2.setList(input2);
  //L1 * L2;
  //L1 + L2;
  L1 / L2;
  //L1 = *L1.add(L1, L2);
  IterateFront(L1, iterator);
}
