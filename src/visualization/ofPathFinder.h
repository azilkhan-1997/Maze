// ofPathFinder.h
#pragma once

#include "PathFinder.h"

class ofPathFinder : public PathFinder
{
public:
	void setup(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze);
	void update();
	void draw();
	void run();

	void endAnimation(float *arg) { is_animated_ = false; }	// Callback �������, ������� ����� �����������, ����� �������� �������������

	void nextStep() override;
private:
	bool is_animated_;	// ���� ��� ������������ ���������, ���������� �� ������ � �������� �������� (����������� ����� ��������)
	bool is_runed_;		// ���� ��� �����������, ������� ����� ��� ��� (� �������� �� �� ������)
	float screen_x_;	// �������� ���������� X
	float screen_y_;	// �������� ���������� Y
};

