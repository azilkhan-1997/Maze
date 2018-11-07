#pragma once
#include <vector>
#include <memory>

class MazeGenerator
{
public:
	static std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height)
	{
		// �������� ����������� ���������� �� 0
		if ((width < 1) || (height < 1))
			return nullptr;

		auto top_limit = std::numeric_limits<unsigned>::max();
		// �������� ����������� �� ������������� ����������� �������
		if (((top_limit - 1) / 2 <= width) || ((top_limit - 1) / 2 <= height))
			return nullptr;

		// �������������� ������ �������� ������� maze
		// ������ ����� ������������ �� ���� ��������� 2x2 + 1 ���� �������� ������ � ����� ��� ����
		unsigned output_height = height * 2 + 1;
		unsigned output_width = width * 2 + 1;
		// �������������� ��������� �� �������� � �������������� ��� ������ ���������
		auto maze = std::make_shared<std::vector<std::vector<char>>>(std::vector<std::vector<char>> {});
		// ������������� ������ ��������� �� ������
		maze.get()->reserve(output_height);

		// ...

		// ������ ��������� �� ���������� ��������
		return maze;
	}

private:
	MazeGenerator() { }
};
