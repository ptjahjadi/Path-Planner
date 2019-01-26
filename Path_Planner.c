/* Path planning program. Program to read a grid and its attributes from a
file and find the shortest path from a specified starting point to the
end points specified from the file.

Program written by Patrick Tjahjadi, October 2017.
Student Number: 890003. The University of Melbourne.
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
#include <stdio.h> 
#include <stdlib.h>

/*999 seconds is one−way only */
#define ONE_WAY 999

/* Initially cost, impossibilities, etc. are 0. Used to
 * initialise most variables. */
# define ZERO 0
/* Used as a false statement */
# define FALSE 0
/* Used as a true statement */
# define TRUE 1

/* North, East, West, South. Used to analyse all directions */
# define NEWS 4
/* Struct for reading the columns and rows of the grid */
typedef struct {
  int dim_1;
  int dim_2;
}
dimensions_t;

/* Struct for storing the attributes of the grid */
typedef struct {
  dimensions_t dimensions;
  int num_intersections;
  int possibilities;
  int impossibilities;
  int cost;
  int grid_locations;
}
grid_attributes_t;

/* Struct for storing the locations of the grid, containing numbers
 * and a letter */
typedef struct {
  int digit;
  char letter;
}
locations_t;

/* Struct for storing the minimum cost, previous location and
 * previous cost associated with each coordinate */
typedef struct {
  locations_t coordinates;
  int min_cost;
  locations_t previous_loc;
  int previous_cost;
}
path_search_t;

// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function Prototypes: */
void read_file(grid_attributes_t * grid, locations_t * pickup,
  70 locations_t * drop_offs, int ** time);
void print_num_intersections(grid_attributes_t * grid);
void print_times(grid_attributes_t * grid, int ** time);
void print_grid_locations(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs);
void path_finding(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs, int ** time, path_search_t * cell);
void initialise_cost(grid_attributes_t * grid, locations_t * pickup,
  path_search_t * cell);
void update_cost(grid_attributes_t * grid, path_search_t * cell, int ** time,
  int coord, int * is_changes);
