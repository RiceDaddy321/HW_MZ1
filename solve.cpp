#include "solve.h"
#include "vertex.h"

//Step 1: decode the maze and create a graph from it
//step 1.1: iterate through the string. on a space we check around it and see if is is a space
//then we add the current space to that space's neighbor list, otherwise ignore it
string solve(string maze)
{
    Graph mz;
    int row = 0;
    int row_length;
    int row_count;
    int start_x;
    int finish_x;
    int start_y;
    int finish_y;
    bool start_found = false;
    bool finish_found = false;

    //find how long a row is
    for(row_length = 0; maze[row_length] != '\n'; row_length++);
    row_length += 1;
    //find the amount of rows
    for(row_count = 0; row_count*row_length < maze.size(); row_count++);

    for (int i = 0; i < maze.size(); i++)
    {
        if (start_found && finish_found)
            break;
        else if (start_found)
        {
            //check row 0, row_count-1, col 0, row_length-1
            if (i / row_length == 0 && maze[i] == ' ')
            {
                finish_x = i % row_length;
                finish_y = i / row_length;
                finish_found = true;
            }
            else if (i / row_length == row_count - 1 && maze[i] == ' ')
            {
                finish_x = i % row_length;
                finish_y = i / row_length;
                finish_found = true;
            }
            else if (i % row_length == 0 && maze[i] == ' ')
            {
                finish_x = i % row_length;
                finish_y = i / row_length;
                finish_found = true;
            }
            else if (i % row_length == row_length - 2 && maze[i] == ' ')
            {
                finish_x = i % row_length;
                finish_y = i / row_length;
                finish_found = true;
            }
        }
        else
        {
            //check row 0, row_count-1, col 0, row_length-1
            if (i / row_length == 0 && maze[i] == ' ')
            {
                start_x = i % row_length;
                start_y = i / row_length;
                start_found = true;
            }
            else if (i / row_length == row_count - 1 && maze[i] == ' ')
            {
                start_x = i % row_length;
                start_y = i / row_length;
                start_found = true;
            }
            else if (i % row_length == 0 && maze[i] == ' ')
            {
                start_x = i % row_length;
                start_y = i / row_length;
                start_found = true;
            }
            else if (i % row_length == row_length - 2 && maze[i] == ' ')
            {
                start_x = i % row_length;
                start_y = i / row_length;
                start_found = true;
            }
        }
    }

    //fill the vertices list
    for(int i = 0; i < maze.size(); i++)
    {
       /* if(maze[i] == '\n')
        {
            row++;
        }*/
        if (maze[i] == ' ')
        {
            mz.addVertex(i / row_length, i % row_length);
        }

    }


//step1.1.1: for up and down we take modulus of the character's position and subtract and add it to
//and check if it's out of bounds if not check if space or not. 
    //fill the neighs list
    for(int i = 0; i < maze.size(); i++)
    {
        //check that the current index is a space
        if(maze[i] == ' ')
        {
            //check right
            if(i+1 < maze.size() && maze[i+1] == ' ')
            {
                mz.addBasicEdge(i/ row_length, i % row_length, i/ row_length, (i+1) % row_length);
            }
            //check down
            if(row_length + i < maze.size() && maze[row_length + i] == ' ')
            {
                mz.addBasicEdge(i/row_length, i % row_length, i/row_length + 1, i % row_length);
            }
        }
    }

//Step 2: run a bredth-first-search from the beginning position
    //declare a breadcrumb list for the bredth-first-search
    unordered_map <Vertex *, Vertex *> breadcrumbs;
    //do a bredth-first search
    mz.breadthFirstSearch(start_y, start_x, breadcrumbs);
//Step 3: trace back the end to start, and on the way change the space to a 'o'
    mz.shortestPath(finish_y, finish_x, start_y, start_x,
    row_length, maze, breadcrumbs);

    return maze;
}