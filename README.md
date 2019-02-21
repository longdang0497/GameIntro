# GameIntro

## 1. Linker -> Input
```
d3dx9.lib
d3d9.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
comdlg32.lib
advapi32.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
odbc32.lib
odbccp32.lib
d3dcompiler.lib
avrt.lib
winmm.lib
dinput8.lib
dxguid.lib
comctl32.lib
dxerr.lib
legacy_stdio_definitions.lib
dsound.lib
```

## 2. Thay đổi Include hay Lib thì sử dụng x86 nha

## 3. Lúc chạy ứng dụng thì nhớ chỉnh chế độ x86

## 4. Grid (phần này mình chỉ nói sơ sơ thôi nha, còn chi tiết thì cái link gì đó mà lạc trôi đâu mất r -_- )
Trong phần này, chúng ta làm việc với Grid, nên có những vấn đề sau cần phải nắm chút chút để mà rõ hơn

### a. Một chút khái niệm sơ sơ về Grid
<img src="https://i.imgur.com/7XsPUaB.jpg?1"/>

- Như hình ở trên, ta thấy đây là một ví dụ điển hình về Grid, nó có cấu trúc dạng lưới và được chia thành các ô (các cells), mỗi cell sẽ chứa các object bên trong nó.
- Một Grid thì ta có thể coi đó là không gian 3 chiều, tức là có chiều dài, chiều ngang và chiều sâu  (width, height, deepth).
- Như hình ở trên thì ta thấy nó giống mảng 2 chiều, có số cột và số dòng, 1 cột và 1 dòng thì tương ứng 1 ô (ví dụ hình trên có 4 cột và 3 dòng, thì nghĩa là ta có măng 2 chiều là 3 dòng và 4 cột <=> Grid grid[3][4]). Tuy nhiên, mỗi 1 ô đó lại chứa các object thuộc cái ô đó, từ đó ta sẽ sử dụng con trỏ 3 chiều để quản lý (Grid *** grid), và ta có thể hiểu mỗi ô đó là một danh sách liên kết đôi (double Linked list). Việc dùng Double Linked List là để giúp cho các object cùng 1 ô sẽ nối nhau, thuận lợi cho việc xét va chạm sau này.

### b. Khởi tạo Grid với một Map cho trước (tham khảo Grid.h và Grid.cpp)
- Đầu tiên là chúng ta sẽ khởi tạo Grid. Lúc này việc cần làm là xác định được độ dài và rộng của cái Map của bạn như thế nào để khởi tạo Grid cho không bị phí phạm vùng nhớ (do mình dùng con trỏ và code bằng C++ nên việc điều khiển các ô nhớ rất là quan trọng).
- Khi ta bắt đầu code, ta có tư tưởng là chạy tới room nào thì mình sẽ khởi tạo room đó, nhưng ở đây, là mình phải khởi tạo toàn bộ Map ngay từ ban đầu, tức là mình phải có rõ thông số của map là gì (chiều dài, chiều cao, số room) vì mình muốn đưa giai đoạn khởi đầu là khởi tạo toàn bản đầu, còn xử lý gì đó là ở phía sau.
- Tất nhiên việc khởi tạo Map là phải ở trong hàm khởi tạo (constructor) của Grid rồi <3 (có thể khai báo khác nếu muốn). Đoạn code sau là khởi tạo Grid.

#### Grid.h
```
class Grid
{
private:
	int numOfRow;			// Số dòng của Grid (y)
	int numOfColumn;		// Số cột của Grid (x)
	Object ***cells;		// Với 3 tham số truyền vào lần lượt là: Số dòng, số cột, và số chiều sâu

	void InitObjectForGrid();
public:
	Grid();
	Grid(int mapHeight, int mapWidth);
	~Grid();
};
```

#### Grid.cpp
```
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
```

- Như code ở trên ta thấy ban đầu ta sẽ khởi tạo mảng 3 chiều, (2 chiều đầu là số dòng và cột, chiều thứ 3 là độ sâu).
- Sau khi khởi tạo được số dòng cột rồi, thì mình phải khởi tạo các cột bằng NULL ban đầu.
- Bản chất của Grid thì cũng chỉ là các mảng 2 chiều, với chiều thứ 3 là chiều các object nối với nhau nên mình có thể tưởng tượng ra.
- (Các kiến thức về Double Linked List có thể tra lại google)

### c. Tiến hành thêm các Object vào Grid
- Tiếp theo đó chính là việc thêm các object vào Grid, có nghĩa là khi khởi tạo Grid xong, ta có một công đoạn là khởi tạo các Object ở một class nào đó, sau đó thì thêm object đó vào Grid.
- Code tham khảo ở hàm `Add(Object* object)` và có comment đầy đủ.

### d. Xử lý va chạm
- À ha, cuối cùng là cái việc khó khăn nhất òi đây.
- Cái việc xử lý va chạm trong Grid là mình cần phải xác định được các object đó đang ở cell nào và cần xét va chạm với các cell nào. Tuyệt đối tránh trường hợp xét va chạm với tất cả các cell, CPU lên cao ráng chịu :V 
- Thứ tự code tham khảo `handleCell() -> handleObject() -> handleCollision()`, mọi hàm đều có comment đầy đủ
- Cái chỗ hàm  `handleCollision()` có liên quan một chút đến va chạm giữa các vật thể, cái này sẽ cập nhật sau ~~

test ở chỗ làm
