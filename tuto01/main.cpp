/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "math.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800


class Entity {
private:
    Texture2D texture;
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    float scale;
    float rotation;

public:
    Entity() {}

    Entity(Texture2D texture, Vector2 position, Vector2 speed) {
        this->texture = texture;
        this->position = position;
        this->speed = speed;
        this->size.x = texture.width;
        this->size.y = texture.height;
        this->scale = 1.0f;
        this->rotation = 0.0f;
    }

    void draw() {
        // existe esse e o pro
        // o pro considera a scala
        // rectangle
        // passa x e y de onde vai começar e acabar, ai passa 0,0 e a largura e altura da imagem original
        Rectangle src = {0, 0, (float) (texture.width), (float) (texture.height)};
        Rectangle dst = {position.x, position.y, size.x, size.y};
        Vector2 origin = {size.x / 2, size.y / 2};
        DrawTexturePro(texture, src, dst, origin, rotation+90, WHITE);
    }

    void setScale(float scale) {
        this->scale = scale;
        this->size.x = abs(this->texture.width * scale);
        this->size.y = abs(this->texture.height * scale);
    }

    void setRotation(float rotation) {
        this->rotation = rotation;
    }

    void update() {
        if (IsKeyDown(KEY_W)) {
            setScale(scale += 0.1f);
        } else if (IsKeyDown(KEY_S)) {
            setScale(scale -= 0.1f);
        } else if (IsKeyDown(KEY_D)) {
            setRotation(rotation += 0.1f);
        } else if (IsKeyDown(KEY_A)) {
            setRotation(rotation -= 0.1f);
        }
    }

};


class Game {
private:
    Entity pumpkin;

public:
    Game() {
        // set up the window
        InitWindow(1024, 800, "Raylib CPP");
    }

    void init_game() {
        pumpkin = Entity(LoadTexture("assets/abrobora.png"),
                         {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
                         {10, 10});
        pumpkin.setScale(10);
    }

    void run() {
        init_game();

        // game loop
        while (!WindowShouldClose()) {

            pumpkin.update();
            // drawing
            BeginDrawing();
            ClearBackground(BLACK);

            DrawText("Pumpkin Scrimblin Monkin Limin Lemon", 200, 200, 20, WHITE);
            pumpkin.draw();

            EndDrawing();
        }

        // cleanup
        CloseWindow();
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}