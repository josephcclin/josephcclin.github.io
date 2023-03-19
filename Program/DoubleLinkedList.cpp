#include <iostream.h>
#include <conio.h>

struct node
{
	int data;
	node* llink;
	node* rlink;
};

class linklist
{
private:
	node* first; // point to the first link
public:
	linklist()
	{
		first = NULL; // We don't have the first link.
		cout << "\nConstructor is working...\n";
	} 
	void add_item(int d);
	void del_item(int d);
	void display();
	~linklist()
	{
		cout << "\n\nDestructor is working.\n\n";
	}
};

void linklist::add_item(int d)
{
	node* newadd = new node;
	newadd->data = d;
	if (first == NULL)
	{
		newadd->rlink = first;
		newadd->llink = newadd;
		first = newadd;
	}
	else
	{
		newadd->rlink = first;
		newadd->llink = newadd;
		first->llink = newadd;
		first = newadd;
	}
}

void linklist::del_item(int d)
{
	node* newdel = new node;
	newdel = first;
	while((newdel != NULL) && (newdel->data != d)) {newdel = newdel->rlink;} // seek for data "d" and move the pointers
	if(newdel == NULL) // We can't find the data "d"
		cout << "\nWe don't find out this data...\n";
	else
	{
		node* temp = new node;
		temp = newdel;
		if (newdel->rlink == NULL)
			(newdel->llink)->rlink = newdel->rlink;
		else
		{
			(newdel->llink)->rlink = newdel->rlink;
			(newdel->rlink)->llink = newdel->llink;
		}
		delete temp;
	}
}

void linklist::display()
{
	node* current = first; // Let pointer be the first pointer
	while(current != NULL)
	{
		cout << endl << current->data;
		current = current->rlink;
	}
	cout << endl;
}

int main()
{
	linklist list;
	int data;
	char choice;
	// Addition...
	do
		{
			cout << "\nInput the data: ";
			cin >> data;
			list.add_item(data);
			cout << "Will you input another data? (Y/n)";
			cin >> choice;
		}
	while(choice != 'n');
	list.display();
	// Deletion...
	do
		{
			cout << "\nInput the data to delete: ";
			cin >> data;
			list.del_item(data);
			cout << "Will you delete another data? (Y/n)";
			cin >> choice;
		}
	while(choice != 'n');
	list.display();
	getche();
	return 0;
}
