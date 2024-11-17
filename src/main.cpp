#include "raylib.h"
#include <vector>
#include <utility>
#include <math.h>
#include <iostream>
#include <ctime> 
#include <stack>
using namespace std;

#define INT_MAX 2147483647
const int screenWidth = 800;
const int screenHeight = 450;
const int scale = 10;

struct Point{
    bool active;
    bool isWall;
    int gDistance;
    int hDistance;
    int dir;
    bool visited;
    Point(){
        active = false;
        gDistance = INT_MAX;
        hDistance = 0;
        visited = false;
        dir = -1;
        isWall = false;
    }
    int getF(){
        return gDistance + hDistance;
    }
};


#include "Astar.h"
#include "mazeGen.h"

void updatePoint(Point matrix[][screenHeight/scale], pair<int, int> &target_point){
    matrix[target_point.first][target_point.second].active = 0;
    target_point.first = GetMouseX()/scale;
    target_point.second = GetMouseY()/scale;
    matrix[target_point.first][target_point.second].active = 1;
}
struct Player{
    pair<float, float> pos;
};
int main(void){
    srand((unsigned)time(0)); 
    pair<int, int> start_point = {1, 1};
    pair<int, int> target_point = {10, 7};
    vector<pair<int, int>> path;
    float mouseX;
    float mouseY;
    bool isClicked = false;
    Point matrix[screenWidth/scale][screenHeight/scale];
    pair<int, int> prev_node;
    Player player;
    player.pos = {scale, scale};
    // Initialization
    matrix[start_point.first][start_point.second].active = 1;

    makeMaze(matrix);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(144);
    while (!WindowShouldClose()){
        mouseX = GetMouseX();
        mouseY = GetMouseY();
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            updatePoint(matrix, target_point);
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && prev_node.first != (int)mouseX/scale && prev_node.second != (int)mouseY/scale){
            prev_node = {(int)mouseX/scale, (int)mouseY/scale};
            matrix[(int)mouseX/scale][(int)mouseY/scale].isWall = !matrix[(int)mouseX/scale][(int)mouseY/scale].isWall;
        }else if (!IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) prev_node = {-1, -1};
        if (IsKeyPressed(KEY_SPACE)){
            makeMaze(matrix);
            matrix[start_point.first][start_point.second].active = 1;
            matrix[target_point.first][target_point.second].active = 1;
        }
        for (int i = 0; i < path.size(); i+=1)
            matrix[path[i].first][path[i].second].active = 0; 
        //cout << player.pos.first << " " << player.pos.second << endl;
        path = Astar(matrix, {round(player.pos.first/((float) scale)), round(player.pos.second/((float) scale))}, target_point);
        for (int i = 0; i < path.size(); i+=1)
            matrix[path[i].first][path[i].second].active = 1;  

        player.pos.first += (path.size() > 0 ? path[path.size()-1].first*scale - player.pos.first : 0)/100;  
        player.pos.second += (path.size() > 0 ? path[path.size()-1].second*scale - player.pos.second : 0)/100;
               
        BeginDrawing();
            ClearBackground(RED);
            for (int i = 0; i < screenWidth/scale; i++)
                DrawLine(i*scale, 0, i*scale, screenHeight, LIGHTGRAY);
            for (int i = 0; i < screenHeight/scale; i++)
                DrawLine(0, i*scale, screenWidth, i*scale, LIGHTGRAY);
            for (int i = 0; i < screenWidth/scale; i++)
                for (int j = 0; j < screenHeight/scale;j++)
                    DrawRectangle(i*scale, j*scale, scale-1, scale-1, matrix[i][j].active ? BLUE : matrix[i][j].isWall ? RED : BLACK);
            DrawRectangle(1+player.pos.first, 1+player.pos.second, scale-4, scale-4, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
