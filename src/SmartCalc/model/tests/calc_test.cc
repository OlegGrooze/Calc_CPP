#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "model/modelCalc.h"

TEST(CalcTest, OneOerator) {
  double a = 13.14;
  double b = 45.01;
  double result = 0., expected_result = 0.;
  std::string lexeme;
  char buff[255];

  std::snprintf(buff, sizeof(buff), "%lf+%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = a + b;
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "%lf-%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result = a - b;
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "%lf*%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result = a * b;
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "%lf/%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc4(lexeme, 0);
  result = calc4.CountLexeme();
  expected_result = a / b;
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "%lfmod%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc5(lexeme, 0);
  result = calc5.CountLexeme();
  expected_result = std::fmod(a, b);
  EXPECT_DOUBLE_EQ(result, expected_result);

  a = 2, b = 2;
  std::snprintf(buff, sizeof(buff), "%lf^%lf", a, b);
  lexeme = buff;
  s21::SmartCalc calc6(lexeme, 0);
  result = calc6.CountLexeme();
  expected_result = std::pow(a, b);
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, OneFunction) {
  double a = 0.18;
  double result = 0., expected_result = 0.;
  std::string lexeme;
  char buff[255];

  std::snprintf(buff, sizeof(buff), "sin(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = sin(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "cos(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result = cos(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "tan(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result = tan(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "asin(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc4(lexeme, 0);
  result = calc4.CountLexeme();
  expected_result = asin(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "acos(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc5(lexeme, 0);
  result = calc5.CountLexeme();
  expected_result = acos(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "atan(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc6(lexeme, 0);
  result = calc6.CountLexeme();
  expected_result = atan(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "sqrt(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc7(lexeme, 0);
  result = calc7.CountLexeme();
  expected_result = sqrt(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "ln(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc8(lexeme, 0);
  result = calc8.CountLexeme();
  expected_result = log(a);
  EXPECT_DOUBLE_EQ(result, expected_result);

  std::snprintf(buff, sizeof(buff), "log(%lf)", a);
  lexeme = buff;
  s21::SmartCalc calc9(lexeme, 0);
  result = calc9.CountLexeme();
  expected_result = log10(a);
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, SeveralOperators) {
  std::string lexeme = "1+2-3.2*7.008/2*2-2.5";
  double result = 0., expected_result = 0.;

  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = 1 + 2 - 3.2 * 7.008 / 2 * 2 - 2.5;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "1.0001*29999.555-456/1.23456789+5*9/9*9+6-7";
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result =
      1.0001 * 29999.555 - 456 / 1.23456789 + 5 * 9 / 9 * 9 + 6 - 7;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "1.+1+1+1+1+1+1+1-1-1./11*1-1/1-11-1*1/1*1/1-1/1*1+1-1/1*1";
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result = 1. + 1 + 1 + 1 + 1 + 1 + 1 + 1 - 1 - 1. / 11 * 1 - 1 / 1 -
                    11 - 1 * 1 / 1 * 1 / 1 - 1 / 1 * 1 + 1 - 1 / 1 * 1;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme =
      "0.0001*12345.6789*12345.921-568.3245687+78.1234567*0.0000001/0.020201";
  s21::SmartCalc calc4(lexeme, 0);
  result = calc4.CountLexeme();
  expected_result = 0.0001 * 12345.6789 * 12345.921 - 568.3245687 +
                    78.1234567 * 0.0000001 / 0.020201;
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, UnaryPlusMinus) {
  std::string lexeme = "-1+2-3.2*7.008/2*2-2.5";
  double result = 0., expected_result = 0.;

  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = -1 + 2 - 3.2 * 7.008 / 2 * 2 - 2.5;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "-1.0001*(+29999.555)-(-456.)/(+1.23456789)+(-5)*9/9*9+6-7";
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result = -1.0001 * (+29999.555) - (-456.) / (+1.23456789) +
                    (-5) * 9 / 9 * 9 + 6 - 7;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "+1.0001*29999.555-456/1.23456789+5*9/9*9+6-7";
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result =
      +1.0001 * 29999.555 - 456 / 1.23456789 + 5 * 9 / 9 * 9 + 6 - 7;
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme =
      "-1.0001*(-29999.555)-(-456.)/(-1.234789)+(-5)*(-9)/(-9)*(-9./"
      "(-6.)+6.-7)";
  s21::SmartCalc calc4(lexeme, 0);
  result = calc4.CountLexeme();
  expected_result = -1.0001 * (-29999.555) - (-456.) / (-1.234789) +
                    (-5) * (-9) / (-9) * (-9. / (-6.) + 6. - 7);
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, Brackets) {
  std::string lexeme = "(((((((5+1)*2)*2)*2)*2)))";
  double result = 0., expected_result = 0.;

  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = (((((((5 + 1) * 2) * 2) * 2) * 2)));
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "(((((((5.+1.)*2.)*2.)*2.)*2.)))*((1.+2.)-1)-(((((1)))))";
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result =
      (((((((5. + 1.) * 2.) * 2.) * 2.) * 2.))) * ((1. + 2.) - 1) - (((((1)))));
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "(-(-(-(-(-(-(5.+1.)*2.)*2.)*2.)*2.)))*((1.+2.)-1)-(((((1)))))";
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result =
      (-(-(-(-(-(-(5. + 1.) * 2.) * 2.) * 2.) * 2.))) * ((1. + 2.) - 1) -
      (((((1)))));
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, SeveralTrigonometricPow) {
  std::string lexeme = "sin(cos(tan(0.0001)))";
  double result = 0., expected_result = 0.;

  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = sin(cos(tan(0.0001)));
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "sin(cos(tan(0.0001)))*tan(sin(-1.*0.2))+cos(atan(0.98/2-0.0001))";
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result = sin(cos(tan(0.0001))) * tan(sin(-1. * 0.2)) +
                    cos(atan(0.98 / 2 - 0.0001));
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme =
      "sin(cos(tan(0.0001)))*tan(sin(-1.*0.2))+cos(atan(0.98/"
      "2-0.0001))+sin(0)+acos(1)+asin(0.000003)";
  s21::SmartCalc calc3(lexeme, 0);
  result = calc3.CountLexeme();
  expected_result = sin(cos(tan(0.0001))) * tan(sin(-1. * 0.2)) +
                    cos(atan(0.98 / 2 - 0.0001)) + sin(0) + acos(1) +
                    asin(0.000003);
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme =
      "2.^(sin(cos(tan(0.0001)))*tan(sin(-1.*0.2)))+0.2^(cos(atan(0.98/"
      "2-0.0001))+sin(0)+acos(1)+asin(0.000003))";
  s21::SmartCalc calc4(lexeme, 0);
  result = calc4.CountLexeme();
  expected_result = pow(2., (sin(cos(tan(0.0001))) * tan(sin(-1. * 0.2)))) +
                    pow(0.2, (cos(atan(0.98 / 2 - 0.0001)) + sin(0) + acos(1) +
                              asin(0.000003)));
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, SeveralAnotherFunctions) {
  std::string lexeme = "ln(1.2mod0.00345+sqrt(3.1415*(-log(0.12300001))))";
  double result = 0., expected_result = 0.;

  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result =
      log(fmod(1.2, 0.00345) + sqrt(3.1415 * (-log10(0.12300001))));
  EXPECT_DOUBLE_EQ(result, expected_result);

  lexeme = "-ln(1.2mod(sin(0.005)*0.00345)+sqrt(3.1415*(-log(0.12300001))))";
  s21::SmartCalc calc2(lexeme, 0);
  result = calc2.CountLexeme();
  expected_result = -log(fmod(1.2, sin(0.005) * 0.00345) +
                         sqrt(3.1415 * (-log10(0.12300001))));
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(CalcTest, AbobusHard) {
  std::string lexeme =
      "-sin(-0.2365/"
      "atan(1.002)+acos(0.141528)^(3.1415))+(-log(10*cos(-sqrt(2.3-3.7/"
      "89)+1415.)))/ln(3.321+atan(-3mod4))";
  double result = 0., expected_result = 0.;
  s21::SmartCalc calc(lexeme, 0);
  result = calc.CountLexeme();
  expected_result = -sin(-0.2365 / atan(1.002) + pow(acos(0.141528), 3.1415)) +
                    (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
                        log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-10);
}

TEST(CalcTest, HardWithArg) {
  std::string lexeme =
      "-sin(-0.2365*x/"
      "atan(1.002)+acos(0.141528)^(3.1415))+(-log(10*cos(-sqrt(2.3-3.7/"
      "89)+1415.)))/ln(3.321+atan(-3mod4))";
  double result = 0., expected_result = 0.;
  double x = 0.1346;

  s21::SmartCalc calc(lexeme, x);
  result = calc.CountLexeme();
  expected_result =
      -sin(-0.2365 * x / atan(1.002) + pow(acos(0.141528), 3.1415)) +
      (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
          log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-10);

  x = -0.000001;
  lexeme =
      "-sin(-0.2365*x/atan(1.002)+acos(0.141528)^(3.1415))+x-x*x/"
      "(-log(10*cos(-sqrt(2.3-3.7/89)+1415.)))/ln(3.321+atan(-3mod4))";
  s21::SmartCalc calc2(lexeme, x);
  result = calc2.CountLexeme();
  expected_result =
      -sin(-0.2365 * x / atan(1.002) + pow(acos(0.141528), 3.1415)) + x -
      x * x / (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
          log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-10);

  x = 0.0000005;
  lexeme =
      "-sin(-0.2365*x/atan(1.002)+acos(0.141528)^(3.1415))+x-x*x/"
      "(-log(10*cos(-sqrt(2.3-3.7/89)+1415.)))/ln(3.321+atan(-3mod4))";
  s21::SmartCalc calc3(lexeme, x);
  result = calc3.CountLexeme();
  expected_result =
      -sin(-0.2365 * x / atan(1.002) + pow(acos(0.141528), 3.1415)) + x -
      x * x / (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
          log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-10);

  x = 4815.162342;
  lexeme =
      "-sin(-0.2365*x/atan(1.002)+acos(0.141528)^(3.1415))+x-x*x/"
      "(-log(10*cos(-sqrt(2.3-3.7/89)+1415.)))/ln(3.321+atan(-3mod4))";
  s21::SmartCalc calc4(lexeme, x);
  result = calc4.CountLexeme();
  expected_result =
      -sin(-0.2365 * x / atan(1.002) + pow(acos(0.141528), 3.1415)) + x -
      x * x / (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
          log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-6);

  x = 0.;
  lexeme =
      "-sin(-0.2365*x/atan(1.002)+acos(0.141528)^(3.1415))+x-x*x/"
      "(-log(10*cos(-sqrt(2.3-3.7/89)+1415.)))/ln(3.321+atan(-3mod4))";
  s21::SmartCalc calc5(lexeme, x);
  result = calc5.CountLexeme();
  expected_result =
      -sin(-0.2365 * x / atan(1.002) + pow(acos(0.141528), 3.1415)) + x -
      x * x / (-log10(10 * cos(-sqrt(2.3 - 3.7 / 89) + 1415.))) /
          log(3.321 + atan(fmod(-3., 4.)));
  EXPECT_NEAR(result, expected_result, 1e-10);
}

TEST(CalcTest, Exceptions) {
  std::string lexeme = "abobus";

  s21::SmartCalc calc(lexeme, 0);
  try {
    calc.CountLexeme();
  } catch (s21::Exception& e) {
    EXPECT_EQ(e.GetMessage(), "Invalid expression");
  }

  lexeme = "1+2-*3.2*+7.008/2*2-2.5";
  s21::SmartCalc calc2(lexeme, 0);
  try {
    calc2.CountLexeme();
  } catch (s21::Exception& e) {
    EXPECT_EQ(e.GetMessage(), "Missing or unexpected operator");
  }

  lexeme = "()))";
  s21::SmartCalc calc3(lexeme, 0);
  try {
    calc3.CountLexeme();
  } catch (s21::Exception& e) {
    EXPECT_EQ(e.GetMessage(), "Not valid brackets sequence");
  }

  lexeme = "(2+3)(2)";
  s21::SmartCalc calc4(lexeme, 0);
  try {
    calc4.CountLexeme();
  } catch (s21::Exception& e) {
    EXPECT_EQ(e.GetMessage(), "Not valid brackets sequence");
  }
}
