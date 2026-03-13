int allocate() {
    for (int i = 0; i < TOTAL_BLOCKS; i++)
        if (freeBlocks[i]) { freeBlocks[i] = 0; return i; }
    throw runtime_error("Disk full: no free blocks available");
    // OR return -1 and always check: if (b == -1) { handle error; }
}

// In main():
try {
    int b = dm.allocate();
    cout << "Allocated block " << b << endl;
} catch (const runtime_error& e) {
    cerr << "Allocation error: " << e.what() << endl;
}
