class USBDrive : public StorageDevice {
public:
    string getInterface() override { return "USB 3.0"; }
    double getBandwidth() override { return 480.0; }
};

// Usage in main():
StorageDevice* d3 = new USBDrive();
d3->read(200);
// Output: USB 3.0: Reading LBA 200 at 480 MB/s
delete d3;
