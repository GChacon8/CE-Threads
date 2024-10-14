#ifndef EDFS_H
#define EDFS_H

#include "../../../CEThreads/CEthreads.h"
#include "../../../CEThreads/CEthreads.c"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void edfs(struct Process processes[], int n, int total_time);

#endif //EDFS_H
