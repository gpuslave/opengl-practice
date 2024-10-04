#pragma once

class Figure
{
public:
	explicit Figure(int size, int offsetX, int offsetY);
	~Figure() = default;

	virtual void draw() = 0;
	virtual bool isInnerPoint(int x, int y) = 0;

	void moveTo(int x, int y);
	void move(int x, int y);

	void startDragging(int x, int y);
	void drag(int x, int y);
	bool isDragging() const;
	void stopDragging(int x, int y);

private:
	bool m_isDragging;
	int m_previousX;
	int m_previousY;

protected:
	int m_size;
	int m_offsetX;
	int m_offsetY;
};
