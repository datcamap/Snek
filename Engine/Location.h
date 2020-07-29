#pragma once

class Location
{
public:
	void Add(const Location& delta_location)
	{
		x += delta_location.x;
		y += delta_location.y;
	}
	bool operator==(const Location& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}
	bool operator!=(const Location& rhs)
	{
		return (x != rhs.x || y != rhs.y);
	}
	int x;
	int y;
};