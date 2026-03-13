#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iomanip> // สำหรับใช้จัดรูปแบบการแสดงผลของ display
using namespace std;

// TODO 1: จำลอง Memory
class Memory {
private:
    vector<uint8_t> data;
    size_t size;
    
public:
    Memory(size_t size) : size(size), data(size, 0) {}
    
    // เขียน read() และ write() methods
    void write(size_t address, uint8_t value) {
        // เช็ค bounds ก่อน write เพื่อป้องกัน Out of bounds exception
        if (address < size) {
            data[address] = value;
        } else {
            cout << "[Memory Error] Write access violation at address " << address << endl;
        }
    }
    
    uint8_t read(size_t address) {
        // เช็ค bounds ก่อน read
        if (address < size) {
            return data[address];
        } else {
            cout << "[Memory Error] Read access violation at address " << address << endl;
            return 0;
        }
    }
    
    void display(size_t start, size_t length) {
        if (start >= size) return;
        size_t end = min(start + length, size);
        
        cout << "[Memory Dump] Address " << start << " to " << end - 1 << ":" << endl;
        for (size_t i = start; i < end; ++i) {
            cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
            if ((i - start + 1) % 16 == 0) cout << endl; // ขึ้นบรรทัดใหม่ทุกๆ 16 bytes
        }
        cout << dec << endl; // คืนค่าการแสดงผลกลับเป็นฐาน 10
    }
};

// TODO 2: จำลอง Programmed I/O
class ProgrammedIO {
private:
    int cpuCyclesUsed;
    
public:
    ProgrammedIO() : cpuCyclesUsed(0) {}
    
    long long transfer(Memory& mem, size_t destAddr, 
                       const vector<uint8_t>& source, size_t size) {
        auto start = chrono::high_resolution_clock::now();
        
        cout << "[PIO] CPU transferring " << size << " bytes..." << endl;
        
        for (size_t i = 0; i < size; i++) {
            // จำลอง CPU ตรวจสอบและ copy ทีละ byte
            mem.write(destAddr + i, source[i]);
            cpuCyclesUsed++; // PIO ต้องใช้ 1 CPU Cycle ต่อ 1 หน่วยการส่งข้อมูล
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        cout << "[PIO] Complete. CPU cycles used: " << cpuCyclesUsed << endl;
        return duration;
    }
};

// TODO 3: จำลอง DMA Controller
class DMAController {
private:
    uint32_t sourceAddress;
    uint32_t destAddress;
    uint32_t transferCount;
    bool busy;
    int cpuCyclesUsed; 
    
public:
    DMAController() : busy(false), cpuCyclesUsed(0) {}
    
    // setup() สำหรับตั้งค่า DMA
    void setup(uint32_t src, uint32_t dest, uint32_t count) {
        sourceAddress = src;
        destAddress = dest;
        transferCount = count;
    }
    
    // transfer() ที่จำลอง DMA transfer
    long long transfer(Memory& mem, const vector<uint8_t>& source) {
        auto start = chrono::high_resolution_clock::now();
        
        busy = true;
        cout << "[DMA] Starting transfer of " << transferCount << " bytes..." << endl;
        cout << "[DMA] CPU is FREE to do other work!" << endl;
        
        // DMA ทำการคัดลอกข้อมูลโดยไม่ต้องใช้ CPU มาเกี่ยวข้องในลูป
        for (uint32_t i = 0; i < transferCount; i++) {
            if (sourceAddress + i < source.size()) {
                mem.write(destAddress + i, source[sourceAddress + i]);
            }
        }
        
        // CPU cycles ถูกใช้แค่ตอนสั่ง Setup และรับ Interrupt เมื่อจบการทำงาน
        cpuCyclesUsed = 2; // setup + interrupt
        
        busy = false;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        
        cout << "[DMA] Transfer complete! CPU cycles used: " << cpuCyclesUsed << endl;
        cout << "[DMA] CPU interrupt sent to notify completion" << endl;
        return duration;
    }
};

int main() {
    cout << "=== DMA vs Programmed I/O Comparison ===" << endl;
    
    const size_t DATA_SIZE = 1024000; // ปรับข้อมูลให้เยอะขึ้นเพื่อให้เห็นความต่างของเวลาได้ชัดเจน
    Memory memory(1500000); // จอง memory ไว้ 1.5M
    
    vector<uint8_t> sourceData(DATA_SIZE);
    for (size_t i = 0; i < DATA_SIZE; i++) {
        sourceData[i] = static_cast<uint8_t>(i % 256);
    }
    
    // ทดสอบ Programmed I/O
    cout << "\n=== Programmed I/O ===" << endl;
    ProgrammedIO pio;
    long long pioTime = pio.transfer(memory, 0, sourceData, DATA_SIZE);
    
    // ทดสอบ DMA
    cout << "\n=== DMA Transfer ===" << endl;
    Memory memory2(1500000);
    DMAController dma;
    dma.setup(0, 0, DATA_SIZE);
    long long dmaTime = dma.transfer(memory2, sourceData);
    
    // เปรียบเทียบผล
    cout << "\n=== Performance Comparison ===" << endl;
    cout << "PIO Time: " << pioTime << " microseconds" << endl;
    cout << "DMA Time: " << dmaTime << " microseconds" << endl;
    
    return 0;
}
