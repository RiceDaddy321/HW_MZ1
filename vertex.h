
#include <vector>

using namespace std;

// A helper class implementing a Vertex in 
// an adjacency-list-based graph.
class Vertex
{
        public:
                Vertex(int r, int c)
                {
                        row = r;
                        col = c;
                        
                }

                // Corresponding row and column location in maze
                int row;
                int col;

                // List of neighboring vertices
                vector<Vertex*> neighs;
                
};

//taken from class
class Graph
{
private:
	//Need a container (data structure) to store
	
        // Two-dimensional key
        //first int is row, second int is col, and 
        unordered_map<int, unordered_map<int, Vertex*> > VertexSet;

public:
	//Run time: O(1) average case, O(n) worst-case
	void addVertex(int r, int c)
	{
		Vertex * babyVertex = new Vertex(r,c);
		VertexSet[r][c] = babyVertex;
	}

	//Add a directed edge going from a to b
	//O(1) ac, O(n) wc
	void addDirectedEdge(int r1, int c1, int r2, int c2)
	{
		//step 0:  double check a and b are actual vertices
		//skipped for time

		//step 1: get the vertices O(1)-average case time
		Vertex* vertA = VertexSet[r1][c1];
		Vertex* vertB = VertexSet[r2][c2];

		vertA->neighs.push_back(vertB);

	}

	//O(1) ac, O(n) wc
	void addBasicEdge(int r1, int c1, int r2, int c2)
	{
		addDirectedEdge(r1, c1, r2, c2);
		addDirectedEdge(r2, c2, r1, c1);
	}

        //starting point and a place to store the breadCrumbs
        void breadthFirstSearch(int row, int col, unordered_map<Vertex*,Vertex*> &breadCrumbs)
	{
		queue<Vertex*> Q;
                Vertex* s = VertexSet[row][col];

		//Create a set data structure
		//to denote what the marked nodes are
		unordered_set<Vertex*> marked;

		//Step 0: Mark s, put s into a queue
		marked.insert(s);  //mark s;
		Q.push(s);

		//Step 1: Enter BFS loop
		while (!Q.empty())
		{
			//Step 1.1: get item from Q
			Vertex* x = Q.front();
			Q.pop();

			//Step 1.2: visit all of x's
			//unmarked neighs
			for (int i = 0; i < x->neighs.size(); i++)
			{
				Vertex * y = x->neighs[i];
				if (marked.count(y) == 0)
				{
					marked.insert(y); //mark y;
					Q.push(y);

					//augment
					breadCrumbs[y] = x;  //set y's breadcrumb to be x;
				}
			}
		}
	}

        void shortestPath(int row1, int col1, int row2, int col2, int row_length, string& maze, unordered_map<Vertex*, Vertex*> breadCrumbs)
        {
                Vertex* vertS = VertexSet[row2][col2];
                Vertex* vertD = VertexSet[row1][col1];

		//step 2: follow the breadCrumbs back
		//from destination to source.
		Vertex * current = vertD;
		while (current != vertS)
		{
        //go to row and col of current and change it to an 'o'
        maze[current->row * row_length + current->col] = 'o';

			//go to next
			current = breadCrumbs[current];
		}
		//need to change vertS too
		maze[current->row * row_length + current->col] = 'o';
	}
};
