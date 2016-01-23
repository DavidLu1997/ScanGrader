#include <iostream>
#include <fstream>
using namespace std;
int main() {
    int ox, oy;
        int sidex, sidey;
        cin >> sidex >> sidey;
    int l, w;
    cin >> l >> w;
    int id;
    ofstream out("numbers.txt", ios::out);
    for(int k = 0; k < 6; k++) {
        int x, y;
        cin >> x >> y;
        ox = x, oy = y;
    cin >> id;
        for(int i = 0; i < l; i++) {
            for(int j = 0; j < w; j++) {
                out << x << " " << y << " " << x + sidex << " " << y + sidey << " " << id << endl;
                y += sidey;
            }
            x += sidex;
            y = oy;
        }
    }
    out.close();
}
