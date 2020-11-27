/*
Nhom Truong: Vu Thai Son-K185480106048

Các thành viên trong nhóm:
Tran Thi Duyen
Tran Van Ngoan
Vuong Thu Hoai
Le Thuy Nga
Nguyen Thi Nhuong
De tai 6:
*/
#include <iostream>
#include <string>
#include <ncurses.h>
#include "Vector.cpp"
// #include <vector>
using namespace std;

string info[5] = {"Nam", "Nu", "Khac", "Tot", "Xau"};

int thang31[7] = {1, 3, 5, 7, 8, 10, 12};
int thang30[5] = {4, 6, 9, 11};

class Tieuhoc;
class Truongthanh;

vector<Tieuhoc> Childlist;         // danh sach tre con
vector<Truongthanh> Adultlist;     // danh sach nguoi lon
vector<Truongthanh> military_list; // danh sach nhan khau di qs
vector<Tieuhoc> Primary_list;      // danh sach di hoc tieu hoc

// Tao kieu ngay thang nam sinh ( date of birth)
struct dob
{
    int ngay;
    int thang;
    int nam;
};

// Ham kiem tra thoi gian nhap co hop le khong
bool checkDateTime(dob Datetime)
{
    if ((Datetime.nam % 400 == 0) || (Datetime.nam % 4 == 0 && Datetime.nam % 100 != 0))
    {
        if (Datetime.thang == 2 && Datetime.ngay <= 29)
            return true;
        else
        {
            for (int i = 0; i < 7; i++)
            {
                if (Datetime.thang == thang31[i])
                {
                    if (Datetime.ngay <= 31 && Datetime.ngay > 0)
                        return true;
                }
                if (Datetime.thang == thang30[i])
                {
                    if (Datetime.ngay <= 30 && Datetime.ngay > 0)
                        return true;
                }
            }
        }
    }
    else
    {
        if (Datetime.thang == 2 && Datetime.ngay <= 28)
            return true;
        else
        {
            for (int i = 0; i < 7; i++)
            {
                if (Datetime.thang == thang31[i])
                {
                    if (Datetime.ngay <= 31 && Datetime.ngay > 0)
                        return true;
                }
                else if (Datetime.thang == thang30[i])
                {
                    if (Datetime.ngay <= 30 && Datetime.ngay > 0)
                        return true;
                }
            }
        }
    }
}

// Ham check tuoi xem truong thanh ( tuoi >= 18) hay tieu hoc (<18)
// Lay thoi diem hien tai la 20-9-2020
bool checkAdult(dob birthdate) // birthdate: ngay sinh, Adult: nguoi lon
{
    dob DateRightNow; // thoi gian hien tai
    DateRightNow.ngay = 20;
    DateRightNow.thang = 9;
    DateRightNow.nam = 2020;
    if (DateRightNow.nam - birthdate.nam > 18 || DateRightNow.nam - birthdate.nam == 18 && DateRightNow.thang > birthdate.thang)
        return true;
    else if (DateRightNow.nam - birthdate.nam == 18 && DateRightNow.thang == birthdate.thang)
    {
        if (DateRightNow.ngay >= birthdate.ngay)
            return true;
        else
            return false;
    }
    else
        return false;
}

//check tuoi >= 18 chua de di NVQS
bool Military_Call(string sex, string con, dob birthdate)
{
    dob DateRightNow;
    DateRightNow.thang = 9;
    DateRightNow.nam = 2020;

    //info = {"Nam", "Nu", "Khac", "Tot", "Xau"};
    if (sex == info[0] && con == info[3])
    {
        if (DateRightNow.nam - birthdate.nam > 18 && DateRightNow.nam - birthdate.nam <= 25)
        {
            return true;
        }
        else if (DateRightNow.nam - birthdate.nam == 18 && DateRightNow.thang >= birthdate.thang)
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        return false;
    }
}

