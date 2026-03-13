#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring> // เพิ่ม <cstring> สำหรับใช้งาน memcpy ใน BufferTest

using namespace std;

// ============================================
// TODO 1: Performance Metrics Structure
// ============================================
struct IOMetrics {
    string testName;
    double throughput;      // bytes per second
    double latency;         // milliseconds
    double iops;            // I/O operations per second
    long long totalBytes;
    int totalOperations;
    double duration;        // seconds
    
    void display() {
        cout << "\n=== " << testName << " ===" << endl;
        cout << fixed << setprecision(2);
        cout << "Throughput:   " << throughput / 1024 / 1024 << " MB/s" << endl;
        cout << "Latency:      " << latency << " ms" << endl;
        cout << "IOPS:         " << iops << " ops/sec" << endl;
        cout << "Total Data:   " << totalBytes / 1024 << " KB" << endl;
        cout << "Operations:   " << totalOperations << endl;
        cout << "Duration:     " << duration << " sec" << endl;
    }
};

// ============================================
// TODO 2: Simulated Disk Drive
// ============================================
class SimulatedDisk {
private:
    vector<vector<uint8_t>> sectors;
    size_t sectorSize;
    size_t numSectors;
    int currentHead;        
    int seekTimeMs;         
    int rotationalLatencyMs;
    
    int calculateSeekTime(int targetSector) {
        int tracks = abs(targetSector - currentHead) / 100;
        return tracks * seekTimeMs + rotationalLatencyMs;
    }
    
public:
    SimulatedDisk(size_t sectorSz, size_t numSect, 
                  int seekMs = 1, int rotMs = 1)
        : sectorSize(sectorSz), numSectors(numSect), 
          currentHead(0), seekTimeMs(seekMs), rotationalLatencyMs(rotMs) {
        sectors.resize(numSectors, vector<uint8_t>(sectorSize, 0));
    }
    
