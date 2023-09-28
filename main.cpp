#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

void work(std::atomic<int>& a) {
  for(int i = 0; i < 100000; ++i) {
    a++;
  }
}

void singleThread() {
  // Create a single atomic integer
  std::atomic<int> a;
  a = 0;

  // Call the work function 4 times, passing 'a' as a reference
  work(a);
  work(a);
  work(a);
  work(a);
  std::cout << "Address of atomic<int> a - " << &a << '\n';
  std::cout << "Address of atomic<int> a - " << a << '\n';
}

void directSharing() {
  // Create a single atomic integer
  std::atomic<int> a;
  a = 0;

  // Four threads all sharing one atomic<int>
  std::thread t1([&]() {work(a);});
  std::thread t2([&]() {work(a);});
  std::thread t3([&]() {work(a);});
  std::thread t4([&]() {work(a);});

  // Join the 4 threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  std::cout << "Address of atomic<int> a - " << &a << '\n';
  std::cout << "Address of atomic<int> a - " << a << '\n';
}

void falseSharing() {
  // Create a single atomic integer
  std::atomic<int> a;
  a = 0;
  std::atomic<int> b;
  b = 0;
  std::atomic<int> c;
  c = 0;
  std::atomic<int> d;
  d = 0;

  // Four threads each with their own atomic<int>
  std::thread t1([&]() {work(a);});
  std::thread t2([&]() {work(b);});
  std::thread t3([&]() {work(c);});
  std::thread t4([&]() {work(d);});

  // Join the 4 threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  std::cout << "Address of atomic<int> a - " << &a << '\n';
  std::cout << "Address of atomic<int> a - " << a << '\n';
  std::cout << "Address of atomic<int> b - " << &b << '\n';
  std::cout << "Address of atomic<int> b - " << b << '\n';
  std::cout << "Address of atomic<int> c - " << &c << '\n';
  std::cout << "Address of atomic<int> c - " << c << '\n';
  std::cout << "Address of atomic<int> d - " << &d << '\n';
  std::cout << "Address of atomic<int> d - " << d << '\n';
}

struct alignas(64) AlignedType {
  AlignedType() { val = 0; }
  std::atomic<int> val;
};

void noSharing() {
  AlignedType a{};
  AlignedType b{};
  AlignedType c{};
  AlignedType d{};
  AlignedType e{};
 
  // Launch the four threads now using our aligned data
  std::thread t1([&]() { work(a.val); });
  std::thread t2([&]() { work(b.val); });
  std::thread t3([&]() { work(c.val); });
  std::thread t4([&]() { work(d.val); });
  std::thread t5([&]() { work(e.val); });
 
  // Join the threads
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  std::cout << "Address of atomic<int> a - " << &a << '\n';
  std::cout << "Address of atomic<int> a - " << a.val << '\n';
  std::cout << "Address of atomic<int> b - " << &b << '\n';
  std::cout << "Address of atomic<int> b - " << b.val << '\n';
  std::cout << "Address of atomic<int> c - " << &c << '\n';
  std::cout << "Address of atomic<int> c - " << c.val << '\n';
  std::cout << "Address of atomic<int> d - " << &d << '\n';
  std::cout << "Address of atomic<int> d - " << d.val << '\n';
  std::cout << "Address of atomic<int> d - " << &e << '\n';
  std::cout << "Address of atomic<int> d - " << e.val << '\n';
}

void cores_calculation() {
    unsigned int numCores = std::thread::hardware_concurrency();
    std::cout << "Número de núcleos de CPU: " << numCores << std::endl;
}

int main() {
  //singleThread();  // Llama a la función para ejecutar el trabajo en un solo hilo
  //directSharing();
  falseSharing();
  //noSharing();
  cores_calculation();
  return 0;
}