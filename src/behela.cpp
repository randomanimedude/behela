#include <sstream>
#include <fstream>
#include "XML/Node.h"

int main()
{
	XML::Node node("a");
	XML::Node node2("b");
	XML::Node node3("c");


	int g = 2;
	std::string g2 = "2";
	node.AddNumberAttribute("two_int", g);
	node2.AddNumberAttribute("five_int", 5);
	node3.AddNumberAttribute("five_float", 5.5f);
	node.AddStringAttribute("five_str", "5.5f");
	node2.AddStringAttribute("two_str", g2);

	node2.AddChild(node3);
	node.AddChild(node2);

	std::ostringstream stream;
	node.BuildNodeString(stream);
	std::ofstream of("out.txt");
	of << stream.str();
	of.close();
}
