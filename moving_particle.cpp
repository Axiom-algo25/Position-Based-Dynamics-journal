#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct particle {
    float x ;
    float y ;
    float vx;
    float vy;

};
void move(particle& p ,float dt) {
    p.x = p.x + p.vx * dt;
    p.y = p.y + p.vy * dt;
}
int main () {
    particle ball;
    ball.x = 0;
    ball.y = 0;
    ball.vx = 10; 
    ball.vy = 20;

    float dt = 0.1;

    move(ball,dt);
    cout << "positon : (" << ball.x <<  "," << ball.y << ")" << endl;
    return 0;
}