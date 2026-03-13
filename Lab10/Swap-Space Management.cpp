void printStatus() {
    cout << "=== Swap Space Status ==" << endl;
    cout << "Total swap: " << swapSize << " MB" << endl;
    cout << "Used swap:  " << usedSwap  << " MB" << endl;
    cout << "Free swap:  " << (swapSize - usedSwap) << " MB" << endl;
    cout << "Processes in swap:" << endl;
    for (auto& [pid, mb] : swapTable)
        cout << "  PID " << pid << " -> " << mb << " MB" << endl;
    if (swapTable.empty())
        cout << "  (none)" << endl;
}
