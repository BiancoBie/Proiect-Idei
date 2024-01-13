#include <iostream>
#include <fstream>
#include <winbgim.h>
#include <windows.h>
#include <string.h>

using namespace std;

#define MAX 100
#define latime 54

#define SUS 72
#define JOS 80
#define STG 75
#define DRP 77
#define ESC 27
#define SPC 32
#define TAB 9
#define BKS 8
#define SPACE 32
#define BUTTON_COUNT 9


int imario, jmario, ipostaza;
char tasta;
string directie;
//
bool inJump = false;
int jumpHeight = 0;
//
bool isGameOver = false;
bool existaInamic=false;
int ienemy, jenemy;
int maxhearts = 5;
int lives=3;
string enemyDirection = "dreapta";
void afiseazaInamic(int i, int j)
{
    if (enemyDirection == "dreapta")
        readimagefile("enemy1.gif", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
    else if (enemyDirection == "stanga")
            readimagefile("enemy2.gif", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
}
bool isInvincible = false;
//

int scor, nrstelute;

int nrLinii, nrColoane, i, j;
char harta[MAX][MAX];
char car;
int incepeX1, incepeY1, incepeX2, incepeY2;
int inchideX1, inchideY1, inchideX2, inchideY2;
int nivelX1, nivelY1, nivelX2, nivelY2;

ifstream fisier("harta.txt");
ofstream gameLog("gameLog.txt");

void SetVolume(DWORD volume) {
    if (waveOutSetVolume(NULL, volume) != MMSYSERR_NOERROR) {
    }
}

void incepejoc(int i);
void afiseazaScor();
void incarcaHarta1();
void incarcaHarta2();
void incarcaHarta3();
void incarcaHarta4();
void incarcaHarta5();
void incarcaHarta6();
void incarcaHarta7();
void incarcaHarta8();
void incarcaHarta9();

void Exit_Transition()
{
    PlaySound("gameover.wav", NULL, SND_SYNC);
    cleardevice();
    for (int i = 0; i <= 600; i++)
    {
        circle(1920 / 2, 800 / 2 + 100, i);
        circle(1920 / 2, 800 / 2 + 100, 1200 - i);
    }
}

void afiseazaMario()
{
    int y = imario * latime, x = jmario * latime;

    switch (ipostaza) {
    case -10: readimagefile("mario_spate_1.gif", x, y, x + latime, y + latime); break;
    case 10: readimagefile("mario_spate_2.gif", x, y, x + latime, y + latime); break;
    case 1:
        readimagefile("mario1.gif", x, y, x + latime, y + latime); break;
    case 2:
        readimagefile("mario4.gif", x, y, x + latime, y + latime); break;
    case -1:
        readimagefile("mario2.gif", x, y, x + latime, y + latime); break;
    case -2:
        readimagefile("mario5.gif", x, y, x + latime, y + latime); break;
    }
}

void afiseazaPoza(char c, int i, int j)
{
    switch (c)
    {
    case '@':
        readimagefile("iarba.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case '#':
        readimagefile("scara.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case '*':
        readimagefile("stea.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case '.':
        readimagefile("cer.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case ',':
        readimagefile("deal1.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case '!':
        readimagefile("deal2.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case '?':
        readimagefile("norisor.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
    case 'E':  // afiseaza inamicul
        afiseazaInamic(i, j);
        break;
    case 'H': //afiseaza heart
        {
        readimagefile("cer.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        readimagefile("heart.gif", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
        }
    case 'I': //afiseaza powerup
        {
        readimagefile("cer.jpg", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        readimagefile("invincibility.gif", latime * j, latime * i, latime * (j + 1), latime * (i + 1));
        break;
        }
    default:
        // cazul in care caracterul nu este recunoscut
        break;
    }
}

void showMenu(int &incepeX1, int &incepeY1, int &incepeX2, int &incepeY2,
              int &nivelX1, int &nivelY1, int &nivelX2, int &nivelY2,
              int &inchideX1, int &inchideY1, int &inchideX2, int &inchideY2) {
    cleardevice();
    setbkcolor(LIGHTGREEN);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = 1820;
    int windowHeight = 900;

    int buttonWidth = 700;
    int buttonHeight =50;

    incepeX1 = windowWidth / 2.5 - 23 * strlen("DEMO") / 2;
    incepeY1 = 270;
    incepeX2 = incepeX1 + 23 * strlen("DEMO");
    incepeY2 = incepeY1 + 30;

    int border_color = WHITE;
    floodfill(nivelX1,nivelY1,border_color);

    rectangle(incepeX1, incepeY1, incepeX2, incepeY2);
    outtextxy(incepeX1 + 5, incepeY1 + 5, "DEMO");

    nivelX1 = windowWidth / 2.5 - 21.5 * strlen("Selecteaza Nivelul") / 2;
    nivelY1 = incepeY1 + 40;
    nivelX2 = nivelX1 + 21.5 * strlen("Selecteaza Nivelul");
    nivelY2 = incepeY2 + 40;

    rectangle(nivelX1, nivelY1, nivelX2, nivelY2);
    outtextxy(nivelX1 + 5, nivelY1 + 5, "Selecteaza Nivelul");

    inchideX1 = windowWidth / 2.5 - 22.5 * strlen("Inchide") / 2;
    inchideY1 = nivelY1 + 40;
    inchideX2 = inchideX1 + 22.5 * strlen("Inchide");
    inchideY2 = inchideY1 + 30;

    rectangle(inchideX1, inchideY1, inchideX2, inchideY2);
    outtextxy(inchideX1 + 5, inchideY1 + 5, "Inchide");
}

bool isInsideButton(int x, int y, int left, int top, int right, int bottom) {
    return (x >= left && x <= right && y >= top && y <= bottom);
}

void showEndGameMenu(int incepeX1, int incepeY1, int incepeX2, int incepeY2,
                        int inchideX1, int inchideY1, int inchideX2, int inchideY2) {
    cleardevice();
    setbkcolor(LIGHTGREEN);
    setcolor(BLUE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int windowWidth = 1820;
    int windowHeight = 900;

    int buttonWidth = 700;
    int buttonHeight =50;

    incepeX1 = windowWidth / 2.5 - 23 * strlen("Reincepe") / 2;
    incepeY1 = 270;
    incepeX2 = incepeX1 + 23 * strlen("Reincepe");
    incepeY2 = incepeY1 + 30;

     int border_color = WHITE;
    floodfill(nivelX1,nivelY1,border_color);

    rectangle(incepeX1, incepeY1, incepeX2, incepeY2);
    outtextxy(incepeX1 + 7, incepeY1 + 7, "Reincepe");

    inchideX1 = windowWidth / 2.5 - 22.5 * strlen("Inchide") / 2;
    inchideY1 = nivelY1 + 40;
    inchideX2 = inchideX1 + 22.5 * strlen("Inchide");
    inchideY2 = inchideY1 + 30;

    rectangle(inchideX1, inchideY1, inchideX2, inchideY2);
    outtextxy(inchideX1 + 5, inchideY1 + 5, "Inchide");
}

void stergeMario()
{
    afiseazaPoza(harta[imario][jmario], imario, jmario);
}

void urmatoareaIpostaza()
{
    stergeMario();

    if (directie == "dreapta")
    {
        if (abs(ipostaza) == 10) ipostaza = 1;
        else if (abs(ipostaza)==2) ipostaza = 1;
        else ipostaza = -1 * ipostaza;
        if (jmario < nrColoane - 1 && harta[imario][jmario + 1] != '@')
            jmario++;
    }

        else if (directie == "stanga")
        {
            if (abs(ipostaza) == 10) ipostaza = 2;
            else if (abs(ipostaza)==1) ipostaza = 2;
            else ipostaza = -1 * ipostaza;
            if (jmario > 0 && harta[imario][jmario - 1] != '@')
                jmario--;
        }
         else if (directie == "sus")
            {
                if (abs(ipostaza) == 10) ipostaza = -1 * ipostaza;
                else ipostaza = 10;
                if (harta[imario - 1][jmario] == '#') imario--;
            }
             else if (directie == "jos")
                    {
                        if (abs(ipostaza) == 10) ipostaza = -1 * ipostaza;
                        else ipostaza = -10;
                        if (harta[imario + 1][jmario] == '#') imario++;
                    }
   // să cadă dacă Mario nu sare și nu există pământ sau scări sub el
    if (!inJump && harta[imario + 1][jmario] != '@' && harta[imario + 1][jmario] != '#') {
        inJump = true;
        jumpHeight = 2;
    }



    //// Sari logica ////
    if (inJump) {
        if (jumpHeight < 2 && harta[imario - 1][jmario] != '@') {
            jumpHeight++;
            imario--;
        } else {
            inJump = false;
            jumpHeight = 0;
            // Repetăm ​​logica căderii la pământ
            while (imario < nrLinii - 1 && harta[imario + 1][jmario] != '@') {
                imario++;
            }
        }
    }





    if (harta[imario][jmario] == '*') {
        scor++;
        harta[imario][jmario] = '.';
        afiseazaScor();

    }
    else if (harta[imario][jmario] == 'H') {
        if(lives<maxhearts)
            lives++;
        harta[imario][jmario] = '.';
        afiseazaScor();
    }
    else if (harta[imario][jmario] == 'I'){
        // activeaza invincibilitatea
        isInvincible = true;
        harta[imario][jmario] = '.';  // sterge powerup-ul de pe harta
    }
    afiseazaMario();

}

struct Button {
    int left, top, right, bottom;
    const char* label;
    void (*action)(); // pointerul functiei pentru apasarea butonului
};

void button1Action();
void button2Action();
void button3Action();
void button4Action();
void button5Action();
void button6Action();
void button7Action();
void button8Action();
void button9Action();

Button buttons[BUTTON_COUNT] = {
    {575, 200, 675, 275, "1", button1Action},
    {725, 200, 825, 275, "2", button2Action},
    {875, 200, 975, 275, "3", button3Action},
    {575, 300, 675, 375, "4", button4Action},
    {725, 300, 825, 375, "5", button5Action},
    {875, 300, 975, 375, "6", button6Action},
    {575, 400, 675, 475, "7", button7Action},
    {725, 400, 825, 475, "8", button8Action},
    {875, 400, 975, 475, "9", button9Action}
};

void drawButton(const Button& button) {
    rectangle(button.left, button.top, button.right, button.bottom);
    outtextxy(button.left + 25, button.top + 25, const_cast<char*>(button.label));
}

void drawMenu() {
    cleardevice();// sterge ecranul
    // deseneaza butoanele
    for (int i = 0; i < BUTTON_COUNT; ++i) {
        drawButton(buttons[i]);
    }
}

int isMouseClickInsideButton(int x, int y, const Button& button) {
    return (x >= button.left && x <= button.right && y >= button.top && y <= button.bottom);
}

void handleButtonClick(int x, int y) {
    for (int i = 0; i < BUTTON_COUNT; ++i) {
        if (isMouseClickInsideButton(x, y, buttons[i])) {
            buttons[i].action(); // apeleaza functia pentru fiecare buton
            break;
        }
    }
}

// functiile pentru fiecare buton
void button1Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=1;
    incepejoc(i);
}

void button2Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=2;
    incepejoc(i);
}

void button3Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=3;
    incepejoc(i);
}

void button4Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=4;
    incepejoc(i);
}

void button5Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=5;
    incepejoc(i);
}

void button6Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=6;
    incepejoc(i);
}

void button7Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=7;
    incepejoc(i);
}

void button8Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=8;
    incepejoc(i);
}

void button9Action() {
    PlaySound("buton.wav", NULL, SND_ASYNC);
    cleardevice();
    int i=9;
    incepejoc(i);
}

void showLevelMenu() {

        drawMenu();
        int clickX, clickY;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
            delay(100);
        }
        getmouseclick(WM_LBUTTONDOWN, clickX, clickY);

        handleButtonClick(clickX, clickY);

        clearmouseclick(WM_LBUTTONDOWN);

}

void incarcaHarta()
{
    ifstream fisier("harta.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta1()
{
    MessageBoxW(NULL, L"Urmeaza procesul de incarcare al hartii. Va rugam asteptati...", L"Incarcare", MB_OK | MB_ICONINFORMATION);
    ifstream fisier("harta1.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
    MessageBoxW(NULL, L"Harta s-a incarcat cu succes! Distractie placuta!", L"Incarcare finalizata", MB_OK | MB_ICONINFORMATION);
}

void incarcaHarta2()
{
    ifstream fisier("harta2.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.';}
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta3()
{
    ifstream fisier("harta3.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta4()
{
    ifstream fisier("harta4.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta5()
{
    ifstream fisier("harta5.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta6()
{
    ifstream fisier("harta6.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta7()
{
    ifstream fisier("harta7.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta8()
{
    ifstream fisier("harta8.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}


void incarcaHarta9()
{
    ifstream fisier("harta9.txt");
    fisier >> nrLinii >> nrColoane;
    //initwindow(latime * nrColoane * 100, latime * nrLinii, "Mario pe scari");
    setbkcolor(WHITE); cleardevice();
    nrstelute = 0;
    for (i = 0; i < nrLinii; i++)
    {
        for (j = 0; j < nrColoane; j++)
        {
            fisier >> car;
            if (car == '*')
                nrstelute++;
            if (car == 'M') { imario = i; jmario = j; car = '.'; }
            if (car == 'E') { ienemy = i; jenemy = j; car = '.'; existaInamic=true; }
            harta[i][j] = car;
            afiseazaPoza(harta[i][j], i, j);
        }
    }
    fisier.close();
    scor = 0;
}

void checkCollisionWithEnemy()
{
    // verifica daca Mario si inamicul sunt pe aceeasi pozitie
    if (imario == ienemy && jmario == jenemy)
    {
        if (!isInvincible)
            lives--;
         afiseazaScor();
    }
}
//
void updateInamic()
{
    // sterge ultima pozitie
    afiseazaPoza(harta[ienemy][jenemy], ienemy, jenemy);

    // verifica daca se afla la margine sau langa un bloc
    if (jenemy == 0 || jenemy == nrColoane - 1||harta[ienemy][jenemy + 1] == '@'||harta[ienemy][jenemy - 1] == '@')
        // schimba directia
        enemyDirection = (enemyDirection == "dreapta") ? "stanga" : "dreapta";
    else if(harta[ienemy + 1][jenemy + 1] == '.'||harta[ienemy + 1][jenemy - 1] == '.')
            enemyDirection = (enemyDirection == "dreapta") ? "stanga" : "dreapta";

    // modifica pozitia
    if (enemyDirection == "dreapta" && jenemy < nrColoane - 1)
            jenemy++;
     else if (enemyDirection == "stanga" && jenemy > 0)
        // se misca la stanga
        jenemy--;


    //verifica daca Mario si inamicul sunt la aceeasi pozitie
    checkCollisionWithEnemy();
    if (lives <= 0)
        isGameOver = true;

    // afiseazaInamic - pozitia urmatoarea a inamicului
    afiseazaInamic(ienemy, jenemy);
    afiseazaMario();
}
//
//
bool canJump() {
    return harta[imario + 1][jmario] == '@' && harta[imario - 1][jmario] != '@';
}

void jump() {
    if (canJump() && !inJump) {
        inJump = true;
        jumpHeight = 0;
    }
}
//

void incepejoc(int i)
{
    bool running=true;
     if (running) {
        cleardevice();
        switch (i){
    case 1:
        incarcaHarta1();
        break;
    case 2:
        incarcaHarta2();
        break;
    case 3:
        incarcaHarta3();
        break;
    case 4:
        incarcaHarta4();
        break;
    case 5:
        incarcaHarta5();
        break;
    case 6:
        incarcaHarta6();
        break;
    case 7:
        incarcaHarta7();
        break;
    case 8:
        incarcaHarta8();
        break;
    case 9:
        incarcaHarta9();
        break;
        }
        ipostaza = 1;
        afiseazaMario();
        afiseazaScor();//afiseaza scorul de inceput
        if(existaInamic)
            afiseazaInamic(ienemy,jenemy);
        PlaySound("Intro.wav", NULL, SND_ASYNC);
        directie = "dreapta";
        do
        {
            if(existaInamic)
                updateInamic();
        if (kbhit())
        {
            tasta = getch(); if (tasta == 0) tasta = getch();
            if (tasta == STG && jmario > 0) directie = "stanga";
            if (tasta == DRP && jmario < nrColoane - 1) directie = "dreapta";
            if (tasta == SUS && harta[imario - 1][jmario] == '#') directie = "sus";
            if (tasta == JOS && harta[imario + 1][jmario] == '#') directie = "jos";
            if (tasta == SPACE && !inJump) jump();
            urmatoareaIpostaza();
            directie = "none";//directia trebuie initializata cu none altfe cand sari, sare intr=o parte
        } else if (inJump)
            urmatoareaIpostaza();

            delay(30);
            if(isGameOver==true)
                break;//    de adaugat meniu atunci cand pierzi
        } while (tasta != ESC);
     }
}

void afiseazaScor()
{
    int i;
    for (i = 1; i <= scor; i++)
    {
        PlaySound("stea.wav", NULL, SND_ASYNC);
        readimagefile("stea.jpg", 30 * i, 0, 30 * i + 30, 30);
    }
    // afiseaza inimile pe ecran in functie de cate mai ai
    for (int i = 1; i <= maxhearts; i++)
        if (i <= lives)
        {
            readimagefile("cer.jpg", 30 * (i - 1), 60, 30 * i, 90);
            readimagefile("heart.gif", 30 * (i - 1), 60, 30 * i, 90);
        }
        else
            readimagefile("cer.jpg", 30 * (i - 1), 60, 30 * i, 90);
    afiseazaMario();
    if (scor < nrstelute)
    {
        for (i = 800; i <= 1200; i += 30) Beep(i, 20);
        PlaySound("Intro.wav", NULL, SND_ASYNC);
    }
    else if (scor==nrstelute)
    {
        showEndGameMenu(incepeX1, incepeY1, incepeX2, incepeY2, inchideX1, inchideY1, inchideX2, inchideY2);
        bool running=true;
        while (running) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (isInsideButton(x, y, incepeX1, incepeY1, incepeX2, incepeY2))
                {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                scor=0;
                showMenu(incepeX1, incepeY1, incepeX2, incepeY2, nivelX1, nivelY1, nivelX2, nivelY2, inchideX1, inchideY1, inchideX2, inchideY2);
        bool running = true;
        while (running) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (isInsideButton(x, y, incepeX1, incepeY1, incepeX2, incepeY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                cleardevice();
                DWORD volume = 0x40004000;
                SetVolume(0x40004000);
                incepejoc(1);
                closegraph();
                gameLog.close();
                break;
            }
            else if (isInsideButton(x, y, nivelX1, nivelY1, nivelX2, nivelY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                showLevelMenu();
                break;
            }
            else if (isInsideButton(x, y, inchideX1, inchideY1, inchideX2, inchideY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                running = false;
                Exit_Transition();
                break;
            }
        }
    }
            }
            else if (isInsideButton(x, y, inchideX1, inchideY1, inchideX2, inchideY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                running = false;
                Exit_Transition();
                break;
            }
        }
    }
  }
}

int main()
{

    initwindow(1920, 800, "Mario");
    setbkcolor(LIGHTBLUE);
    showMenu(incepeX1, incepeY1, incepeX2, incepeY2, nivelX1, nivelY1, nivelX2, nivelY2, inchideX1, inchideY1, inchideX2, inchideY2);

    bool running = true;
    while (running) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (isInsideButton(x, y, incepeX1, incepeY1, incepeX2, incepeY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                cleardevice();
                DWORD volume = 0x40004000;
                SetVolume(0x40004000);
                incepejoc(1);
                closegraph();
                gameLog.close();
                break;
            }
            else if (isInsideButton(x, y, nivelX1, nivelY1, nivelX2, nivelY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                showLevelMenu();
                break;
            }
            else if (isInsideButton(x, y, inchideX1, inchideY1, inchideX2, inchideY2)) {
                PlaySound("buton.wav", NULL, SND_ASYNC);
                running = false;
                Exit_Transition();
                break;
            }
        }
    }
}
