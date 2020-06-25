//Code made by Lilian "Banalian" Pouvreau in 2020
//For any questions/help with this code
//Mail    : lilian.pouvreau@free.fr
//Discord : Banalian#0584
//Open source code :can be used and modified by anyone at anytime as long as credit is given


//for any french programmer :
//tout les commentaires de ce code sont en anglais,
//car j'ai pour habitude de coder en anglais,et si j'ai besoin d'aide,
//il est plus simple de partager des morceaux de code déjà en anglais


//useful tips imo :
//- when deleting a object via a pointer using "delete" make sure to make it a nullptr afterward, for the assertions to work
//- remember to check the project's settings to be sure that sfml is correctly installed(check their tutorial to be sure)

//Things that can be done :
//- keep the tree in a file to re-use it :use serialization via the boost library (Big things to do, IMO)
//- switch arrays for vectors (should be done quickly, just adapt the code)
//- create a vector to have multiples fruits at once(should be done quickly, just adapt the code)
//- fix the postorderTraversal function (no idea of how easy it can be to fix)
//- make the MCTS better by saying that a move is better if it gets us closer to a fruit (mostly useful with one fruit)


#include <SFML/Graphics.hpp> // to show the game with more than just text
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <algorithm>
#include <iostream>
using namespace std;


// not used anymore, i left it here to show some of the work i did
//#include <mcts.h>

//My tree structure
#include "SnakeNode.h"
#include"SnakeStruct.h"

using namespace sf;// for the graphics from sfml

int N = 30, M = 20; // IF YOU CHANGE THEM, CHANGE THEM IN SnakeNode.cpp TOO, where there's '//OOB' written
int offSetWindow =40; // to show the score
int sizegame = 16;// the sprite need to be x*x
//Width and height
int w = sizegame*N;
int h = sizegame*M;

//used when testing with keeping the tree between games
int compteurtour = 0;

//MCTS :  c, use in the formula, choosen by experiment
//const float c = 1.41421356237309504880;
const float c = 1; //nice results, better that sqrt(2)
//const float c = 1.1;

int dir, botdir , olddir = 0, num = 1, scoreplayer = 0;
bool needtoreset = false;

Snake s[600]; 
//Snake snakeAI[600];

Fruit f;

void Tick(SnakeNode * game);
String movename(int);


//made from some exemple about connect4
//-------------------------SnakeState---------------------------------//
/*

class SnakeState
{
public:
	typedef int Move;
	static const Move no_move = -1;

	SnakeState::SnakeState(int row, int col, int direc) {
		num_rows = row;
		num_cols = col;
		dir = direc;

	}

	void do_move(Move move, int realorAI = 0)
	{
		// only AI and one player
		if (realorAI == 0) {
			for (int i = num; i>0; --i)
			{
				snakeAI[i].x = snakeAI[i - 1].x; snakeAI[i].y = snakeAI[i - 1].y;
			}



			if (move == 0) snakeAI[0].y += 1;
			if (move == 1) snakeAI[0].x -= 1;
			if (move == 2) snakeAI[0].x += 1;
			if (move == 3) snakeAI[0].y -= 1;

			if ((snakeAI[0].x == f.x) && (snakeAI[0].y == f.y))
			{
				//if (scoreplayer <= 100) num++;
				//scoreplayer++;
				//f.x = rand() % N; f.y = rand() % M;
				
			}

			if (snakeAI[0].x>N - 1) snakeAI[0].x = 0;  if (snakeAI[0].x<0) snakeAI[0].x = N - 1;
			if (snakeAI[0].y>M - 1) snakeAI[0].y = 0;  if (snakeAI[0].y<0) snakeAI[0].y = M - 1;		
		}
		else if(realorAI ==1){
			for (int i = num; i>0; --i)
			{
				s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
			}



			if (move == 0) s[0].y += 1;
			if (move == 1) s[0].x -= 1;
			if (move == 2) s[0].x += 1;
			if (move == 3) s[0].y -= 1;

			if ((snakeAI[0].x == f.x) && (snakeAI[0].y == f.y))
			{
				//if (scoreplayer <= 100) num++;
				//scoreplayer++;
				//f.x = rand() % N; f.y = rand() % M;
			}

			if (s[0].x>N - 1) s[0].x = 0;  if (s[0].x<0) s[0].x = N - 1;
			if (s[0].y>M - 1) s[0].y = 0;  if (s[0].y<0) s[0].y = M - 1;
			
			
		}
		

	}

	template<typename RandomEngine>
	void do_random_move(RandomEngine* engine)
	{
		


		std::uniform_int_distribution<Move> moves(0, 3);

		while (true) {
			auto move = moves(*engine);
			//do a move if the move is possible
			do_move(move);
			return;
		}
		
	}

	bool has_moves() const
	{
		int possible = 4;

		if ((snakeAI[0].x == f.x) && (snakeAI[0].y == f.y))
		{
			//printf("i got a fruit!");
			return 0;
		}

		for (int i = 1; i < num; i++)
		{
			//If Snake can eat its tail, remove 1
			if ((snakeAI[0].x+1 == snakeAI[i].x) || (snakeAI[0].x -1 == snakeAI[i].x) || (snakeAI[0].y+1 == snakeAI[i].y) || (snakeAI[0].y -1 == snakeAI[i].y))  possible--;
		}
			
		return possible;
	}

	std::vector<Move> get_moves() const
	{
		std::vector<Move> moves;
		for (Move move = 0; move <= 3; ++move) {
			moves.push_back(move);
		}
		return moves;
	}

	char get_winner() const
	{

	}

	double get_result(int current_player_to_move) const
	{
		if ((snakeAI[0].x == f.x) && (snakeAI[0].y == f.y))
		{
			return 1.0;
		}
		return 0.0;

	}

	void print(void) const
	{

	}

	int player_to_move = 1;
private:

	void check_invariant() const
	{
		
	}

	int num_rows, num_cols;
	Move dir;
	
	vector<vector<char>> board;
};



*/

