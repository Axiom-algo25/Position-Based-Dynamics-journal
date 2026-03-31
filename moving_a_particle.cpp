#include <iostream>
#include <vector>
using namespace std;

struct particle{
    float x,y;
    float vx,vy;

    particle(float startx ,float starty ,float startvx,float startvy){
        x = startx;
        y = starty;
        vx = startvx;
        vy = startvy;
    }

        void applyforce(float fx,float fy,float dt){
            vx += fx * dt; // adding to the exsisting value (line 5 of section 3.1 (vi <-- vi + dt * fext))
            vy += fy * dt;

        }
        
        void move(float dt){
            x += vx * dt; // new position = old position + velocity * time
            y += vy * dt;

        }
    };
int main() {
    vector<particle>particles;

    for (int i = 0 ; i < 10 ;i++) {
        particles.push_back(particle(i * 20 , 0 , 0 , 0  ));
    }
    float dt = 0.1;
    float gravity = 500;

    for (int frame = 0 ; frame < 100 ; frame++) {
        cout << "Frame" << frame << ":" << endl;


        for(auto& p : particles){
        p.applyforce(0,gravity,dt);
        p.move (dt);
        cout << "(" << p.x << ", " << p.y << ") ";
        
    }
    cout << endl;

     
    }
    return 0;
}
    
