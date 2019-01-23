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

bool Grid::HandleCollision(Object * objSrc, Object * objDes)
{
	return false;
}

bool Grid::HandleObject(Object * objSrc, Object * objDes)
{
	return false;
}

// Cập nhật lại Grid sau khi xử lý va chạm này nọ
void Grid::UpdateGrid(Object * object, float newPosX, float newPosY)
{
	// Kiểm tra xem có thay đổi cell hay không
	int oldRow = floor(object->GetLastPos()->getPosY() / CELL_SIZE);
	int oldColumn = floor(object->GetLastPos()->getPosX() / CELL_SIZE);

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
	object->GetLastPos()->setPosX(object->GetCurPos()->getPosX());
	object->GetLastPos()->setPosY(object->GetCurPos()->getPosY());
}

// Bản chất của Grid là DSLK đôi, nên mình sẽ thao tác giống danh sách liên kết đôi
// Ở đây 1 cell là 1 danh sách liên kết đôi, nên khi xác định được vị trí của Object ở cell nào rồi
// thì mình sẽ đưa vào đầu danh sách của cell đó
// Mỗi lần vị trí của Object được cập nhật thì bắt buộc phải lưu lại vị trí trước đó
void Grid::Add(Object *object) {

	// Lưu lại giá trị cũ của object sau mỗi lần update
	object->GetLastPos()->setPosX(object->GetCurPos()->getPosX());
	object->GetLastPos()->setPosY(object->GetCurPos()->getPosY());

	// Xác định object đang nằm ở grid nào
	int column = floor(object->GetCurPos()->getPosX() / CELL_SIZE);
	int row = floor(object->GetCurPos()->getPosY() / CELL_SIZE);

	// Thêm object vào đầu dslk
	object->SetPreObject(NULL);
	object->SetNextObject(this->cells[row][column]);

	if (object->GetNextObject() != NULL) {
		object->GetNextObject()->SetPreObject(object);
	}
}

void Grid::ResetGrid(int height, int width) {
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
	Object* cell = this->cells[row][column];

	if (object == NULL)
		return false;

	

	return false;
}

void Grid::SetDeltaTime(float deltaTime)
{
	this->deltaTime = deltaTime;
}

float Grid::GetDeltaTime()
{
	return this->deltaTime;
}
