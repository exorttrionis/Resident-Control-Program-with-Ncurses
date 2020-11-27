#include <stdio.h>
#include <ncurses.h>
#include "NhanKhau.cpp"
using namespace std;

#define WIDTH 36
#define HEIGHT 8

int startx = 0;
int starty = 0;

const char *choices[] = {
    "+ Nhap danh sach",
    "+ Danh sach nhan khau truong thanh",
    "+ Danh sach nhan khau tieu hoc",
    "+ Danh sach nhap ngu",
    "+ Danh sach den tuoi di hoc",
    "+ Exit",

};
int n_choices = 6;

void print_menu(WINDOW *menu_win, int highlight) // highlight the choice
{
    int x, y, i;

    x = 1;
    y = 1;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; i++)
    {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_STANDOUT);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_STANDOUT);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        y++;
    }
    wrefresh(menu_win);
}

int main()
{

    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;
    int option;

    Nhankhau Household;
    Tieuhoc Child;
    Truongthanh Adult;

    initscr();

    clear();
    noecho();
    raw();

    menu_win = newwin(HEIGHT, WIDTH, 1, 1);
    scrollok(menu_win, true);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
    mvprintw(9, 0, "----------------------------------------------------------------------------");
    refresh();
    print_menu(menu_win, highlight);

    while (1)
    {
        option = 0;
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                highlight--;
            break;

        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                highlight++;
            break;

        case 10:                        // enter
            if (highlight == n_choices) // quit
            {
                choice = highlight;
                break;
            }

            else if (highlight - 1 == 0) // nhap thong tin
            {
                Household.InputInfo();
                break;
            }

            else if (highlight - 1 == 2) // thong tin nhan khau tieu hoc
            {

                erase();
                if (Childlist.empty() == true)
                {
                    erase();
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");
                }
                else
                {

                    erase();
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");

                    int jumpX = 0;
                    int line = 10;
                    int jump = 0;

                    for (int i = 0; i < Childlist.size(); i++)
                    {

                        mvprintw(line + 0, jumpX, "Ten: %s", Childlist[i].Name);
                        mvprintw(line + 1, jumpX, "Ngay thang nam sinh: %d / %d / %d", Childlist[i].ngaysinh.ngay, Childlist[i].ngaysinh.thang, Childlist[i].ngaysinh.nam);
                        mvprintw(line + 2, jumpX, "MSCD: %d", Childlist[i].PersonalCode);
                        mvprintw(line + 3, jumpX, "Gioi tinh: %s", Childlist[i].Gender);
                        mvprintw(line + 4, jumpX, "Dia chi: %s", Childlist[i].Addr);
                        mvprintw(line + 5, jumpX, "\n");

                        line = line + 6;

                        if ((i + 1) % 3 == 0) // moi cot 3 nhan khau duoc hien
                        {
                            line = 10;
                            jumpX = jumpX + 40;
                        }
                    }
                }
                refresh();
                break;
            }

            else if (highlight - 1 == 1) //danh sach nhan khau truong thanh
            {
                erase();
                if (Adultlist.empty() == true)
                {
                    erase();
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");
                }
                else
                {

                    erase();
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");

                    int jumpX = 0;
                    int line = 10;
                    int jump = 0;

                    for (int i = 0; i < Adultlist.size(); i++)
                    {

                        mvprintw(line + 0, jumpX, "Ten: %s", Adultlist[i].Name);
                        mvprintw(line + 1, jumpX, "Ngay thang nam sinh: %d / %d / %d", Adultlist[i].ngaysinh.ngay, Adultlist[i].ngaysinh.thang, Adultlist[i].ngaysinh.nam);
                        mvprintw(line + 2, jumpX, "MSCD: %d", Adultlist[i].PersonalCode);
                        mvprintw(line + 3, jumpX, "Gioi tinh: %s", Adultlist[i].Gender);
                        mvprintw(line + 4, jumpX, "Tinh trang suc khoe: %s", Adultlist[i].Condition);
                        mvprintw(line + 5, jumpX, "Dia chi: %s", Adultlist[i].Addr);
                        mvprintw(line + 6, jumpX, "\n");

                        line = line + 7;

                        if ((i + 1) % 3 == 0) // moi cot 3 nhan khau duoc hien
                        {
                            line = 10;
                            jumpX = jumpX + 40;
                        }
                    }
                }
                refresh();
                break;
            }

            else if (highlight - 1 == 3) // danh sach nhap ngu
            {
                erase();
                if (military_list.empty() == true)
                {
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");
                }
                else
                {
                    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                    mvprintw(9, 0, "----------------------------------------------------------------------------");

                    int jumpX = 0;
                    int line = 10;
                    int count = 0;

                    for (int i = 0; i < military_list.size(); i++)
                    {
                        mvprintw(line + 0, jumpX, "Ten: %s", military_list[i].Name);
                        mvprintw(line + 1, jumpX, "Ngay thang nam sinh: %d / %d / %d", military_list[i].ngaysinh.ngay, military_list[i].ngaysinh.thang, military_list[i].ngaysinh.nam);
                        mvprintw(line + 2, jumpX, "MSCD: %d", military_list[i].PersonalCode);
                        mvprintw(line + 3, jumpX, "Gioi tinh: %s", military_list[i].Gender);
                        mvprintw(line + 4, jumpX, "Tinh trang suc khoe: %s", military_list[i].Condition);
                        mvprintw(line + 5, jumpX, "Dia chi: %s", military_list[i].Addr);
                        if (military_list[i].call_state == false)
                        {
                            endwin();
                            military_list[i].call_state == true;
                            refresh();
                            mvprintw(line + 6, jumpX, "Den tuoi di quan su");
                        }
                        else if (military_list[i].call_state == true)
                        {
                            mvprintw(line + 6, jumpX, "Dang di quan su");
                        }

                        mvprintw(line + 7, jumpX, "\n");

                        line = line + 8;

                        if ((i + 1) % 3 == 0) // moi cot 3 nhan khau duoc hien
                        {
                            line = 10;
                            jumpX = jumpX + 40;
                        }
                    }
                }
                refresh();
                break;
            }

            else if (highlight - 1 == 4) // danh sach den tuoi di hoc
            {
                erase();

                mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice, Press the exit button or ESC to quit");
                mvprintw(9, 0, "----------------------------------------------------------------------------");

                int jumpX = 0;
                int line = 10;

                for (int i = 0; i < Primary_list.size(); i++)
                {

                    mvprintw(line + 0, jumpX, "Ten: %s", Primary_list[i].Name);
                    mvprintw(line + 1, jumpX, "Ngay thang nam sinh: %d / %d / %d", Primary_list[i].ngaysinh.ngay, Primary_list[i].ngaysinh.thang, Primary_list[i].ngaysinh.nam);
                    mvprintw(line + 2, jumpX, "MSCD: %d", Primary_list[i].PersonalCode);
                    mvprintw(line + 3, jumpX, "Gioi tinh: %s", Primary_list[i].Gender);
                    mvprintw(line + 4, jumpX, "Dia chi: %s", Primary_list[i].Addr);
                    mvprintw(line + 5, jumpX, "\n");

                    line = line + 6;

                    if ((i + 1) % 3 == 0) // moi cot 3 nhan khau duoc hien
                    {
                        line = 10;
                        jumpX = jumpX + 40;
                    }
                }
                refresh();
                break;
            }

            break;

        case 27: // esc == thoat
            choice = highlight;
            break;

        default:
            mvprintw(31, 0, "Charcter pressed is = %3d, it can be printed as '%c'", c, c);
            refresh();
            break;
        }
        print_menu(menu_win, highlight);
        if (choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    endwin();
    return 0;
}
