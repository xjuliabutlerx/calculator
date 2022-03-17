#include <Keypad.h>
#include <LiquidCrystal.h>

// Creating a variable to hold a pseudo "null" value to compare with
// operands in the expression
int empty = -9999;

// Setting up the keyboard object
const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'#','0','*','D'}
};

// Connecting keypad to digital pwm pins on board
byte rowPins[ROWS] = {7, 6, 5, 4}; // wire 1 -> pin 7, 2 -> 6, 3 -> 5, 4 -> 4
byte colPins[COLS] = {3, 2, 1, 0}; // wire 5 -> pin 3, 6 -> 2, 7 -> 1, 8 -> 0

// Creating keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Creating LCD display object
// rs -> 8, e -> 9, d4 -> 10, d5 -> 11, d6 -> 12, d7 -> 13)
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Creating global variables to do the math on
int expression[16] = {empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty, empty}; // Creating an integer array to hold the expression
int operators[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Creating an integer array to hold the placement of operators
int counter = 0; // Creating a counter to iterate through the expression array
String expr = ""; // Creating an empty string to hold the expression
String token = ""; // Creating an empty string to hold each token (operator or operand)

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.blink();
}
 
void loop() {
  // Get the key that the user just pressed
  char key = keypad.getKey(); 

  // Action for each key on the keypad
  if (key != NO_KEY) {
    if (key == '1') {
      if (expr.length() <= 16) {
        token += "1";
        expr += "1";
        lcd.print("1");
      }
      
    } else if (key == '2') {
      if (expr.length() <= 16) {
        token += "2";
        expr += "2";
        lcd.print("2");
      }
      
    } else if (key == '3') {
      if (expr.length() <= 16) {
        token += "3";
        expr += "3";
        lcd.print("3");
      }
      
    } else if (key == '4') {
      if (expr.length() <= 16) {
        token += "4";
        expr += "4";
        lcd.print("4");
      }
      
    } else if (key == '5') {
      if (expr.length() <= 16) {
        token += "5";
        expr += "5";
        lcd.print("5");
      }
      
    } else if (key == '6') {
      if (expr.length() <= 16) {
        token += "6";
        expr += "6";
        lcd.print("6");
      }
      
    } else if (key == '7') {
      if (expr.length() <= 16) {
        token += "7";
        expr += "7";
        lcd.print("7");
      }
      
    } else if (key == '8') {
      if (expr.length() <= 16) {
        token += "8";
        expr += "8";
        lcd.print("8");
      }
      
    } else if (key == '9') {
      if (expr.length() <= 16) {
        token += "9";
        expr += "9";
        lcd.print("9");
      }
      
    } else if (key == '0') {
      if (expr.length() <= 16) {
        token += "0";
        expr += "0";
        lcd.print("0");
      }
      
    } else if (key == 'A') {
      if (expr.length() <= 16) {
        expression[counter] = token.toInt();
        token = "";
        counter++;
        operators[counter] = -1;
        counter++;
        expr += "+";
        lcd.print("+");
      }
      
    } else if (key == 'B') {
      if (expr.length() <= 16) {
        expression[counter] = token.toInt();
        token = "";
        counter++;
        operators[counter] = -2;
        counter++;
        expr += "-";
        lcd.print("-");
      }
      
    } else if (key == 'C') {
      if (expr.length() <= 16) {
        expression[counter] = token.toInt();
        token = "";
        counter++;
        operators[counter] = -3;
        counter++;
        expr += "*";
        lcd.print("*");
      }
      
    } else if (key == 'D') {
      if (expr.length() <= 16) {
        expression[counter] = token.toInt();
        token = "";
        counter++;
        operators[counter] = -4;
        counter++;
        expr += "/";
        lcd.print("/");
      }
      
    } else if (key == '#') {
      clearArray();
      expr = "";
      token = "";
      counter = 0;
      lcd.clear();
      
    } else if (key == '*') {
      // Inserts the last token (operand) to the expression array
      // if not empty
      if (token.length() > 0) {
        expression[counter] = token.toInt();
        token = "";
      }
      
      lcd.setCursor(0, 1);

      if (isValid() == false) {
        lcd.print("Syntax Error");
      } else {
        lcd.setCursor(0, 1);
        lcd.print(calculate());
      }
      
      lcd.setCursor(0, 0);
    }
  }
}

// Converts operators into negative integers
// + -> -1
// - -> -2
// * -> -3
// / -> -4
int OptoInt(char i) {
  int ret = -1;
  switch (i) {
    case '+':
      ret = -1;
      break; 
    case '-':
      ret = -2;
      break;
    case '*':
      ret = -3;
      break;
    case '/':
      ret = -4;
      break;
    default:
      // Default is addition
      break;
  }
  return ret;
}

