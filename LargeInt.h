//Creator: Me
//Created: 4/18/2022
//Last Updated: 5/6/2022 1:10 AM
//Worked on: Overloaded Modulus operator
//Description: Large Int Uses a doubly linked list to store numbers that are too large for
//primitive data types for primitive data types and uses them to perform arithmetic operations.
#ifndef LargeInt_H
#define LargeInt_H
#include "Linked_List.h"

template <class T>
class LargeInt
{
private:
  // Each node in the list represents a digit.
  LinkedList<T> List;
  // if the integer is negative
  bool negative;

public:
  LargeInt()
  {
    List;
    negative = false;
  }
  LargeInt(const LargeInt<T>& other)
  {
    List = other.List;
    negative = other.negative;
  }
  LargeInt(LinkedList<T> list, bool TF)
  {
    List = list; negative = TF;
  }
  ~LargeInt()
  {
    negative = 0;
    List.~LinkedList();
  }
  LinkedList<T> getList() const
  {
    return List;
  }
  void setList(const LinkedList<T> l)
  {
    List = l;
  }
  void setList(std::string s)
  {
    LinkedList<T>* p = new LinkedList<T>();
    int digit = 0;
    if ((s[0]) == '-')
    {
      setNegative(true);
    }
    if ((s[0] == '+'))
    {
      setNegative(false);
    }
    if (isdigit(s[0]))
    {
      setNegative(false);
      //convert char to an integer
      digit = (int)s[0] - 48;
      p->AddBack(digit);
    }
    for (int i = 1; i < s.length(); i++)
    {
      if (isdigit(s[i]))
      {
        //convert char to an integer
        digit = (int)s[i] - 48;
        p->AddBack(digit);
      }
    }
    List = *p;
  }
  void setNegative(bool TF)
  {
    negative = TF;
  }
  bool getNegative()
  {
    return negative;
  }
  bool operator == (const LargeInt& other)
  {
    return (checker(*this, other) == 0);
  }
  bool operator < (const LargeInt& other)
  {
    // 15 < 12 
    // -1 implies that the left side of the == is less than the right side.
    return (checker(*this, other) == -1);
  }
  bool operator <= (const LargeInt& other)
  {
    // -1 implies that the left side of the == is less than the right side.
    // 0 implies that they are equal.
    return (checker(*this, other) == -1 || checker(*this, other) == 0);
  }
  bool operator > (const LargeInt& other)
  {
    return (checker(*this, other) == 1);
  }
  bool operator >= (const LargeInt& other)
  {
    return (checker(*this, other) == 1 || checker(*this, other) == 0);
  }
  const LargeInt<T>& operator << (const LargeInt<T>&);
  const LargeInt<T>& operator >> (const LargeInt<T>&);
  //unecessary zeroes in front of the list
  LargeInt<T>* cleanList()
  {
    LinkedList<int>::Iterator i;
    LinkedList<T> List1 = this->getList();
    i = List1.firstnode();
    while (*i == 0 && List1.getLength() != 1)
    {
      this->List.deleteFront();
      ++i;
    }
    return this;
  }
  //adds one to a largeint
  LargeInt<T>* addOne()
  {
    LargeInt<T>* ret = new LargeInt();
    LinkedList<int>::Iterator i;
    //LinkedList<T>List1 = this->getList();
    i = this->List.lastnode();
    bool add = false;
    while (add == false && i != nullptr)
    {
      if (*i != 9)
      {
        *i = *i + 1;
        add = true;
      }
      ++i;
    }
    if (add == false)
    {
      this->List.AddFront(1);
      for (auto i = this->List.firstnode(); i != nullptr; ++i)
      {
        if (*i == 9) { *i = 0; }
      }
    }
    return this;
  }
  //checks the value of the large int list not considering the signs.
  int Listchecker(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    //compares only the digit in L1 and L2 without considering the sign.
    //L1 compared to L2 Values.
    // 1 = greater
    //-1 = less than
    // 0 = equal
    LinkedList<int> List1 = L1.getList();
    LinkedList<int> List2 = L2.getList();
    LinkedList<int>::Iterator i1;
    LinkedList<int>::Iterator i2;
    if (List1.getLength() > List2.getLength()) { return 1; }
    if (List1.getLength() < List2.getLength()) { return -1; }
    if (List1.getLength() == List2.getLength())
    {
      i1 = List1.firstnode();
      i2 = List2.firstnode();
      while (i1 != nullptr && i2 != nullptr)
      {
        // if the first list is greater than the second list.
        if (*i1 > *i2) { return 1; }
        // if the second list is greater than the first list.
        if (*i1 < *i2) { return -1; }
        // to traverse through the list.
        ++i1; ++i2;
      }
      //if they are neither greater nor less, then they must be even.
      return 0;
    }
  }
  //checks the value of of the large ints considering the sign.
  int checker(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    //L1 compared to L2
    // 1 = greater
    //-1 = less than
    // 0 = equal
    LinkedList<int> List1 = L1.getList();
    LinkedList<int> List2 = L2.getList();
    LinkedList<int>::Iterator i1;
    LinkedList<int>::Iterator i2;
    // checks the signs
    if (L1.negative == true && L2.negative == false)
    {
      return -1;
    }
    if (L1.negative == false && L2.negative == true)
    {
      return 1;
    }
    // takes care of if the length are different.
    if (List1.getLength() > List2.getLength()) { return 1; }
    if (List1.getLength() < List2.getLength()) { return -1; }
    if (List1.getLength() == List2.getLength())
    {
      i1 = List1.firstnode();
      i2 = List2.firstnode();
      while (i1 != nullptr && i2 != nullptr)
      {
        // if the first list is greater than the second list.
        if (*i1 > *i2) { return 1; }
        // if the second list is greater than the first list.
        if (*i1 < *i2) { return -1; }
        // to traverse through the list.
        ++i1; ++i2;
      }
      //if they are neither greater nor less, then they must be even.
      return 0;
    }
  }
  //borrows numbers for subtraction
  LinkedList<T> borrow(LinkedList<T>& List1, LinkedList<T>& List2)
  {
    //List 1 must be longer than List2.
    LinkedList<int>::Iterator i1 = List1.lastnode();
    LinkedList<int>::Iterator i2 = List2.lastnode();
    int num1 = 0; int num2 = 0; int counter = 0;
    while (i1 != NULL && i2 != NULL)
    {
      (i1 != NULL) ? num1 = *i1 : num1 = 0;
      (i2 != NULL) ? num2 = *i2 : num2 = 0;
      // go to the left while the number is 0. 
      if (*i1 < *i2)
      {
        --i1; counter++;
        while (*i1 <= 0)
        {
          if (i1 != NULL) { --i1; } counter++;
        }
        while (counter > 0)
        {
          *i1 = *i1 - 1;
          ++i1;
          *i1 = *i1 + 10;
          counter--;
        }
      }
      if (i1 != NULL) { --i1; }
      if (i2 != NULL) { --i2; }
    }
    return List1;
  }
  //adds two large ints
  LargeInt* add(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    LargeInt<T>* ret = new LargeInt();
    LinkedList<int> List1 = L1.getList();
    LinkedList<int> List2 = L2.getList();
    LinkedList<int> List3;
    LinkedList<int>::Iterator i1;
    i1 = List1.lastnode();
    LinkedList<int>::Iterator i2;
    i2 = List2.lastnode();
    int temp = 0; int carry = 0;

    while (i1 != nullptr && i2 != nullptr)
    {
      if ((*i1 + *i2 + carry) < 10)
      {
        *i1 = *i1 + *i2 + carry;
        carry = 0;
        List3.AddFront(*i1);
        --i1; --i2;
      }
      else
      {
        temp = (*i1 + *i2 + carry) / 10;
        *i1 = (*i1 + *i2 + carry) % 10;
        carry = temp;
        List3.AddFront(*i1);
        --i1; --i2;
      }
    }
    while (i1 != nullptr || i2 != nullptr)
    {
      if (i1 != nullptr)
      {
        if (*i1 + 0 + carry < 10)
        {
          *i1 = *i1 + 0 + carry;
          List3.AddFront(*i1);
          --i1;
          carry = 0;
        }
        else
        {
          temp = (*i1 + 0 + carry) / 10;
          *i1 = (*i1 + 0 + carry) % 10;
          carry = temp;
          List3.AddFront(*i1);
          --i1;
        }
      }
      else
      {
        if (*i2 + 0 + carry < 10)
        {
          *i2 = *i2 + 0 + carry;
          List3.AddFront(*i2);
          --i2;
          carry = 0;
        }
        else
        {
          temp = (*i2 + 0 + carry) / 10;
          *i2 = (*i2 + 0 + carry) % 10;
          carry = temp;
          List3.AddFront(*i2);
          --i2;
        }
      }
    }
    if (carry > 0)
    {
      List3.AddFront(carry);
    }
    ret->setList(List3);
    return ret;
  }
  //subtracts two large ints
  LargeInt* subtract(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    // 348 - 1024 = -676
    //1024 - 348  =  676
    LargeInt<T>* ret = new LargeInt();
    LinkedList<T> List1;
    LinkedList<T> List2;
    LinkedList<T> List3;
    LinkedList<int>::Iterator i1;
    LinkedList<int>::Iterator i2;
    int num1; int num2;
    //borrow all the values necessary for L1.
    if (Listchecker(L1, L2) == 0)
    {
      List1.AddFront(0);
      ret->setList(List1);
      ret->setNegative(false);
      return ret;
    }
    else if (Listchecker(L1, L2) == 1)
    {
      // if list 1 is larger than list 2.
      List1 = L1.getList();
      List2 = L2.getList();
    }
    else
    {
      //if list 2 is larger than list 1.
      List1 = L2.getList();
      List2 = L1.getList();
    }
    List1 = borrow(List1, List2);
    i1 = List1.lastnode(); i2 = List2.lastnode();
    while (i1 != NULL || i2 != NULL)
    {
      (i1 != NULL) ? num1 = *i1 : num1 = 0;
      (i2 != NULL) ? num2 = *i2 : num2 = 0;
      List3.AddFront(num1 - num2);
      if (i1 != NULL) { --i1; }
      if (i2 != NULL) { --i2; }
    }
    ret->setList(List3);
    ret->setNegative(L1.negative);
    return ret;
  }
  //multiplies two large ints
  LargeInt* multiply(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    LargeInt<T>* temp = new LargeInt<T>();
    LargeInt<T>* temp2 = new LargeInt<T>();
    LinkedList<T> List1; LinkedList<T> List2; LinkedList<T> List3;
    LinkedList<T> List4;
    List1.AddFront(0); temp2->setList(List1);
    LinkedList<int>::Iterator i1; LinkedList<int>::Iterator i2;
    int num1 = 0; int num2 = 0; int sum = 0; int carry = 0;
    if (Listchecker(L1, L2) == 1)
    {
      List1 = L1.getList();
      List2 = L2.getList();
    }
    else
    {
      List1 = L2.getList();
      List2 = L1.getList();
    }
    i1 = List1.lastnode();
    i2 = List2.lastnode();
    //1500*92
    //List1 = 1500 
    //List2 = 92
    for (int i = 0; i < List2.getLength(); i++)
    {
      List3 = List4;
      for (int k = 0; k <= i - 1; k++)
      {
        List3.AddBack(0);
      }
      for (int j = 0; j < List1.getLength(); j++)
      {
        (i1 != nullptr) ? num1 = *i1 : num1 = 0;
        (i2 != nullptr) ? num2 = *i2 : num2 = 0;
        sum += ((*i2) * (*i1)) + carry;
        carry = sum / 10;
        List3.AddFront(sum % 10);
        sum = 0;
        --i1;
      }
      if (carry > 0)
      {
        List3.AddFront(carry);
        carry = 0;
      }
      temp->setList(List3);
      ret = add(*temp, *temp2);
      temp2->setList(ret->getList());
      --i2;
      i1 = List1.lastnode();
    }
    return ret;
  }
  //divides two large ints
  LargeInt* divide(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    LargeInt<T>* ret = new LargeInt();
    if (Listchecker(L1, L2) == -1)
    {
      ret->List.AddFront(0);
      return ret;
    }
    if (Listchecker(L1, L2) == 0)
    {
      ret->List.AddFront(1);
      return ret;
    }    
    LargeInt<T>* temp = new LargeInt();
    LargeInt<T>* temp2 = new LargeInt<T>();
    LargeInt<T>* temp3 = new LargeInt<T>();
    //LinkedList<T> counter;
    LinkedList<int>::Iterator i1; LinkedList<int>::Iterator i2;
    LinkedList<T> List1 = L1.getList(); LinkedList<T> List2 = L2.getList();
    temp->setList(List1); temp2->setList(List2); temp3->setList(List2);
    List1 = temp->getList();
    List2 = temp2->getList();
    i1 = List1.firstnode();
    i2 = List2.firstnode();
    int counter = 0;
    std::cout << "\n";
    while (Listchecker(*temp2, *temp) != 1)
    {
      counter++;
      temp2 = add(*temp2, *temp3);
    }
    List1 = temp2->getList();
    while (counter > 0)
    {
      ret->List.AddFront(counter%10);
      counter = counter / 10;
    }
    return ret;
  }
  //modulate two large ints
  LargeInt* modulo(const LargeInt<T>& L1, const LargeInt<T>& L2)
  {
    //12/5 = 2; quotient
    //2*5 = 10; product
    //12-10;
    // return 2;
    LargeInt<T>* zero = new LargeInt(); zero->List.AddFront(0);
    LargeInt<T>* ret = new LargeInt();
    //LargeInt<T>* temp = new LargeInt();
    LargeInt<T>* left = new LargeInt(); left->setList(L1.getList());
    LargeInt<T>* right = new LargeInt(); right->setList(L2.getList());
      
        //12%2452 || -12%2452
    if (L1.negative == L2.negative)
    {
      if (Listchecker(L1, L2) == 1)
      {
        ret = divide(L1, L2); const LargeInt<T> quotient = *ret;
        ret = multiply(quotient, L2); const LargeInt<T> product = *ret;
        ret = subtract(L1, product); const LargeInt<T> difference = *ret;
      }
      else
      {
        ret->setList(L1.getList());
      }
      ret->cleanList(); return ret;
    }
    else
    {
      ret = divide(L1, L2); ret->addOne(); const LargeInt<T> quotient = *ret;
      ret = multiply(quotient, L2); const LargeInt<T> product = *ret;
      ret = subtract(L1, product); const LargeInt<T> difference = *ret;
    }
    ret->cleanList(); return ret;
  }
  const LargeInt<T>& operator - (const LargeInt& other)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    if (this->getNegative() == false)
    {
      if (other.negative == false)
      {
        //if digit of this >= other then it is positive.
        //if digit of this < other then it is negative.
        //sub(positive, positive) 500 - 50 = 450
        if (this->getList().getLength() >= other.getList().getLength())
        {
          // becomes negative
          ret = subtract(*this, other);
          List = ret->getList();
          negative = true;
          return *this;
        }
        else
        {
          // becomes positive
          ret = subtract(*this, other);
          List = ret->getList();
          negative = false;
          return *this;
        }
      }
      else
      {
        //always positive.
        //500--50 = 500 + 50
        ret = add(*this, other);
        List = ret->getList();
        negative = false;
        return *this;
      }
    }
    else // this is negative
    {
      if (other.negative == false)
      {
        // always negative.
        //-50 -50 = -100
        ret = add(*this, other);
        List = ret->getList();
        negative = true;
        return *this;
      }
      else
      {
        // -100 -- 500 = -100 + 500
        //if digit of other >= L1 then it is positive.
        //if digit of other < L1 then it is negative.
        if (other.getList().getLength() >= this->getList().getLength())
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = false;
          return *this;
          //ret.setNegative(false);
        }
        else
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = true;
          return *this;
          //ret.setNegative(true);
        }
      }
    }
  }
  const LargeInt<T>& operator + (const LargeInt& other)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    // this object is not negative.
    if (this->getNegative() == false)
    {
      // 1+1 always positive.
      if (other.negative == false)
      {
        ret = add(*this, other);
        List = ret->getList();
        negative = false;
        return *this;
      }
      // 5+-1 = positive.
      // 1+-5 = negative
      else
      {
        //this > other
        if (Listchecker(*this, other) == 1)
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = false;
          return *this;
        }
        else
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = true;
          return *this;
        }
      }
    }
    // this object is negative.
    else
    {
      // -1+-1 always negative.
      if (other.negative == true)
      {
        ret = add(*this, other);
        List = ret->getList();
        negative = true;
        return *this;
      }
      //-5 + 1
      //-1 + 6 
      else
      {
        if (Listchecker(*this, other) == 1)
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = true;
          return *this;
        }
        else
        {
          ret = subtract(*this, other);
          List = ret->getList();
          negative = false;
          return *this;
        }
      }
    }
  }
  const LargeInt<T>& operator * (const LargeInt& other)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    if (this->getNegative() == other.negative)
    {
      ret = multiply(*this, other);
      List = ret->getList();
      negative = false;
      return *this;
    }
    else
    {
      ret = multiply(*this, other);
      List = ret->getList();
      negative = true;
      return *this;
    }
  }
  const LargeInt<T>& operator / (const LargeInt& other)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    if (this->getNegative() == other.negative)
    {
      ret = divide(*this, other);
      List = ret->getList();
      negative = false;
      return *this;
    }
    else
    {
      ret = divide(*this, other);
      List = ret->getList();
      negative = false;
      return *this;
    }
  }
  const LargeInt<T>& operator % (const LargeInt& other)
  {
    LargeInt<T>* ret = new LargeInt<T>();
    if (this->getNegative() == other.negative)
    {
      ret = modulo(*this, other);
      List = ret->getList();
      negative = this->getNegative();
      return *this;
    }
    else
    {
      if (this->getNegative() == true)
      {
        ret = modulo(*this, other);
        List = ret->getList();
        negative = false;
        return *this;
      }
      else
      {
        ret = modulo(*this, other);
        List = ret->getList();
        negative = true;
        return *this;
      }
    }
  }
};

#endif
