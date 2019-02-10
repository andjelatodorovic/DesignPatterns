#include <queue>
#include <iostream>

using namespace std;

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout << q.size() << "," << q.empty() << endl;
    cout << q.front() << "," << q.back() << endl;
    q.pop();
    cout << q.front() << endl;

    priority_queue<int> pq;
    pq.push(4);
    pq.push(7);
    pq.push(1);
    pq.push(3);
    pq.push(8);
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    pq.pop();
}
