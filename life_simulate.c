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
uint8_t *simulate_life(uint32_t grid_dim, start_coord_t *initial_points, uint32_t initial_point_count)
{
  uint8_t *grid = VirtualAlloc(NULL, grid_dim * grid_dim * sizeof(uint8_t), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  uint32_t cc = 0;
  while (cc < initial_point_count) {
    grid[initial_points[cc].y * grid_dim + initial_points[cc].x] = 1;
    cc++;
  }
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
  return grid;
}

