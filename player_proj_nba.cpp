
#include<map>
#include<vector>
#include<string>
#include<random>
#include<iostream>
#include<fstream>
#include <map>
#include <sstream>
#include<iterator>
#include <algorithm>
#include<string>
#include<stdlib.h>
#include<typeinfo>


using std::map; 
using std::vector;
using std::string; 
using std::ostream; using std::cout; using std::cin; using std::endl;
using std::fstream;
using std::ifstream;
using std::pair;
using std::stringstream;
using std::ostringstream;
using std::ostream_iterator;
using std::transform;
using std::make_pair;
using std::atof;

//Function to add player to the map
void add_player(string player,long salary, float proj_points, map<string, pair<long,float> > &player_map){
    pair<long,float> the_pair;
    the_pair = make_pair(salary,proj_points);
    player_map[player] = the_pair;
}

//Function to add point guards to the map
void player_update(map<string,pair<long,float> > &player_map_pg, map<string,pair<long,float> > &player_map_sg, map<string, pair<long, float> > &player_map_sf,map<string,pair<long,float> > &player_map_pf, map<string, pair<long, float> > &player_map_c,  string file_name){
 ifstream in_file(file_name);
 string player, player2, pos, date, vs, team, points2, sal;
 float points;
 //float salary;
 //float proj_points;
 
 while(in_file >> player >> player2 >> pos >> date >> vs >> team >> sal >> points >> points2) {
     sal = sal.substr(1);
     sal = sal.substr(0,sal.size()-1);
     float salary = strtof(sal.c_str(),0);
     salary = salary*1000;
     player = player+player2;
     if (pos == "PG") {
         add_player(player,salary,points,player_map_pg);
     }
     else if (pos == "SG") {
         add_player(player,salary,points,player_map_sg);
     }
     else if(pos == "SF"){
         add_player(player,salary,points,player_map_sf);
     }
     else if(pos == "PF"){
         add_player(player,salary,points,player_map_pf);
     }
     else if(pos == "C"){
         add_player(player,salary,points,player_map_c);
     }
     else {
         cout << "Error with: " << player << " " << player2 << endl;
     }
 }
}


//Function to optimize and eliminate weak candidates
void optimize_pos_c(map<string, pair<long, float> > &player_map){
    
    //Create a vector to store all the players who will be eliminated
    vector<string> losers;
    
    //Loop through the map twice
    for (map<string, pair<long,float> >::iterator it=player_map.begin(); it!=player_map.end(); ++it) {
        for (map<string, pair<long,float> >::iterator it2=player_map.begin(); it2!=player_map.end(); ++it2) {
            
            //If it's the same player, ignore it, else check to see if the cheaper guy scores more points
            if (it->first == it2->first) {}
            else {
                
            //If the cheaper guy scores more points, eliminate the more expensive guy because you would never
                //play a guy who costs more, but scores less
            if (((it->second.first) > (it2->second.first)) && (((it->second.second) < (it2->second.second)))) {
                //cout << "Problem is: " << it->first << "Costs More Than" << it2-> first << endl << " and had " << it->second.second << " points while "
                   //      << it2->first << " had " << it2->second.second << endl;               
                std::map<string,pair<long, float> >::iterator it3;
                string temp = it->first;
                 if(std::find(losers.begin(), losers.end(), temp) != losers.end()) {
                    
                } else {
                    losers.push_back(temp);
                }
          
            }         
            }
        }
    }
    
    //After you grab all the losers, delete them from the map 
    for (auto element : losers) {
        std::map<string,pair<long, float> >::iterator it3;
        it3=player_map.find(element);
        player_map.erase(it3);
    }
}


void optimize_pos(map<string, pair<long, float> > &player_map){
   vector<string> losers;
    for (map<string, pair<long,float> >::iterator it=player_map.begin(); it!=player_map.end(); ++it) {
        for (map<string, pair<long,float> >::iterator it2=player_map.begin(); it2!=player_map.end(); ++it2) {
            if (it->first == it2->first) {}
            else {
            for (map<string, pair<long,float> >::iterator it3=player_map.begin(); it3!=player_map.end(); ++it3) {
                if((it->first == it3->first)) {}
                else if (it2->first == it3->first) {}
                else {
            if (((it->second.first) > (it2->second.first)) && (((it->second.second) < (it2->second.second)))) {
                if (((it->second.first) > (it3->second.first)) && (((it->second.second) < (it3->second.second)))) {                
                string temp = it->first;
                if(std::find(losers.begin(), losers.end(), temp) != losers.end()) {
                    
                } else {
                    losers.push_back(temp);
                  }
                }
            }
            }
            }
            }          
        }
    }
    for (auto element : losers) {
       std::map<string,pair<long, float> >::iterator it3;
        it3=player_map.find(element);
        player_map.erase(it3);
    }
}

