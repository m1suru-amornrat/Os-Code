#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <stdexcept>
#include <queue> //
using namespace std;


// ============================================
// TODO 1: สร้าง Base class สำหรับ Device
// ============================================
class IODevice {
protected:
    string deviceName;
    bool isOpen;
    
public:
    IODevice(string name) : deviceName(name), isOpen(false) {}
    virtual ~IODevice() {}
    
    // TODO: Pure virtual methods ที่ทุก device ต้องมี
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual string getDeviceType() = 0;
    virtual void displayInfo() = 0;
    
    string getName() { return deviceName; }
    bool getStatus() { return isOpen; }
};

// ============================================
// TODO 2: Block Device (Disk, USB Drive)
// ============================================
class BlockDevice : public IODevice {
private:
    size_t blockSize;
    size_t totalBlocks;
    vector<vector<uint8_t>> blocks; // จำลอง disk blocks
    
public:
    BlockDevice(string name, size_t blockSz, size_t totalBlk) 
        : IODevice(name), blockSize(blockSz), totalBlocks(totalBlk) {
        blocks.resize(totalBlocks, vector<uint8_t>(blockSize, 0));
    }
    
    bool open() override {
        // TODO: เปิด device
        isOpen = true;
        cout << "[Block Device] " << deviceName << " opened" << endl;
        return true;
    }
    
    void close() override {
        // TODO: ปิด device
        isOpen = false;
        cout << "[Block Device] " << deviceName << " closed" << endl;
    }
    
    // TODO 3: เขียน method readBlock(blockNum)
    vector<uint8_t> readBlock(size_t blockNum) {
        if (!isOpen) throw runtime_error("Device not open");
        if (blockNum >= totalBlocks) throw out_of_range("Block number out of range");
        // return block data
        return blocks[blockNum];
    }
    
    // TODO 4: เขียน method writeBlock(blockNum, data)
    void writeBlock(size_t blockNum, vector<uint8_t>& data) {
        if (!isOpen) throw runtime_error("Device not open");
        if (blockNum >= totalBlocks) throw out_of_range("Block number out of range");
        if (data.size() != blockSize) throw invalid_argument("Data size mismatch");
        // write data to block
        blocks[blockNum] = data;
        cout << "[Block Device] Block " << blockNum << " written" << endl;
    }
    
    string getDeviceType() override { return "Block Device"; }
    
    void displayInfo() override {
        cout << "Device: " << deviceName << endl;
        cout << "Type: " << getDeviceType() << endl;
        cout << "Block Size: " << blockSize << " bytes" << endl;
        cout << "Total Blocks: " << totalBlocks << endl;
        cout << "Total Capacity: " << (blockSize * totalBlocks) << " bytes" << endl;
    }
};

// ============================================
// TODO 5: Character Device (Keyboard, Serial Port)
// ============================================
class CharacterDevice : public IODevice {
private:
    queue<char> inputBuffer;
    string outputBuffer;
    
public:
    CharacterDevice(string name) : IODevice(name) {}
    
    bool open() override {
        isOpen = true;
        cout << "[Char Device] " << deviceName << " opened" << endl;
        return true;
    }
    
    void close() override {
        isOpen = false;
        cout << "[Char Device] " << deviceName << " closed" << endl;
    }
    
    // TODO 6: เขียน method getChar()
    char getChar() {
        if (!isOpen) throw runtime_error("Device not open");
        if (inputBuffer.empty()) {
            // จำลองการรับ character
            return '\0';
        }
        char c = inputBuffer.front();
        inputBuffer.pop();
        return c;
    }
    
    // TODO 7: เขียน method putChar(char c)
    void putChar(char c) {
        if (!isOpen) throw runtime_error("Device not open");
        outputBuffer += c;
        cout << "[Char Device] Output: " << c << endl;
    }
    
    void simulateInput(string input) {
        for (char c : input) inputBuffer.push(c);
    }
    
    string getDeviceType() override { return "Character Device"; }
    
    void displayInfo() override {
        cout << "Device: " << deviceName << endl;
        cout << "Type: " << getDeviceType() << endl;
        cout << "Buffer size: " << inputBuffer.size() << " chars" << endl;
    }
};

// ============================================
// TODO 8: Network Device
// ============================================
class NetworkDevice : public IODevice {
private:
    string ipAddress;
    int port;
    bool connected;
    vector<string> receivedPackets;
    
public:
    NetworkDevice(string name, string ip, int p) 
        : IODevice(name), ipAddress(ip), port(p), connected(false) {}
    
