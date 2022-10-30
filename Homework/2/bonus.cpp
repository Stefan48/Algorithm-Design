#include <bits/stdc++.h>
#define TIME_MAX 405
#define LOGS_MAX 85
using namespace std;
ifstream in("bonus.in");
ofstream out("bonus.out");

struct Position
{
    pair<int, int> position;
    int log;

    bool operator < (const Position &other) const
    {
        if(log == other.log)
        {
            if(position.first == other.position.first)
                return position.second < other.position.second;
            return position.first < other.position.first;
        }
        return log < other.log;
    };
    bool operator > (const Position &other) const
    {
        if(log == other.log)
        {
            if(position.first == other.position.first)
                return position.second > other.position.second;
            return position.first > other.position.first;
        }
        return log > other.log;
    };
    bool operator == (const Position &other) const
    {
        return position.first == other.position.first && position.second == other.position.second && log == other.log;
    }
};

// position of each log ((x_start, y_start), (x_end, y_end))
pair< pair<int, int>, pair<int, int> > pos_logs[LOGS_MAX];
// direction in which each log is moving
char dir[LOGS_MAX][TIME_MAX];
// vector containing all the logs stacked on each position
map< pair<int, int>, vector<int> > logs_on_pos;
// <(position, log), (energy, path)> - maps used for current and next possible positions of Robin
map< Position, pair<int, string> > *positions1, *positions2, *aux;

pair<int, int> next_position(pair<int, int> pos, char dir)
{
    switch(dir)
    {
        case 'N': return {pos.first, pos.second + 1};
        case 'S': return {pos.first, pos.second - 1};
        case 'E': return {pos.first + 1, pos.second};
        case 'V': return {pos.first - 1, pos.second};
        default: return pos;
    }
}

