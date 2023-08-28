/*******************************************************************************************
* Basic 2D game with raylib.
* 
* To build: 
*		Ctrl + Sht + B
* To run: 
* 		$ ./main
* 
********************************************************************************************/

#include <cmath>
#include <string>
#include "raylib.h"
#include "vector"
#include "cstdlib"
#include "map"


using namespace std; // nao precisar escrever std:: toda hora


#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 800

#define GETSET(type, field) protected: type field; public: type get_##field() { return field; }; void set_##field(type value) {field = value;}

////////////////////////////////////////////////////////////////////////
// ENTITY CLASS
////////////////////////////////////////////////////////////////////////




class Entity {
private:
GETSET(Texture2D, texture);
GETSET(Vector2, pos);
GETSET(Vector2, vel);
GETSET(Vector2, size);
GETSET(float, rotation);
GETSET(float, rotationSpeed);
GETSET(float, radius);
GETSET(bool, visible);

    float scale;


    // visible // é pra desenhar ou nao
    // radius circulo em volta da entidade, basicamente a colisao

public:
    Entity() {}

    Entity(Texture2D texture, Vector2 pos, Vector2 vel) {
        this->texture = texture;
        this->pos = pos;
        this->vel = vel;
        this->size.x = texture.width;
        this->size.y = texture.height;
        this->scale = 1.0f;
        this->rotation = 0.0f;
    }

    void set_scale(float scale) {
        this->scale = scale;
        this->size.x = fabs(this->texture.width * scale);
        this->size.y = fabs(this->texture.height * scale);
        this->radius = size.x * 0.8f;
    }

    // delta time = tempo que foi o ultimo frame
    // virtual é pra indicar que pode ser sobreposto de outra classe
    virtual void update(float delta_time) {
//        if (IsKeyDown(KEY_W))
//            set_scale(scale + 0.1f);
//        else if (IsKeyDown(KEY_S))
//            set_scale(scale - 0.1f);
//
//        if (IsKeyDown(KEY_D))
//            rotation += 0.1f;
//        else if (IsKeyDown(KEY_A))
//            rotation -= 0.1f;
    }

    void draw() {
        Rectangle src = {0, 0, (float) texture.width, (float) texture.height};
        Rectangle dst = {pos.x, pos.y, size.x, size.y};
        Vector2 origin = {size.x / 2, size.y / 2};

        DrawTexturePro(texture, src, dst, origin, rotation + 90, WHITE);
    }

    void screen_wrap() {
        if (pos.x < -size.x / 2) {
            pos.x = SCREEN_WIDTH + size.x / 2;
        } else if (pos.x > SCREEN_WIDTH + size.x / 2) {
            pos.x = -size.x / 2;
        }

        if (pos.y < -size.y / 2) {
            pos.y = SCREEN_HEIGHT + size.y / 2;
        } else if (pos.y > SCREEN_HEIGHT + size.y / 2) {
            pos.y = -size.y / 2;
        }
    }
};

////////////////////////////////////////////////////////////////////////
// PUMPKIN CLASS
////////////////////////////////////////////////////////////////////////
class Pumpkin : public Entity {
public:
    Pumpkin() {}

    Pumpkin(Texture2D texture, Vector2 pos, Vector2 vel) : Entity(texture, pos, vel) {}

    void update(float delta_time) override {
        rotation += rotationSpeed *
                    delta_time; // todo deslocamento de entidade vc multiplica pela taxa de quadro, se nao ele fica diferente pra cada jogo

        pos.x += vel.x * delta_time;
        pos.y += vel.y * delta_time;
        screen_wrap();
    }

};


////////////////////////////////////////////////////////////////////////
// PLAYER CLASS
////////////////////////////////////////////////////////////////////////
class Player : public Entity {
public:
    Player() {}

    Player(Texture2D texture, Vector2 pos, Vector2 vel) : Entity(texture, pos, vel) {}

    void update(float delta_time) override {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            vel = {0, -400};
            rotation = 270;
        } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            vel = {0, 400};
            rotation = 90;
        } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            vel = {400, 0};
            rotation = 0;
        } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            vel = {-400, 0};
            rotation = 180;
        } else if (IsKeyDown(KEY_H)) {
            vel = {0, 0};
        }
        pos.x += vel.x * delta_time;
        pos.y += vel.y * delta_time;
        screen_wrap();
    }

};

////////////////////////////////////////////////////////////////////////
// GAME CLASS
////////////////////////////////////////////////////////////////////////

class Game {
private:
    Player player;
    vector<Pumpkin> pumpkins;
    map<string, Texture2D> cache;
    float launchCounter;
    float launchDelay;

public:
    Game() {
        // set up the window
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Basic Game");
        SetTargetFPS(60);
        launchCounter = 0;
        launchDelay = 1.0;
    }

    Texture2D get_cache_texture(string key) {
        if (cache.count(key) == 0) {
            cache[key] = LoadTexture(key.c_str()); // converter uma string(objeto) do c++ para uma string do c (char *)
        }
        return cache[key];
    }

    void init_game() {
        player = Player(get_cache_texture("assets/nave.png"), {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {0, 0});
        player.set_scale(2);
    }

    void launch_pumpkin() {
        Texture2D texture2D = get_cache_texture("assets/abrobora.png");
        Vector2 vel = {(float) (rand() % 601 - 300), (float) (rand() % 600 - 300)};
        Pumpkin pumpkin = Pumpkin(texture2D, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, vel);
        pumpkin.set_rotationSpeed(rand() % 100 - 50);
        pumpkin.set_scale(4);
        pumpkins.push_back(pumpkin);
    }

    // vai passar pra atualizar  e para cada instancia ele faz algo
    void game_update(float delta_time) {
        player.update(delta_time);

        launchCounter += delta_time;
        if (launchCounter > launchDelay) {
            launchCounter -= launchDelay;
            launch_pumpkin();
            launchDelay -= 0.01f;
            if (launchDelay < 0.3f) {
                launchDelay = 0.3f;
            }
        }

        for (Pumpkin &e: pumpkins) {
            e.update(delta_time);
        }
    }

    void run() {
        init_game();

        // game loop
        while (!WindowShouldClose()) {
            game_update(GetFrameTime());

            // drawing
            BeginDrawing();
            ClearBackground(BLACK);
            //DrawText("Hello Raylib UTF Game Group", 200,200,20,WHITE);
            player.draw();
            for(Pumpkin& e : pumpkins) {
                e.draw();
            }

            DrawFPS(SCREEN_WIDTH - 100, 20);

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