#include <iostream>
#include <functional>
#include <thread>
#include <barrier>

int p = 1, q = 1, r = 0;
int pp, p1, p2, qq, r1, q1, rr, pr;

std::barrier tact1(4);
std::barrier tact2(3);


void foo1() {
    
    //std::cout << "THREAD 1 START \n";
    
    pp = p * p;
    
    tact1.arrive_and_wait();

    p1 = pp + qq;

    tact2.arrive_and_wait();

    p2 = p1 + q1;
}

void foo2() {
    //std::cout << "THREAD 2 START \n";

    qq = q * q;
    
    tact1.arrive_and_wait();
    
    r1 = qq + rr;

    tact2.arrive_and_wait();
}

void foo3() {
    
    //std::cout << "THREAD 3 START \n";

    rr = r * r;

    tact1.arrive_and_wait();
    
    q1 = q + pr;

    tact2.arrive_and_wait();
}

void foo4() {

    //std::cout << "THREAD 4 START \n";

    pr = p + r;

    tact1.arrive_and_wait();
}

int fibon_par(int n) {

    p = 1;
    q = 1;
    r = 0;

    int N = n / 2;
    int par = n % 2;

    while (N > 0) {

        std::thread th1(foo1);
        std::thread th2(foo2);
        std::thread th3(foo3);
        std::thread th4(foo4);

        th1.join();
        th2.join();
        th3.join();
        th4.join();

        if (N % 2 == 1) { p = p2; q = p1; r = q1; }
        else { p = p1; q = q1; r = r1; }
        N /= 2;
    }
    if (par == 0) return r;
    else return q;

}


int Fibc(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return Fibc(n - 2) + Fibc(n - 1);
}


int main()
{

    std::cout << "========\t"<<"MAIN START\t"<< "========\n";    

    int const n = 20;
    for (int i = 1; i < n; i++) {

       
        if (Fibc(i) != fibon_par(i)) std::cout << "  !";
        std::cout << "\t" << i << ": " << Fibc(i) << "  " << fibon_par(i) << std::endl;
    }

    std::cout << "\n========\t" << "MAIN FINISH\t" << "========";
    return 0;    
   
}
