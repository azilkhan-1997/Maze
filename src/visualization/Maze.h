// Maze.h
#pragma once

#include <vector>
#include <memory>

class Maze
{
public:
	// ����� ��� ������������� ��������� �������� (������ ������������)
	void setup(int width, int height);
	// ����� ������ ���������� ����� ����������� ������� ����� (������������ ��� ��������)
	void update();
	// ����� ��� ���������� ����� � �����������
	void draw();

	// �����, � ������� �� ����� ������������ ���������� � scale ��� ���������,
	// ����� �� ��������� ����� �� ��� ��������� ��������� �� ������ ������
	void show_in_center();

	// ����������� ��� ������� ������ ����������
	void windowResized(int w, int h);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);

private:
	// ��������� �� ��������������� ��������
	std::shared_ptr<std::vector<std::vector<char>>> maze_;
	// ����������� ���������� ��� ����������� ����������� �� ������
	float scale_ = 0;
	// �������� ����� ��������� ������������ ������ �������� ���� ������
	int pos_x_ = 0;
	int pos_y_ = 0;
	// ��������� �������� ������� ���� 
	// (������������ ��� ����, ����� � ���������� �� ����� "�������" ������ ��������)
	int last_mouse_pos_x_ = 0;
	int last_mouse_pos_y_ = 0;
};

