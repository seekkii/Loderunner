#include "mobs.h"

mobs::mobs()
{
    inactive_timer = new QTimer();
    inactive_timer->setSingleShot(true);
    rand_timer = new QTimer();
    hold = false;
    ani_right.set_mob_animate(3);
    ani_left.set_mob_animate(3);
    ani_down.set_mob_animate(2);
    ani_up.set_mob_animate(2);
}

QTimer* mobs::get_inactivetimer(){
    return inactive_timer;
}

QTimer* mobs::get_rand_timer(){
    return rand_timer;
}

bool mobs::holding(){
    return hold;
}

void mobs::set_holding(bool hold)
{
    this->hold = hold;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//A* Search Algorithm


// Check whether given cell (row, col) is a valid cell or not.
bool pathsearch::isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}

// Check whether the given cell is blocked or not
bool isUnBlocked(QVector<QVector<int>>grid, int row, int col)
{
    // Returns true if the cell is not blocked else false
    if (grid[row][col] == 1)
        return (true);
    else
        return (false);
}

// check whether destination cell has been reached or not
bool isDestination(int row, int col, QPair<int, int> dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

// calculate 'h'
double calculateHValue(int row, int col, QPair<int, int> dest)
{
    // Return using the distance formula
    return
        abs(row - dest.first)
        + abs(col - dest.second) ;

}

// trace path from source
void pathsearch::tracePath(QVector<QVector<cell>> cellDetails, QPair<int, int> dest)
{
    int row = dest.first;
    int col = dest.second;


    QStack<QPair<int, int>> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col)) {
        Path.push(QPair<int,int>(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(QPair<int,int>(row, col));
    while (!Path.empty()) {
        QPair<int, int> p = Path.top();
        Path.pop();

        pathlist.enqueue(QPair<int,int>(p.first, p.second));

    }

    return;
}

// A* Search Algorithm
void pathsearch::aStarSearch(QVector<QVector<int>> grid, QPair<int,int> src, QPair<int,int> dest)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == false) {
        return;
    }//if source is invalide return

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == false) {
        return;
    }// if destination is invalid return

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == false
        || isUnBlocked(grid, dest.first, dest.second)
               == false) {
        return;
    }// if destination or source is blocked return

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)) {
        return;
    }// if source == dest return

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet
    QVector<QVector<bool> > closedList(false,QVector<bool>(false));
    closedList.resize(ROW,QVector<bool>(COL));



    // Declare a 2D array of structure to hold the details
    // of that cell
    QVector<QVector<cell>> cellDetails;
    cellDetails.resize(ROW,QVector<cell>(COL));

    int i, j;

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    QSet<QPair<double, QPair<int, int> >> openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair(0.0, QPair<int,int>(i, j)));



    while (!openList.empty()) {
        pPair p = *openList.begin();

        // Remove this vertex from the open list
        openList.erase(openList.begin());

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // To store the 'g', 'h' and 'f' of the successors
        double gNew, hNew, fNew;

        //----------- 1st Successor (Up) ------------

        // Only process this cell if this is a valid one
        if (isValid(i - 1, j) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;

                tracePath(cellDetails, dest);

                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j] == false
                     && isUnBlocked(grid, i - 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                // If it isn???t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, QPair<int,int>(i - 1, j)));

                    // Update the details of this cell
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        //----------- 2nd Successor (Down) ------------

        if (isValid(i + 1, j) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                tracePath(cellDetails, dest);
                return;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j] == false
                     && isUnBlocked(grid, i + 1, j)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                // If it isn???t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew) {
                    openList.insert(make_pair(
                        fNew, QPair<int,int>(i + 1, j)));
                    // Update the details of this cell
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        //----------- 3rd Successor (Right) ------------

        // Only process this cell if this is a valid one
        if (isValid(i, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                tracePath(cellDetails, dest);
                return;
            }

            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j + 1] == false
                     && isUnBlocked(grid, i, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                // If it isn???t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, QPair<int,int>(i, j + 1)));

                    // Update the details of this cell
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        //----------- 4th Successor (Left) ------------

        if (isValid(i, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                tracePath(cellDetails, dest);
                return;
            }


            else if (closedList[i][j - 1] == false
                     && isUnBlocked(grid, i, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;
                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, QPair<int,int>(i, j - 1)));

                    // Update the details of this cell
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }




    }

    return;
}

void pathsearch::search(QVector<QVector<int>> grid,QPair<int,int> src, QPair<int,int> dest)
{

    aStarSearch(grid, src, dest);

}

QQueue<QPair<int,int>> pathsearch::getpathlist()
{
    return pathlist;
}


