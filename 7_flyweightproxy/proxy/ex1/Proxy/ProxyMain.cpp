#include "Proxy.h"
#include "RealSubject.h"

int main() {
    Subject* realSubject = new RealSubject();
    Subject* proxy = new Proxy();
    cout << "Calling method Request through the proxy: " << endl;
    proxy->Request();
    cout << "Calling method Request through the real subject: " << endl;
    realSubject->Request();

    delete proxy;
    delete realSubject;

    return 0;
}