// in xem du toi di hoc chua (aka = 6 tuoi)
bool checkDiHoc(dob birthdate)
{
    if ((2020 - birthdate.nam == 6) && (9 >= birthdate.thang))
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Nhankhau
{
public:
    int SoThuTu, PersonalCode; // Personal Code: chung minh nhan dan, ma so cong dan
    int SoLuong;

    //info = {"Nam", "Nu", "Khac", "Tot", "Xau"};
    string Ten, DiaChi;
    string GioiTinh;
    const char *Name;
    const char *Addr;
    const char *Gender;
    // Nhankhau *nhankhau;

    dob NgaySinh;
    friend void NhapTieuHoc(Nhankhau Household); //Household: nhan khau
    friend void NhapTruongThanh(Nhankhau Household);

    // Y tuong: Nhap ngay thang nam sinh cua Nhan khau, neu
    // >= 18 thi se chay ham NhapTruongThanh(),
    // < 18 thi se chay ham NhapTieuHoc()
    void InputInfo()
    {
        endwin();
        system("clear");

        cout << "So luong nhan khau: ";
        cin >> SoLuong;

        Nhankhau *nhankhau;
        nhankhau = new Nhankhau[SoLuong];

        for (int i = 0; i < SoLuong; i++)
        {
        jump:
            cout << "\nNgay thang nam sinh: " << endl;
            cout << "Ngay: ";
            cin >> nhankhau[i].NgaySinh.ngay;

            cout << "Thang: ";
            cin >> nhankhau[i].NgaySinh.thang;

            cout << "Nam: ";
            cin >> nhankhau[i].NgaySinh.nam;
            if (checkDateTime(nhankhau[i].NgaySinh) == true)
            {
                if (checkAdult(nhankhau[i].NgaySinh) == true)
                {
                    NhapTruongThanh(nhankhau[i]);
                }
                else
                {
                    NhapTieuHoc(nhankhau[i]);
                }
            }
            else
            {
                cout << "Invalid Date and Time, please input again" << endl; // thong bao ngay thang khong hop le
                goto jump;
            }
        }
        refresh();
    }
};

class Tieuhoc : public Nhankhau
{
public:
    dob ngaysinh; //dob: date of birth: ngay sinh

    friend void NhapTieuHoc(Nhankhau Household);
    void DiHoc()
    {
        for (int i = 0; i < Childlist.size(); i++)
        {

            if (checkDiHoc(Childlist[i].ngaysinh) == true) // tuoi >= 6
            {

                Childlist[i].Name = Childlist[i].Ten.c_str();
                Childlist[i].Gender = Childlist[i].GioiTinh.c_str();
                Childlist[i].Addr = Childlist[i].DiaChi.c_str();
                Primary_list.push_back(Childlist[i]);
            }
        }
    }

    // ham in du lieu
};

class Truongthanh : public Nhankhau
{
public:
    dob ngaysinh;
    string TinhTrang; // tinh trang suc khoe
    const char *Condition;
    bool call_state;

    friend void NhapTruongThanh(Nhankhau Household);

    // ham thong ke du lieu
};

void NhapTieuHoc(Nhankhau Household) // Household : nhan khau
{
    Tieuhoc Child;
    char sex;

    Child.ngaysinh = Household.NgaySinh;

    //info = {"Nam", "Nu", "Khac", "Tot", "Xau"};

    cout << "\nNhập tên: ";
    cin.ignore();
    getline(cin, Child.Ten);

jump:
    cout << "Giới Tính (F/M): ";
    cin >> sex;
    if (sex == 'M' || sex == 'm')
    {
        Child.GioiTinh = info[0];
    }
    else if (sex == 'F' || sex == 'f')
    {
        Child.GioiTinh = info[1];
    }
    else
    {
        cout << "Please input Gender again with M as Nam, F as Nu" << endl;
        goto jump;
    }

    cout << "Mã Số Công Dân: ";
    cin >> Child.PersonalCode;

    cout << "Địa Chỉ: ";
    cin.ignore();
    getline(cin, Child.DiaChi);

    cout << "\n";

    Childlist.push_back(Child); // vector Childlist

    Child.DiHoc();

    for (int i = 0; i < Childlist.size(); i++)
    {
        Childlist[i].Name = Childlist[i].Ten.c_str();
        Childlist[i].Gender = Childlist[i].GioiTinh.c_str();
        Childlist[i].Addr = Childlist[i].DiaChi.c_str();
    }
}

void NhapTruongThanh(Nhankhau Household)
{

    Truongthanh Adult;
    char sex;
    char condition;

    Adult.ngaysinh = Household.NgaySinh;
    Adult.call_state = false;
    cout << "\nNhập tên: ";
    cin.ignore();
    getline(cin, Adult.Ten);

jump1:
    cout << "Giới Tính (F/M): ";
    cin >> sex;

    if (sex == 'M' || sex == 'm')
    {
        Adult.GioiTinh = info[0];
    }
    else if (sex == 'F' || sex == 'f')
    {
        Adult.GioiTinh = info[1];
    }
    else
    {
        cout << "Please input Gender again with M as Nam, F as Nu" << endl;
        goto jump1;
    }

    //vector<string> info = {"Nam", "Nu", "Khac", "Tot", "Xau"};

jump2:
    cout << "Tình trạng sức khoẻ (G/B) :";
    cin >> condition;

    if (condition == 'G' || condition == 'g')
    {
        Adult.TinhTrang = info[3];
    }
    else if (condition == 'B' || condition == 'b')
    {
        Adult.TinhTrang = info[4];
    }
    else
    {
        cout << "Please input condition again with G as Tot, B as Xau" << endl;
        goto jump2;
    }
    Adult.Condition = Adult.TinhTrang.c_str();
    cout << "Mã Số Công Dân: ";
    cin >> Adult.PersonalCode;

    cout << "Địa Chỉ: ";
    cin.ignore();
    getline(cin, Adult.DiaChi);

    cout << "\n";

    Adultlist.push_back(Adult);

    if (Military_Call(Adult.GioiTinh,
                      Adult.TinhTrang,
                      Adult.ngaysinh) == true)
    {
        military_list.push_back(Adult);
        for (int i = 0; i < Adultlist.size(); i++)
        {
            military_list[i].Name = military_list[i].Ten.c_str();
            military_list[i].Gender = military_list[i].GioiTinh.c_str();
            military_list[i].Condition = military_list[i].TinhTrang.c_str();
            military_list[i].Addr = military_list[i].DiaChi.c_str();
        }
    }

    for (int i = 0; i < Adultlist.size(); i++)
    {
        Adultlist[i].Name = Adultlist[i].Ten.c_str();
        Adultlist[i].Gender = Adultlist[i].GioiTinh.c_str();
        Adultlist[i].Condition = Adultlist[i].TinhTrang.c_str();
        Adultlist[i].Addr = Adultlist[i].DiaChi.c_str();
    }
}
