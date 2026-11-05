#include <iostream>
#include <string>
#include <vector>
#include <cctype>

/* Vector Lexer version-attempt: 1 */

/* Test version of lexical anylizer made by MasterMindingASF  */

/* How i did it: First i did some research on how lexer / compiler works 
   and i've looked at lexer examples and i recreated it myself without copy and pasting

   This is vector lexer which saves text fully in RAM and assigns token by dividing source text into small strings.
   I've tried to reduce memory usage by using references(&) but i am afraid that butterflies inside my stomach rushed it.
   (It might be unoptimized)

   If you're reading this, please feel free to judge my code and tell me how i can improve it.
*/

// Creates token scope
enum tokenType {
     texts,
     numbers,
     operators,
     unknowns
};

struct token {
     std::string tokenText;
     int tokenType;
};

// Divides source text into small strings to feed tokenizer
std::vector<std::string> divideString(std::string &srcText) {
     std::vector<std::string> text {srcText};
     std::string word;
     for(char ch : srcText) {
          if(ch != ' ') {
               word += ch;
          }
          else{
               std::cout << word << '\n';
               text.push_back(word);
               word.clear();
          }
     }
     if(!word.empty()) {
          text.push_back(word);
     }

     return text;
}

// Decides text's token type if its not empty and if there's no token that fits category then put it in unknown category
std::vector<std::string> tokenizer(std::string &srcText) {
     std::vector<token> tokens;
     std::vector<std::string> src {divideString(srcText)};

     while(!srcText.empty()) {
          if(isdigit(srcText.front())) {
               std::string number;
               while(!srcText.empty() && isdigit(srcText.front())) {
                    int i {0};
                    number += srcText[i++];
               }
          }
     }
     return src;
}

// Token type checkers
bool isWord(std::string &word) {
     if(word.empty()) {
          return false;
     }
     for(char ch : word) {
          if(!isalpha(ch)) {
               return false;
          }
     }
     return true;
}

bool isNumber(std::string &word) {
     if(word.empty()) {
          return false;
     }
     for(char ch : word) {
          if(!isdigit(ch)) {
               return false;
          }
     }
     return true;
}

bool isOperator(std::string &word) {
     std::string operatorChars {"+-*/"};
     if(word.size() != 1) {
          return false;
     }
     for(char op : operatorChars) {
          if(word.front() == op) {
               return true;
          }
     }
     return false;
}

// Creates token
token makeToken(std::string &word) {
     token newToken;
     newToken.tokenText = word;
     if(isNumber(word)) {
          newToken.tokenType = numbers;
     }
     else if(isWord(word)) {
          newToken.tokenType = texts;
     }
     else if(isOperator(word)) {
          newToken.tokenType = operators;
     }
     else{
          newToken.tokenType = unknowns;
     }
     return newToken;
}

int main() {
     std::string sourceText;
     std::getline(std::cin, sourceText);
     std::vector<std::string> words {divideString(sourceText)};

     for(std::string &word : words) {
          token checkedToken {makeToken(word)};
          std::cout << word << " -> type " << checkedToken.tokenType << '\n';
     }
     return 0;
}