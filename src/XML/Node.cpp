#include "Node.h"
#include <sstream>


namespace XML
{
	Node::Node(std::string tag)
		: _tag(tag)
	{
	}

	void Node::AddStringAttribute(std::string name, std::string value)
	{
		if (_attributes.count(name) > 0) {
			_attributes.erase(name);
		}
		_attributes.emplace(name, std::make_unique<StringNodeAttribute>(value));
	}

	std::string Node::GetAttributeString(std::string name)
	{
		if (_attributes.count(name) == 0) {
			return _attributes[name]->GetDataString();
		}
	}

	std::vector<std::shared_ptr<Node>>& Node::GetChildren() noexcept
	{
		return _children;
	}

	std::weak_ptr<Node> Node::GetChildAt(size_t index) const
	{
		if (index > _children.size()) {
			return {};
		}
		return _children[index];
	}

	std::weak_ptr<Node> Node::AddChild(std::string tag)
	{
		_children.emplace_back(std::make_shared<Node>(tag));
		return _children.back();
	}

	std::weak_ptr<Node> Node::AddChild(Node& node)
	{
		_children.emplace_back(std::make_shared<Node>(node));
		return _children.back();
	}

	size_t Node::GetChildrenCount() const noexcept
	{
		return _children.size();
	}

	void Node::BuildNodeString(std::ostringstream& stream, int level/* = 0*/) const
	{
		AddIndentation(stream, level);

		stream << '<' << _tag;
		for (const auto& [attributeName, attribute] : _attributes) {
			stream << ' ' << attributeName << "=\"" << attribute->GetDataString() << '"';
		}

		if (_children.size() == 0) {
			stream << " />\n";
		}
		else {
			stream << ">\n";

			for (const auto& child : _children) {
				child->BuildNodeString(stream, level + 1);
			}

			AddIndentation(stream, level);
			stream << "</" << _tag << ">\n";
		}
	}

	void Node::AddIndentation(std::ostringstream& stream, int level) const
	{
		for (int i = 0; i < level; ++i) {
			stream << '\t';
		}
	}
}