    bool open() override {
        isOpen = true;
        cout << "[Network Device] " << deviceName << " opened" << endl;
        return true;
    }
    
    void close() override {
        isOpen = false;
        connected = false;
        cout << "[Network Device] " << deviceName << " closed" << endl;
    }
    
    // TODO 9: จำลอง network operations
    bool connect() {
        if (!isOpen) return false;
        connected = true;
        cout << "[Network] Connected to " << ipAddress << ":" << port << endl;
        return true;
    }
    
    void sendPacket(string data) {
        if (!connected) throw runtime_error("Not connected");
        cout << "[Network] Sending: " << data << endl;
    }
    
    void receivePacket(string packet) {
        receivedPackets.push_back(packet);
    }
    
    string getDeviceType() override { return "Network Device"; }
    
    void displayInfo() override {
        cout << "Device: " << deviceName << endl;
        cout << "Type: " << getDeviceType() << endl;
        cout << "IP: " << ipAddress << ":" << port << endl;
        cout << "Connected: " << (connected ? "Yes" : "No") << endl;
    }
};

// ============================================
// TODO 10: Device Manager (จำลอง Kernel's Device Table)
// ============================================
class DeviceManager {
private:
    map<string, shared_ptr<IODevice>> deviceTable;
    
public:
    void registerDevice(shared_ptr<IODevice> device) {
        deviceTable[device->getName()] = device;
        cout << "[DevMgr] Registered: " << device->getName() 
             << " (" << device->getDeviceType() << ")" << endl;
    }
    
    shared_ptr<IODevice> getDevice(string name) {
        // TODO: return device จาก deviceTable
        if (deviceTable.find(name) == deviceTable.end())
            throw runtime_error("Device not found: " + name);
        return deviceTable[name];
    }
    
    void listAllDevices() {
        cout << "\n=== Registered Devices ===" << endl;
        for (auto& pair : deviceTable) {
            cout << "- " << pair.first 
                 << " [" << pair.second->getDeviceType() << "]"
                 << " Status: " << (pair.second->getStatus() ? "Open" : "Closed")
                 << endl;
        }
    }
    
    void openDevice(string name) {
        // TODO: เปิด device ตามชื่อ
        getDevice(name)->open();
    }
    
    void closeDevice(string name) {
        // TODO: ปิด device ตามชื่อ
        getDevice(name)->close();
    }
};

int main() {
    cout << "=== Application I/O Interface Demo ===" << endl;
    
    DeviceManager devMgr;
    
    // สร้างและ register devices
    auto disk = make_shared<BlockDevice>("sda", 512, 100);
    auto keyboard = make_shared<CharacterDevice>("keyboard");
    auto ethernet = make_shared<NetworkDevice>("eth0", "192.168.1.1", 8080);
    
    devMgr.registerDevice(disk);
    devMgr.registerDevice(keyboard);
    devMgr.registerDevice(ethernet);
    
    devMgr.listAllDevices();
    
    // TODO: ทดสอบ Block Device
    cout << "\n--- Block Device Test ---" << endl;
    devMgr.openDevice("sda");
    auto diskDevice = dynamic_pointer_cast<BlockDevice>(devMgr.getDevice("sda"));
    
    vector<uint8_t> testData(512, 0xAB);
    diskDevice->writeBlock(0, testData);
    auto readData = diskDevice->readBlock(0);
    cout << "Read block 0, first byte: " << hex << (int)readData[0] << dec << endl;
    diskDevice->displayInfo();
    
    // TODO: ทดสอบ Character Device
    cout << "\n--- Character Device Test ---" << endl;
    devMgr.openDevice("keyboard");
    auto kbDevice = dynamic_pointer_cast<CharacterDevice>(devMgr.getDevice("keyboard"));
    kbDevice->simulateInput("Hello OS!");
    for (int i = 0; i < 5; i++) {
        char c = kbDevice->getChar();
        if (c != '\0') cout << "Read char: " << c << endl;
    }
    
    // TODO: ทดสอบ Network Device
    cout << "\n--- Network Device Test ---" << endl;
    devMgr.openDevice("eth0");
    auto netDevice = dynamic_pointer_cast<NetworkDevice>(devMgr.getDevice("eth0"));
    netDevice->connect();
    netDevice->sendPacket("GET / HTTP/1.1");
    
    devMgr.listAllDevices();
    
    return 0;
}
