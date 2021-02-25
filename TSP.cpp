#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <queue>
#include <limits>

struct Point
{
    int num;
    int x;
    int y;
};

float RouteDistance(std::vector<int> route, std::vector<std::vector<float>> distance)
{
    float dist = 0.0;
    for(int i = 0; i <= route.size(); i++)
    {
        if(i == 0) {}
        else if(i == route.size())
            dist += distance[route[route.size() - 1]][0];
        else
            dist += distance[route[i - 1]][route[i]];
    }

    return dist;
}

void RoutePrint(std::vector<int> route)
{
    for(int i = 0; i <= route.size(); i++)
    {
        if(i == 0)
            std::cout << route[i] + 1;
        else if(i == route.size())
            std::cout << " -> " << route[0] + 1;
        else
            std::cout << " -> " << route[i] + 1;
    }
}

std::vector<int> optSwap(std::vector<int> route, int i, int k)
{
    std::vector<int> new_route;
    for(int x = 0; x < i; x++)
        new_route.push_back(route[x]);

    for(int x = k; x >= i; x--)
        new_route.push_back(route[x]);

    for(int x = k + 1; x < route.size(); x++)
        new_route.push_back(route[x]);

    return new_route;
}

int main()
{
    std::vector<Point> base;
    std::string trash, points;
    std::vector<int> route;
    float best_distance;

    getline (std::cin, trash);
    getline (std::cin, trash);
    getline (std::cin, trash);
    getline (std::cin, trash);
    getline (std::cin, trash);
    getline (std::cin, points);
    getline (std::cin, trash);
    getline (std::cin, trash);

    int dim = atoi(points.substr(12, points.size()).c_str());

    std::vector<std::vector<float>> distance(dim);   // Macierz odleglosci miedzy punktami
    bool visited[dim] = {};

    for(int i = 0; i < dim; i++)
    {
        Point p;
        std::cin >> p.num >> p.x >> p.y;
        base.push_back(p);
    }

    std::cin >> trash;

    float d;

    for(int i = 0; i < base.size(); i++) // Uzupelnianie macierzy odleglosciami (nieskonczonosc na przekatnej = -1)
    {
        for(int j = 0; j < base.size(); j++)
        {
            if(i == j)
                d = -1;
            else
                d = sqrt(pow((base[i].x - base[j].x), 2) + pow((base[i].y - base[j].y), 2));

            distance[i].push_back(d);
        }
    }

    float mini;
    int last_index = 0; // Cykl zaczyna się od punktu pierwszego
    int curr_index = 0;

    while(route.size() != dim) // Tworzenie cyklu Hamiltona (najblizszy sasiad)
    {
        mini = std::numeric_limits<double>::max();
        visited[last_index] = true;
        route.push_back(last_index);

        for(int j = 0; j < base.size(); j++)
        {
            if(j != last_index)
            {
                if(visited[j] == false)
                {
                    if(distance[last_index][j] < mini)
                    {
                        mini = distance[last_index][j];
                        curr_index = j;
                    }
                }
            }
        }
        last_index = curr_index;
    }

    std::cout << "\nHamilton Route: \n";
    RoutePrint(route);
    best_distance = RouteDistance(route, distance);
    std::cout << "\nDistance: " << best_distance;

    std::vector<int> new_route;
    float new_distance;
    bool finish = true;

    while(true)
    {
        std::vector<int> last_route = route;
        for(int i = 0; i < dim - 1; i++)
        {
            for(int j = i + 1; j < dim; j++)
            {
                new_route = optSwap(route, i, j);
                new_distance = RouteDistance(new_route, distance);
                if(new_distance < best_distance)
                {
                    route = new_route;
                    best_distance = new_distance;

                    std::cout << "\n2opted Route: \n";
                    RoutePrint(new_route);
                    std::cout << "\nDistance: " << best_distance;
                }
            }
        }

        int finish = 0;
        for(int i = 0; i < route.size(); i++)
        {
            if(route[i] == last_route[i])
                finish++;
        }

        if(finish == route.size()) break;
    }

    std::cout << "\n\nFinal distance: " << best_distance;

    return 0;
}
