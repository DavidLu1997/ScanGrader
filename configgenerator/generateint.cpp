#include <iostream>
#include <fstream>
using namespace std;
int main() {
    int x, y;
    cin >> x >> y;
    int ox = x, oy = y;
    int side;
    cin >> side;
    int l, w;
    cin >> l >> w;
    int id;
    cin >> id;

    ofstream out("numbers.txt", ios::out);
    for(int i = 0; i < l; i++) {
        for(int j = 0; j < w; j++) {
            out << x << " " << y << " " << x + side << " " << y + side << " " << id << endl;
            x += side;
        }
        y += side;
        x = ox;
    }

    out.close();
}