// Iterates through the expression array to determine
// if the given expression is in valid infix form
// An expression is invalid if:
//  a) the expression array is empty
//  b) the expression starts with an operator
//  c) the expression ends with an operator
//  d) two operators are next to each other
//  e) the # of operators >= # of operands (or
//     similarly, # of operators >= 8)
// Case D will typically catch Case E
bool isValid() {
  if (expr.length() == 0) {
    // Case A
    //lcd.print("Failed Case A");
    return false;
    
  } else if (expr.charAt(0) == '+' || expr.charAt(0) == '-' || expr.charAt(0) == '*' || expr.charAt(0) == '/') {
    // Case B
    //lcd.print("Failed Case B");
    return false;
    
  } else if ((expr.length() > 1) && (expr.endsWith("+") || expr.endsWith("-") || expr.endsWith("*") || expr.endsWith("/"))) {
    // Case C
    //lcd.print("Failed Case C");
    return false;
    
  } else if ((expr.length() == 1) && (expr.charAt(0) != '+' || expr.charAt(0) != '-' || expr.charAt(0) != '*' || expr.charAt(0) != '/')) {
    // Not a specified case, but if the only token is an operand, then it's ok
    return true;
    
  } else {
    char a, b;
    int numOpr = 0; // number of operators
    for (int i = 0; (i < (expr.length() - 1)) && (expr.length() > 1); i++) {
      a = expr.charAt(i);
      b = expr.charAt(i+1);

      if (b == '+' || b == '-' || b == '*' || b == '/')
        numOpr++;

      if (numOpr >= 8) {
        // Case E
        //lcd.print("Failed Case E");
        return false;
      }
      
      if ((a == '+' || a == '-' || a == '*' || a == '/') && (b == '+' || b == '-' || b == '*' || b == '/')) {
        // Case D
        //lcd.print("Failed Case D");
        return false;
      }
    }
  }
  
  return true;
}

// Find the minimum value in the operators array
// (either multiplication or division) and do the
// math for the operands sitting to the left and
// right of the operator. Save the result in the
// blank cell of the expressions array, set the
// cell in the operators array to 0, and set the
// cells of the operands to 0 in the expressions
// array. Repeat until there are no operators
// (negative numbers) in the operators array.
int calculate() {
  // If there's only one token in the expression
  // array, then it must be an operand, so just
  // return the operand
  if (hasOneOpd() == true) {
    return expression[0];
  } else {
    int oprIndex, leftO, rightO;

    while (hasOpr() == true) {
      oprIndex = findMin();
      //lcd.print(oprIndex);
      leftO = findLeft(oprIndex);
      rightO = findRight(oprIndex);

      operate(oprIndex, leftO, rightO);
    }

    return expression[oprIndex];
  }
}

// Finds the smallest value in the expressions array
// and returns the minimum value. Follows PEMDAS by
// not treating (division (-4) and multiplcation (-3))
// and (subtraction (-2) and addition (-1)) the same.
int findMin() {
  int low = 0;
  int lowVal = operators[0];
  for (int i = 1; i < 16; i++) {
    if (lowVal > operators[i] && ((lowVal != -3 && operators[i] != -4) || (lowVal != -1 && operators[i] != -2))) {
      lowVal = operators[i];
      low = i;
    }
  }

  return low;
}

// Calculates the index of the operand to the left of the
// operator index. If an operand can't be found, return
// the operator's index.
int findLeft(int oprIndex) {
  for (int i = oprIndex - 1; i >= 0; i--) {
    if (expression[i] > empty) {
      return i;
    }
  }
  return oprIndex;
}

// Calculates the index of the operand to the right of the
// operator index. If an operand can't be found, return the
// operator's index.
int findRight(int oprIndex) {
  for (int i = oprIndex + 1; i < 16; i++) {
    if (expression[i] > empty) {
      return i;
    }
  }
  return oprIndex;
}

// Returns true if there are still operators in the
// operators array
bool hasOpr() {
  for (int i = 0; i < 16; i++) {
    if (operators[i] != 0) {
      return true;
    }
  }
  return false;
}

// Returns true if there is only one operand in the
// expression array in the first position
bool hasOneOpd() {
  if (expression[0] == empty) {
    return false;
  }
  
  for (int i = 1; i < 16; i++) {
    if (expression[i] != empty) {
      return false;
    }
  }

  return true;
}

// Does the mathematical operation on the operands given
// based on their index and sets the value at oprIndex
// to the result
void operate(int oprIndex, int leftO, int rightO) {
  if (operators[oprIndex] == -1) {
    expression[oprIndex] = expression[leftO] + expression[rightO];

    operators[oprIndex] = 0;
    expression[leftO] = empty;
    expression[rightO] = empty;
    
  } else if (operators[oprIndex] == -2) {
    expression[oprIndex] = expression[leftO] - expression[rightO];

    operators[oprIndex] = 0;
    expression[leftO] = empty;
    expression[rightO] = empty;
    
  } else if (operators[oprIndex] == -3) {
    expression[oprIndex] = expression[leftO] * expression[rightO];

    operators[oprIndex] = 0;
    expression[leftO] = empty;
    expression[rightO] = empty;
    
  } else if (operators[oprIndex] == -4) {
    // Logic for dealing with inputs that try to divide by 0
    // (Essentially, reset everything and print division
    // error)
    if (expression[rightO] == 0) {
      clearArray();
      expr = "";
      token = "";
      counter = 0;
      lcd.clear();
      lcd.home();
      lcd.print("Division Error");
      return;
    } else {
      expression[oprIndex] = expression[leftO] / expression[rightO];
      
      operators[oprIndex] = 0;
      expression[leftO] = empty;
      expression[rightO] = empty; 
    }
  }
}

// Set each position in the expression array to empty and operations
// array to 0
void clearArray() {
  for (int i = 0; i < 16; i++) {
    expression[i] = empty;
    operators[i] = 0;
  }
}
