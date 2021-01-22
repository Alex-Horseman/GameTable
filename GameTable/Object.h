#pragma once
# include <QSize>
# include <QPointF>
# include <QImage>
#include <QVector>




class Object
{
public:
	static int OBJECT_ID_ITERATOR;
	int id;
	QSize size;
	QImage front_image;
	QImage back_image;
	bool visible; // ��������ʱ����������Ƿ�ɼ�
public:
	Object(QSize size, QImage front_image, QImage back_image);
	~Object();
	Object* copy_with_new_id();
};



class Deck {
public:
	static int DECK_ID_ITERATOR;
	int id;
	int chosen_id; // �����ѡ�� Ψһ
	QVector<int> over_id; //������������û����
	bool backside;
	QPointF position;
	QVector<Object *> objects;
public:
	Deck(bool backside = true, QPointF position = QPointF(0, 0));
	void append(Object * obj, int count);
};