// Returns starting block index, or -1 if not enough contiguous space
int allocateContiguous(int n) {
    int count = 0, start = -1;
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        if (freeBlocks[i]) {
            if (count == 0) start = i;
            count++;
            if (count == n) {
                // Mark all n blocks as used
                for (int j = start; j < start + n; j++)
                    freeBlocks[j] = 0;
                return start;
            }
        } else {
            count = 0; start = -1; // reset streak
        }
    }
    return -1; // not enough contiguous free blocks
}
