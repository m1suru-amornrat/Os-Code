RAID-5 distributes both data AND parity. For 3 disks, each stripe has 2 data chunks + 1 parity chunk (XOR of the data), rotated across disks.
Code:
void writeRAID5(string blockA, string blockB) {
    // Compute parity: XOR all characters
    string parity = "";
    for (int i = 0; i < min(blockA.size(), blockB.size()); i++)
        parity += char(blockA[i] ^ blockB[i]);

    // Stripe 0: parity on disk 2
    disks[0].push_back(blockA);
    disks[1].push_back(blockB);
    disks[2].push_back(parity); // P on disk 2

    // Next stripe: rotate parity to disk 1
    // disks[0].push_back(blockC);
    // disks[1].push_back(parity2); // P on disk 1
    // disks[2].push_back(blockD);
}

// Recovery example: if disk 0 fails, restore from disk 1 XOR disk 2 (parity)
