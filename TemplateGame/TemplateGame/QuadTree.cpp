#include "QuadTree.h"



QuadTree::QuadTree()
{

}

QuadTree::QuadTree(int nodeLevel, RECT* mapBoundary) {
	this->nodeLevel = nodeLevel;
	this->mapBoundary = mapBoundary;
	this->vectorObject = new vector<Object*>();
	this->quadNodes = new QuadTree*[4];

	this->topLeftRect = new RECT();
	this->topRightRect = new RECT();
	this->bottomLeftRect = new RECT();
	this->bottomRightRect = new RECT();
}

QuadTree::~QuadTree()
{
	delete this->topLeftRect;
	delete this->topRightRect;
	delete this->bottomLeftRect;
	delete this->bottomRightRect;

	delete this->vectorObject;
}

// Xóa tất cả các node trong quadtree
void QuadTree::ClearQuadTree()
{
	if (this->quadNodes) {
		for (int i = 0; i < 4; i++) {
			this->quadNodes[i]->ClearQuadTree();
			delete this->quadNodes[i];
		}
	}

	this->vectorObject->clear();
}

// Chia Quadtree ra làm 4 phần

//   II     |   I
//   III    |   IV
void QuadTree::SplitQuadTree()
{

	long left = mapBoundary->left;
	long top = mapBoundary->top;
	long right = mapBoundary->right;
	long bottom = mapBoundary->bottom;
	long subRight = (right - left) / 2;
	long subBottom = (bottom - top) / 2;

	// II
	this->topLeftRect->left = left;
	this->topLeftRect->right = subRight;
	this->topLeftRect->top = top;
	this->topLeftRect->bottom = subBottom;

	// I
	this->topRightRect->left = subRight;
	this->topRightRect->right = right;
	this->topRightRect->top = top;
	this->topRightRect->bottom = subBottom;

	// III
	this->bottomLeftRect->left = left;
	this->bottomLeftRect->right = subRight;
	this->bottomLeftRect->top = subBottom;
	this->bottomLeftRect->bottom = bottom;

	// IV
	this->bottomRightRect->left = subRight;
	this->bottomRightRect->right = right;
	this->bottomRightRect->top = subBottom;
	this->bottomRightRect->bottom = bottom;

	this->quadNodes[0] = new QuadTree(this->nodeLevel + 1, this->topRightRect);
	this->quadNodes[1] = new QuadTree(this->nodeLevel + 1, this->topLeftRect);
	this->quadNodes[2] = new QuadTree(this->nodeLevel + 1, this->bottomLeftRect);
	this->quadNodes[3] = new QuadTree(this->nodeLevel + 1, this->bottomRightRect);
}

void QuadTree::Insert(Object * obj)
{
	if (this->quadNodes[0] != nullptr) {
		int index = this->GetIndex(obj);

		if (index != -1) {
			this->quadNodes[index]->Insert(obj);
			return;
		}
	}

	this->vectorObject->push_back(obj);

	if (this->vectorObject->size() > QUADTREE_MAX_OBJECTS && this->nodeLevel < QUADTREE_MAX_LEVELS) {
		if (this->quadNodes[0] == nullptr) {
			this->SplitQuadTree();
		}

		int i = 0;

		while (i < this->vectorObject->size()) {
			Object* tempObj = this->vectorObject->at(i);

			int index = this->GetIndex(tempObj);
			if (index != -1) {
				this->quadNodes[index]->Insert(tempObj);
				this->vectorObject->erase(this->vectorObject->begin() + i);
			}
			else {
				i++;
			}
		}
	}
}

// Hàm lấy ra tất cả các Objects có khả năng va chạm với Object cần xét
void QuadTree::Retrieve(vector<Object*>* returnObjects, Object * obj)
{
	int index = this->GetIndex(obj);
	if (index != -1 && this->quadNodes[0] != nullptr) {
		this->quadNodes[index]->Retrieve(returnObjects, obj);
	}

	for (int i = 0; i < this->vectorObject->size(); i++) {
		returnObjects->push_back(this->vectorObject->at(i));
	}
}

// Cái hàm này dùng để xác định Object đang nằm ở node nào của QuadTree
// -1 nghĩa là nó không (completely fit) của node con nhưng bản chất nó vẫn là 1 phần của node cha
int QuadTree::GetIndex(Object * obj)
{
	int index = -1;

	long verticalMidPoint = (mapBoundary->right - mapBoundary->left) / 2;
	long horizontalMidPoint = (mapBoundary->bottom - mapBoundary->top) / 2;

	// Kiểm tra Object có nằm hẳn (completely fit) ở ô phía trên hay không
	bool topQuadrant = obj->GetCurPos()->GetPosY() < horizontalMidPoint && obj->GetCurPos()->GetPosY() + obj->GetObjectHeight() < horizontalMidPoint;

	// Kiểm tra Object có nằm hẳn (completely fit) ở ô phía dưới hay không
	bool bottomQuadrant = obj->GetCurPos()->GetPosY() > horizontalMidPoint;

	// Kiểm tra Object có nằm hẳn ở bên trái qua không
	if (obj->GetCurPos()->GetPosX() < verticalMidPoint && obj->GetCurPos()->GetPosX() + obj->GetObjectWidth() < verticalMidPoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Kiểm tra Object có nằm hẳn ở bên phải qua không 
	else if (obj->GetCurPos()->GetPosX() > verticalMidPoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant)
			index = 3;
	}

	return index;
}
