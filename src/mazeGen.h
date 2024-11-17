
void randomMazeNoise(Point matrix[][screenHeight/scale], int amount){
    int sizeX = screenWidth/scale;
    int sizeY = screenHeight/scale;
    int vx, vy;
    for (int i = 0; i < amount; i++){
        vx = 2*(rand()%((sizeX/2)-1));
        vy = 2*(rand()%((sizeY/2)-1));
        if ((vx == 0 || vy == 0) || (vx == sizeX || vy == sizeY)) continue;
        matrix[vx][vy].isWall = false;
    }
    
}
void makeMaze(Point matrix[][screenHeight/scale]){
    stack<pair<int, int>> stack;
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < screenWidth/scale; i++){
        for (int j = 0; j < screenHeight/scale; j++){
            matrix[i][j].isWall = 1;
            matrix[i][j].visited = 0;
        }
    }
    stack.push({1, 1});
    matrix[1][1].isWall = 0;
    pair<int, int> curr_node;
    int r;
    auto isBounds = [&](pair<int, int> pos, int dx=0, int dy=0){
        return pos.first+dx >= 0 && pos.first+dx < screenWidth/scale && pos.second+dy >= 0 && pos.second+dy < screenHeight/scale;
    };
    auto isPossible = [&](pair<int, int> pos){
        return  (isBounds(pos, 2, 0) && matrix[pos.first+1][pos.second].isWall && !matrix[pos.first+2][pos.second].visited) || 
                (isBounds(pos, -2, 0) && matrix[pos.first-1][pos.second].isWall && !matrix[pos.first-2][pos.second].visited) || 
                (isBounds(pos, 0, 2) && matrix[pos.first][pos.second+1].isWall && !matrix[pos.first][pos.second+2].visited) || 
                (isBounds(pos, 0, -2) && matrix[pos.first][pos.second-1].isWall && !matrix[pos.first][pos.second-2].visited);
    };
    int counter = 0;
    while (!stack.empty() && counter < (screenHeight/scale/2)*(screenWidth/scale/2) - 1){
        curr_node = stack.top();
        //cout << curr_node.first << " " << curr_node.second << endl;
        stack.pop();
        if (matrix[curr_node.first][curr_node.second].visited) continue;
        counter++;
        matrix[curr_node.first][curr_node.second].visited = 1;
        matrix[curr_node.first][curr_node.second].isWall = 0;
        r = rand()%4;
        if (!isPossible(curr_node)){
            curr_node = {1,1};
            //cout << "here\n";
            while (!isPossible(curr_node)){
                curr_node.first += 2;
                if (curr_node.first >= screenWidth/scale){
                    curr_node.first = 1;
                    curr_node.second += 2;
                }
                if (curr_node.second >= screenHeight/scale) break;
            }
        };
        while (!(inBounds({curr_node.first+directions[r].first*2, curr_node.second+directions[r].second*2}) && 
                    matrix[curr_node.first+directions[r].first][curr_node.second+directions[r].second].isWall &&
                    !matrix[curr_node.first+directions[r].first*2][curr_node.second+directions[r].second*2].visited)) r = rand()%4;
        stack.push({curr_node.first+directions[r].first*2, curr_node.second+directions[r].second*2});
        matrix[curr_node.first+directions[r].first][curr_node.second+directions[r].second].isWall = 0;
    }
    int scaleTo3 = scale*scale*scale;
    randomMazeNoise(matrix, (screenWidth*screenHeight)/((scaleTo3))/8);
}