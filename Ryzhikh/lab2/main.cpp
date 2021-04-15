#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;



class FindingPath {
public:
    FindingPath() = default;
    vector<char> GreedyAlgorithm();
    vector<char> AStar();
    void Sort();
    void SortAStar();
    void Read();
    int Heuristic(char a, char b);

private:
    map<char, vector<pair<char, double>>> graph;
    map<char, bool> visited;
    char start;
    char end;
    int number;
};

struct Sorting { //функция сортировки для приоритетной очереди
    bool operator() (pair<char, double> a, pair<char, double> b) {
        //если стоимость двух вершин равна, то возвращается меньшая из них в алфавитном порядке, если стоимость разная, то большая из них
        if (a.second == b.second)
            return (a.first < b.first);
        else
            return (a.second > b.second);
    }
};

int FindingPath::Heuristic(char a, char b) {
    return abs(a - b);
}

vector<char> FindingPath::AStar() {  //А*
    cout << "\nАлгоритм А*:\n";
    map<char, pair<vector<char>, double>> ShortPathes;  //текущие кратчайшие пути
    vector<char> vertex;
    priority_queue < pair<char, double>, vector<pair<char, double>>, Sorting> PriorityQueue; //очередь в алгоритме

    PriorityQueue.push({ start, 0 });
    vertex.push_back(start);
    ShortPathes[start].first = vertex;

    while (!PriorityQueue.empty()) {  //пока очередь не пуста
        if (PriorityQueue.top().first == end) {  //если найдена конечная вершина
            cout << "Найдена конечная вершина!\n";
            return ShortPathes[end].first;  //то заканчивается поиск
        }

        auto TmpVertex = PriorityQueue.top();  //достается приоритетная вершина из очереди
        cout << "Текущая вершина - " << TmpVertex.first << endl;
        PriorityQueue.pop();

        for (auto& i : graph[TmpVertex.first]) {  //рассматриваются все вершины, которые соединены с текущей вершиной
            cout << "   Рассматривается смежная для " << TmpVertex.first << " вершина "<< i.first << endl;
            double CurLength = ShortPathes[TmpVertex.first].second + i.second;
            if (ShortPathes[i.first].second == 0 || ShortPathes[i.first].second > CurLength) { //если пути нет или найденный путь короче
                cout << "       В путь родительской вершины добавляется текущая вершина " << i.first <<"(" << CurLength << ")"<< endl;
                vector<char> path = ShortPathes[TmpVertex.first].first;  //добавляется в путь родительской вершины текущая вершина с кратчайшим путем
                path.push_back(i.first);
                ShortPathes[i.first] = { path, CurLength };  //обновление пути и расстояния
                int heur = Heuristic(TmpVertex.first, i.first);
                cout << "   Эвристика для вершин " << TmpVertex.first << " и " << i.first << " = " << heur << endl << endl;
                PriorityQueue.push({ i.first, heur + ShortPathes[i.first].second }); //записывается в очередь текущая вершина 
            }

        }

    }
    return ShortPathes[end].first;
}


void FindingPath::SortAStar() {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cout << "Для вершины " << it->first << " есть следующие смежные вершины:\n";
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second[i].first << '(' << it->second[i].second << ')' << ' ';
        }
        cout << endl;
        std::sort(it->second.begin(), it->second.end(), [](pair<char, double>& a, pair<char, double>& b) -> bool 
            { 
                if (a.second == b.second)
                    return (a.first < b.first);
                else
                    return (a.second < b.second); 
            });
        cout << "Отсортированные вершины:\n";
        for (int j = 0; j < it->second.size(); j++) {
            cout << it->second[j].first << '(' << it->second[j].second << ')' << ' ';
        }
        cout << endl;
    }
}


void FindingPath::Sort() {
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cout << "Для вершины " << it->first << " есть следующие смежные вершины:\n";
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second[i].first << '(' << it->second[i].second << ')' << ' ';
        }
        cout << endl;
        std::sort(it->second.begin(), it->second.end(), [](pair<char, double>& a, pair<char, double>& b) -> bool {return a.second < b.second; });
    
        cout << "Отсортированные вершины:\n";
        for (int j = 0; j < it->second.size(); j++) {
            cout << it->second[j].first << '(' << it->second[j].second << ')' << ' ';
        }
        cout << endl;
    }
}


void FindingPath::Read() {
    char start, end;
    cin >> start >> end;
    this->start = start;
    this->end = end;
    int count = 0;

    while (cin >> start) {
        if (start == '0')  //символ остановки ввода данных
            break;
        double weight;
        cin >> end >> weight;
        graph[start].push_back({ end,weight });
        visited[start] = false;
        visited[end] = false;
        count++;
    }
    this->number = count;
}



vector<char> FindingPath::GreedyAlgorithm() {
    cout << "\nЖадный алгоритм:\n";
    double min;
    vector<char> result;
    result.reserve(this->number);
    result.push_back(this->start);

    char CurVertex = this->start;

    while (CurVertex != this->end) {
        cout << "Текущая вершина - " << CurVertex << endl;
        char NextVertex;
        min = 100;
        bool found = false;

        for (auto& i : this->graph[CurVertex]) {
            //cout << "Рассматривается смежная вершина - " << i.first << endl;
            if (!visited[i.first] && i.second < min) {
                cout << "Идём в вершину " << i.first << "(" << i.second << ")\n";
                min = i.second;
                NextVertex = i.first;
                found = true;
        
            }
        }
        //cout << endl;
        visited[CurVertex] = true;

        if (!found) {
            if (!result.empty()) {
                cout << "Из вершины " << CurVertex << " конечная вершина недостижима, возвращаемся обратно\n";
                result.pop_back();
                CurVertex = result.back();
            }
            continue;
        }
        CurVertex = NextVertex;
        result.push_back(CurVertex);
        cout << endl;
    }
    cout << "Конец алгоритма!\n";
    return result;
}


int main() {
    setlocale(LC_ALL, "Russian");
    FindingPath answer;
    answer.Read();
    answer.SortAStar();
    vector<char> out = answer.AStar();
    cout << "Ответ:";
    for (auto& i : out) {
        cout << i;
    }
    return 0;
}