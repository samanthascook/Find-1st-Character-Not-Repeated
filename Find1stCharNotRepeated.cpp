#include <iostream>
#include <string>

// demonstrating understanding of classes 
// and inheritance

// to compile:  g++ Find1stCharNotRepeated.cpp -o Find1stCharNotRepeated.exe
// to execute:  ./Find1stCharNotRepeated.exe

// strings used for testing:
// 
// aaccbbdefdefac // should find all characters were repeated
// accbbdefdefc // should find a
// aaccbbdefefac // should find d
// aabbdefdefac // should find c

// a virtual class that the DefaultStream
// class is derived from. 
class Stream {

  public:
  
    virtual char getNext() = 0;
    virtual bool hasNext() = 0;

  private:

    std::string aString;
};

// the class we actually use
class DefaultStream: public Stream {

  public:

    // constructor
    DefaultStream(std::string s);

    char getNext();
    bool hasNext();

  private:

    std::string aString;
    int counter;
};

DefaultStream::DefaultStream(std::string s): counter(0) { 

  aString = s; 
}

bool DefaultStream::hasNext() {
 
  return (counter < aString.length());
}

char DefaultStream::getNext() {

  bool nextExists = hasNext();
  char returnvalue;

  if(nextExists) {
    returnvalue = aString.at(counter);
    counter++;
    return returnvalue;
  }

  return aString.at(aString.length() - 1);
}

bool isAlphaNumeric(std::string s) {

  int length = s.length();
  
  for (int i = 0; i < length; i++) {

    if (std::isalnum(s[i]) == false) return false;
  }
  
  return true;
}

// Note:  no matter how long the string is after the 
//        the string is traversed once the search 
//        for the first char that is not repeated 
//        will be constant.
int Find1stCharNotRepeated(std::string input) {

  char counter[255] = {0};
  int found = -1;
  int i = 0;

  DefaultStream s(input);

  // O(n)
  while (s.hasNext()) {
    counter[(int)s.getNext()]++;  // using ascii
  }

  // O(1)
  while ((found==-1) && (i<255)) {
    if(counter[i]==1) { 
      found = i; 
    }
    i++;
  }

  return found;
}

// precondition:  the string used must contain only letters and numbers.
int main(void)
{
  int found = -1;
  char firstCharNotRepeated;
  std::string temp = "";

  std::cout << "Please enter a string (letters and numbers only):  ";
  std::cin >> temp;

  if (isAlphaNumeric(temp) == true) {

    found = Find1stCharNotRepeated(temp);

    if (found!=-1) {
      firstCharNotRepeated = (char)found;
      std::cout << "first non repeated:  " << firstCharNotRepeated << std::endl; 
    }
    else { 
      std::cout << "all characters were repeated." << std::endl; 
    }
  }
  else {

    std::cout << "Invalid string" << std::endl;
  }

  return 0;
}
