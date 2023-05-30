#include "Expression.h"

#include <algorithm>
#include <memory>
#include <iostream>
#include <string>

namespace Expression {
	/*
    Old Implementation

    std::string reversed(std::string source) {
		std::reverse(source.begin(), source.end());
		return source;
	}

    std::shared_ptr<ExpressionTree> Expression::BuildTreeSum(const std::string& expression) {
		if (expression.length() <= 2) {
			m_Value = expression;
			m_Left = std::make_shared<ExpressionTree>();
            m_Left.reset();
			m_Right = std::make_shared<ExpressionTree>();
            m_Right.reset();
			return this;
		}
		std::string leftS;
		std::string rightS = reversed(expression);
		bool foundOperation = false;
		for (char start : expression) {
			if (start == '+' || start == '-') {
                foundOperation = true;
                rightS.pop_back();
				std::string reversed_back = reversed(rightS);
				m_Value = start;
				this->m_Left = std::make_shared<ExpressionTree>(leftS);
                this->m_Right = std::make_shared<ExpressionTree>(reversed_back);
			}
			else {
				leftS += start;
				rightS.pop_back();
			}
		}
        if(!foundOperation) {
            m_Value = leftS;
            m_Left = std::make_shared<ExpressionTree>();
            m_Left.reset();
            m_Right = std::make_shared<ExpressionTree>();
            m_Right.reset();
        }
        return this;
	}

    std::shared_ptr<ExpressionTree> Expression::BuildTreeMult(ExpressionTree* tree) {
        if(tree == nullptr) {
            return nullptr;
        }
        std::string leftS;
        std::string rightS = reversed(tree->m_Value);
        bool foundOperation = false;
        for (auto c : tree->m_Value) {
            if(c == '-' || c == '+') foundOperation = true;
            if(c == '*' || c == '/') {
                foundOperation = true;
                rightS.pop_back();
                std::string reversed_back = reversed(rightS);
                m_Value = c;
                tree->m_Left = std::make_shared<ExpressionTree>(leftS);
                tree->m_Right = std::make_shared<ExpressionTree>(reversed_back);
            } else {
                leftS += c;
                rightS.pop_back();
            }
        }
        if(!foundOperation) {
            tree->m_Value = leftS;
            tree->m_Left = std::make_shared<ExpressionTree>();
            tree->m_Left.reset();
            tree->m_Right = std::make_shared<ExpressionTree>();
            tree->m_Right.reset();
        }
        return tree;
    }
     */

    std::shared_ptr<ExpressionTree> Expression::BuildTree(const std::string &expression, std::shared_ptr<ExpressionTree> tree)  {
        size_t operatorPos = getOperatorPos(expression);
        if(operatorPos == std::string::npos) {
            // no operator is present then the current item should be the numbers
            tree-> m_Value = expression;
        }
        else {
            // set sides for tree properties
            std::string op = std::string(1, expression[operatorPos]);
            std::string leftSide = expression.substr(0, operatorPos);
            std::string rightSide = expression.substr(operatorPos + 1, expression.size() - 1);

            tree->m_Value = op;

            //instantiate left and right
            tree->m_Left = std::make_shared<ExpressionTree>();
            tree->m_Right = std::make_shared<ExpressionTree>();

            //recursively call to fill left and right
            tree->m_Left = BuildTree(leftSide, tree->m_Left);
            tree->m_Right = BuildTree(rightSide, tree->m_Right);
        }
        return tree;
    }

    size_t Expression::getOperatorPos(const std::string& expression) {
        size_t pos = expression.find("+");
        pos = pos == std::string::npos ? expression.find("-") : pos;
        pos = pos == std::string::npos ? expression.find("*") : pos;
        pos = pos == std::string::npos ? expression.find("/") : pos;
        return pos;
    }

    std::ostream &operator<<(std::ostream &os, const ExpressionTree &tree) {
        std::shared_ptr<ExpressionTree> ptr = std::make_shared<ExpressionTree>();
        std::string values = Expression::getValuesR(ptr);
        os << values;
        return os;
    }

    std::string Expression::getValuesR(std::shared_ptr<ExpressionTree> tree) {
        if(tree == nullptr) {
            return "";
        }
        std::string values = getValuesR(tree->m_Left) + tree->m_Value;
        values += getValuesR(tree->m_Right);
        return values;
    }

    double Expression::Evaluate() const {
        return EvaluateR(m_ExpressionTree);
    }

    double Expression::EvaluateR(std::shared_ptr<ExpressionTree> tree) const {
        if(tree == nullptr) {
            return 0;
        }
        double result = 0;
        if(tree->m_Value == "+") {
            result = EvaluateR(tree->m_Left) + EvaluateR(tree->m_Right);
        } else if(tree->m_Value == "-") {
            result = EvaluateR(tree->m_Left) - EvaluateR(tree->m_Right);
        } else if(tree->m_Value == "*") {
            result = EvaluateR(tree->m_Left) * EvaluateR(tree->m_Right);
        } else if(tree->m_Value == "/") {
            result = EvaluateR(tree->m_Left) / EvaluateR(tree->m_Right);
        } else {
            char *treeEnd;
            result = std::strtod(tree->m_Value.c_str(), &treeEnd);
        }
        return result;
    }
}