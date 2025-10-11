#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "parser.h"

// Вычисление значения постфиксного выражения
double evaluate_postfix(Token* postfix, int count, double x);

#endif // EVALUATOR_H
