#include <iostream>
using namespace std;

struct node
{
	int data;
	node* next;
};
node* merge(node* head1, node* head2)
{
	node* p1=head1; // working ptr
	node* p2=head2;
	node* temp=nullptr;
	if (p1->data < p2->data)//base: first element in head1 is smaller in head2, replace head 2
	{
		head1=p1->next;
		p1->next=p2;
		head2=p1;
	}

	for(p1=head1;p1!=nullptr;)
	{	
        for(p2=head2;p2->next!=nullptr&&(p2->next->data <= p1->data);p2=p2->next);
        if(p2->next==nullptr)
        {    
            p2->next=p1;
            break;
        }
        else
        {
            temp=p2->next;
            p2->next=p1;
            head1=head1->next;
            p1->next=temp;
            p1=head1;
        }
        
	}
    return head2;
}
int main()
{
    node head1;
    head1.data=1;
    head1.next=new node;
    head1.next->data=3;
    head1.next->next=new node;
    head1.next->next->data=5;
    head1.next->next->next=nullptr;
    node head2;
    head2.data=0;
    head2.next=new node;
    head2.next->data=4;
    head2.next->next=nullptr;
    node* new_head;
    new_head=merge(&head1, &head2);
    for(;new_head->next!=nullptr;new_head=new_head->next)
    {
        cout<<new_head->data<<"\t";
    }
    cout<<new_head->data<<endl;
    return 0;
}