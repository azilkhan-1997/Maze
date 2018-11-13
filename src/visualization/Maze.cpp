#include "Maze.h"
#include "MazeGenerator.h"
#include "ofMesh.h"
#include "ofBitmapFont.h"
#include "ofxTweener.h"

void Maze::setup(int width, int height)
{
	alpha_ = 0.0f;

	// ���� ����� �������� ��� ��� ������
	if (maze_ != nullptr)
		// �� ���������� ������� ���������
		maze_.reset();
	// ���������� ����� ��������
	maze_ = MazeGenerator::generate(width, height);

	// ������� � �������� "����� ������" � ������ ������ ���� �������� ������� ����
	maze_.get()->at(maze_.get()->size() - 2).at(maze_.get()->at(0).size() - 2) = 'X';
	
	// ������������� ������
	player_.setup(Position2D{ 1, 1 }, maze_);

	// �������� �������� � ������ ������
	show_in_center();
}

void Maze::update()
{
	// ���������� 
	player_.update();
}

void Maze::draw()
{
	// ���������, ������ �� ��������
	if (maze_ == nullptr)
		return;
	// �������� ����������� ������� ����������������� �����
	ofPushMatrix();
	// ������� ����� �� ����������� ��������
	ofTranslate(pos_x_, pos_y_);
	// �������� ������ ��������� ����������� �� ������������ ������� �������
	ofScale(scale_, scale_);
	// ������� ����� ��� ����� ���������� ����-������� ������
	//ofSetHexColor(0x777777FF);
	ofSetColor(128, 128, 255, alpha_ / 2);
	// �������� ��� � ���� ��������������
	ofDrawRectangle(0, 0, maze_.get()->at(0).size(), maze_.get()->size());
	// ������� ������ ���� ��� ����
	//ofSetHexColor(0x000000);
	ofSetColor(0, 0, 0, alpha_);
	// � �������� �� ������� � ����������
	for (size_t i = 0; i < maze_.get()->size(); ++i)
		for (size_t j = 0; j < maze_.get()->at(0).size(); j++)
			if (maze_.get()->at(i).at(j) == '#')
				// ����������� ��� ���� �����
				ofDrawRectangle(j, i, 1, 1);
	// �������� ����� ������
	if (maze_.get()->at(maze_.get()->size() - 2).at(maze_.get()->at(0).size() - 2) == 'X')
	{
		// ������� ������� ����
		//ofSetHexColor(0xFF00FF00);
		ofSetColor(0, 255, 0, alpha_);
		// �������� ����� ������
		ofDrawRectRounded(maze_.get()->at(0).size() - 2, maze_.get()->size() - 2, 1, 1, 0.3);
	}

	// ��������� ������ (������ ��� ������ ���� �� ���� ��� �� ������� ofPopMatrix)
	player_.draw();

	// ������ ������� ����������������� ����� � ����������� ���������
	ofPopMatrix();

	// � ��������� � ����� ����, ������� ����� ofPopMatrix
	if (player_.isWin())
	{
		std::stringstream reportStr;
		reportStr << "Short way FOUNDED! Need " << player_.getShortWayLenght() << " steps";
		ofDrawBitmapStringHighlight(reportStr.str(), 100, ofGetWindowHeight() - 100, ofColor::orangeRed, ofColor::black);
	}
}

void Maze::show_in_center()
{
	// ���������, ������ �� ��������
	if (maze_ == nullptr)
		return;
	// �������� ������� ����
	auto w = ofGetWindowWidth();
	auto h = ofGetWindowHeight();
	// ������� ����������� ����������� �������� ���� � �������� ������� �� ����������� � ��������� ��������������
	auto k = static_cast<float>(w) / maze_.get()->at(0).size();
	auto kh = static_cast<float>(h) / maze_.get()->size();
	// �������� ����������� � ����������� �� ����, ����� ����������� ������
	k = k < kh ? k : kh;
	// ������� ������� ������ 75% �� ������� ������, ����� ����������� ���� �� �� ����� �����
	scale_ = k * 0.75;
	// � ������� � ������ � ����������� �� ��������
	pos_x_ = (w - maze_.get()->at(0).size() * scale_) / 2;
	pos_y_ = (h - maze_.get()->size() * scale_) / 2;
}

void Maze::setTransparency(int new_alpha, float delay)
{
	Tweener.addTween(alpha_, new_alpha, delay);
}

void Maze::setAlpha(float new_alpha)
{
	alpha_ = new_alpha;
}

void Maze::windowResized(int w, int h)
{
	show_in_center();
}

void Maze::keyPressed(int key)
{
}

void Maze::keyReleased(int key)
{
}

void Maze::mouseDragged(int x, int y, int button)
{
	// ��� �������� ���� � ������� �������, ������� ����������� �� �������� ����
	pos_x_ -= last_mouse_pos_x_ - x;
	pos_y_ -= last_mouse_pos_y_ - y;
	// � ����� ���������� ������������ ����
	mousePressed(x, y, button);
}

void Maze::mousePressed(int x, int y, int button)
{
	// ���������� ������������ ���� ��� ������� �� ������
	last_mouse_pos_x_ = x;
	last_mouse_pos_y_ = y;
}

void Maze::mouseReleased(int x, int y, int button)
{
}

void Maze::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	// ���� ������ ������������� � ���������� �������� ����� ������ �������
	if ((scrollY < 0) && (scale_ * 0.9 <= 1.0))
		// �� ������ �� ������
		return;
	// ����� ������� ������� ����� �������� ���� � ��������� ��������� � ����� �� �������, ����� ���������� �������� ��� ��������
	auto deltaX = static_cast<double>(x - pos_x_) / scale_;
	auto deltaY = static_cast<double>(y - pos_y_) / scale_;
	// ������� ����������� � 10/9 � ������ �������������� ������� � � 0.9 � ������ ��������������
	scale_ *= scrollY < 0 ? 0.9 : 10.0 / 9.0;
	// ����������� �������� � ����� ���������
	pos_x_ = x - deltaX * scale_;
	pos_y_ = y - deltaY * scale_;
}
