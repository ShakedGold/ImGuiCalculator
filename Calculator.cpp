#include "Calculator.h"
#include "CButton.h"
#include "Expression.h"


#include <imgui_internal.h>
#include <imgui.h>
#include <string>

namespace Calculator {
	double Calc::Evaluate() const {
		std::shared_ptr<Expression::Expression> expressionTree = std::make_shared<Expression::Expression>(m_Expression);
        return expressionTree->Evaluate();
	}

	Calc::Calc(std::string expression) : m_Expression(std::move(expression)) {
		for (int i = 1; i <= 9; i++) {
			m_NumberButtons.push_back(std::make_shared<CButton>(std::to_string(i)));
		}

		m_ToolButtons = { std::make_shared<CButton>("+"), std::make_shared<CButton>("-"), std::make_shared<CButton>("*"), std::make_shared<CButton>("/"), std::make_shared<CButton>("D"), std::make_shared<CButton>("C") };
	}

    void Calc::AddExpression(const std::string &expression) {
        m_Expression += expression;
        if (m_Expression.find('C') != std::string::npos) {
            m_Expression = "";
        }
        else if(m_Expression.find('D') != std::string::npos) {
            //remove first space
            m_Expression.pop_back();
            //remove D
            m_Expression.pop_back();
            //remove second space
            m_Expression.pop_back();
            if(!m_Expression.empty()) {
                //remove number / symbol
                m_Expression.pop_back();
                if(!m_Expression.empty() && m_Expression.back() == ' ') m_Expression.pop_back();
            }
        }
    }

    void Calc::ShowButtons(std::vector<std::shared_ptr<CButton>> buttons,
                           const std::function<void(std::shared_ptr<CButton>)> &pressedFunc)  {
        for (int i = 0; i < buttons.size(); i++) {
            std::string value = buttons[i]->GetName();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.3,.3,.3,1));
            //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.4,.4,.4,1));
            bool didPress = ImGui::Button(value.c_str(),ImVec2{60,60});
            ImGui::PopStyleColor();
            if (didPress) {
                pressedFunc(buttons[i]);
            }
            if((i + 1) % 3) {
                ImGui::SameLine();
            }
        }
    }

    void Render(Calc& calc) {
		ImGui::Begin("Calculator", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

        ImGuiID node;
        ImGui::DockBuilderDockWindow("Calculator", node);
		std::string expr = calc.GetExpression();
        std::string expressionResult = std::to_string(calc.Evaluate());

        int precision = 2;
        char endChar = '\0';
        if(!expr.empty()) {
            char last = expr.back();
            expr.pop_back();
            endChar = expr.empty() ? '\0' : expr.back();
            expr += last;
        }
        bool isOperatorInEndOrStrEmpty = endChar == '+' || endChar == '-' || endChar == '*' || endChar == '/' || expr.empty();
        expressionResult = expressionResult.substr(0, expressionResult.size() - (6 - precision));

        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::PushFont(ImGui::GetIO().FontDefault);
		ImGui::Text("%s%s", expr.c_str(),isOperatorInEndOrStrEmpty ? "" : (" = " + expressionResult).c_str());
        ImGui::PopFont();

		calc.ShowButtons(calc.GetNumberButtons(), [&calc](const std::shared_ptr<CButton>& t) {
			calc.AddExpression(t->GetName());
		});

		calc.ShowButtons(calc.GetToolButtons(), [&calc](const std::shared_ptr<CButton>& t) {
			calc.AddExpression(" " + t->GetName() + " ");
		});

		//ImGui::Text("%s", std::to_string(calc.Evaluate()).c_str());
		ImGui::End();
	}
}