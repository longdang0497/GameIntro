#include "Grid.h"

Grid::Grid()
{
	this->numOfColumn = DEFAULT_GRID_COLUMN;
	this->numOfRow = DEFAULT_GRID_ROW;
	this->InitObjectForGrid();
}

Grid::Grid(int height, int width)
{
	this->numOfRow = (int) ceil((float)height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int) ceil((float)width * BRICK_SIZE / CELL_SIZE);
	this->InitObjectForGrid();
}

// Hủy bỏ đối tượng Grid
Grid::~Grid()
{
	for (int row = 0; row < this->numOfRow; row++) {
		for (int column = 0; column < this->numOfColumn; column++) {
			delete[] this->cells[row][column];
		}
		delete[] this->cells[row];
	}

	delete[] this->cells;
}

// Khởi tạo đối tượng ban đầu cho Grid
// Khi khởi tạo phải chú ý là khởi tạo dòng trước, rồi cột rồi ms tới chiều sâu
void Grid::InitObjectForGrid()
{
	this->cells = new Object**[this->numOfRow];

	for (int row = 0; row < this->numOfRow; row++) {
		this->cells[row] = new Object*[this->numOfColumn];

		for (int column = 0; column < this->numOfColumn; column++) {
			this->cells[row][column] = NULL;
		}
	}

	this->deltaTime = 0.0f;
}

// Cập nhật lại Grid sau khi xử lý va chạm này nọ
void Grid::UpdateGrid(Object * object, float newPosX, float newPosY)
{
	if (newPosX == 0.0f && newPosY == 0.0f) {
		newPosX = object->GetCurPos()->GetPosX();
		newPosY = object->GetCurPos()->GetPosY();
	}

	// Kiểm tra xem có thay đổi cell hay không
	int oldRow = floor(object->GetLastPos()->GetPosY() / CELL_SIZE);
	int oldColumn = floor(object->GetLastPos()->GetPosX() / CELL_SIZE);

	int newRow = floor(newPosY / CELL_SIZE);
	int newColumn = floor(newPosX / CELL_SIZE);

	// Nếu không thay đổi thì thoát ra
	if (oldRow == newRow && oldColumn == newColumn)
		return;

	// Xóa object ra khỏi cell hiện tại và cập nhật lại cell mới
	if (object->GetPreObject() != NULL) {
		object->GetPreObject()->SetNextObject(object->GetNextObject());
	}
	if (object->GetNextObject() != NULL) {
		object->GetNextObject()->SetPreObject(object->GetPreObject());
	}

	// Nếu object đang đứng đầu
	if (cells[oldRow][oldColumn] == object) {
		cells[oldRow][oldColumn] = object->GetNextObject();
	}

	this->Add(object);

	// Cập nhật lại vị trí last của object
	object->GetLastPos()->SetPosX(object->GetCurPos()->GetPosX());
	object->GetLastPos()->SetPosY(object->GetCurPos()->GetPosY());
}

// Bản chất của Grid là DSLK đôi, nên mình sẽ thao tác giống danh sách liên kết đôi
// Ở đây 1 cell là 1 danh sách liên kết đôi, nên khi xác định được vị trí của Object ở cell nào rồi
// thì mình sẽ đưa vào đầu danh sách của cell đó
// Mỗi lần vị trí của Object được cập nhật thì bắt buộc phải lưu lại vị trí trước đó
void Grid::Add(Object *object) {

	// Lưu lại giá trị cũ của object sau mỗi lần update
	object->GetLastPos()->SetPosX(object->GetCurPos()->GetPosX());
	object->GetLastPos()->SetPosY(object->GetCurPos()->GetPosY());

	// Xác định object đang nằm ở grid nào
	int column = floor(object->GetCurPos()->GetPosX() / CELL_SIZE);
	int row = floor(object->GetCurPos()->GetPosY() / CELL_SIZE);

	// Thêm object vào đầu dslk
	object->SetPreObject(NULL);
	object->SetNextObject(this->cells[row][column]);
	this->cells[row][column] = object;

	if (object->GetNextObject() != NULL) {
		object->GetNextObject()->SetPreObject(object);
	}
}

void Grid::ReSetGrid(int height, int width) {
	Grid::Grid(height, width);
}

