#include <bits/stdc++.h>
using namespace std;
struct QNode {
	int data;
	QNode* next;
	QNode(int d)
	{
		data = d;
		next = NULL;
	}
};
struct Queue {
	QNode *front, *rear;
	Queue() { front = rear = NULL; }

	void enQueue(int x)
	{
		QNode* temp = new QNode(x);
		if (rear == NULL) {
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}
	void deQueue()
	{
		if (front == NULL)
			return;
		QNode* temp = front;
		front = front->next;
		if (front == NULL)
			rear = NULL;

		delete (temp);
	}
};
int main()
{

	Queue q;
	q.enQueue(101);
	q.enQueue(202);
	q.deQueue();
	q.deQueue();
	q.enQueue(303);
	q.enQueue(404);
	q.enQueue(505);
	q.deQueue();
	cout << "Queue Front : " << ((q.front != NULL) ? (q.front)->data : -1)<< endl;
	cout << "Queue Rear : " << ((q.rear != NULL) ? (q.rear)->data : -1);
}
