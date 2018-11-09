// PathFinder.cpp
#include "PathFinder.h"

PathFinder::PathFinder() { }

PathFinder::~PathFinder() { }

void PathFinder::init(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze)
{
	// ������� ������� ����������� 
	map_.clear();
	short_way_.clear();
	// ���������� �������� ��� �������� ������� ����
	maze_ = maze;
	// �� ������ �� ��� �� ����� ����� ������
	is_win_ = false;
	// 1. ������� ��������� ������� � ����������� ������.
	// ��������� ������� ����� ������ � ������� ������ ������ �������� ���� ���������
	current_position_ = start_position;
	// � ��������� ����������� ����� ����� "�������" (�� ������)
	current_direction_ = RIGHT;	
}

void PathFinder::nextStep()
{
	// ���� �� ��� ��������� �� ����� ������, �� �� ����� ������ ������ �������������� ����
	if (is_win_) return;

	// 2. ���������� ���������� ������� ������, � ������ ������� ��������� �����
	map_[current_position_] = true;
	short_way_.push_back(current_position_);

	// 3. ����� �������������� �� 90 �������� **������ ������� �������**
	current_direction_ = current_direction_ == UP ? LEFT : current_direction_ == LEFT ? DOWN : current_direction_ == DOWN ? RIGHT : UP;
	// �������������� ��������� ���������� ��� �������� ������� ������� ������
	Position2D forward_cell;
	do {
		// 4. ����� ��������� ������, ������� ���������� ����� ��� :
		forward_cell = current_position_;
		switch (current_direction_) 
		{ 
			case RIGHT: forward_cell.X++; break;
			case DOWN: forward_cell.Y++; break;
			case LEFT: forward_cell.X--; break;
			case UP: forward_cell.Y--; break;
		}
		// 4.1. ���� ��� ����� :
			// * ����� �������������� �� 90 �������� **�� ������� �������**
		current_direction_ = current_direction_ == UP ? RIGHT : current_direction_ == LEFT ? UP : current_direction_ == DOWN ? LEFT : DOWN;
			// * ����� ��������� _��� 4_
	} while (maze_.get()->at(forward_cell.Y).at(forward_cell.X) == '#');

	// 4.2. ���� ��� ��������� ������ :
		// * ����� ��������� _��� 5_
	// ���������� ���������� �����������
	current_direction_ = current_direction_ == UP ? LEFT : current_direction_ == LEFT ? DOWN : current_direction_ == DOWN ? RIGHT : UP;
	
	// 5. ����� ��������� �� ����� ��������� ������
	current_position_ = forward_cell;
	// 6. �� ������� ���� ���������� ����� �����, ��������� ��� ����� � ���� ����� ������ ��� ��� :
	auto foundedIter = map_.find(forward_cell);
	// 6.1. ���� ����� ��� � ���� ������ :
	if (foundedIter != map_.end())
	{
		// * ������� �� ������� ���������� ����� ��� ������, ������� � ���������, �� ��������� ������� ������ 
		if (!short_way_.empty()) {
			while ((!short_way_.empty()) && ((short_way_.back().X != foundedIter->first.X) || (short_way_.back().Y != foundedIter->first.Y)))
			{
				short_way_.erase(--short_way_.end());
			}
			// **������������**
			if (!short_way_.empty()) {
				short_way_.erase(--short_way_.end());
			}
		}
		// * ��������� � _���� 7_
	}
	// 6.2. ���� ����� �� ��� ����� � ���� ������, �� ����� ��������� � _���� 7_
	// 7. ���������, �������� �� ������� ������ `������ ������`:
	// 7.1. ���� ��� �� �������� `������ ������`, �� ��������� � _���� 2_
	// 7.2. ���� ��� `����� ������`, �� _����������� ��������_.	
	is_win_ = maze_.get()->at(current_position_.Y).at(current_position_.X) == 'X';
}
