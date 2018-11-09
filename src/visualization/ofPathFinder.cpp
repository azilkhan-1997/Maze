#include "ofPathFinder.h"
#include "ofxTweener.h"

void ofPathFinder::setup(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze)
{
	// ��� �������������� ������������� ������ ��� ����� ���������� ��������
	Tweener.removeAllTweens();
	is_animated_ = false;
	is_runed_ = false;
	// �������� ������������� �������� ������
	init(start_position, maze);
	// �������������� ��������� �������� ����������
	screen_x_ = current_position_.X;
	screen_y_ = current_position_.Y;
}

void ofPathFinder::update()
{
	// ���� �� ������� - �� ������ �� ������
	if (!is_runed_) return;
	// ���� ������� � ��� �������� �� ����� - ������ �� ������
	if (is_win_) return;
	// ���� ��� �� �������� �� ������, ������� � ����������, �� ������ ��������� ���
	if (!is_animated_)
		nextStep();
}

void ofPathFinder::draw()
{
	// ��������� ��������
	if (maze_ == nullptr) return;	
	// ������� ����� �������� ��� ���������� ����� ������
	ofSetHexColor(0x33555555);
	for (auto& pos : map_)
		ofDrawRectangle(pos.first.X, pos.first.Y, 1, 1);
	// ������ ������� ������� ���������� ����
	ofSetHexColor(0x5500FF00);
	for (auto& pos : short_way_)
		ofDrawRectangle(pos.X, pos.Y, 1, 1);
	// � ������� �������� ������ "������"
	ofSetHexColor(0x77FF0000);
	ofDrawRectangle(screen_x_, screen_y_, 1, 1);
}

void ofPathFinder::run()
{
	// ��������� ������
	is_runed_ = true;
}

void ofPathFinder::nextStep()
{
	// ���������� ������� ��������� ������
	screen_x_ = current_position_.X;
	screen_y_ = current_position_.Y;
	// ������� callback, ������� ����� ���������� ��� ��������� ��������
	auto callback = std::bind(&ofPathFinder::endAnimation, this, std::placeholders::_1);
	// ������� ������� ����� ��� ���������� ���������� ����
	PathFinder::nextStep();
	// � ��������� ����������� ������
	if (is_win_)
	{
		Tweener.addTween(screen_x_, static_cast<float>(current_position_.X), /* ������������ �������� */0.1F, &ofxTransitions::linear);
		Tweener.addTween(screen_y_, static_cast<float>(current_position_.Y), /* ������������ �������� */0.1F, &ofxTransitions::linear);
	} else
	{
		Tweener.addTween(screen_x_, static_cast<float>(current_position_.X), /* ������������ �������� */0.1F, &ofxTransitions::linear, callback);
		Tweener.addTween(screen_y_, static_cast<float>(current_position_.Y), /* ������������ �������� */0.1F, &ofxTransitions::linear, callback);
	}
}
