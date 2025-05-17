#include <iostream>
#include <string>
using namespace std;

class Petugas;
class Admin;

class Buku {
private:
    string judul;
    string penulis;
    bool dipinjam;

public:
    Buku(string j, string p) : judul(j), penulis(p), dipinjam(false) {}

    void infoBuku() const {
        cout << "Judul: " << judul << ", Penulis: " << penulis 
             << ", Status: " << (dipinjam ? "Dipinjam" : "Tersedia") << endl;
    }

    friend class Petugas;
    friend void aksesTerbatas(Admin* a, Buku* b);
};

class Peminjam {
private:
    string nama;
    int id;
    int totalPinjaman;

public:
    Peminjam(string n, int i) : nama(n), id(i), totalPinjaman(0) {}

    void infoPeminjam() const {
        cout << "Nama: " << nama << ", ID: " << id 
             << ", Total Pinjaman: " << totalPinjaman << endl;
    }

    friend class Petugas;
    friend void aksesTerbatas(Admin* a, Peminjam* p);
};

class Petugas {
private:
    string nama;
    int id;
    string levelAkses;

public:
    Petugas(string n, int i, string la) : nama(n), id(i), levelAkses(la) {}

    void prosesPinjam(Buku* b, Peminjam* p) {
        if (!b->dipinjam) {
            b->dipinjam = true;
            p->totalPinjaman++;
            cout << "Buku berhasil dipinjam.\n";
        } else {
            cout << "Buku sudah dipinjam.\n";
        }
    }

    void prosesKembali(Buku* b) {
        if (b->dipinjam) {
            b->dipinjam = false;
            cout << "Buku berhasil dikembalikan.\n";
        } else {
            cout << "Buku belum dipinjam.\n";
        }
    }

    friend class Admin;
};

class Admin {
public:
    void ubahAkses(Petugas* p, string aksesBaru) {
        p->levelAkses = aksesBaru;
        cout << "Level akses petugas diubah menjadi: " << aksesBaru << endl;
    }

    friend void aksesTerbatas(Admin* a, Buku* b);
    friend void aksesTerbatas(Admin* a, Peminjam* p);
};

void aksesTerbatas(Admin* a, Buku* b) {
    cout << "[Admin Akses Terbatas] Status Buku: " 
         << (b->dipinjam ? "Dipinjam" : "Tersedia") << endl;
}

void aksesTerbatas(Admin* a, Peminjam* p) {
    cout << "[Admin Akses Terbatas] Total Pinjaman: " << p->totalPinjaman << endl;
}

int main() {
    Buku* buku1 = new Buku("Clean Code", "Robert C. Martin");
    Peminjam* peminjam1 = new Peminjam("Andi", 101);
    Petugas* petugas1 = new Petugas("Budi", 201, "Level 1");
    Admin* admin1 = new Admin();

    buku1->infoBuku();
    peminjam1->infoPeminjam();

    petugas1->prosesPinjam(buku1, peminjam1);
    buku1->infoBuku();
    peminjam1->infoPeminjam();

    admin1->ubahAkses(petugas1, "Level 2");

    aksesTerbatas(admin1, buku1);
    aksesTerbatas(admin1, peminjam1);

    petugas1->prosesKembali(buku1);
    buku1->infoBuku();

    delete buku1;
    delete peminjam1;
    delete petugas1;
    delete admin1;

    return 0;
}