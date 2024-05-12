#include "model/stringTokenizer.h"

#include "model/bracketsChecker.h"

std::vector<s21::Token> s21::StringTokenizer::ParseLexeme() {
  int16_t flagOperator = 1;
  tokens_.clear();

  BracketsChecker bCheck(lexeme_);
  bCheck.Check();

  while (lexIter_ < lexeme_.size()) {
    bool check_parse = GetBrackets() || GetFunction() || GetOperator() ||
                       GetVariable() || GetNumber();
    if (!check_parse) {
      throw(s21::Exception("Некорректное выражение"));
    }
    if (tokens_.back().lexeme == Lexeme::kMinus && flagOperator == 1) {
      tokens_.back().lexeme = Lexeme::kUnMinus;
      tokens_.back().type = LexemeType::kUnMinus;
      tokens_.back().priority = Priority::kThird;
    }
    if (tokens_.back().type == LexemeType::kOperator) {
      ++flagOperator;
    } else if (tokens_.back().type == LexemeType::kNumber ||
               tokens_.back().type == LexemeType::kVariable) {
      --flagOperator;
    }
    if (tokens_.back().lexeme == Lexeme::kPlus && flagOperator == 2) {
      --flagOperator;
      tokens_.pop_back();
    }
    if (flagOperator < 0 || flagOperator > 1) {
      // throw(s21::Exception("Missing or unexpected operator"));
      throw(s21::Exception("Пропущенный или неожидаемый оператор"));
    }
  }
  return tokens_;
}

bool s21::StringTokenizer::GetBrackets() {
  if (lexeme_[lexIter_] == '(') {
    Token t;
    t.lexeme = Lexeme::kOpenBracket;
    t.type = LexemeType::kBracket;
    ++lexIter_;
    tokens_.push_back(t);
    return true;
  }

  if (lexeme_[lexIter_] == ')') {
    Token t;
    t.lexeme = Lexeme::kCloseBracket;
    t.type = LexemeType::kBracket;
    ++lexIter_;
    tokens_.push_back(t);
    return true;
  }
  return false;
}

bool s21::StringTokenizer::GetFunction() {
  uint16_t shift = 0;
  Token t;

  if (lexeme_.size() > lexIter_ + 4) {
    if (lexeme_.compare(lexIter_, 3, "sin") == 0) {
      t.lexeme = Lexeme::kSin;
      shift = 3;
    } else if (lexeme_.compare(lexIter_, 3, "cos") == 0) {
      t.lexeme = Lexeme::kCos;
      shift = 3;
    } else if (lexeme_.compare(lexIter_, 3, "tan") == 0) {
      t.lexeme = Lexeme::kTan;
      shift = 3;
    } else if (lexeme_.compare(lexIter_, 4, "asin") == 0) {
      t.lexeme = Lexeme::kAsin;
      shift = 4;
    } else if (lexeme_.compare(lexIter_, 4, "acos") == 0) {
      t.lexeme = Lexeme::kAcos;
      shift = 4;
    } else if (lexeme_.compare(lexIter_, 4, "atan") == 0) {
      t.lexeme = Lexeme::kAtan;
      shift = 4;
    } else if (lexeme_.compare(lexIter_, 4, "sqrt") == 0) {
      t.lexeme = Lexeme::kSqrt;
      shift = 4;
    } else if (lexeme_.compare(lexIter_, 2, "ln") == 0) {
      t.lexeme = Lexeme::kLn;
      shift = 2;
    } else if (lexeme_.compare(lexIter_, 3, "log") == 0) {
      t.lexeme = Lexeme::kLog;
      shift = 3;
    }
  }

  if (shift > 0) {
    t.type = LexemeType::kFunction;
    t.priority = Priority::kFifth;
    tokens_.push_back(t);
    lexIter_ += shift;
    return true;
  }
  return false;
}

bool s21::StringTokenizer::GetNumber() {
  double number = 0.;
  std::string tempStr(lexeme_.begin() + lexIter_, lexeme_.end());
  int32_t count;

  sscanf(tempStr.c_str(), "%le %n", &number, &count);
  if (count == 0) {
    return false;
  }

  lexIter_ += count;
  Token t;
  t.type = LexemeType::kNumber;
  t.value = number;
  tokens_.push_back(t);

  return true;
}

bool s21::StringTokenizer::GetOperator() {
  bool check = false;
  Token t;
  uint16_t shift = 1;

  switch (lexeme_[lexIter_]) {
    case '+':
      t.lexeme = Lexeme::kPlus;
      t.priority = Priority::kFirst;
      check = true;
      break;
    case '-':
      t.lexeme = Lexeme::kMinus;
      t.priority = Priority::kFirst;
      check = true;
      break;
    case '*':
      t.lexeme = Lexeme::kMul;
      t.priority = Priority::kSecond;
      check = true;
      break;
    case '/':
      t.lexeme = Lexeme::kDiv;
      t.priority = Priority::kSecond;
      check = true;
      break;
    case '^':
      t.lexeme = Lexeme::kPow;
      t.priority = Priority::kFourth;
      check = true;
      break;
    default:
      break;
  }

  if (!check && lexeme_.size() > lexIter_ + 3 &&
      lexeme_.compare(lexIter_, 3, "mod") == 0) {
    t.lexeme = Lexeme::kMod;
    t.priority = Priority::kSecond;
    check = true;
    shift = 3;
  }

  if (check) {
    t.type = LexemeType::kOperator;
    tokens_.push_back(t);
    lexIter_ += shift;
  }
  return check;
}

bool s21::StringTokenizer::GetVariable() {
  if (lexeme_[lexIter_] == 'x') {
    Token t;
    t.type = LexemeType::kVariable;
    tokens_.push_back(t);
    ++lexIter_;
    return true;
  }
  return false;
}