//-------------------------SnakeState end-----------------------------//


//-------------------------MCTS Algo----------------------------------//

// main function for the Monte Carlo Tree Search
SnakeNode * monte_carlo_tree_search(SnakeNode *root);

//function for node traversal
// Exploration : find the best children to explore
SnakeNode* traverse(SnakeNode *node); 

//function for the result of the simulation
// simulate the game until the end
int rollout(SnakeNode *node);

//function for randomly selecting a child node
// how to simulate
int rollout_policy(SnakeNode *node);

//function for backpropagation
//updating the scores
void backpropagate(SnakeNode *node, int winornah);

// function for selecting the best child
//node with highest number of visits
SnakeNode * best_child(SnakeNode *node);


//-------------------------MCTS Algo-end------------------------------//





int main()
{
	//for the MCTS library, not used anymore
	/*
	MCTS::ComputeOptions player1_options;
	player1_options.max_iterations = 1000;
	player1_options.verbose = true;

	SnakeState state(20,30,0);*/

	
	//to have the same "seed", change "time(0)" to a number that stays the same
	srand(time(0));
	
	//w and h : width and height, the offset is so i can add the score and prediction
	RenderWindow window(VideoMode(w, h+ offSetWindow), "Snake Game!");

	//generic name because i kept changing the files, you can change them if you change the Draw part
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	t4.loadFromFile("images/floor1.png");
	t5.loadFromFile("images/floor2.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);
	Sprite sprite5(t5);
	
	//used to change a text color
	//Color redcolor(255, 0, 0);

	//you can dl a font and change it if necessary,
	Font fontjoystix;
	fontjoystix.loadFromFile("fonts/joystix.ttf");

	// the string is the initial string id you don't change it
	Text score("Score : 0",fontjoystix);
	Text prediction("Pred : down", fontjoystix);

	score.setPosition(0,0);
	prediction.setPosition(225, 0);

	//change the value of delay if necessary
	Clock clock;
	float timer = 0, delay = 0.5;

	//initial position of the fruit
	f.x = 10;
	f.y = 10;


	SnakeNode *root;
	root = new SnakeNode(nullptr, 0, 0, num, s, f,0,0);

	//root->addchildrens();
	//root->addVisitsOrWins(1, 0);
	//for (int i = 0; i < 3; i++)root->children[i]->addVisitsOrWins(1,0);
	
	SnakeNode *bestmove;
	SnakeNode *currentgame = root;
	//currentgame->getsnakesseg();
	//Snake botseg[10] =;
	
	//use when the AI is playing
	//currentgame = monte_carlo_tree_search(currentgame); //get the first best next move
	//dir = currentgame->dir;

	
	//use when a player is playing
	bestmove = monte_carlo_tree_search(currentgame); //get the first best next move
	prediction.setString("Pred : " + movename(bestmove->dir));

	//to fill the entire tree - WARNING, TAKES A LOT OF TIME (~1H to fill a 20-depth tree)
	//root->expendTree();

	//this isn't working, because my recursive function isn't correct for the moment
	//std::cout << "smallest numbers of movement to get to an apple : " << root->postorderTraversal() << endl;
	

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		
		//to exit the application
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) {
				delete root;
				window.close();
			}
				
		}

		//if it's a real player, prevent it from going back
		//cant' go back and eat himself
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if(!(olddir==2))dir = 1;
		} 
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (!(olddir == 1))dir = 2;
		} 
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (!(olddir == 0))dir = 3;
		} 
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (!(olddir == 3))dir = 0;
		} 

		olddir = dir;



		
		


		// if we waited long enough
		if (timer>delay) { 
			//for(int i = 0; i<num; i++)snakeAI[i] = s[i];
			timer = 0;
			Tick(currentgame);// do the movements

			//for real player
			//choose based on dir to have the next good node
			for (int i = 0; i < 3; i++) {

				if (currentgame->children[i]->dir = dir) {
					currentgame = currentgame->children[i];
					break;
				}
			}
			score.setString("Score:" + std::to_string(scoreplayer));// show the score
			
			//real player
			bestmove= monte_carlo_tree_search(currentgame); // find the best next move
			prediction.setString("Pred:" + movename(bestmove->dir));

			//AI
			//currentgame = monte_carlo_tree_search(currentgame); // find the best next move
			//dir = currentgame->dir;

			//i can delete the children that weren't used, if i don't need to keep them
			//until i can find a way to store data, i'm deleting them
			for (int i = 0; i < 3; i++) {
				if (currentgame->parent!=nullptr)if (currentgame->parent->children[i] != currentgame) {
					delete currentgame->parent->children[i];
					currentgame->parent->children[i] = nullptr;
				}
			}
		}

		////// draw  ///////
		window.clear();

		//floor
		for (int i = 0; i<N; i++)
			for (int j = 0; j<M; j++)
			{
				//2 sprite one after another
				if (((j+i) % 2 )== 0) {
					sprite4.setPosition(i*sizegame, j*sizegame + offSetWindow);  window.draw(sprite4);
				}
				else {
					sprite5.setPosition(i*sizegame, j*sizegame + offSetWindow);  window.draw(sprite5);
				}

				//only one sprite
				//sprite1.setPosition(i*sizegame, j*sizegame + offSetWindow);  window.draw(sprite1);
			}

		//snake
		for (int i = 0; i<num; i++)
		{
			sprite3.setPosition(s[i].x*sizegame, s[i].y*sizegame + offSetWindow);  window.draw(sprite3);
		}

		//fruit
		sprite2.setPosition(f.x*sizegame, f.y*sizegame + offSetWindow);  window.draw(sprite2);


		window.draw(score);
		window.draw(prediction);
		window.display();


		// test to see how the MCTS works if it does multiples games with the same tree
		// reset to start
		/*if (needtoreset || currentgame->movesSinceLastFruit >149) {

			currentgame = root;
			for (int i = num + 1; i>=0; --i)
			{
				s[i].x = (currentgame->getsnakesseg())[i].x;
				s[i].y = (currentgame->getsnakesseg())[i].y;
			}

			needtoreset = false;
			num = 1;
			compteurtour++;
			if (compteurtour > 10) {
				//after too many loop, it takes too much space, so i stop it before
				system("PAUSE");
			}
		}*/
	}

	return 0;
}



