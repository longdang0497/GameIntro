#include "Grid.h"

Grid::Grid()
{
	this->numOfColumn = DEFAULT_GRID_COLUMN;
	this->numOfRow = DEFAULT_GRID_ROW;
	this->InitObjectForGrid();
}

Grid::Grid(int height, int width)
{
	this->numOfRow = (int)ceil((float)height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil((float)width * BRICK_SIZE / CELL_SIZE);
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
