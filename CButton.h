#pragma once

#include <string>
class CButton {
private:
	std::string m_Name;

public:
	explicit CButton(const std::string& name) : m_Name(name) { }
	std::string GetName() const { return m_Name; }
};