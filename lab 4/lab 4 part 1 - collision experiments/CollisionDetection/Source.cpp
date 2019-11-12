#include <iostream>
#include <math.h>
#include <time.h>

class Point {
public:
	int x;
	int y;

	void print() {
		std::cout << "x:" << x << " y:" << y << std::endl;
	}
};

class Box 
{ public:
	Point p; 
	int w; 
	int h; 
	void print() { std::cout << "Width: " << w << "Height: " << h << "x: " << p.x << "y: " << p.y << std::endl; }
};

class Circle {
public:
	Point p;
	int r;

	void print() {
		std::cout << "x:" << p.x << " y:" << p.y << " r:" << r << std::endl;
	}
};

int calculate_hypotenuse(Point a, Point b) {
	int result = 0;

	// Find the distance (Length) of X and Y  

	int x_Distance = b.x - a.x;
	int y_Distance = b.y - a.y;

	// Now that we have the distance (Length)
	// of x and y, use Pythagoras theorem 
	// to get the distance (length of hypotenuse) 
	// between Point a and Point b 
	result = sqrt(pow(x_Distance, 2) + pow(y_Distance, 2));

	return result;
}

bool boxToBox(Box t_boxA, Box t_boxB)
{ 
	return t_boxA.p.x < t_boxB.p.x + t_boxB.w &&
		t_boxA.p.x + t_boxA.w > t_boxB.p.x &&
		t_boxA.p.y < t_boxB.p.y + t_boxB.h &&
		t_boxA.p.y + t_boxA.h > t_boxB.p.y;
}

int main() {

	srand(time(NULL));

	// Point Collision
	Point player_point;
	player_point.x = rand() % 10 + 1;
	player_point.y = rand() % 10 + 1;

	Point npc_point;
	npc_point.x = rand() % 10 + 1;
	npc_point.y = rand() % 10 + 1;

	// Circle Collision
	Circle player_circle;
	player_circle.p.x = rand() % 10 + 1;
	player_circle.p.y = rand() % 10 + 1;
	player_circle.r = rand() % 2 + 1;
	
	Circle npc_circle;
	npc_circle.p.x = rand() % 10 + 1;
	npc_circle.p.y = rand() % 10 + 1;
	npc_circle.r = rand() % 2 + 1;


	//stuff i've done
	//circle to point collision
	Circle enemy_circle;
	enemy_circle.p.x = rand() % 10 + 1;
	enemy_circle.p.y = rand() % 10 + 1;
	enemy_circle.r = rand() % 2 + 1;


	Point enemy_point;
	enemy_point.x = rand() % 10 + 1;
	enemy_point.y = rand() % 10 + 1;

	Box boxA;
	boxA.h= rand() % 10 + 1;
	boxA.w= rand() % 10 + 1;
	boxA.p.x = rand() % 10 + 1;
	boxA.p.y = rand() % 10 + 1;

	Box boxB;
	boxB.h = rand() % 10 + 1;
	boxB.w = rand() % 10 + 1;
	boxB.p.x = rand() % 10 + 1;
	boxB.p.y = rand() % 10 + 1;

	while (true) {

		// Point Collision check
		if (calculate_hypotenuse(player_point, npc_point) == 0)
		{
			std::cout << "Point to Point Collision" << std::endl;
			player_point.print();
			npc_point.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Point to Point Collision" << std::endl;
			player_point.print();
			npc_point.print();
		}

		player_point.x = rand() % 10 + 1;
		player_point.y = rand() % 10 + 1;

		// Circle Collision check
		if (calculate_hypotenuse(player_circle.p, npc_circle.p) < (player_circle.r + npc_circle.r))
		{
			std::cout << "Circle to Circle Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Circle to Circle Collision" << std::endl;
			player_circle.print();
			npc_circle.print();
		}

		player_circle.p.x = rand() % 10 + 1;
		player_circle.p.y = rand() % 10 + 1;


		if (calculate_hypotenuse(enemy_circle.p, enemy_point) < (enemy_circle.r))
		{
			std::cout << "Circle to Point Collision" << std::endl;
			enemy_circle.print();
			enemy_point.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Circle to Point Collision" << std::endl;
			enemy_circle.print();
			enemy_point.print();
		}


		if (boxToBox(boxA, boxB))
		{
			std::cout << "Box to Box Collision" << std::endl;
			boxA.print();
			boxB.print();
			std::cin.get();
		}
		else
		{
			std::cout << "No Box to Box Collision" << std::endl;
			boxA.print();
			boxB.print();
		}
	}

	return 0;
}