void print_path(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs, path_search_t * cell);
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Program begins at main function here. */
int main() {
  int i;
  /* Initialise all required structs to store attributes of the grid */
  grid_attributes_t grid;
  locations_t pickup;
  locations_t * drop_offs;
  path_search_t * cell;
  /* Scans the dimensions of the grid for memory allocation purposes */
  scanf("%d %d", & grid.dimensions.dim_1, & grid.dimensions.dim_2);
  grid.num_intersections = grid.dimensions.dim_1 * grid.dimensions.dim_2;
  /* Allocate memory for all necessary structs and arrays */
  drop_offs = (locations_t * ) malloc(sizeof(locations_t) * grid.num_intersections);
  int ** time = (int ** ) malloc(sizeof(int * ) * grid.num_intersections);
  for (i = 0; i < grid.num_intersections; i++) {
    time[i] = (int * ) malloc(sizeof(int) * NEWS);
  }
  grid.impossibilities = ZERO;a
  grid.cost = ZERO;
  grid.grid_locations = ZERO;
  cell = (path_search_t * ) malloc(sizeof(path_search_t) * grid.num_intersections);
  /* S1: Read from the file */
  read_file( & grid, & pickup, drop_offs, time);
  /* S2: Find shortest path */
  printf("\n");
  path_finding( & grid, & pickup, drop_offs, time, cell);
  free(time);
  free(drop_offs);
  free(cell);
  return 0;
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function reads the file from input */
void read_file(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs, int ** time) {
  print_num_intersections(grid);
  print_times(grid, time);
  print_grid_locations(grid, pickup, drop_offs);
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function outputs the dimensions of the grid, along with the number of
intersections */
void print_num_intersections(grid_attributes_t * grid) {
  printf("S1: grid is %d x %d, and has %d intersections\n",
    grid− > dimensions.dim_1, grid− > dimensions.dim_2,
    grid− > num_intersections);
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

/* Function outputs the total cost of remaining possibilities, along with
150 * possibilities and impossibilities of paths */
void print_times(grid_attributes_t * grid, int ** time) {
  int i;
  int j;
  grid− > possibilities = (grid− > num_intersections * NEWS);
  locations_t * location = (locations_t * ) malloc(sizeof(locations_t) * grid− > num_intersections);
  for (i = ZERO; i < grid− > num_intersections; i++) {
    scanf("%d%c", & location[i].digit, & location[i].letter);
    for (j = ZERO; j < NEWS; j++) {
      /* Increase total cost for every possibility */
      scanf("%d", & time[i][j]);
      if (time[i][j] == ONE_WAY) {
        grid− > impossibilities += 1;
      } else {
        grid− > cost += time[i][j];
      }
    }
  }
  printf("S1: of %d possibilities, %d of them cannot be used\n",
    grid− > possibilities, grid− > impossibilities);
  printf("S1: total cost of remaining possibilities is %d seconds\n",
    grid− > cost);
  free(location);
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function outputs the number of grid locations specified in the file */
void print_grid_locations(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs) {
  int i = ZERO;
  /* The first grid location is considered as the starting location */
  scanf("%d%c", & pickup− > digit, & pickup− > letter);
  grid− > grid_locations += 1;
  /* Find end locations from the file */
  while (scanf("%d%c", & drop_offs[i].digit, & drop_offs[i].letter) != EOF) {
    i += 1;
    grid− > grid_locations += 1;
  }
  /* Condition where there are no drop off locations (just in case) */
  if (grid− > grid_locations == 1) {
    printf("S1: %d grid locations supplied, first one is %d%c, "
      "last one is %d%c\n",
      grid− > grid_locations, pickup− > digit,
      pickup− > letter, pickup− > digit,
      pickup− > letter);
  } else {
    printf("S1: %d grid locations supplied, first one is %d%c, "
      "last one is %d%c\n",
      grid− > grid_locations, pickup− > digit,
      pickup− > letter, drop_offs[i− 1].digit,
      drop_offs[i− 1].letter);
  }
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function finds the shortest path from the starting location to the
destination. */
void path_finding(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs, int ** time, path_search_t * cell) {
  int coord;
  /* Initialise a flag have_changes that checks whether there are any
  minimum cost update for each iteration in the grid */
  int have_changes;
  initialise_cost(grid, pickup, cell);
  /* Update the minimum cost, previous cost and previous location for
  each cell by iterating through all possible paths. */
  do {
    have_changes = FALSE;

    for (coord = ZERO; coord < grid− > num_intersections; coord++) {
      if (cell[coord].min_cost != ONE_WAY) {
        update_cost(grid, cell, time, coord, & have_changes);
      }
    }
  } while (have_changes != FALSE);
  print_path(grid, pickup, drop_offs, cell);
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function initially labels the minimum cost of the pickup location as 0
and 999 for the other locations. */
void initialise_cost(grid_attributes_t * grid, locations_t * pickup,
  path_search_t * cell) {
  int i, j;
  int k = ZERO;
  char curr_letter = ’a’;
  for (i = 0; i < grid− > dimensions.dim_2; i++) {
    for (j = 0; j < grid− > dimensions.dim_1; j++) {
      /* Associate each cell with the location’s coordinates */
      cell[k].coordinates.digit = j;
      cell[k].coordinates.letter = curr_letter;
      if (j == pickup− > digit && curr_letter == pickup− > letter) {
        cell[k].min_cost = ZERO;
        cell[k].previous_cost = ZERO;
        cell[k].previous_loc.digit = ZERO;
        cell[k].previous_loc.letter = ZERO;
      } else {
        cell[k].min_cost = ONE_WAY;
      }
      k += 1;
    }
    curr_letter += 1;
  }
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
/* Function updates the minimum time to reach the locations one block next
 * to the specified coordinate and stores the previous location and cost. */
void update_cost(grid_attributes_t * grid, path_search_t * cell, int ** time,
  int coord, int * is_changes) {
  int direction;
  /* Array to_update specifies the order of directions from the initial
   * location (respectively): east, north, west and south. */
  int to_update[] = {
    coord + 1,
    coord− grid− > dimensions.dim_1,
    coord− 1,
    coord + grid− > dimensions.dim_1
  };
  /* Iterate through each direction and updates if the cost is lower, or
   * the previous location is alphabetically smaller.*/
  for (direction = 0; direction < NEWS; direction++) {
    if (time[coord][direction] + cell[coord].min_cost <
      cell[to_update[direction]].min_cost) {
      cell[to_update[direction]].min_cost =
        time[coord][direction] + cell[coord].min_cost;
      cell[to_update[direction]].previous_cost = cell[coord].min_cost;
      cell[to_update[direction]].previous_loc = cell[coord].coordinates;
      * is_changes = TRUE;
    }
    /* Note: use nested if statements so that when updating the cost from
    999, it will not compare the previous location because there are no
    previous locations yet */
    else if (time[coord][direction] + cell[coord].min_cost ==
      cell[to_update[direction]].min_cost) {
      if ((cell[coord].coordinates.digit <
          cell[to_update[direction]].previous_loc.digit) ||
        (cell[coord].coordinates.digit ==
          cell[to_update[direction]].previous_loc.digit &&
          cell[coord].coordinates.letter <
          cell[to_update[direction]].previous_loc.letter)) {
        cell[to_update[direction]].previous_cost =
          cell[coord].min_cost;
        cell[to_update[direction]].previous_loc =
          cell[coord].coordinates;
        * is_changes = TRUE;
      }
    }
  }
}
// −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

/* Function outputs the path required to reach the destination
 * from the starting point in the shortest time possible. */
void print_path(grid_attributes_t * grid, locations_t * pickup,
  locations_t * drop_offs, path_search_t * cell) {
  int i, j;
  int cross;
  /* Number of drop off locations is the number of grid locations excluding
   * the pick up point */
  int num_drop_offs = grid− > grid_locations− 1;
  /* Allocate memory for a 2D array cost_array, containing the costs of
   * the path */
  int ** cost_array = (int ** ) malloc(sizeof(int * ) * num_drop_offs);
  /* Allocate memory for a 2D array of structs loc_array, containing the
  previous locations of the path */
  locations_t ** loc_array = (locations_t ** ) malloc(sizeof(locations_t * ) * num_drop_offs);
  for (i = 0; i < num_drop_offs; i++) {
    cost_array[i] = (int * ) malloc(sizeof(int) * grid− > num_intersections);
    loc_array[i] = (locations_t * ) malloc(sizeof(locations_t) * grid− > num_intersections);
  }
  /* Iterate through every drop off point */
  for (i = 0; i < num_drop_offs; i++) {
    printf("S2: start at grid %d%c, cost of 0\n", pickup− > digit,
      pickup− > letter);
    cross = ZERO;
    for (j = 0; j < grid− > num_intersections; j++) {
      if ((cell[j].coordinates.digit == drop_offs[i].digit) &&
        (cell[j].coordinates.letter == drop_offs[i].letter)) {
        cost_array[i][cross] = cell[j].min_cost;
        loc_array[i][cross].digit = cell[j].coordinates.digit;
        loc_array[i][cross].letter = cell[j].coordinates.letter;
        break;
      }
    }
    /* Find previous locations until starting point is found. */
    while (cost_array[i][cross] != ZERO) {
      for (j = 0; j < grid− > num_intersections; j++) {
        if (cell[j].coordinates.digit == loc_array[i][cross].digit &&
          cell[j].coordinates.letter ==
          loc_array[i][cross].letter) {
          cross += 1;
          cost_array[i][cross] = cell[j].previous_cost;
          loc_array[i][cross] = cell[j].previous_loc;
          break;
        }
      }
    }
    /* Prints the path taken */
    for (j = cross− 1; j >= 0; j−−) {
      printf("S2: then to %d%c, cost of %d\n",
        loc_array[i][j].digit, loc_array[i][j].letter,
        cost_array[i][j]);
    }
  }
  free(loc_array);
  free(cost_array);
}
/* algorithms are fun */