#pragma once
#include<string>
#include<memory>
#include <iostream>

namespace Expression {
    struct ExpressionTree {
        std::string m_Value;
        std::shared_ptr<ExpressionTree> m_Left;
        std::shared_ptr<ExpressionTree> m_Right;

        ExpressionTree() : m_Value(), m_Left(nullptr), m_Right(nullptr) { }
        ExpressionTree(std::shared_ptr<ExpressionTree> expressionTree) : m_Value(expressionTree->m_Value),
                                                                        m_Left(expressionTree->m_Left),
                                                                        m_Right(expressionTree->m_Right) {}

        std::shared_ptr<ExpressionTree> GetLeft() const { return m_Left; }
        std::shared_ptr<ExpressionTree> GetRight() const { return m_Right; }
    };

	class Expression {
	private:
        std::string m_Expression;
        std::shared_ptr<ExpressionTree> m_ExpressionTree;

	public:
		explicit Expression(const std::string& expression) : m_Expression(expression) {
            m_ExpressionTree  = std::make_shared<ExpressionTree>();
            m_ExpressionTree = std::make_shared<ExpressionTree>(BuildTree(expression, m_ExpressionTree));
		}

		Expression() : m_ExpressionTree() { }
        friend std::ostream& operator<<(std::ostream& os, const ExpressionTree& tree);
        std::string GetExpression();
        double Evaluate() const;

    private:
        static size_t getOperatorPos(const std::string& expression) ;
        double EvaluateR(std::shared_ptr<ExpressionTree> tree) const;
        std::shared_ptr<ExpressionTree> BuildTree(const std::string& expression, std::shared_ptr<ExpressionTree> tree);
        static std::string getValuesR(std::shared_ptr<ExpressionTree> tree);
    };
}