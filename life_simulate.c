#pragma warning(push, 0)
#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#pragma(pop)

#pragma warning(disable :5045)

typedef struct
{
  uint32_t x;
  uint32_t y;
} start_coord_t;

// typedef struct s_n {
//   t_n *top_l;
//   t_n *top_r;
//   t_n *bot_l;
//   t_n *bot_r;
//   uint32_t depth;
//   uint32_t area;
// } t_n;

// typedef struct s_c {
//   uint32_t top_l;
//   uint32_t top_r;
//   uint32_t bot_l;
//   uint32_t bot_r;
//   uint32_t depth;
//   uint32_t area;
// } t_c;

// uint8_t rule_alive(uint8_t **slow, uint8_t y, uint8_t x, uint8_t dim) {
//   uint8_t cc = 0;
//   if (y > 0 && x > 0) {
//     if (slow[y - 1][x - 1] == 1)
//       cc++;
//     if (slow[y - 1][x] == 1)
//       cc++;
//     if (slow[y][x - 1] == 1)
//       cc++;
//   }
//   if (x < dim && y < dim) {
//     if (slow[y + 1][x + 1] == 1)
//       cc++;
//     if (slow[y + 1][x] == 1)
//       cc++;
//     if (slow[y][x + 1] == 1)
//       cc++;
//   }
//   if (cc >= 2 && cc <= 3)
//     return (1);
//   return (0);
// }

// uint8_t rule_dead() {
//   return (1);
// }

/*
  Main rules:
  checking alive, 2-3: stay the same
  checking dead, exactly 3: create life
  everything else dies

  Extra:
  y 0 x 0, index 0;
  y 0 x 1, index 1;
*/

uint32_t counting_cells(uint8_t *grid, uint32_t cc, uint32_t whole_grid) {
  uint32_t counter = 0;
  if (cc > 3 && cc < whole_grid - 4) {
    uint32_t tmp = cc - 4;
    while (tmp < cc) {
    if (grid[tmp] == 1)
      counter++;
    tmp++;
    }
    tmp = cc + 1;
    while (tmp < cc + 4) {
      if (grid[tmp] == 1)
        counter++;
      tmp++;
    }
  }
  else if (cc <= 3) {
    uint32_t tmp = whole_grid - (4 - cc);
    while (tmp < whole_grid) {
      if (grid[tmp] == 1)
        counter++;
      tmp++;
    }
    tmp = 0;
    while (tmp < cc) {
      if (grid[tmp] == 1)
        counter++;
      tmp++;
    }
    tmp = cc + 1;
    while (tmp < cc + 4) {
      if (grid[tmp] == 1)
        counter++;
      tmp++;
    }
  }
  else {
    uint32_t tmp = cc - 4;
    while (tmp < cc) {
    if (grid[tmp] == 1)
      counter++;
    tmp++;
    }
    if (cc < whole_grid - 1) {
      tmp = cc + 1;
    }
    uint8_t checked = 0;
    while (tmp < whole_grid) {
      if (grid[tmp] == 1)
        counter++;
      checked++;
      tmp++;
    }
    tmp = 0;
    while (checked < 4) {
      if (grid[tmp] == 1)
        counter++;
      tmp++;
      checked++;
    }
  }
  return (counter);
}

uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  const uint32_t whole_grid = grid_dim * grid_dim;
  // static int first = 0;
  uint8_t *grid = NULL;
  if (grid == NULL) {
    grid = VirtualAlloc(NULL, whole_grid * sizeof(uint8_t), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  }
  uint32_t cc = 0;
  while (cc < initial_point_count) {
    grid[initial_points[cc].y * grid_dim + initial_points[cc].x] = 1;
    cc++;
  }
  cc = 0;
  uint8_t to_keep[1024] = {0};
  while (cc < whole_grid) {
    /*
      Checking the living cells
    */
    if (grid[cc] == 1) {
      uint32_t counter = counting_cells(grid, cc, whole_grid); 
      if (counter == 2 || counter == 3) 
        to_keep[cc] = 1;
    }
    /*
      Checking the dead ones
    */
    else {
      if (counting_cells(grid, cc, whole_grid) == 3)
        to_keep[cc] = 1;
    }
    cc++;
  }
  cc = 0;
  while (cc < whole_grid) {
    grid[cc] = to_keep[cc];
    cc++;
  }
  return (grid);
  // while (cc < initial_point_count) {
  //   uint32_t inner = 0;
  //   uint32_t temp_x = initial_points[cc].x;
  //   uint32_t temp_y = initial_points[cc].y;
  //   while (inner < initial_point_count) {
  //     uint32_t compare_x = initial_points[inner].x;
  //     uint32_t compare_y = initial_points[inner].y;
  //     if (compare_x != temp_x && compare_y != temp_y) {
        
  //     }
  //   }
  //   cc++;
  // }
  // uint8_t slow[16][16] = {0};
  // uint32_t cc = 0;
  // while (cc < initial_point_count) {
  //   slow[initial_points[cc].y][initial_points[cc].x] = 1;
  //   cc++;
  // }
  // uint32_t h = 0;
  // while (h < grid_dim) {
  //   uint32_t w = 0;
  //   while (w < grid_dim) {
  //     if (slow[h][w] == 1) {
  //       grid[h * grid_dim + w] = rule_alive(slow, h, w, (uint8_t)grid_dim);
  //     }
  //     else {
  //       grid[h * grid_dim + w] = rule_dead();
  //     }
  //     w++;
  //   }
  //   h++;
  // }
}
