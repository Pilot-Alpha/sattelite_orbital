#include "raylib.h"
#include <iostream>
#include <numbers>
#include <cmath>
#include <tuple>
#include <string>

// declaring constants
const double pi = std::numbers::pi;
const double G = 2.62144 * pow(10, -6);
const float dt = 100.0f; // seconds spent per frame


struct Planet {
        std::string name;
        long double mass;
        long double radius;
        double density;
        Color color;

        std::tuple<float, float> r;
        std::tuple<float, float> v;

        Planet(std::string Name, long double Mass, long double Radius, Color Color, float X, float Y, float Vx, float Vy) {
            name = Name;
            mass = Mass;
            radius = Radius;
            density = mass / ((4.0f/3.0f) * pi * pow(radius, 3));
            color = Color;

            r = {X, Y};
            v = {Vx, Vy};
        }



        void DrawPlanet() {
            auto [x, y] = r;
            DrawCircle(x, y, radius, color);
        }


        auto CalculateAcceleration(const Planet& planet) {
            auto [x, y] = r;
            float rx = std::get<0>(planet.r) - x;
            float ry = std::get<1>(planet.r) - y;
            float r_net = std::sqrt(pow(rx, 2) + pow(ry, 2));

            // avoid division by 0 problem
            if (r_net < 1.0f) r_net = 1.0f; 

            float a = (G * planet.mass / pow(r_net, 2));
            float sin_theta = ry/r_net;
            float cos_theta = rx/r_net;
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
            
        }
    };

int main() {

    int ScreenWidth = 1600;
    int ScreenHeight = 1000;

    float asteroid_orbital_velocity = pow(G * 60000/ 200, 0.5);

    Planet earth("Earth", 6 * pow(10, 4), 100, BLUE, 800, 500, 0, 0);
    Planet asteroid("101", 5 * pow(10, -18), 20, WHITE, 800, 300, asteroid_orbital_velocity, 0);


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