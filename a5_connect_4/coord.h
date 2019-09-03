
#ifndef COORD_H
#define COORD_H
class Coord{
public:
    Coord(){x = 0; y = 0;};
    Coord(int x_coord, int y_coord){x = x_coord; y = y_coord;}
    int get_x(){return x;}
    int get_y(){return y;};
private:
    int x;
    int y;
};
#endif //COORD_H