// Dùng để xét cái ô cell hiện tại, như là va chạm của object mình đang xét với các object còn lại
// Kế bên đó là xét với các cell lân cận
// Theo người ta nói các cell càn xét thêm là:
//		1 ô trên,
//		1 ô trái trên
//		1 ô trái
//		1 ô trái dưới
// Ở đây ta cho vào vòng lặp là xét tất cả các object với nhau
bool Grid::HandleCell(Object * object, int row, int column)
{
	bool isCollided = false;

	if (object == NULL || object->GetObjectType() == BRICK || !object->GetIsActive())
		return false;

	// Xét va chạm với chính cell của nó trước
	if (this->HandleObject(object, this->cells[row][column]))
		isCollided = true;

	// Xét va chạm với các cell kế bên

	if (row > 0) {
		if (this->HandleObject(object, this->cells[row - 1][column])) // Phía trên
			isCollided = true;
	}

	if (row < this->numOfRow - 1) {
		if (this->HandleObject(object, this->cells[row + 1][column])) // Phía dưới dưới
			isCollided = true;
	}

	if (object->GetCurVec()->GetVx() <= 0) { // Nếu đang đi qua trái
		if (row > 0 && column > 0) {
			if (this->HandleObject(object, this->cells[row - 1][column - 1])) isCollided = true; // Trái trên
		}

		if (column > 0) {
			if (this->HandleObject(object, this->cells[row][column - 1])) isCollided = true; // Phía trái
		}

		if (column > 0 && row < this->numOfRow - 1) {
			if (this->HandleObject(object, this->cells[row + 1][column - 1])) isCollided = true; // Trái dưới
		}

	}
	else { // Nếu đang đi qua phải
		if (row > 0 && column < this->numOfColumn - 1)
			if (this->HandleObject(object, cells[row - 1][column + 1])) // phai tren
				isCollided = true;
		if (column < this->numOfColumn - 1)
			if (this->HandleObject(object, cells[row][column + 1]))    // ben phai
				isCollided = true;
		if (column < this->numOfColumn - 1 && row < this->numOfRow - 1)
			if (this->HandleObject(object, cells[row + 1][column + 1])) // phai duoi
				isCollided = true;
	}
		
	
	return isCollided;
}

// Lấy tất cả object có khả năng va chạm với object đang xét
std::vector<Object*> *Grid::GetCollisionObjects(Object * object)
{

	std::vector<Object*> *objects = new std::vector<Object*>();

	if (object == nullptr || object->GetObjectType() == BRICK)
		return objects;

	int row = (int)floor(object->GetCurPos()->GetPosY() / CELL_SIZE);
	int column = (int) floor(object->GetCurPos()->GetPosX() / CELL_SIZE);

	// Lấy object ở cell hiện tại
	this->PushObjectToVector(objects, this->cells[row][column]);

	// Lấy các cell ở kế bên

	// Nếu đang đi qua trái
	if (object->GetCurVec()->GetVx() < 0) {
		if (column > 0) this->PushObjectToVector(objects, this->cells[row][column - 1]); // Bên trái

		if (column > 0 && row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column - 1]); // Trái trên

		if (column > 0 && row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column - 1]); //Trái dưới
	}

	// Nếu đang đi qua phải
	else {
		if (column < this->numOfColumn - 1) this->PushObjectToVector(objects, this->cells[row][column + 1]); //Bên phải

		if (column < this->numOfColumn - 1 && row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column + 1]); // Phải trên

		if (column < this->numOfColumn - 1 && row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column + 1]); // Phải dưới
	}

	// Nếu đang đi lên
	if (object->GetCurVec()->GetVy() < 0) {
		if (row > 0) this->PushObjectToVector(objects, this->cells[row - 1][column]);
	}
	// Nếu đang đi xuống
	else {
		if (row < this->numOfRow - 1) this->PushObjectToVector(objects, this->cells[row + 1][column]);
	}

	return objects;
}

void Grid::PushObjectToVector(std::vector<Object*> *vectors, Object*cell) {
	while (cell != NULL) {
		
		vectors->push_back(cell);
		cell = cell->GetNextObject();
	}
}

// Dùng để xét giữa object đang xét với các object còn lại trong cell hoặc cell lân cận
bool Grid::HandleObject(Object * objSrc, Object * objDes)
{
	bool isCollided = false;

	while (objDes != NULL) {
		if (objSrc != objDes && objDes->GetIsActive()) {
			if(objSrc->handleCollision(objDes))
				isCollided = true;
		}

		objDes = objDes->GetNextObject();
	}


	return isCollided;
}

void Grid::SetDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

float Grid::GetDeltaTime()
{
	return this->deltaTime;
}
