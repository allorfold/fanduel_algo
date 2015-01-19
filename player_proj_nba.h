/* 
 * File:   player_proj_nba.h
 * Author: Dave
 *
 * Created on November 27, 2014, 10:09 AM
 */

#ifndef PLAYER_PROJ_NBA_H
#define	PLAYER_PROJ_NBA_H
#include<map>
using std::map; 
#include<vector>
using std::vector;
#include<string>
using std::string; 
#include<iostream>
using std::ostream;
using std::cout; using std::cin; using std::endl;
using std::pair;




void player_update(map<string,pair<long,float> > &player_map_pg, map<string,pair<long,float> > &player_map_sg, map<string, pair<long, float> > &player_map_sf,map<string,pair<long,float> > &player_map_pf, map<string, pair<long, float> > &player_map_c,  string file_name);

void add_player(string player,long salary, float proj_points, map<string, pair<long,float> > &player_map);

void optimize_pos(map<string, pair<long, float> > &player_map);

vector<string> optimize(map<string,pair<long,float> > &player_map_pg, map<string,pair<long,float> > &player_map_sg, map<string, pair<long, float> > &player_map_sf,map<string,pair<long,float> > &player_map_pf, map<string, pair<long, float> > &player_map_c);

void print_max(vector<string> the_squad);

void optimize_pos_c(map<string, pair<long, float> > &player_map);

#endif	/* PLAYER_PROJ_NBA_H */

