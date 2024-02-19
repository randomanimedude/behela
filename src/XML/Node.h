#pragma once
#include "NodeAttribute.h"
#include <map>
#include <string>
#include <memory>
#include <vector>

namespace XML
{
	class Node
	{
	public:
		Node(std::string tag);

		void AddStringAttribute(std::string name, std::string value);
		std::string GetAttributeString(std::string name);

		template<typename T>
		void AddNumberAttribute(std::string name, T value)
		{
			if (_attributes.count(name) > 0) {
				_attributes.erase(name);
			}
			_attributes.emplace(name, std::make_unique<NumberNodeAttribute<T>>(value));
		}

		std::vector<std::shared_ptr<Node>>& GetChildren() noexcept;
		std::weak_ptr<Node> GetChildAt(size_t index) const;
		std::weak_ptr<Node> AddChild(std::string tag);
		std::weak_ptr<Node> AddChild(Node& node);
		size_t GetChildrenCount() const noexcept;

		void BuildNodeString(std::ostringstream& stream, int level = 0) const;

	private:
		void AddIndentation(std::ostringstream& stream, int level) const;

	private:
		std::string _tag;
		std::map<std::string, std::shared_ptr<NodeAttributeBase>> _attributes;
		std::vector<std::shared_ptr<Node>> _children;
	};
}
