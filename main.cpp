#include "raylib.h"
#include <iostream>
#include <numbers>
#include <cmath>

double pi = std::numbers::pi;


struct Planet {
        std::string name;
        long double mass;
        long double radius;
        double density;
        Color color;
        float x;
        float y;

        Planet(std::string Name, long double Mass, long double Radius, Color Color, float X, float Y) {
            name = Name;
            mass = Mass;
            radius = Radius;
            density = mass / ((4.0/3.0) * pi * pow(radius, 3));
            color = Color;
            x = X;
            y = Y;
        }

        void DrawPlanet() {
            DrawCircle(x, y, radius, color);
        }

        void MovePlanet(float distance_x, float distance_y) {
            x += distance_x;
            y += distance_y;
        }
    };

int main() {

    int ScreenWidth = 1600;
    int ScreenHeight = 1000;

    Planet earth("Earth", 6 * pow(10, 4), 100, BLUE, 800, 500);
    Planet asteroid("101", 5 * pow(10, -18), 20, WHITE, 100, 100);


    InitWindow(ScreenWidth, ScreenHeight, "Raylib");

    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();

        earth.DrawPlanet();

        asteroid.DrawPlanet();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}