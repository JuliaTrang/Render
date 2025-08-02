// FOR REFERENCE
//#ifndef HEADER_H
//#define HEADER_H
//#include <mutex>
//#include <windows.h>
//#include <iostream>
//using namespace std;
//class cpoint {
//	public:
//	// const and data
//		const static int MAP_SIZE = 10;
//		const static int LEFT = 3;
//		const static int TOP = 1;
//private:
//	int x, y, c;
//public:
//	cpoint() { x = y = c = 0; }
//	cpoint(int tx, int ty, int tc) { x = tx; y = ty; c = tc; }
//	int getX() { return x; }
//	int getY() { return y; }
//	int getC() { return c; }
//	void setC(int tc) { c = tc; }
//	static cpoint fromXYToRowCol(cpoint v);
//	static cpoint fromRowColToXY(cpoint s);
//};
//
//class ctool {
//public:
//	static mutex mtx;
//	static void ShowConsoleCursor(bool);
//	static void GotoXY(int x, int y);
//	static void Draw(char*, int, cpoint[], cpoint&);
//};
//
//class cenemy {
//private:
//	int speed;
//	cpoint start, end, curr;
//	cpoint p[cpoint::MAP_SIZE * cpoint::MAP_SIZE];
//	int dd[4], dc[4];
//public:
//	cenemy();
//	cenemy(cpoint tStart, cpoint tEnd, cpoint tCurr);
//	cpoint* getP() { return p; }
//	cpoint getStart() { return start; }
//	cpoint getEnd() { return end; }
//	int getSpeed() { return speed; }
//	cpoint getCurr() { return curr; }
//	void getSpeed(int tSpeed)
//	{
//		if (tSpeed > 0 && tSpeed < 10) speed = tSpeed;
//	}
//	void setStart(cpoint tStart)
//	{
//		start = tStart;
//	}
//	void setEnd(cpoint tEnd)
//	{
//		end = tEnd;
//	}
//	void setCurr(cpoint tCurr)
//	{
//		curr = tCurr;
//	}
//	void findPath(cpoint[][cpoint::MAP_SIZE], cpoint, cpoint);
//private:
//	void calcPath(int[][cpoint::MAP_SIZE], int, cpoint, cpoint, int = 1);
//};
//
//class cbullet {
//private:
//	int size, speed;
//	cpoint p[cpoint::MAP_SIZE * cpoint::MAP_SIZE];
//	// map info to cal the path array p
//	cpoint m[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
//	cpoint curr;
//public:
//	cbullet();
//	void updateMap(int, int, cpoint);
//	cpoint getCurr() { return curr; };
//	void setCurr(cpoint tCurr)
//	{
//		curr = tCurr;
//	}
//	cpoint* getP(){ return p; }
//	int getSpeed() { return speed; }
//	int getSize() { return size; }
//	void setSize(int tSize)
//	{
//		size = tSize;
//	}
//	void setSpeed(int tSpeed)
//	{
//		speed = tSpeed;
//	}
//	int queryCFromRowCol(int, int);
//	int calcPathBullet(cpoint);
//};
//
//class ctower {
//private:
//	cpoint location;
//	cbullet bullet;
//public:
//	ctower() { location = { 0, 0, 0 }; }
//	cpoint getLocation() { return location; }
//	void setLocation(cpoint tLocation)
//	{
//		location = tLocation;
//	}
//	void setMapForBullet(cpoint[][cpoint::MAP_SIZE]);
//	void calcPathBullet() {
//		bullet.calcPathBullet(location);
//	}
//	// returning ref is quite dangerous
//	// you need to build test functions for the bullet
//	// class before changing the value of the internal properties
//	cbullet& getBullet() { return bullet; }
//};
//class cmap {
//	cenemy _ce;
//	ctower _ctw;
//	// Map matrix _m 
//	cpoint _m[cpoint::MAP_SIZE][cpoint::MAP_SIZE];
//public:
//	cmap();
//	//-1 là tường, 0 là trống, 1 là Tower 
//	void resetMapData();
//	void makeMapData();
//	void drawMap();
//
//	cenemy& getEnemy() { return _ce; }
//	ctower& getTower() { return _ctw; }
//};
//
//class cgame {
//private:
//	cmap _map;
//	bool _ISEXIT1, _ISEXIT2;
//public:
//	cgame();
//	bool getIsExist1() { return _ISEXIT1; }
//	void setIsExist1(bool b) { _ISEXIT1 = b; }
//	bool getIsExist2() { return _ISEXIT2; }
//	void setIsExist2(bool b) { _ISEXIT2 = b; }
//	cmap& getMap() { return _map; }
//	void startGame();
//};
//#endif