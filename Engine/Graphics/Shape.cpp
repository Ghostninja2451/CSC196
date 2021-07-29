#include "Shape.h"
#include <fstream>

void henry::Shape::Draw(Core::Graphics& graphics, const Vector2& position, float angle, float scale)
{
	graphics.SetColor(color);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		henry::Vector2 p1 = position + (Vector2::Rotate(points[i], angle) * scale);// + henry::Vector2{ rand() % 5,rand() % 5 };
		henry::Vector2 p2 = position + (Vector2::Rotate(points[i + 1], angle) * scale);// + henry::Vector2{ rand() % 5,rand() % 5 };

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void henry::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(color);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		//henry::Vector2 p1 = transform.position + (Vector2::Rotate(points[i], transform.rotation) * transform.scale);// + henry::Vector2{ rand() % 5,rand() % 5 };
		//henry::Vector2 p2 = transform.position + (Vector2::Rotate(points[i + 1], transform.rotation) * transform.scale);// + henry::Vector2{ rand() % 5,rand() % 5 };
		henry::Vector2 p1 = transform.matrix * points[i];
		henry::Vector2 p2 = transform.matrix * points[i+1];

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

bool henry::Shape::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		stream >> color;

		std::string line;
		std::getline(stream, line);
		size_t size = std::stoi(line);
		// read points
		for (size_t i = 0; i < size; i++)
		{
			henry::Vector2 point;
			stream >> point;

			points.push_back(point);
		}

		ComputeRadius();

	}


	return success;
}

void henry::Shape::ComputeRadius()
{
	for (auto& point : points)
	{
		radius = std::max(radius, point.Length());

	}

}