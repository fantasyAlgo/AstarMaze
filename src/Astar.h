#include <queue>

struct PointPriority{
    int fDistance;
    pair<int, int> pos;
    bool operator>(const PointPriority &rhs) const{
        return fDistance > rhs.fDistance;
    }
};
bool inBounds(pair<int, int> pos){
    return pos.first >= 0 && pos.first < screenWidth/scale && pos.second >= 0 && pos.second < screenHeight/scale;
}
vector<pair<int, int>> Astar(Point matrix[][screenHeight/scale], pair<int, int> startPoint, pair<int, int> endPoint){
    priority_queue<PointPriority, vector<PointPriority>, greater<PointPriority>> pq;
    for (int i = 0; i < screenWidth/scale; i++)
        for (int j = 0; j < screenHeight/scale; j++){
            matrix[i][j].gDistance = INT_MAX;
            matrix[i][j].hDistance = abs(i - endPoint.first) + abs(j - endPoint.second);
            matrix[i][j].dir = -1;
            matrix[i][j].visited = false;
        }
    pq.push({matrix[startPoint.first][startPoint.second].hDistance , startPoint});
    matrix[startPoint.first][startPoint.second].gDistance = 0;
    pair<int, int> curr_node;
    auto get = [&](pair<int, int> pos, int dx=0, int dy=0){
        return matrix[pos.first+dx][pos.second+dy];
    };
    auto check_and_push = [&](pair<int, int> pos, int dx, int dy){
        if (inBounds({pos.first+dx, pos.second+dy}) && !get(pos, dx, dy).isWall && !get(pos, dx, dy).visited && 
                (get(pos, dx,dy).gDistance != INT_MAX || 
                get(pos, dx,dy).gDistance+10 < get(pos, dx,dy).gDistance)){
            matrix[pos.first+dx][pos.second+dy].gDistance = get(pos).gDistance+10;
            matrix[pos.first+dx][pos.second+dy].dir = (dx == 0 ? dy == 1 ? 2 : 4 : dx == 1 ? 1 : 3);
            pq.push({get(pos).gDistance+10 + get(pos,dx,dy).hDistance,{pos.first+dx, pos.second+dy}});
        }
    };
    while (pq.size() > 0){
        curr_node = pq.top().pos;
        pq.pop();
        if (matrix[curr_node.first][curr_node.second].visited) continue;
        matrix[curr_node.first][curr_node.second].visited = true;
        //cout << curr_node.first << " " << curr_node.second << endl;
        //cout << "values node -> " << matrix[curr_node.first+1][curr_node.second].visited << " " << matrix[curr_node.first-1][curr_node.second].visited << " " << matrix[curr_node.first][curr_node.second+1].visited << " " << matrix[curr_node.first][curr_node.second-1].visited << endl;
        if (curr_node == endPoint){
            //cout << "Path found\n";
            vector<pair<int, int>> path;
            while (curr_node != startPoint){
                path.push_back({curr_node.first, curr_node.second});
                if (matrix[curr_node.first][curr_node.second].dir == 1)
                    curr_node.first--;
                else if (matrix[curr_node.first][curr_node.second].dir == 2)
                    curr_node.second--;
                else if (matrix[curr_node.first][curr_node.second].dir == 3)
                    curr_node.first++;
                else if (matrix[curr_node.first][curr_node.second].dir == 4)
                    curr_node.second++;
            }
            return path;
        }
        check_and_push(curr_node, 1, 0);
        check_and_push(curr_node, -1, 0);
        check_and_push(curr_node, 0, 1);
        check_and_push(curr_node, 0, -1);
    }
    return vector<pair<int, int>>();
}