//Function to print off the squad
void print_max(vector<string> the_squad) {
    for (auto element : the_squad){
        cout << element << endl;
    }
}

//This function generates the best possible lineup using the maps
vector<string> optimize(map<string,pair<long,float> > &player_map_pg, map<string,pair<long,float> > &player_map_sg, map<string, pair<long, float> > &player_map_sf,map<string,pair<long,float> > &player_map_pf, map<string, pair<long, float> > &player_map_c){
   //create a bunch of initial variables to store things
    float projected_score=0;
    float max_score=0;
    vector<string> the_squad;
    long salary_total=0;
    long max_salary=0;
    size_t count=0;
    
    //The algorithm to produce the best is below.
    for (map<string, pair<long,float> >::iterator it=player_map_pg.begin(); it!=player_map_pg.end(); ++it) {
        for (map<string, pair<long,float> >::iterator it2=player_map_pg.begin(); it2!=player_map_pg.end(); ++it2) {
            if(it->first==it2->first) {}
            else {
            for (map<string, pair<long,float> >::iterator it3=player_map_sg.begin(); it3!=player_map_sg.end(); ++it3) {
                for (map<string, pair<long,float> >::iterator it4=player_map_sg.begin(); it4!=player_map_sg.end(); ++it4) {
                    if(it3->first==it4->first) {}
                    else {
                    for (map<string, pair<long,float> >::iterator it5=player_map_sf.begin(); it5!=player_map_sf.end(); ++it5) {
                        for (map<string, pair<long,float> >::iterator it6=player_map_sf.begin(); it6!=player_map_sf.end(); ++it6) {                         
                            if(it5->first == it6-> first) {}
                            else{
                                for (map<string, pair<long,float> >::iterator it7=player_map_pf.begin(); it7!=player_map_pf.end(); ++it7) {
                                        for (map<string, pair<long,float> >::iterator it8=player_map_pf.begin(); it8!=player_map_pf.end(); ++it8) {
                                            if(it7->first==it8->first){}
                                            else {
                                                for (map<string, pair<long,float> >::iterator it9=player_map_c.begin(); it9!=player_map_c.end(); ++it9) {
                                                projected_score = (it->second.second + it2->second.second + it3->second.second + it4->second.second + it5->second.second + it6->second.second + it7 ->second.second+it8->second.second +it9->second.second);
                                                count++;
                                                salary_total = (it->second.first + it2->second.first + it3 ->second.first +it4->second.first+it5->second.first+it6->second.first + it7->second.first+it8->second.first + it9->second.first);
                                                if ((projected_score > max_score) && (salary_total <= 60000)){
                                               
                                                    max_score = projected_score;
                                                    max_salary=salary_total;
                                                    the_squad.clear();
                                                    the_squad.push_back(it->first);
                                                    the_squad.push_back(it2->first);
                                                    the_squad.push_back(it3->first);
                                                    the_squad.push_back(it4->first);
                                                    the_squad.push_back(it5->first);
                                                    the_squad.push_back(it6->first);
                                                    the_squad.push_back(it7->first);
                                                    the_squad.push_back(it8->first);
                                                    the_squad.push_back(it9->first);
                                                    //if(projected_score > 275) {
                                                      //  cout << "Max Score: " << max_score << "  Cost: $" << max_salary << endl;
                                                        //cout << "Made: " << count << " lineups." << endl;
                                                       // print_max(the_squad);
                                                        //cout << endl;
                                                    //}
                                                }
                                            }
                                    }
                            }
                
                
                                }}}}}}}}}}
    cout << "Max Score: " << max_score << "  Cost: $" << max_salary << endl;
    cout << "Made: " << count << " lineups." << endl;
    return the_squad;
}

