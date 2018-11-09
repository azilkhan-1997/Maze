// Position2D.h
#pragma once

struct Position2D
{
	unsigned X;
	unsigned Y;

	// ������������� "operator < "
	// ��� ���������� ��� ����������� ������������� ���� ��������� � �������� ����� ��� std::map
	bool operator < (const Position2D &p1) const
	{
		if (Y < p1.Y)
			return true;
		if (Y > p1.Y)
			return false;
		if (Y == p1.Y)
			return X < p1.X;
		return false;
	}
};
