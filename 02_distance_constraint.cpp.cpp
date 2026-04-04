#include <iostream>
#include <cmath>
using namespace std;
struct particle {
    float x,y;
};
int main() {
    particle p1 = {0,0};
    particle p2 = {12,0};

    float rest_length = 6;
    for (int i = 0; i < 10; i++) {
        float dx = p1.x - p2.x;
        float dy = p1.y - p2.y;
        
        float dist = sqrt( dx * dx + dy * dy ) ;
        float cons = dist - rest_length;        
        

        dx /= dist;
        dy /= dist;

        p1.x -= 0.5 * cons * dx;
        p2.x += 0.5 * cons * dx;
        p1.y -= 0.5 * cons * dy;
        p2.y += 0.5 * cons * dy;
        
    } ;
    cout << "p1: (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "p2: (" << p2.x << ", " << p2.y << ")" << endl;
    return 0;
}    

        