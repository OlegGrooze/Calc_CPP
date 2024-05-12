#include "model/modelCalc.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

#include "model/mathFunctions.h"
#include "model/mathOperators.h"

s21::SmartCalc::SmartCalc(const std::string& l, double arg)
    : lexeme_(l), arg_(arg) {}

void s21::SmartCalc::SetLexeme(const std::string& l) noexcept {
  ClearStructures();
  lexeme_ = l;
}

void s21::SmartCalc::SetArg(const double arg) noexcept { arg_ = arg; }

double s21::SmartCalc::CountLexeme() {
  PostfixNotation();
  return CountNotation();
}

void s21::SmartCalc::PostfixNotation() {
  std::stack<Token> tokenStack;
  StringTokenizer getTokens(lexeme_);
  tokens_ = getTokens.ParseLexeme();

  for (uint16_t i = 0; i < tokens_.size(); ++i) {
    if (tokens_[i].type == LexemeType::kVariable ||
        tokens_[i].type == LexemeType::kNumber) {
      notation_.push_back(tokens_[i]);
    } else if (tokens_[i].type == LexemeType::kFunction) {
      tokenStack.push(tokens_[i]);
    } else if (tokens_[i].type == LexemeType::kBracket) {
      if (tokens_[i].lexeme == Lexeme::kOpenBracket) {
        tokenStack.push(tokens_[i]);
      } else {
        while (tokenStack.top().lexeme != Lexeme::kOpenBracket) {
          notation_.push_back(tokenStack.top());
          tokenStack.pop();
        }
        tokenStack.pop();
        if (!tokenStack.empty() &&
            tokenStack.top().type == LexemeType::kFunction) {
          notation_.push_back(tokenStack.top());
          tokenStack.pop();
        }
      }
    } else if (tokens_[i].type == LexemeType::kOperator ||
               tokens_[i].type == LexemeType::kUnMinus) {
      while (!tokenStack.empty() &&
             tokenStack.top().type != s21::LexemeType::kBracket &&
             tokenStack.top().priority >= tokens_[i].priority) {
        notation_.push_back(tokenStack.top());
        tokenStack.pop();
      }
      tokenStack.push(tokens_[i]);
    }
  }

  while (!tokenStack.empty()) {
    notation_.push_back(tokenStack.top());
    tokenStack.pop();
  }
}

double s21::SmartCalc::CountNotation() {
  std::stack<Token> operandStack;
  auto countFunction = std::make_unique<s21::MathFunctions>();
  auto countOperator = std::make_unique<s21::MathOperators>();

  for (uint16_t i = 0; i < notation_.size(); ++i) {
    if (notation_[i].type == LexemeType::kVariable) {
      notation_[i].value = arg_;
      operandStack.push(notation_[i]);
    } else if (notation_[i].type == LexemeType::kNumber) {
      operandStack.push(notation_[i]);
    } else if (notation_[i].type == LexemeType::kOperator) {
      if (operandStack.size() < 2) {
        throw(s21::Exception("Некорректное выражение"));
      }
      Token upper = operandStack.top();
      operandStack.pop();
      Token lower = operandStack.top();
      operandStack.pop();
      lower.value = countOperator->CallOperator(notation_[i].lexeme,
                                                lower.value, upper.value);
      operandStack.push(lower);
    } else if (notation_[i].type == LexemeType::kFunction ||
               notation_[i].type == LexemeType::kUnMinus) {
      if (operandStack.size() < 1) {
        throw(s21::Exception("Некорректное выражение"));
      }
      Token upper = operandStack.top();
      operandStack.pop();
      upper.value =
          countFunction->CallFunction(notation_[i].lexeme, upper.value);
      operandStack.push(upper);
    }
  }
  return operandStack.empty() ? 0. : operandStack.top().value;
}

void s21::SmartCalc::ClearStructures() noexcept {
  tokens_.clear();
  notation_.clear();
}
