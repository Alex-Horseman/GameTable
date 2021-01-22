#include "Object.h"

int Object::OBJECT_ID_ITERATOR;

Object::Object(QSize size, QImage front_image, QImage back_image)
{
	this->id = OBJECT_ID_ITERATOR++;
	this->size = size;
	this->front_image = front_image;
	this->back_image = back_image;
	this->visible = false;
}


Object::~Object()
{

}

Object* Object::copy_with_new_id() {
	return new Object(this->size, this->front_image, this->back_image);
}

int Deck::DECK_ID_ITERATOR = 0;

Deck::Deck(bool backside, QPointF position) {
	this->id = DECK_ID_ITERATOR++;
	this->backside = backside;
	this->position = position;
	this->chosen_id = -1;
}
void Deck::append(Object * obj, int count) {
	if (count == 1) {
		objects.append(obj);
	}
	else if (count > 1) {
		for (int i = 0; i < count - 1; i++) {
			objects.append(obj->copy_with_new_id());
		}
	}
}