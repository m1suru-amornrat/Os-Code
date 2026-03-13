const int NUM_BLOCKS = 8;
int writeCount[NUM_BLOCKS] = {0};

int wearLevelWrite(int logicalBlock) {
    // Find physical block with fewest writes
    int minWrites = writeCount[0], physBlock = 0;
    for (int i = 1; i < NUM_BLOCKS; i++)
        if (writeCount[i] < minWrites) { minWrites = writeCount[i]; physBlock = i; }
    writeCount[physBlock]++;
    cout << "Logical " << logicalBlock << " -> Physical " << physBlock << endl;
    return physBlock;
}
