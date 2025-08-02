// FOR REFERENCE
//#include "header.h"
//
//cpoint cpoint::fromXYToRowCol(cpoint v) {
//	return { (v.y - 1 - TOP) / 2, (v.x - 2 - LEFT) / 4, v.c };
//}
//cpoint cpoint::fromRowColToXY(cpoint s) {
//	return { 4 * s.y + 2 + LEFT, 2 * s.x + 1 + TOP, s.c };
//}
//
//mutex ctool::mtx;
//void ctool::ShowConsoleCursor(bool showFlag) {
//	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_CURSOR_INFO cursorInfo;
//	GetConsoleCursorInfo(out, &cursorInfo);
//	cursorInfo.bVisible = showFlag; // set the cursor visibility 
//	SetConsoleCursorInfo(out, &cursorInfo);
//}
//void ctool::GotoXY(int x, int y) {
//	COORD crd = { x,y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
//}
//void ctool::Draw(char* str, int i, cpoint p[], cpoint& _p) {
//	mtx.lock();
//	_p = p[i];
//	ctool::GotoXY(_p.getX(), _p.getY());
//	cout << str;
//	mtx.unlock();
//}
//
//cenemy::cenemy() {
//	for (int i = 0; i < cpoint::MAP_SIZE * cpoint::MAP_SIZE;i++)
//		p[i] = { 0,0,0 };
//	dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
//	dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;
//	start = end = curr = { 0,0,0 };
//	speed = 3;
//}
//cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
//	start = tstart;
//	end = tend;
//	curr = tcurr;
//}
//void cenemy::calcPath(int a[][cpoint::MAP_SIZE], int n, cpoint s,
//	cpoint e, int step) {
//	if (s.getX() == e.getX() && s.getY() == e.getY()) {
//		int k = 1;
//		a[s.getX()][s.getY()] = step;
//		while (k <= step) {
//			for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//				for (int j = 0; j < cpoint::MAP_SIZE; j++) {
//					if (a[i][j] == k) {
//						p[k - 1] = cpoint::fromRowColToXY({ i,j,0 });
//						goto nhan;
//					}
//				}
//			}
//		nhan: k++;
//		}
//		return;
//	}
//	for (int i = 0; i < 4;i++) {
//		int dmoi = dd[i] + s.getX(), cmoi = dc[i] + s.getY();
//		if (dmoi >= 0 && dmoi < n && cmoi >= 0 && cmoi < n && a[dmoi][cmoi] == 0)
//			calcPath(a, n, { dmoi, cmoi, 0 }, e, step + 1);
//	}
//	a[s.getX()][s.getY()] = 0;
//}
//void cenemy::findPath(cpoint a[][cpoint::MAP_SIZE], cpoint s, cpoint e)
//{
//	int ta[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
//	for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//		for (int j = 0; j < cpoint::MAP_SIZE; j++)
//			ta[i][j] = a[i][j].getC();
//	}
//	s = cpoint::fromXYToRowCol(s);
//	e = cpoint::fromXYToRowCol(e);
//	calcPath(ta, cpoint::MAP_SIZE, s, e);
//}
//
//cbullet::cbullet() {
//	size = 0;
//	speed = 4;
//	curr = { 0,0,0 };
//	for (int i = 0; i < cpoint::MAP_SIZE *
//		cpoint::MAP_SIZE;i++) p[i] = { 0,0,0 };
//	for (int i = 0; i < cpoint::MAP_SIZE;i++) {
//		for (int j = 0; j < cpoint::MAP_SIZE;j++) {
//			m[i][j] = { 0, 0, 0 };
//		}
//	}
//}
//void cbullet::updateMap(int i, int j, cpoint v) {
//	if (i >= 0 && i < cpoint::MAP_SIZE && j >= 0 && j < cpoint::MAP_SIZE) {
//		m[i][j] = v;
//	}
//}
//
//int cbullet::queryCFromRowCol(int row, int col) {
//	if (row < 0 || row >= cpoint::MAP_SIZE || col < 0 || col >= cpoint::MAP_SIZE)
//		return -2;
//	else {
//		for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//			for (int j = 0; j < cpoint::MAP_SIZE; j++) {
//				cpoint tmp = cpoint::fromXYToRowCol(m[i][j]);
//				if (tmp.getX() == row && tmp.getY() == col) {
//					return m[i][j].getC();
//				}
//			}
//		}
//	}
//	return -1;
//}
//int cbullet::calcPathBullet(cpoint tower) {
//	cpoint tmp = cpoint::fromXYToRowCol(tower);
//	int row = tmp.getX(), col = tmp.getY(), i = 0;
//	do {
//		col++; row--;
//		if (queryCFromRowCol(row, col) == 0) {
//			p[i] = cpoint::fromRowColToXY({ row,col,0 });
//			i += 2;
//		}
//		else break;
//	} while (i < cpoint::MAP_SIZE);
//	int size = i;
//	for (i = 1; i < size;i += 2) {
//		p[i] = { p[i - 1].getX() + 2,p[i - 1].getY() - 1,0 };
//	}
//	cpoint curr = { p[0].getX(),p[0].getY(),p[0].getC() };
//	return size;
//}
//
//void ctower::setMapForBullet(cpoint a[][cpoint::MAP_SIZE])
//{
//	for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//		for (int j = 0; j < cpoint::MAP_SIZE; j++) {
//			bullet.updateMap(i, j, a[i][j]);
//		}
//	}
//}
//
//cmap::cmap() {
//	resetMapData();
//	makeMapData();
//}
//void cmap::resetMapData() {
//	for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//		for (int j = 0; j < cpoint::MAP_SIZE; j++) {
//			_m[i][j] = { 4 * j + cpoint::LEFT + 2,2 * i + cpoint::TOP + 1,-1 };
//		}
//	}
//}
//void cmap::makeMapData() {
//	_m[2][0].setC(0); _m[2][1].setC(0); _m[2][2].setC(0); _m[2][3].setC(0);
//	_m[2][7].setC(-2); _m[2][8].setC(-2);
//	_m[3][1].setC(-2); _m[3][2].setC(-2); _m[3][3].setC(0);
//	_m[3][4].setC(0); _m[3][5].setC(0); _m[3][6].setC(0);
//	_m[3][7].setC(-2); _m[3][8].setC(-2);
//	_m[4][1].setC(-2); _m[4][2].setC(-2); _m[4][6].setC(0);
//	_m[4][7].setC(0); _m[4][8].setC(0);
//	_m[5][8].setC(0);
//	_m[5][6].setC(0);
//	_m[6][5].setC(0);
//	_m[6][8].setC(0);
//	_m[7][3].setC(0); _m[7][4].setC(0); _m[7][5].setC(0); _m[7][6].setC(0);
//	_m[7][7].setC(0); _m[7][8].setC(0);
//	_m[8][1].setC(-2); _m[8][2].setC(-2); _m[8][3].setC(0);
//	_m[9][1].setC(-2); _m[9][2].setC(-2); _m[9][3].setC(0);
//	// Initializes the current, starting and ending coordinates that  
//	// character passes through 
//	_ce.setStart(_m[2][0]);_ce.setEnd(_m[9][3]);_ce.setCurr(_m[2][0]);
//	// Calculate the path for the character 
//	_ce.findPath(_m, _ce.getStart(), _ce.getEnd());
//	// Start assigning coordinates for Tower _ctw 
//	_ctw.setLocation(_m[9][2]);
//	// Updated map information for cbullet object of Tower _ctw 
//	_ctw.setMapForBullet(_m);
//	// Calculate the path for the cbullet object of Tower _ctw 
//	_ctw.calcPathBullet();
//}
//void cmap::drawMap() {
//	// Draw map data _m 
//	for (int i = 0; i < cpoint::MAP_SIZE; i++) {
//		for (int j = 0; j < cpoint::MAP_SIZE; j++) {
//			ctool::GotoXY(_m[i][j].getX(), _m[i][j].getY());
//			if (_m[i][j].getC() == -1) cout << '+';
//			else if (_m[i][j].getC() == -2) cout << 'U';
//		}
//	}
//	// Draw _ctw 
//	ctool::GotoXY(_ctw.getLocation().getX(), _ctw.getLocation().getY());
//	cout << 'T';
//}
//
//cgame::cgame() {
//	_ISEXIT1 = _ISEXIT2 = false;
//}
//void cgame::startGame() {
//	system("cls");
//	_map.drawMap();
//}
//
//void ThreadFunc2(cgame&);
//void ThreadFunc1(cgame&);
//
//int main() {
//	cout << "Press any key to start demo: ";
//	cin.get();
//	ctool::ShowConsoleCursor(false);
//	cgame cg;
//	cg.startGame();
//
//	thread t1(ThreadFunc1, std::ref(cg));
//	thread t2(ThreadFunc2, std::ref(cg));
//	t1.join();
//	t2.join();
//
//	ctool::GotoXY(0, 20); // Jump to the last line to exit the program 
//	return 0;
//}
//
//void ThreadFunc2(cgame& cg) {
//	int i = 0;
//	cenemy& ce = cg.getMap().getEnemy(); // Get the cenemy object 
//	cpoint _ENEMY;
//	cbullet& cb = cg.getMap().getTower().getBullet(); // Get the cbullet object 
//	int _SPEED = cb.getSpeed(), _NBULLET = cb.getSize();
//	cpoint* _BULLET1_P = cb.getP();
//	cpoint _BULLET1 = cb.getCurr();
//	while (!cg.getIsExist1()) {
//		ctool::Draw((char*)"o", i, _BULLET1_P, _BULLET1);
//		cb.setCurr(_BULLET1);
//		_ENEMY = ce.getCurr();
//		if (_BULLET1.getX() == _ENEMY.getX() && _BULLET1.getY() == _ENEMY.getY()) {
//			ctool::Draw((char*)" ", i, _BULLET1_P, _BULLET1);
//			cg.setIsExist1(true);
//			break;
//		}
//		else i++;
//		Sleep(1000 / _SPEED);
//		ctool::Draw((char*)" ", i - 1, _BULLET1_P, _BULLET1);
//		if (i == _NBULLET)i = 0;
//	}
//	cg.setIsExist2(true);
//}
//
//void ThreadFunc1(cgame& cg) {
//	int i = 0;
//	cenemy& ce = cg.getMap().getEnemy(); // Get the cenemy object 
//	cpoint _ENEMY = ce.getCurr(), _END = ce.getEnd(); int SPEED = ce.getSpeed();
//	cpoint* _P = ce.getP(); // Get the _p path of the cenemy object 
//	cbullet& cb = cg.getMap().getTower().getBullet(); // Get the cbullet object 
//	cpoint _BULLET1;
//	while (!cg.getIsExist1()) {
//		ctool::Draw((char*)"K", i, _P, _ENEMY);
//		ce.setCurr(_ENEMY);
//		_BULLET1 = cb.getCurr();
//		if (_ENEMY.getX() == _END.getX() && _ENEMY.getY() == _END.getY()) {
//			break;
//		}
//		else if (_ENEMY.getX() == _BULLET1.getX() && _ENEMY.getY() == _BULLET1.getY()) {
//			ctool::Draw((char*)" ", i, _P, _ENEMY);
//			break;
//		}
//		else i++;
//		Sleep(1000 / SPEED);
//		ctool::Draw((char*)" ", i - 1, _P, _ENEMY);
//	}
//	cg.setIsExist1(true);
//}
//
////#include <SFML/Graphics.hpp>
////
////using namespace std;
////
////int main()
////{
////    // take desktop screen res
////    
////    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
////    // Create a window
////    sf::RenderWindow window(desktop, "SFML Test", sf::Style::Fullscreen);
////
////    // Create a circle
////    sf::CircleShape circle(50); // radius = 50
////    circle.setFillColor(sf::Color::Cyan);
////    circle.setPosition(100, 100);
////    circle.setOrigin(50.0f, 50.0f);
////
////    while (window.isOpen())
////    {
////        sf::Event event;
////        while (window.pollEvent(event))
////        {
////            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
////                window.close();
////        }
////
////        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
////        {
////            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
////            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
////            circle.setPosition(worldPos);
////        }
////        window.clear();
////        window.draw(circle);
////        window.display();
////    }
////    return 0;
////}
