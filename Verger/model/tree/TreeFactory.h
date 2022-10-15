#pragma once
#include <map>

#include "Tree.h"

const std::map<TreeType, std::string> TREE_TO_STRING = {
	{TreeType::APPLE, "Apple"},
	{TreeType::PEAR, "Pear"},
	{TreeType::CHERRY, "Cherry"}
};

namespace TreeFactory
{
	Tree GetTree(TreeType type);
	std::string GetTreeName(TreeType type);
	std::vector<TreeData> GetTreeData();	
};