    double sequentialWrite(size_t numOps) {
        auto start = chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < numOps && i < numSectors; i++) {
            currentHead = i;
            vector<uint8_t> data(sectorSize, static_cast<uint8_t>(i % 256));
            sectors[i] = data;
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
    
    double sequentialRead(size_t numOps) {
        auto start = chrono::high_resolution_clock::now();
        
        for (size_t i = 0; i < numOps && i < numSectors; i++) {
            currentHead = i;
            volatile uint8_t dummy = sectors[i][0]; 
            (void)dummy;
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
    
    double randomWrite(size_t numOps) {
        auto start = chrono::high_resolution_clock::now();
        
        srand(42); 
        for (size_t i = 0; i < numOps; i++) {
            size_t target = rand() % numSectors;
            currentHead = target;
            vector<uint8_t> data(sectorSize, static_cast<uint8_t>(i % 256));
            sectors[target] = data;
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
    
    double randomRead(size_t numOps) {
        auto start = chrono::high_resolution_clock::now();
        
        srand(42);
        for (size_t i = 0; i < numOps; i++) {
            size_t target = rand() % numSectors;
            currentHead = target;
            volatile uint8_t dummy = sectors[target][0];
            (void)dummy;
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
    }
    
    size_t getSectorSize() { return sectorSize; }
};

// ============================================
// TODO 3: Buffer Size Impact Test
// ============================================
class BufferTest {
public:
    static IOMetrics testBufferSize(size_t bufferSize, size_t totalData) {
        IOMetrics metrics;
        metrics.testName = "BufSize: " + to_string(bufferSize);
        
        vector<uint8_t> src(totalData);
        vector<uint8_t> dst(totalData, 0);
        
        for (size_t i = 0; i < totalData; i++) src[i] = i % 256;
        
        auto start = chrono::high_resolution_clock::now();
        
        size_t ops = 0;
        for (size_t offset = 0; offset < totalData; offset += bufferSize) {
            size_t copySize = min(bufferSize, totalData - offset);
            memcpy(dst.data() + offset, src.data() + offset, copySize);
            ops++;
        }
        
        auto end = chrono::high_resolution_clock::now();
        metrics.duration = chrono::duration<double>(end - start).count();
        metrics.totalBytes = totalData;
        metrics.totalOperations = ops;
        metrics.throughput = totalData / metrics.duration;
        metrics.latency = (metrics.duration / ops) * 1000.0;
        metrics.iops = ops / metrics.duration;
        
        return metrics;
    }
};

// ============================================
// TODO 4: Asynchronous vs Synchronous I/O
// ============================================
// ... (คงเดิมตามโค้ดต้นฉบับของคุณ) ...

// ============================================
// TODO 5: Performance Report Generator
// ============================================
class PerformanceReport {
private:
    vector<IOMetrics> results;
    
public:
    void addResult(IOMetrics m) {
        results.push_back(m);
    }
    
    void generateReport() {
        cout << "\n";
        cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║              I/O PERFORMANCE REPORT                          ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        cout << left << setw(23) << "║ Test Name" 
             << right << setw(12) << "MB/s  "
             << setw(13) << "Latency(ms) "
             << setw(10) << "IOPS"
             << "    ║" << endl;
        cout << "╠══════════════════════════════════════════════════════════════╣" << endl;
        
        for (auto& m : results) {
            cout << "║ " << left << setw(21) << m.testName.substr(0, 20)
                 << right << fixed << setprecision(2)
                 << setw(10) << m.throughput / 1024 / 1024 << "  "
                 << setw(10) << m.latency << "  "
                 << setw(10) << (int)m.iops
                 << "    ║" << endl;
        }
        
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    }
    
    void analyzeBestWorst() {
        if (results.empty()) return;
        
        auto best = max_element(results.begin(), results.end(),
            [](const IOMetrics& a, const IOMetrics& b) {
                return a.throughput < b.throughput;
            });
        
        auto worst = min_element(results.begin(), results.end(),
            [](const IOMetrics& a, const IOMetrics& b) {
                return a.throughput < b.throughput;
            });
        
        cout << "\n🏆 Best Throughput:  " << best->testName 
             << " (" << fixed << setprecision(2) 
             << best->throughput / 1024 / 1024 << " MB/s)" << endl;
        cout << "⚠️  Worst Throughput: " << worst->testName 
             << " (" << fixed << setprecision(2) 
             << worst->throughput / 1024 / 1024 << " MB/s)" << endl;
    }
};

int main() {
    cout << "=== I/O Performance Measurement ===" << endl;
    PerformanceReport report;
    
    cout << "\n=== Disk I/O Performance ===" << endl;
    SimulatedDisk disk(512, 10000);
    const size_t NUM_OPS = 5000;
    
    // Sequential Write
    cout << "Testing Sequential Write..." << endl;
    double seqWriteTime = disk.sequentialWrite(NUM_OPS);
    IOMetrics seqWrite;
    seqWrite.testName = "Seq Write";
    seqWrite.totalBytes = NUM_OPS * disk.getSectorSize();
    seqWrite.totalOperations = NUM_OPS;
    seqWrite.duration = seqWriteTime;
    seqWrite.throughput = seqWrite.totalBytes / seqWriteTime;
    seqWrite.latency = (seqWriteTime / NUM_OPS) * 1000.0;
    seqWrite.iops = NUM_OPS / seqWriteTime;
    report.addResult(seqWrite);
    
    // เติมส่วนที่ขาดไป: Sequential Read
    cout << "Testing Sequential Read..." << endl;
    double seqReadTime = disk.sequentialRead(NUM_OPS);
    IOMetrics seqRead;
    seqRead.testName = "Seq Read";
    seqRead.totalBytes = NUM_OPS * disk.getSectorSize();
    seqRead.totalOperations = NUM_OPS;
    seqRead.duration = seqReadTime;
    seqRead.throughput = seqRead.totalBytes / seqReadTime;
    seqRead.latency = (seqReadTime / NUM_OPS) * 1000.0;
    seqRead.iops = NUM_OPS / seqReadTime;
    report.addResult(seqRead);

    // เติมส่วนที่ขาดไป: Random Write
    cout << "Testing Random Write..." << endl;
    double randWriteTime = disk.randomWrite(NUM_OPS);
    IOMetrics randWrite;
    randWrite.testName = "Random Write";
    randWrite.totalBytes = NUM_OPS * disk.getSectorSize();
    randWrite.totalOperations = NUM_OPS;
    randWrite.duration = randWriteTime;
    randWrite.throughput = randWrite.totalBytes / randWriteTime;
    randWrite.latency = (randWriteTime / NUM_OPS) * 1000.0;
    randWrite.iops = NUM_OPS / randWriteTime;
    report.addResult(randWrite);

    // ===== BUFFER SIZE TEST =====
    cout << "\n=== Buffer Size Impact ===" << endl;
    size_t totalDataSize = 10 * 1024 * 1024; // 10 MB
    
    report.addResult(BufferTest::testBufferSize(64, totalDataSize));        // 64 Bytes
    report.addResult(BufferTest::testBufferSize(1024, totalDataSize));      // 1 KB
    report.addResult(BufferTest::testBufferSize(4096, totalDataSize));      // 4 KB
    report.addResult(BufferTest::testBufferSize(1024 * 1024, totalDataSize)); // 1 MB

    // สร้างตาราง Report
    report.generateReport();
    report.analyzeBestWorst();
    
    return 0;
}