String movename(int direction) {

	switch (direction)
	{
	case 0:return "Down";
	case 1:return "Left";
	case 2:return "Right";
	case 3:return "Up";
	default:
		return "error";
		break;
	}

}


void Tick(SnakeNode * game)
{
	//prepare to move
	//Snake* currentseg [600];
	/*for (int i = num+1; i >0; --i) {
		s[i] = (game->getsnakesseg())[i];
	}*/

		for (int i = num+1; i>0; --i)
		{
			//each segment equals to the one in front of him
			s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
		}

	//do the next move
	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;

	//if The Snake goes OOB(Out Of Bound)
	if (s[0].x>N - 1) s[0].x = 0; 
	if (s[0].x<0) s[0].x = N - 1;

	if (s[0].y>M - 1) s[0].y = 0; 
	if (s[0].y<0) s[0].y = M - 1;

	//if you got the apple
	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		num++; scoreplayer++;

		//change the position of the apple
		//disabled sometimes because i'm trying to see how the snake does with the same setup and the same tree
		//can be enabled
		f.x = rand() % N; f.y = rand() % M;

		//update the tree
		game->updateFruit(num, f.x, f.y);
		//delete the childrens who have the wrong fruit positions
		for (int i = 0; i < 3; i++) {
			game->children[i]->updateFruit(num, f.x, f.y);
			for (int j = 0; j < 3; j++) {
				delete game->children[i]->children[j];
				game->children[i]->children[j] = nullptr;
			}
			
		}
		//reset to start
		//needtoreset = true;
	}


	//disabled for testing purpose- can be enabled
	//for (int i = 1; i < num; i++);
		//If Snake eats its tail, cut it
		//if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;

	//delete currentseg;
}

//-------------------------MCTS Algo----------------------------------//

