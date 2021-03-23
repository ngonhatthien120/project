/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2021
    * Author: Nguyen Thanh Nhan
    * Date: 08.02.2021
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef firstFight_h
#define firstFight_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

void check(int& X, int& Y) // kiem tra yeu cau bai toan
{
    if (X > 1000) X = 1000;
    if (X < 0) X = 0;
    if (Y > 1000) Y = 1000;
    if (Y < 0) Y = 0;
}
void buy(int& x, int& HP, int& M) // mua mu giap
{
    switch (x)
    {
    case 1:
        if (M >= 190) {
            HP += 5;
            M -= 190;
            break;
        }
        else break;
    case 2:
        if (M >= 195) {
            HP += 7;
            M -= 195;
            break;
        }
        else break;
    case 3:
        if (M >= 200) {
            HP += 9;
            M -= 200;
            break;
        }
        else break;
    case 4:
        if (M >= 205) {
            HP += 11;
            M -= 205;
            break;
        }
        else break;
    }
}
int fight(int& HP1, int& HP2, const int& ID1, const int& ID2)  // Hinh thuc chien dau 
{
    if (ID1 == 1 && ID2 == 2) return 0;
    else if (ID1 == 1 && ID2 != 2) {
        HP2 = 0; return 1;
    }
    else if (ID1 != 1 && ID2 == 2) {
        HP1 = 0; return -1;
    }
    else {
        int n = ceil((2.f * HP1 * HP2) / (HP1 + HP2));
        int HP = HP1;
        HP1 = HP1 - abs(HP2 - n);
        HP2 = HP2 - abs(HP - n);
        if (HP1 < 0) HP1 = 0;
        if (HP2 < 0) HP2 = 0;
        if (HP1 > HP2) return 1;
        else if (HP1 < HP2) return -1;
        else return 0;
    }
}
bool nguyento(int n) // kiem tra so nguyen to
{
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return false;
    return true;
}
int getReady(int& HP, const int& ID, int& M, const int& E1) {
    //Complete this function to gain point on task 1
    check(HP, M);
    if (E1 >= 100 && E1 <= 199) {         // TH1
        if (ID == 1) HP += 75;   // Mục 4.1 upload( loi vua mua do hỏi bởi Kha Sang
        else if (ID != 2) {
            int h = (E1 - 100) % 64;
            int J = HP % 100;
            if (J > h) {
                if (HP >= 500 && M % 2 != 0 && M >= 300) { HP += 50; M -= 300; }
                else if (M % 2 == 0 && M >= 200) { HP += 25; M -= 200; }
            }
        }
        check(HP, M);
        return HP + M;
    }
    else if (E1 >= 200 && E1 <= 299) {    // TH2 (kiem tra lai)
        int  x = E1 % 4 + 1;
        if (ID == 1 || ID == 2) buy(x, HP, M);
        else if ((M % 2 != 0 && x % 2 != 0) || (M % 2 == 0 && x % 2 == 0)) { 
            buy(x, HP, M);
        }
        check(HP, M);
        return HP + M;
    }
    else if (E1 >= 300 && E1 <= 399) {    // TH3
        if (HP >= 600) {
            int a = 1;
            int e = E1 % 10;
            if (nguyento(e)) a = 2 * e;
            int i = HP % 10;
            if (nguyento(i) && M >= 500) {
                if (ID == 1) {
                    HP += 200;
                    M -= 500;
                }
                else {
                    HP = ceil((1 + 2 * a * 0.01f) * HP);
                    M -= 500;
                }
            }
            else if (!nguyento(i) && M >= 300) {         // luu y 
                HP = ceil(HP * (1 + a * 0.01f));
                M -= 300;
            }
        }

        check(HP, M);
        return HP + M;
    }
    else if (E1 >= 400 && E1 <= 499) {    // TH4
        if (E1 % 5 == 0) HP = ceil(HP * 0.9f);
        check(HP, M);
        return HP + M;
    }
    else if (E1 == 500) {                 // TH5
        HP = ceil(HP * 0.75f);
        M = ceil(M * 0.75f);
        return HP + M;
    }
    else return -999;
}

int firstBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E2) {
    //Complete this function to gain point on task 2
    bool dem = false;
    if (E2 >= 100 && E2 <= 199) { //TH1
        HP1 = ceil(HP1 * 1.1f);
        HP2 = ceil(HP2 * 1.3f);
        check(HP1, HP2);
        dem = true;
    }
    else if (E2 >= 200 && E2 <= 299) { //TH2
        HP1 = ceil(HP1 * 1.7f);
        HP2 = ceil(HP2 * 1.2f);
        check(HP1, HP2);
        dem = true;
    }
    else if (E2 >= 300 && E2 <= 399) { // TH3
        if (HP1 < 350) HP1 += 30;
        else HP1 += E2 % 100;
        check(HP1, HP2);
        dem = true;
    }
    else if (E2 >= 400 && E2 <= 499) { //TH4
        HP1 = ceil(HP1 * 1.3f);
        HP2 = ceil(HP2 * 0.8f);
        HP1 = ceil(HP1 * 0.5f);
        check(HP1, HP2);
        dem = true;
    }
    else return -999;
    if (dem) {                        //TH5
        int res = fight(HP1, HP2, ID1, ID2);
        HP1 = ceil(HP1 * 0.8f);
        return res;
    }
}

int secondBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E3) {
    //Complete this function to gain point on task 3
    if (E3 < 100 || E3 > 299) return -999; 
    HP1 = ceil(HP1 * 1.4f);
    HP2 = ceil(HP2 * 1.6f);
    check(HP1, HP2);
    if (ID1 == 1) HP1 *= 2;
    check(HP1, HP2);
    if (E3 >= 100 && E3 <= 199) { //TH1 Le Trung Duc, Nguyen Hoang Minh Tri
        int so = HP1;
        if (ID2 != 2) HP2 = ceil(HP2 * 0.95f);
        int res = fight(HP1, HP2, ID1, ID2); 
        if (res == -1) {
            if (ID2 != 2) HP1 = so;
        }
        return res;
    }
    else if (E3 >= 200 && E3 <= 299) { //TH2
        if (ID2 != 2) HP2 = ceil(HP2 * 0.95f);
        return 0;
    }
}

int finalBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E4) {
    //Complete this function to gain point on task 4
    if (E4 >= 100 && E4 <= 199) { //TH1
        if (ID2 == 2) HP2 = ceil(HP2 * 0.3f);
        else HP2 = ceil(HP2 * 0.1f);
        return 0;
    }
    else if (E4 >= 200 && E4 <= 299) { //TH2
        HP2 = 0;
        return 1;
    }
    else return -999;
}
////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* firstFight_h */
