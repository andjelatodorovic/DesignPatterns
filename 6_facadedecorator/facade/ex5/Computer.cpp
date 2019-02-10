/* primer adaptiran sa interneta - nalazi se i na Wikipediji na stranici o Facade Pattern */

#include <iostream>

using namespace std;

/* kompleksan podsistem */
class CPU {
public:
    void freeze() { cout << "CPU freezing" << endl; }
    void jump(long position) { cout << "CPU jumping " << position << endl; }
    void execute() { cout << "CPU executing" << endl; }
};
/* kompleksan podsistem */
class Memory {
public:
    void load(long position, char* data) { cout << "Memory loading at " << position << endl; }
};
/* kompleksan podsistem */
class HardDrive {
public:
    char* read(long lba, int size) { cout << "HDA reading " << lba << ", " << size << endl; }
};

/* fasada */
class ComputerFacade {
public:
    ComputerFacade(): BOOT_ADDRESS(1234), BOOT_SECTOR(12), SECTOR_SIZE(1024) {
        m_processor = new CPU();
        m_ram = new Memory();
        m_hd = new HardDrive();
    }
    ~ComputerFacade() {
        delete m_processor;
        delete m_ram;
        delete m_hd;
    }
    void start() {
        m_processor->freeze();
        m_ram->load(BOOT_ADDRESS, m_hd->read(BOOT_SECTOR, SECTOR_SIZE));
        m_processor->jump(BOOT_ADDRESS);
        m_processor->execute();
    }
private:
    const int   BOOT_ADDRESS;
    const int   BOOT_SECTOR;
    const int   SECTOR_SIZE;
    CPU*        m_processor;
    Memory*     m_ram;
    HardDrive*  m_hd;
};

/* klijent startuje kompjuter koristeci fasadu */
int main() {
    ComputerFacade computer;
    computer.start();

    return 0;
}