// main function for the Monte Carlo Tree Search
SnakeNode * monte_carlo_tree_search(SnakeNode *root) {
	SnakeNode *leaf;
	int cpt = 1000, simulation_result;

	//it's like giving him X times to compute the best move
	while (cpt>0) {
		leaf = (traverse(root));
		// if the  leaf is an end of the game, find another leaf
		//sometimes it says the snake died but it's not the case
		//while (leaf->eatHimself) leaf = traverse(root);

		simulation_result = rollout(leaf);

		backpropagate(leaf, simulation_result);
		cpt--;
	}

	leaf = nullptr;
	return best_child(root);//find the best move
}

//function for node traversal
SnakeNode* traverse(SnakeNode *node) {
	
	float results[3], endr;
	if (!(node->assertchildren()))return node;
	for (int i = 0; i < 3; i++)
		//	w/v  *  c* sqrt((ln N)/v)
		//node = best_uct(node);
		results[i] = ((node->children[i]->getWins()) / (node->children[i]->getVisits()))*c*sqrt((log(node->getVisits())) / node->children[i]->getVisits());
		
	endr = *max_element(results, results+3);
	if (endr == 0) {
		int randnode = rand() % 3;
		if(!(node->children[randnode]->assertchildren()))return node->children[randnode];
		else return traverse(node->children[randnode]);
		
	}
	//in case no children are present / node is terminal
	if (!(node->children[((max_element(results, results + 3)) - results)]->assertchildren())) return node->children[((max_element(results, results + 3)) - results)];

	/*pick_univisted*/
	return traverse((node->children[((max_element(results, results + 3)) - results)])) ;
}
//function for the result of the simulation
int rollout(SnakeNode *node) {
	int wins = 0;
	node->addchildren();
	for (int i = 0; i < 3; i++) {
		
		
		if (node->assertchild(i)) {
			wins+= rollout_policy(node->children[i]);
			//wins += node->children[i]->getWins();
			if (node->children[i]->eatAppleThisMove)node->addVisitsOrWins(0, 1);
		}

		
	}

	
	return wins;
}
//function for randomly selecting a child node
int rollout_policy(SnakeNode *node) {
	/*pick_random*/
	if (node == nullptr)return 0;
	int direction = node->dir;
	Snake * oldsseg = node->getsnakesseg();
	Snake sseg[600];
	bool endfor = false;
	for (int i = num+1; i > 0; --i)sseg[i] = oldsseg[i];
	
	for (int cpt =100; cpt > 0; cpt--) {
		
		if (endfor)break;
		for (int i = num+1; i>0; --i)
		{
			sseg[i].x = sseg[i - 1].x; sseg[i].y = sseg[i - 1].y;
		}

		if (direction == 0) {
			//if(((sseg[0].y + 1) - f.y) < (sseg[0].y - f.y))
			sseg[0].y += 1;
		}

		if (direction == 1) {
			//if (((sseg[0].x - 1) - f.x) < (sseg[0].x - f.x))
			sseg[0].x -= 1;
		}

		if (direction == 2) {
			//if (((sseg[0].x + 1) - f.x) < (sseg[0].x - f.x))
			sseg[0].x += 1;
		}

		if (direction == 3) {
			//if (((sseg[0].y - 1) - f.y) < (sseg[0].y - f.y))
			sseg[0].y -= 1;
		}

		
		//if it got a fruit
		if ((sseg[0].x == f.x) && (sseg[0].y == f.y))
		{
			node->addVisitsOrWins(1, 1);
			endfor = true;
			return 1;
			break;
		}

		//if Snake goes OOB
		if (sseg[0].x>N - 1) sseg[0].x = 0;
		if (sseg[0].x<0) sseg[0].x = N - 1;

		if (sseg[0].y>M - 1) sseg[0].y = 0;
		if (sseg[0].y<0) sseg[0].y = M - 1;

		for (int i = 1; i < num; i++)
			//If Snake eats its tail
			if (sseg[0].x == sseg[i].x && sseg[0].y == sseg[i].y) {
				//node->addVisitsOrWins(1, 0);
				endfor = true;
				break;
			}

		direction = rand()%4;
	}
	//int temp = (rand() % 3);
	//while (node->children[temp]->getVisits() != 0) temp = (rand() % 3);
	node->addVisitsOrWins(1, 0);
	return 0;
}
//function for backpropagation
void backpropagate(SnakeNode *node, int winornah) {
	
	node->addVisitsOrWins(3,winornah);
	if (node->parent == nullptr) return;
	backpropagate(node->parent, winornah);
}
// function for selecting the best child
//node with highest number of visits
SnakeNode * best_child(SnakeNode *node) {
	//pick child with highest number of wins

	int results[3];

	//if (node->children[0] == nullptr)return node;
	for (int i = 0; i < 3; i++)	if (node->assertchild(i)) results[i] = node->children[i]->getWins();

	max_element(results, results + 3);
	return node->children[((max_element(results, results + 3))-results)];
}


//-------------------------MCTS Algo-end------------------------------//