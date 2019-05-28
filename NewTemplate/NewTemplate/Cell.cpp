#include "Cell.h"



Cell::Cell()
{
	this->objs = NULL;
}


Cell::~Cell()
{
	if (this->objs != NULL) delete this->objs;
}

// Thêm vào đầu dslk đơn
void Cell::Add(Object * obj)
{
	obj->SetPreObj(NULL);
	obj->SetNextObj(this->objs);

	this->objs = obj;

	if (obj->GetNextObj() != NULL) {
		obj->GetNextObj()->SetPreObj(obj);
	}
}

void Cell::Remove(Object * obj)
{

	if (this->objs == NULL || obj == NULL)
		return;

	if (this->objs == obj) {
		this->objs = obj->GetNextObj();
	}

	if (obj->GetPreObj() != NULL) {
		obj->GetPreObj()->SetNextObj(obj->GetNextObj());
	}

	if (obj->GetNextObj() != NULL) {
		obj->GetNextObj()->SetPreObj(obj->GetPreObj());
	}

	obj->SetPreObj(NULL);
	obj->SetNextObj(NULL);
}

void Cell::Delete()
{
	while (this->objs != NULL) {
		Object* temp = this->objs;
		this->objs = this->objs->GetNextObj();

		temp->SetPreObj(NULL);
		temp->SetNextObj(NULL);

		if(temp->GetObjectType() != MAIN_CHARACTER)
			delete temp;
	}
}
