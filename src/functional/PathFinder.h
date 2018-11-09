// PathFinder.h
#pragma once

#include "Position2D.h"
#include "Direction2D.h"
#include <vector>
#include <map>
#include <memory>

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	// ����� ��� ������������� ������
	void init(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze);	
	// ����� ��� ���������� ���� ������
	virtual void nextStep();

	// ����� ��� ��������� ���������� ���������� ����� ���������
	unsigned getCountVisitedCells() { return map_.size() + 1; }
	// ����� ��� ��������� ������ ����������� ���� (� �������� ������ ���� - �� ����� ���� �� �����������)
	unsigned getShortWayLenght() { return short_way_.size() + 1; }
	// �����, ����� ��������, �������� �� ����� �� ����� ������
	bool isWin() { return is_win_; }

protected:
	bool is_win_;	// ����, ������� ����������, �������� �� ����� �� ����� ������

	Position2D current_position_;							// ������� ������� ������
	Direction2D current_direction_;							// ������� ����������� ������

	std::map<Position2D, bool> map_;						// ��� ���������� ������. ����������� "�����"
	std::vector<Position2D> short_way_;						// ������, ������� ����� ������� ���������� ������ ����������� ����
	
	std::shared_ptr<std::vector<std::vector<char>>> maze_;	// ��������� �� ��������, �� �������� �� ����� �������������
};
