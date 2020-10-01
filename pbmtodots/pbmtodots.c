#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pbm.h>
#include "grid.h"
#include "renderer.h"

int main(int argc, char **argv)
{
  int pbmwide = 0, pbmtall = 0;
  int gwide = 0, gtall = 0, format;
  bit *brow;
  grid *g;
 
  pbm_init(&argc, argv);

  if (argc > 1) {
      if (!freopen(argv[1], "r", stdin)) {
	  fprintf(stderr, "pbmtodots: failed to open %s\n", argv[1]);
	  fprintf(stderr, "Usage:  pbmtodots [ PBM_INPUT ]\n");
	  return 1;
      }
  }
  pbm_readpbminit(stdin, &pbmwide, &pbmtall, &format);

  gwide = pbmwide + (pbmwide % 2);
  gtall = pbmtall;
  if (gtall % 4) {
      gtall += 4 - (pbmtall % 4);
  }

  if ((gtall < 1) || (gwide < 1)) {
      fprintf(stderr, "pbmtodots: input has no size\n");
      return 1;
  } else {
      fprintf(stderr, "pbmtodots: input %dx%d, output %dx%d\n",
              pbmwide, pbmtall, gwide, gtall
             );
  }

  brow = pbm_allocrow(pbmwide + (pbmwide % 8));
  g = grid_new(gwide, gtall);

  if (!brow || !g)
  {
     fprintf(stderr, "pbmtodots: allocations failed\n");
     return 1;
  }

  grid_generate_lookup_table();

  for (int prow = 0; prow < pbmtall; prow++)
  {
      pbm_readpbmrow(stdin, brow, pbmwide, format);
      for (int pcol = 0; pcol < pbmwide; pcol++)
      {
	  if ( PBM_BLACK == brow[pcol] )
	  {
	      grid_set_pixel(g, pcol, prow);
          }
      }
  }

  
  renderer_raw_dump(g, 1);

  // Free allocations
  pbm_freerow(brow);
  grid_free(g);
  return 0;
}
