#include "Object.h"


Object::Object(QSize size, QImage front_image, QImage back_image)
{
	this->size = size;
	this->front_image = front_image;
	this->back_image = back_image;
}


Object::~Object()
{
}
Deck::Deck(bool backside, QPointF position) {
	this->backside = backside;
	this->position = position;
}
void Deck::append(Object * obj, int count) {
	if (count == 1) {
		objects.append(obj);
	}
	else if (count > 1) {
		Object * other_objs = (Object *)malloc(sizeof(Object)*(count - 1));
		for (int i = 0; i < count - 1; i++) {
			objects.append(other_objs++);
		}
	}
}