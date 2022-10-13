#include "TreeFactory.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

Tree TreeFactory::GetRandomTree()
{
	switch (Random::GetInt(0, 2))
	{
	case 0:
		return AppleTree();
	case 1:
		return PearTree();
	case 2:
		return CherryTree();
	default:
		return AppleTree();
	}
}
