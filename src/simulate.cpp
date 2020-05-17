/**
    simulate.cpp

    Purpose: implements a Simulation class which
    simulates a robot living in a 2D world. Relies 
    on localization code from localizer.py 

*/

#include "localizer.cpp"
#include <algorithm>
// #include "helpers.cpp"

class Simulation {

private:
    vector <char> get_colors() {
        vector <char> all_colors;
        char color;
        int i,j;
        for (i=0; i<height; i++) {
            for (j=0; j<width; j++) {
                color = grid[i][j];
                if(std::find(all_colors.begin(), all_colors.end(), color) != all_colors.end()) {
                    /* v contains x */
                } else {
                    all_colors.push_back(color);
                    cout << "adding color " << color << endl;
                    /* v does not contain x */
                }
            }
        }
        colors = all_colors;
        num_colors = colors.size();
        return colors;
    }

public: 
    vector < vector <char> > grid;
    vector < vector <float> > beliefs;

    float blur, p_hit, p_miss, incorrect_sense_prob;

    int height, width, num_colors;

    std::vector<int> true_pose;
    std::vector<int> prev_pose;

    vector <char> colors;
    Simulation(vector < vector<char> >, float, float, vector <int>);

};

/**
Constructor for the Simulation class.
*/
Simulation::Simulation(vector < vector <char> > map, 
    float blurring,
    float hit_prob, 
    std::vector<int> start_pos
    ) 
{
    grid = map;
    blur = blurring;
    p_hit = hit_prob;
    p_miss = 1.0 - hit_prob;
    beliefs = initialize_beliefs(map);
    incorrect_sense_prob = p_miss / (p_hit + p_miss);
    true_pose = start_pos;
    prev_pose = true_pose;
}

/**
You can test your code by running this function. 

Do that by first compiling this file and then 
running the output.
*/
/*
 int main() {

     vector < vector <char> > map;
     vector <char> mapRow;
     int i, j, randInt;
     char color;
     std::vector<int> pose(2);
     srand((unsigned) time (NULL)); //给srand()提供一个种子，它是一个unsigned int类型；与时间相关
     int map_row =5, map_col=5;

     pose[0] = rand()%map_row; //给pose分配一个随机位置
     pose[1] = rand()%map_col;

     for (i = 0; i < map_row; i++)
     {
         mapRow.clear();
         for (j=0; j< map_col; j++)
         {
             randInt = rand()%2; //rand()产生随机数
             if (randInt == 0 ) {
                 color = 'r';
             } 
             else {
                 color = 'g';
             }
             mapRow.push_back(color);
         }
         map.push_back(mapRow);
     }
     cout << "map is\n";
     Simulation simulation (map, 0.1, 0.9, pose);
      //simulation = Simulation(map, 0.1, 0.9, pose);
     cout << "initialization success!\n";
     show_grid(map);

     cout << "x, y = (" << simulation.true_pose[0] << ", " << simulation.true_pose[1] << ")" << endl;
     return 0;
 }
*/