int main()
{
    int T, n;
    pair<int, int> dest;
    int w1, w2, w3;
    positions1 = new map< Position, pair<int, string> >;
    positions2 = new map< Position, pair<int, string> >;
    int result = INT_MAX;
    string result_path = "";

    in >> T >> n;
    in >> dest.first >> dest.second;
    in >> w1 >> w2 >> w3;
    for(int i = 1, xs, ys, xe, ye; i <= n; ++i)
    {
        in >> xs >> ys >> xe >> ye;
        // set pos_logs
        pos_logs[i] = {{xs, ys}, {xe, ye}};
        // set logs_on_pos
        if(xs == xe)
        {
            // vertical log
            for(int j = ys; j <= ye; ++j)
                logs_on_pos[{xs, j}].push_back(i);
        }
        else if(ys == ye)
        {
            // horizontal log
            for(int j = xs; j <= xe; ++j)
                logs_on_pos[{j, ys}].push_back(i);
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int t = 0; t < T; ++t)
            in >> dir[i][t];
    }

    Position position, new_position;
    pair<int, int> pos, new_pos;
    pair<int, int> log_start, log_end;
    int log, new_log;
    int energy, new_energy, prev_energy;
    string path, new_path, str;
    char log_idx[10];
    map< Position, pair<int, string> >::iterator it;

    pos = pos_logs[1].first;
    if(pos == dest)
        result = 0;
    position.position = pos;
    position.log = 1;
    positions1->insert({position, {0, ""}});

    for(int t = 0; t < T; ++t)
    {
        for(auto itr = positions1->begin(); itr != positions1->end(); ++itr)
        {
            position = itr->first;
            pos = position.position;
            log = position.log;
            energy = itr->second.first;
            path = itr->second.second;
            // check new solution
            if(pos == dest)
            {
                if(energy < result)
                {
                    result = energy;
                    result_path = path;
                }
                continue;
            }
            // if Robin stands still
            new_position.position = next_position(pos, dir[log][t]);
            new_position.log = log;
            new_energy = energy + w1;
            str = "H\n";
            new_path = path + str;
            it = positions2->find(new_position);
            if(it != positions2->end())
            {
                prev_energy = it->second.first;
                if(new_energy < prev_energy)
                    it->second = {new_energy, new_path};
            }
            else positions2->insert({new_position, {new_energy, new_path}});
            // if Robin moves on the same log
            log_start = pos_logs[log].first;
            log_end = pos_logs[log].second;
            if(log_start.first == log_end.first)
            {
                // vertical log
                if(pos.second + 1 <= log_end.second)
                {
                    // North
                    new_position.position = next_position({pos.first, pos.second + 1}, dir[log][t]);
                    new_position.log = log;
                    new_energy = energy + w2;
                    str = "N\n";
                    new_path = path + str;
                    it = positions2->find(new_position);
                    if(it != positions2->end())
                    {
                        prev_energy = it->second.first;
                        if(new_energy < prev_energy)
                            it->second = {new_energy, new_path};
                    }
                    else positions2->insert({new_position, {new_energy, new_path}});
                }
                if(pos.second - 1 >= log_start.second)
                {
                    // South
                    new_position.position = next_position({pos.first, pos.second - 1}, dir[log][t]);
                    new_position.log = log;
                    new_energy = energy + w2;
                    str = "S\n";
                    new_path = path + str;
                    it = positions2->find(new_position);
                    if(it != positions2->end())
                    {
                        prev_energy = it->second.first;
                        if(new_energy < prev_energy)
                            it->second = {new_energy, new_path};
                    }
                    else positions2->insert({new_position, {new_energy, new_path}});
                }
            }
            else
            {
                // horizontal log
                if(pos.first + 1 <= log_end.first)
                {
                    // East
                    new_position.position = next_position({pos.first + 1, pos.second}, dir[log][t]);
                    new_position.log = log;
                    new_energy = energy + w2;
                    str = "E\n";
                    new_path = path + str;
                    it = positions2->find(new_position);
                    if(it != positions2->end())
                    {
                        prev_energy = it->second.first;
                        if(new_energy < prev_energy)
                            it->second = {new_energy, new_path};
                    }
                    else positions2->insert({new_position, {new_energy, new_path}});
                }
                if(pos.first - 1 >= log_start.first)
                {
                    // West
                    new_position.position = next_position({pos.first - 1, pos.second}, dir[log][t]);
                    new_position.log = log;
                    new_energy = energy + w2;
                    str = "V\n";
                    new_path = path + str;
                    it = positions2->find(new_position);
                    if(it != positions2->end())
                    {
                        prev_energy = it->second.first;
                        if(new_energy < prev_energy)
                            it->second = {new_energy, new_path};
                    }
                    else positions2->insert({new_position, {new_energy, new_path}});
                }
            }
            // if Robin jumps on another log
            for(unsigned int i = 0; i < logs_on_pos[pos].size(); ++i)
            {
                new_log = logs_on_pos[pos][i];
                if(new_log != log)
                {
                    new_position.position = next_position(pos, dir[new_log][t]);
                    new_position.log = new_log;
                    new_energy = energy + w3;
                    sprintf(log_idx, "%d", new_log);
                    str = "J ";
                    new_path = path + str;
                    str = log_idx;
                    new_path += str;
                    str = "\n";
                    new_path += str;
                    it = positions2->find(new_position);
                    if(it != positions2->end())
                    {
                        prev_energy = it->second.first;
                        if(new_energy < prev_energy)
                            it->second = {new_energy, new_path};
                    }
                    else positions2->insert({new_position, {new_energy, new_path}});
                }
            }
        }

        positions1->clear();
        // swap pointers
        aux = positions1;
        positions1 = positions2;
        positions2 = aux;

        // update pos_logs and logs_on_pos
        logs_on_pos.clear();
        for(int i = 1; i <= n; ++i)
        {
            log_start = next_position(pos_logs[i].first, dir[i][t]);
            log_end = next_position(pos_logs[i].second, dir[i][t]);
            pos_logs[i] = {log_start, log_end};
            if(log_start.first == log_end.first)
            {
                // vertical log
                for(int j = log_start.second; j <= log_end.second; ++j)
                    logs_on_pos[{log_start.first, j}].push_back(i);
            }
            else if(log_start.second == log_end.second)
            {
                // horizontal log
                for(int j = log_start.first; j <= log_end.first; ++j)
                    logs_on_pos[{j, log_start.second}].push_back(i);
            }
        }
    }

    for(it = positions1->begin(); it != positions1->end(); ++it)
    {
        position = it->first;
        pos = position.position;
        //log = position.log;
        energy = it->second.first;
        path = it->second.second;
        if(pos == dest && energy < result)
        {
            result = energy;
            result_path = path;
        }
    }
    int path_length = 0;
    for(int i = 0; result_path[i] != '\0'; ++i)
        if(isalpha(result_path[i])) path_length++;

    out << result << '\n' << path_length << '\n' << result_path;

    delete positions1;
    delete positions2;
    return 0;
}
