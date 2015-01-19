/* 
 * File:   main_NBA_fd.cpp
 * Author: David Saksa
 *
 * Created on November 27, 2014, 10:09 AM
 */


 /*	THIS IS THE MAIN FILE FOR THE NBA ALGORITHM

	Each of the functions are defined in the player_proj_nba.cpp file
	and defined in the header file as well.

	TO BE ADDED:

	Create a function to pull information off of a website instead of using a text file.

 */


// Using the following includes

#include <cstdlib>
#include "player_proj_nba.h"
#include<map>
using std::map;
#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<fstream>
using std::ifstream;
#include<vector>
using std::vector;
#include<algorithm>
using std::find; using std::copy;
#include<iterator>
using std::ostream_iterator;
using std::istringstream;
using std::istream_iterator;


int main(int argc, char** argv) {
	//Creates the vector for which the optimal team will be stored as well as the projected points.
	pair<vector<string>, float> the_squad;


	//Create the maps that store each position type in them. The varlies will be a string,
	// which is the players name, and a pair of long, float which will be the players
	// salary cost and the players projected fantasy points for the night.

	map<string, pair<long, float> > player_map_pg;
	map<string, pair<long, float> > player_map_sg;
	map<string, pair<long, float> > player_map_sf;
    map<string, pair<long, float> > player_map_pf;
    map<string, pair<long, float> > player_map_c;

    //Using a text file, update all of the player maps above to push in all the data 
    // needed. The text will contains all the information needed.
    player_update(player_map_pg, player_map_sg, player_map_sf, 
    	player_map_pf, player_map_c, "player_proj.txt");

    //The following is the first optimization algorithm. It runs on the assumption
    // that you do not want to play a player who costs more and performs worse than
    // a guy who costs less. This is different depending on position because for a 
    // position like PG, you must select two players a night and therefore you must 
    // have two guys perform better at a lower price in order to eliminate them.
    optimize_pos(player_map_pf);
    optimize_pos(player_map_sf);
    optimize_pos(player_map_sg);
    optimize_pos(player_map_pg);
    optimize_pos_c(player_map_c);

    //After optimization, the lineup must be generated! This is using a function I called
    // optimize which outputs a pair which I store in the_squad created above.

    the_squad = optimize(player_map_pg,player_map_sg,player_map_sf,player_map_pf,player_map_c);

    //Function to print off and display the optimal team. The reason I do not print off
    // the team in the optimize function above is so that the user can view and change/edit
    // the contents of the_squad if they desire.
    print_max(the_squad);


    return 0;
}