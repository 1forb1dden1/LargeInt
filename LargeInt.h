//Creator: Me
//Created: 4/18/2022
//Last Updated: 5/2/2022 9:08 PM
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
    LargeInt(LinkedList<T> list, bool TF)
    {
      List = list; negative = TF;
    }
    ~LargeInt()
    {
      negative = 0;
      List.~LinkedList();
    }
    LargeInt(const LargeInt<T>& other)
    {
      // temp points to this object's list.
      LinkedList<T>* temp = this->getList();
      // temp2 points to the other object's list.
      LinkedList<T>* temp2 = other->getList();
      // temp list copies temp2 list. 
      temp->copy(temp2);
      setNegative(other.negative());
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
    // checks the value of the large int list not considering the signs.
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
    // checks the value of of the large ints considering the sign.
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
          // counter shows how many times we need to move the iterator.
          --i1; counter++;
          while (*i1 <= 0)
          {
            if (i1 != NULL) { --i1; } counter++;
          }
          //for (int i = 0; i < counter; i++)
          //{
          //  *i1 = *i1 - 1;
          //  ++i1;
          //  *i1 = *i1 + 10;
          //}
          while (counter > 0)
          {
            *i1 = *i1 - 1;
            ++i1;
            *i1 = *i1 + 10;
            counter--;
          }
          
          //*i1 = *i1 - 1;
          //++i1;
          //*i1 = *i1 + 10;
        }
        if (i1 != NULL) { --i1; }
        if (i2 != NULL) { --i2; }
      }
      return List1;
    }
    LargeInt* add(const LargeInt<T>& L1, const LargeInt<T>& L2)
    {
      LargeInt<T>* ret = new LargeInt();
      LinkedList<int> List1 = L1.getList();
      LinkedList<int> List2 = L2.getList();
      LinkedList<int> List3;
      LinkedList<int>::Iterator i1 = List1.lastnode();
      LinkedList<int>::Iterator i2 = List2.lastnode();
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
        List3.AddBack(carry);
      }
      ret->setList(List3);
      return ret;
    }
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
        List3.AddFront(num1-num2);
        if (i1 != NULL) { --i1; }
        if (i2 != NULL) { --i2; }
      }
      ret->setList(List3);
      ret->setNegative(L1.negative);
      return ret;
    }
    LargeInt* multiply(const LargeInt<T>& L1, const LargeInt<T>& L2)
    {
      LargeInt<T>* ret = new LargeInt<T>();
      return ret;
    }
    const LargeInt<T>& operator - (const LargeInt& other)
    {
      LargeInt<T> *ret = new LargeInt<T>();
      if (this->getNegative() == false)
      {
        if (other.negative == false)
        {
          //if digit of this >= other then it is positive.
          //if digit of this < other then it is negative.
          //sub(positive, positive) 500 - 50 = 450
          if (this->getList().getLength() >= other.getList().getLength())
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
    const LargeInt<T>& operator + (const LargeInt& other);
    const LargeInt<T>& operator * (const LargeInt&);
    const LargeInt<T>& operator / (const LargeInt&);
    const LargeInt<T>& operator % (const LargeInt&);
};

#endif
