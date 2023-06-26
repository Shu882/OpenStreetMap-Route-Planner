#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y) : m_Model(model)
{
	// Convert inputs to percentage:
	start_x *= 0.01;
	start_y *= 0.01;
	end_x *= 0.01;
	end_y *= 0.01;

	start_node = &m_Model.FindClosestNode(start_x, start_y);
	end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node)
{
	return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node)
{
	current_node->FindNeighbors(); // populate the neighbors vector
	for (auto node : current_node->neighbors)
	{
		node->parent = current_node; // set the parent
		node->h_value = CalculateHValue(node);
		node->g_value = current_node->g_value + current_node->distance(*node);
		open_list.push_back(node);
		node->visited = true;
	}
}

bool Compare(const RouteModel::Node *n1, const RouteModel::Node *n2)
{
	return (n1->g_value + n1->h_value) > (n2->g_value + n2->h_value);
}

RouteModel::Node *RoutePlanner::NextNode()
{
	// sort the list based on sum from high to low
	std::sort(open_list.begin(), open_list.end(), Compare);
	RouteModel::Node *lowSum = open_list.back();
	open_list.pop_back();
	return lowSum;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node)
{
	distance = 0.0f;
	std::vector<RouteModel::Node> path_found;

	while (current_node != start_node)
	{
		path_found.emplace_back(*current_node);
		distance += current_node->distance(*current_node->parent);
		current_node = current_node->parent;
	}
	path_found.push_back(*start_node);
	std::reverse(path_found.begin(), path_found.end());
	distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
	return path_found;
}

void RoutePlanner::AStarSearch()
{
	RouteModel::Node *current_node = nullptr;

	start_node->visited = true;
	open_list.push_back(start_node);
	while (current_node != end_node && !open_list.empty())
	{
		current_node = NextNode();
		if (current_node == end_node)
		{
			m_Model.path = ConstructFinalPath(current_node);
			return;
		}
		AddNeighbors(current_node);
	}
}