#pragma once
#include <string>

namespace XML
{
	class NodeAttributeBase
	{
	public:
		virtual std::string GetDataString() const = 0;
	};


	template<typename T>
	class NumberNodeAttribute final : public NodeAttributeBase
	{
	public:
		template<typename T>
		NumberNodeAttribute(T&& data) 
			: _data(data)
		{
		}

		virtual std::string GetDataString() const override
		{
			return std::to_string(_data);
		}

	private:
		 const T _data;
	};

	// Deduction guide
	template<typename T>
	NumberNodeAttribute(T&&) -> NumberNodeAttribute<T>;


	class StringNodeAttribute final : public NodeAttributeBase
	{
	public:
		StringNodeAttribute(std::string data);

		virtual std::string GetDataString() const override;

	private:
		 const std::string _data;
	};
}
