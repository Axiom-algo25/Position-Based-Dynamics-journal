#include "raylib.h"
#include "raylib.h"
#include <cmath>
#include <vector>

struct Particle {
    float x, y;
    float oldX, oldY;
    bool pinned;
};

struct Constraint {
    int a, b;
    float restLength;
};

const int COLS = 20;
const int ROWS = 15;
const float SPACING = 30.0f;
const int SOLVER_ITERATIONS = 10;

std::vector<Particle> particles;
std::vector<Constraint> constraints;

void setup() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Particle p;
            p.x = 200 + c * SPACING;
            p.y = 50 + r * SPACING;
            p.oldX = p.x;
            p.oldY = p.y;
            p.pinned = (r == 0);
            particles.push_back(p);
        }
    }

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int i = r * COLS + c;
            if (c < COLS - 1) {
                constraints.push_back({i, i + 1, SPACING});
            }
            if (r < ROWS - 1) {
                constraints.push_back({i, i + COLS, SPACING});
            }
        }
    }
}

void simulate(float dt, bool windOn) {
    for (auto& p : particles) {
        if (p.pinned) continue;

        float vx = (p.x - p.oldX) * 0.99f;
        float vy = (p.y - p.oldY) * 0.99f;

        p.oldX = p.x;
        p.oldY = p.y;

        p.x += vx;
        p.y += vy;
        p.y += 9.8f * dt * dt * 60.0f;

        if (windOn) {
            p.x += 0.5f * dt * 60.0f;
        }
    }

    for (int iter = 0; iter < SOLVER_ITERATIONS; iter++) {
        for (auto& c : constraints) {
            Particle& a = particles[c.a];
            Particle& b = particles[c.b];

            float dx = b.x - a.x;
            float dy = b.y - a.y;
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist == 0.0f) continue;

            float diff = (dist - c.restLength) / dist * 0.5f;

            if (!a.pinned) {
                a.x += dx * diff;
                a.y += dy * diff;
            }
            if (!b.pinned) {
                b.x -= dx * diff;
                b.y -= dy * diff;
            }
        }
    }
}

void drawCloth() {
    for (auto& c : constraints) {
        Particle& a = particles[c.a];
        Particle& b = particles[c.b];
        DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, BLUE);
    }

    for (auto& p : particles) {
        Color col = p.pinned ? GREEN : WHITE;
        DrawCircle((int)p.x, (int)p.y, p.pinned ? 5 : 2, col);
    }
}

int main() {
    InitWindow(800, 600, "Cloth Simulation");
    SetTargetFPS(60);
    setup();

    bool windOn = false;
    int grabbed = -1;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_W)) windOn = !windOn;
        if (IsKeyPressed(KEY_R)) {
            particles.clear();
            constraints.clear();
            setup();
        }

        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            float closest = 20.0f;
            for (int i = 0; i < (int)particles.size(); i++) {
                float dx = particles[i].x - mouse.x;
                float dy = particles[i].y - mouse.y;
                float d = sqrtf(dx * dx + dy * dy);
                if (d < closest) {
                    closest = d;
                    grabbed = i;
                }
            }
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && grabbed != -1) {
            particles[grabbed].x = mouse.x;
            particles[grabbed].y = mouse.y;
            particles[grabbed].oldX = mouse.x;
            particles[grabbed].oldY = mouse.y;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) grabbed = -1;

        simulate(dt, windOn);

        BeginDrawing();
        ClearBackground(BLACK);
        drawCloth();
        DrawText(windOn ? "Wind: ON  (W)" : "Wind: OFF (W)", 10, 10, 18, GRAY);
        DrawText("Drag cloth with mouse", 10, 35, 18, GRAY);
        DrawText("R = reset", 10, 60, 18, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}