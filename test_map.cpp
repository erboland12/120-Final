////
//// Created by Eric on 4/20/2018.
////
//#include <iostream>
//#include <vector>
//
//#include "map.h"
//vector<vector<Square>> v;
//vector<Square> v2 = {empty, empty, empty};
//
//using namespace std;
//void testMapConstructors();
//void testSquareConstructors();
//void testMapGetters();
//void testSquareGetters();
//void testMapSetters();
//void testSquareSetters();
//int main(){
//    testMapConstructors();
//    testSquareConstructors();
//    testMapGetters();
//    testSquareGetters();
//    testMapSetters();
//    testSquareSetters();
//
//    Square s = Square(empty);
//    v.push_back(v2);
//    cout << v.size() << endl;
//    cout << v[0][0].printSquareType() << endl;
//
//    Map m = Map(v,40,40);
//
//    m.save();
//    cout << "Test print square type" << endl;
//    cout << "Should return empty" << endl;
//    cout << s.printSquareType() << endl;
//
//
//    return 0;
//};
//
//void testMapConstructors(){
//    //Constructors for map class
//    cout << "Map default constructor" << endl;
//    Map m;
//    cout << m.getX() << endl; //Should return 0.
//    cout << "Map non-default constructor" << endl;
//    Map m2(v,50,50);
//    cout << m2.getX() << endl; //Should return 0.
//}
//void testSquareConstructors(){
//    //Constructors for square class.
//    cout << "Square default constructor" << endl;
//    Square s;
//    cout << s.getSquare() << endl; //Should return 0.
//    cout << "Square non-default constructor" << endl;
//    Square s2 = Square(wall);
//    cout << s2.getSquare() << endl; //Should return 0.
//}
//void testMapGetters(){
//    //Testing getters in Map
//    Map m = Map(v, 45, 55);
//    cout << "Method to get the x value" << endl; //Should return 45
//    cout << m.getX() << endl;
//    cout << "Method to get the y value" << endl; //Should return 55
//    cout << m.getY() << endl;
//    m.getMap();
//}
//void testSquareGetters(){
//    //Testing getters in Square
//    Square s = Square(empty);
//    cout << "Method to get the square type" << endl; //Should return 0
//    cout << s.getSquare() << endl;
//}
//void testMapSetters(){
//    //Testing setters in Map class
//    cout << "Empty map fields" << endl;
//    Map m;
//    cout << m.getX() << endl; //Should return 0.
//    cout << m.getY() << endl; //Should return 0.
//    m.getMap();
//    cout << "Map fields after calling set methods." << endl;
//    m.setX(40);
//    m.setY(50);
//    cout << m.getX() << endl; //Should return 40.
//    cout << m.getY() << endl; //Should return 50.
//    m.getMap();
//}
//void testSquareSetters(){
//    //Testing setters in Square.
//    cout << "Empty Square fields" << endl;
//    Square s;
//    cout << s.getSquare() << endl; //Should return 0.
//    cout << "Square fields after calling set methods." << endl;
//    s.setSquare(wall);
//    cout << s.getSquare() << endl; //Should return 1.
//}
//
