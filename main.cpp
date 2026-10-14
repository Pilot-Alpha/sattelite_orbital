#include "raylib.h"
#include <iostream>
#include <numbers>
#include <cmath>
#include <tuple>
#include <string>

double pi = std::numbers::pi;
double G = 2.62 * pow(10, -9);
float dt = 1000.0f;


struct Planet {
        std::string name;
        long double mass;
        long double radius;
        double density;
        Color color;
        float x;
        float y;
        float vx;
        float vy;
        std::tuple<float, float> r;
        std::tuple<float, float> v;

        Planet(std::string Name, long double Mass, long double Radius, Color Color, float X, float Y, float Vx, float Vy) {
            name = Name;
            mass = Mass;
            radius = Radius;
            density = mass / ((4.0f/3.0f) * pi * pow(radius, 3));
            color = Color;
            x = X;
            y = Y;
            vx = Vx;
            vy = Vy;
            r = {X, Y};
            v = {Vx, Vy};
        }



        void DrawPlanet() {
            DrawCircle(x, y, radius, color);
        }


        auto CalculateAcceleration(const Planet& planet) {
            float rx = planet.x - x;
            float ry = planet.y - y;
            float r = std::sqrt(pow(rx, 2) + pow(ry, 2));

            if (r < 1.0f) r = 1.0f; 

            float a = (G * planet.mass / pow(r, 2));
            float sin_theta = ry/r;
            float cos_theta = rx/r;
            float ax = a * cos_theta;
            float ay = a * sin_theta;
            return std::make_tuple(ax, ay);
        }

        auto CalculateVelocity(auto v, auto a) {
            auto [vx, vy] = v;
            auto [ax, ay] = a;

            vx = vx + ax * dt;
            vy = vy + ay * dt;

            return std::make_tuple(vx, vy);
        }

        auto CalculateDisplacement(auto r, auto v) {
            auto [rx, ry] = r;
            auto [vx, vy] = v;

            rx += vx * dt;
            ry += vy * dt;

            return std::make_tuple(rx, ry);
        }

        void MovePlanet(const Planet& planet) {
            auto a = CalculateAcceleration(planet);
            v = CalculateVelocity(v, a);
            r = CalculateDisplacement(r, v);
            x = std::get<0>(r);
            y = std::get<1>(r);
            // sync the new velocity back
            vx = std::get<0>(v);
            vy = std::get<1>(v);
        }
    };

int main() {

    int ScreenWidth = 1600;
    int ScreenHeight = 1000;

    Planet earth("Earth", 6 * pow(10, 4), 100, BLUE, 800, 500, 0, 0);
    Planet asteroid("101", 5 * pow(10, -18), 20, WHITE, 1000, 900, 0, 0);


    InitWindow(ScreenWidth, ScreenHeight, "Raylib");

    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        earth.DrawPlanet();

        asteroid.DrawPlanet();

        asteroid.MovePlanet(earth);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}