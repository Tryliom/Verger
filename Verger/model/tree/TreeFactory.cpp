#include "TreeFactory.h"

Tree TreeFactory::GetTree(const TreeType type)
{
	if (type == TreeType::CHERRY)
	{
		return CherryTree();
	}
	
	if (type == TreeType::APPLE)
	{
		return AppleTree();
	}
	
	if (type == TreeType::PEAR)
	{
		return PearTree();
	}

	return PearTree();
}

std::string TreeFactory::GetTreeName(const TreeType type)
{
	return TREE_TO_STRING.at(type);
}

std::vector<TreeData> TreeFactory::GetTreeData()
{
	std::vector<TreeData> treeData;
	float maxTotalWeight = 0;

	for (int i = 0; i < static_cast<int>(TreeType::END); i++)
	{
		const auto type = static_cast<TreeType>(i);
		const auto tree = GetTree(type);
		const auto data = tree.GetData();
		treeData.push_back(data);

		if (data.MaxTotalWeight > maxTotalWeight)
		{
			maxTotalWeight = data.MaxTotalWeight;
		}
	}

	for (auto& data : treeData)
	{
		data.MaxTotalWeight /= maxTotalWeight;
		data.MinTotalWeight /= maxTotalWeight;
	}

	return treeData;
}
