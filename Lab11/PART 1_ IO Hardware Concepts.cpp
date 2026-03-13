#include <iostream>
#include <bitset>
#include <thread>
#include <chrono>
#include <queue>
#include <functional>
#include <mutex>
#include <string>
using namespace std;

// TODO 1: สร้าง struct สำหรับ Status Register
struct StatusRegister {
    // TODO: เพิ่ม flags: busy, error, ready, transferComplete
    // Hint: ใช้ bool หรือ bitfield
};

// TODO 2: สร้าง class IOPort
class IOPort {
public:
    uint8_t dataRegister;
    StatusRegister status;
    uint8_t controlRegister;
    
    IOPort() {
        // TODO: initialize registers
    }
    
    // TODO 3: เขียน method writeData(uint8_t data)
    void writeData(uint8_t data) {
        // จำลองการเขียนข้อมูลไปยัง port
        // ต้องเช็ค busy flag ก่อน
        // ถ้า busy ให้แสดง error
    }
    
    // TODO 4: เขียน method readData()
    uint8_t readData() {
        // จำลองการอ่านข้อมูลจาก port
        // return ค่าจาก dataRegister
    }
    
    // TODO 5: เขียน method pollStatus()
    bool pollStatus() {
        // return true ถ้า ready
        // return false ถ้า busy
    }
};

// TODO 6: สร้าง class DeviceController
class DeviceController {
private:
    IOPort port;
    string deviceName;
    queue<function<void()>> interruptQueue;
    
public:
    DeviceController(string name) {
        // TODO: initialize
    }
    
    // TODO 7: จำลอง Polling I/O
    void pollingIO(uint8_t data) {
        cout << "[POLLING] Waiting for device ready..." << endl;
        // วน loop จนกว่า device จะพร้อม
        // เมื่อพร้อมแล้วให้ write data
    }
    
    // TODO 8: จำลอง Interrupt-driven I/O
    void interruptDrivenIO(uint8_t data, function<void()> callback) {
        cout << "[INTERRUPT] Sending data, registering interrupt handler..." << endl;
        // ส่ง data และลงทะเบียน interrupt handler
        // เรียก callback เมื่อ transfer เสร็จ
    }
    
    void processInterrupts() {
        // TODO: process interrupt queue
    }
};

int main() {
    cout << "=== I/O Hardware Simulation ===" << endl;
    
    DeviceController keyboard("Keyboard");
    DeviceController disk("Disk Drive");
    
    // TODO 9: ทดสอบ Polling I/O
    cout << "\n--- Polling I/O Test ---" << endl;
    // เรียกใช้ pollingIO
    
    // TODO 10: ทดสอบ Interrupt-driven I/O
    cout << "\n--- Interrupt-driven I/O Test ---" << endl;
    // เรียกใช้ interruptDrivenIO พร้อม lambda callback
    
    return 0;
}
________________________________________
