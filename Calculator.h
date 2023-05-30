#pragma once
#include "CButton.h"
#include <imgui.h>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <functional>
#include <iostream>

namespace Calculator {
	class Calc {
	private:
		std::vector<std::shared_ptr<CButton>> m_NumberButtons;
		std::vector<std::shared_ptr<CButton>> m_ToolButtons;
		std::string m_Expression;

	public:
		explicit Calc(std::string  expression);
        double Evaluate() const;
		std::string GetExpression() const { return m_Expression; }
		std::vector<std::shared_ptr<CButton>> GetNumberButtons() const { return m_NumberButtons; }
		std::vector<std::shared_ptr<CButton>> GetToolButtons() const { return m_ToolButtons; }

		static void ShowButtons(std::vector<std::shared_ptr<CButton>> buttons, const std::function<void(std::shared_ptr<CButton> t)>& pressedFunc);
		void SetExpression(std::string expression) { m_Expression = std::move(expression); }
		void AddExpression(const std::string& expression);
	};
	void Render(Calc& calc);
}